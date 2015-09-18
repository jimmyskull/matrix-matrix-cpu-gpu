#include "cusparse.hpp"

#include <cstdio>
#include <cstdlib>

#include <cusparse.h>

#include "cutil.hpp"

namespace core {

struct COOSparseMatrixHost {
  COOSparseMatrixHost();

  ~COOSparseMatrixHost();

  // Allocate space according to |nnz|
  void Allocate();

  float* values;
  int* row_indices;
  int* column_indices;
  int nnz;
  int rows;
};

struct COOSparseMatrixDevice {
  COOSparseMatrixDevice();

  ~COOSparseMatrixDevice();

  void CopyFrom(const COOSparseMatrixHost& host, cusparseHandle_t handle);

  cusparseMatDescr_t mat;
  float* values;
  int* row_indices;
  int* column_indices;
  int* csr_row_ptr;
  int nnz;
  int rows;

private:
  void Allocate();
};

template<typename SpMatType>
struct SparseDataStructures {
  SpMatType A;
  SpMatType B;
  SpMatType C;
};

struct CUSPARSEInternals {
  cusparseHandle_t handle;
  SparseDataStructures<COOSparseMatrixHost> host;
  SparseDataStructures<COOSparseMatrixDevice> dev;
};

COOSparseMatrixHost::COOSparseMatrixHost() {
  values = NULL;
  row_indices = NULL;
  column_indices = NULL;
  nnz = 0;
  rows = 0;
}

COOSparseMatrixHost::~COOSparseMatrixHost() {
  if (values) {
    delete[] values;
    values = NULL;
  }
  if (row_indices) {
    delete[] row_indices;
    row_indices = NULL;
  }
  if (column_indices) {
    delete[] column_indices;
    column_indices = NULL;
  }
}

void COOSparseMatrixHost::Allocate() {
  if (nnz == 0) {
    fprintf(stderr, "COOSparseMatrixHost Warning: nnz is zero.\n");
    return;
  }
  values = new float[nnz];
  row_indices = new int[nnz];
  column_indices = new int[nnz];
}

COOSparseMatrixDevice::COOSparseMatrixDevice() {
  cusparseStatus_t stat;

  stat = cusparseCreateMatDescr(&mat);
  cusparseSafeCall(stat);

  stat = cusparseSetMatType(mat, CUSPARSE_MATRIX_TYPE_GENERAL);
  cusparseSafeCall(stat);

  stat = cusparseSetMatIndexBase(mat, CUSPARSE_INDEX_BASE_ZERO);
  cusparseSafeCall(stat);

  row_indices = NULL;
  column_indices = NULL;
  values = NULL;
  csr_row_ptr = NULL;
  nnz = 0;
  rows = 0;
}

COOSparseMatrixDevice::~COOSparseMatrixDevice() {
  cudaError_t custat;
  cusparseStatus_t stat;

  if (values != NULL) {
    custat = cudaFree(values);
    cudaSafeCall(custat);
    values = NULL;
  }

  if (row_indices != NULL) {
    custat = cudaFree(row_indices);
    cudaSafeCall(custat);
    row_indices = NULL;
  }

  if (column_indices != NULL) {
    custat = cudaFree(column_indices);
    cudaSafeCall(custat);
    column_indices = NULL;
  }

  if (csr_row_ptr != NULL) {
    custat = cudaFree(csr_row_ptr);
    cudaSafeCall(custat);
    csr_row_ptr = NULL;
  }

  stat = cusparseDestroyMatDescr(mat);
  cusparseSafeCall(stat);
}

void COOSparseMatrixDevice::Allocate() {
  if (nnz == 0) {
    fprintf(stderr, "COOSparseMatrixDevice Warning: nnz is zero.\n");
    return;
  }
  cudaError_t status;

  status = cudaMalloc((void**)&values, nnz * sizeof(values[0]));
  cudaSafeCall(status);

  status = cudaMalloc((void**)&row_indices, nnz * sizeof(row_indices[0]));
  cudaSafeCall(status);

  status = cudaMalloc((void**)&column_indices, nnz * sizeof(column_indices[0]));
  cudaSafeCall(status);

  status = cudaMalloc((void**)&csr_row_ptr, (rows + 1) * sizeof(csr_row_ptr[0]));
  cudaSafeCall(status);
}

void COOSparseMatrixDevice::CopyFrom(const COOSparseMatrixHost& host,
  cusparseHandle_t handle) {
  cudaError_t stat;
  cusparseStatus_t status;

  rows = host.rows;
  nnz = host.nnz;
  Allocate();

  stat = cudaMemcpy(row_indices, host.row_indices,
    static_cast<std::size_t>(nnz * sizeof(host.row_indices[0])),
                         cudaMemcpyHostToDevice);
  cudaSafeCall(stat);

  stat = cudaMemcpy(column_indices, host.column_indices,
    static_cast<std::size_t>(nnz * sizeof(host.column_indices[0])),
                         cudaMemcpyHostToDevice);
  cudaSafeCall(stat);

  stat = cudaMemcpy(values, host.values,
    static_cast<std::size_t>(nnz * sizeof(host.values[0])),
                 cudaMemcpyHostToDevice);
  cudaSafeCall(stat);

  status = cusparseXcoo2csr(handle,
    row_indices, nnz, rows, csr_row_ptr, CUSPARSE_INDEX_BASE_ZERO);
  cusparseSafeCall(status);
}

CUSPARSE::CUSPARSE() : Algorithm() {
}

CUSPARSE::~CUSPARSE() {
}

void CUSPARSE::Init(const reader::Entry& entry) {
  Algorithm::Init(entry);
  internal = new CUSPARSEInternals;

  int N = static_cast<int>(entry.vertices);

  internal->host.A.rows = entry.vertices;
  internal->host.B.rows = entry.vertices;
  internal->host.C.rows = entry.vertices;

  internal->dev.A.rows = entry.vertices;
  internal->dev.B.rows = entry.vertices;
  internal->dev.C.rows = entry.vertices;

  internal->host.A.nnz = 0;
  internal->host.B.nnz = 0;
  internal->host.C.nnz = 0;

  internal->dev.A.nnz = 0;
  internal->dev.B.nnz = 0;
  internal->dev.C.nnz = 0;

  cusparseStatus_t stat;
  cudaError_t status;

  stat = cusparseCreate(&internal->handle);
  cusparseSafeCall(stat);

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (A[i * N + j] > 1e-10) {
        internal->host.A.nnz++;
      }
      if (B[i * N + j] > 1e-10) {
        internal->host.B.nnz++;
      }
      if (C[i * N + j] > 1e-10) {
        internal->host.C.nnz++;
      }
    }
  }

  // printf("host.C.nnz = %d\n", internal->host.C.nnz);

  internal->host.A.Allocate();
  internal->host.B.Allocate();
  // internal->host.C.Allocate();

  std::size_t ca = 0, cb = 0, cc = 0;  // Current index

  for (std::size_t i = 0; i < N; ++i) {
    for (std::size_t j = 0; j < N; ++j) {
      if (A[i * N + j] - 0.0 > 1e-10) {
        internal->host.A.row_indices[ca] = i;
        internal->host.A.column_indices[ca] = j;
        internal->host.A.values[ca] = A[i * N + j];
        ca++;
      }
      if (B[i * N + j] - 0.0 > 1e-10) {
        internal->host.B.row_indices[cb] = i;
        internal->host.B.column_indices[cb] = j;
        internal->host.B.values[cb] = B[i * N + j];
        cb++;
      }
      // if (C[i * N + j] - 0.0 > 1e-10) {
      //   internal->host.C.row_indices[cc] = i;
      //   internal->host.C.column_indices[cc] = j;
      //   internal->host.C.values[cc] = C[i * N + j];
      //   cc++;
      // }
    }
  }

  internal->dev.A.CopyFrom(internal->host.A, internal->handle);
  internal->dev.B.CopyFrom(internal->host.B, internal->handle);

  stat = cusparseSetPointerMode(internal->handle, CUSPARSE_POINTER_MODE_HOST);
  cusparseSafeCall(stat);

  status = cudaMalloc((void**)&internal->dev.C.csr_row_ptr,
    (internal->dev.C.rows + 1) * sizeof(internal->dev.C.csr_row_ptr[0]));
  cudaSafeCall(status);

  int baseC = 0, nnzC = 0;
  int *nnzTotalDevHostPtr = &nnzC;

  stat = cusparseXcsrgemmNnz(internal->handle,
                              CUSPARSE_OPERATION_NON_TRANSPOSE,
                              CUSPARSE_OPERATION_NON_TRANSPOSE,
                              N, N, N,
                              internal->dev.A.mat,
                              internal->dev.A.nnz,
                              internal->dev.A.csr_row_ptr,
                              internal->dev.A.column_indices,
                              internal->dev.B.mat,
                              internal->dev.B.nnz,
                              internal->dev.B.csr_row_ptr,
                              internal->dev.B.column_indices,
                              internal->dev.C.mat,
                              internal->dev.C.csr_row_ptr,
                              nnzTotalDevHostPtr);
  cusparseSafeCall(stat);

  if (nnzTotalDevHostPtr != NULL){
    nnzC = *nnzTotalDevHostPtr;
  } else {
    status = cudaMemcpy(&nnzC, internal->dev.C.csr_row_ptr+N, sizeof(int),
               cudaMemcpyDeviceToHost);
    cudaSafeCall(status);
    status = cudaMemcpy(&baseC, internal->dev.C.csr_row_ptr, sizeof(int),
               cudaMemcpyDeviceToHost);
    cudaSafeCall(status);
    nnzC -= baseC;
  }
  internal->host.C.nnz = nnzC;
  internal->dev.C.nnz = nnzC;

  status = cudaMalloc((void**)&internal->dev.C.values,
    internal->dev.C.nnz * sizeof(internal->dev.C.values[0]));
  cudaSafeCall(status);

  status = cudaMalloc((void**)&internal->dev.C.column_indices,
    internal->dev.C.nnz * sizeof(internal->dev.C.column_indices[0]));
  cudaSafeCall(status);

  // internal->dev.C.CopyFrom(internal->host.C, internal->handle);
}

void CUSPARSE::Finalize() {
  cusparseDestroy(internal->handle);
  delete internal;
}

void CUSPARSE::Compute() {
  int N = static_cast<int>(entry.vertices);
  cusparseStatus_t status;

  status = cusparseScsrgemm(internal->handle,
                    CUSPARSE_OPERATION_NON_TRANSPOSE,
                    CUSPARSE_OPERATION_NON_TRANSPOSE,
                    N, N, N,
                    internal->dev.A.mat,
                      internal->dev.A.nnz,
                      internal->dev.A.values,
                      internal->dev.A.csr_row_ptr,
                      internal->dev.A.column_indices,
                    internal->dev.B.mat,
                      internal->dev.B.nnz,
                      internal->dev.B.values,
                      internal->dev.B.csr_row_ptr,
                      internal->dev.B.column_indices,
                    internal->dev.C.mat,
                      internal->dev.C.values,
                      internal->dev.C.csr_row_ptr,
                      internal->dev.C.column_indices);
  cusparseSafeCall(status);
}

} // namespace core

