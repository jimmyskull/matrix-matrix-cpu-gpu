#include "cublas.hpp"

#include <cstdio>

#include <stdexcept>
#include <iostream>

#include <cublas_v2.h>

namespace core {

struct CUBLASGPUInternals {
  float* dev_a;
  float* dev_b;
  float* dev_c;
  cublasHandle_t handle;
};

CUBLAS::CUBLAS() : Algorithm() {
  internal = new CUBLASGPUInternals;
}

CUBLAS::~CUBLAS() {
  delete internal;
}

void CUBLAS::Init(const reader::Entry& entry) {
  Algorithm::Init(entry);
  std::size_t N = static_cast<std::size_t>(entry.vertices);
  std::size_t N2 = N * N;

  int status;

  status = cublasCreate(&internal->handle);

  if (status != CUBLAS_STATUS_SUCCESS) {
    fprintf(stderr, "!!!! CUBLAS initialization error\n");
  }

  /* Allocate device memory for the matrices */
  if (cudaMalloc((void **)&internal->dev_a, N2 * sizeof(internal->dev_a[0])) != cudaSuccess) {
      fprintf(stderr, "!!!! device memory allocation error (allocate A)\n");
  }

  if (cudaMalloc((void **)&internal->dev_b, N2 * sizeof(internal->dev_b[0])) != cudaSuccess) {
      fprintf(stderr, "!!!! device memory allocation error (allocate B)\n");
  }

  if (cudaMalloc((void **)&internal->dev_c, N2 * sizeof(internal->dev_c[0])) != cudaSuccess) {
    fprintf(stderr, "!!!! device memory allocation error (allocate C)\n");
  }

}

void CUBLAS::Finalize() {
  if (cudaFree(internal->dev_a) != cudaSuccess) {
      fprintf(stderr, "!!!! memory free error (A)\n");
  }

  if (cudaFree(internal->dev_b) != cudaSuccess) {
      fprintf(stderr, "!!!! memory free error (B)\n");
  }

  if (cudaFree(internal->dev_c) != cudaSuccess) {
      fprintf(stderr, "!!!! memory free error (C)\n");
  }

  cublasDestroy(internal->handle);
}

void CUBLAS::Compute() {
  std::size_t N = static_cast<std::size_t>(entry.vertices);
  std::size_t N2 = N * N;
  cublasStatus_t status;
  float alpha = 1.0f;
  float beta = 0.0f;

  status = cublasSetVector(N2, sizeof(A[0]), A, 1, internal->dev_a, 1);

  if (status != CUBLAS_STATUS_SUCCESS) {
    fprintf(stderr, "!!!! device access error (write A)\n");
  }

  status = cublasSetVector(N2, sizeof(B[0]), B, 1, internal->dev_b, 1);

  if (status != CUBLAS_STATUS_SUCCESS) {
      fprintf(stderr, "!!!! device access error (write B)\n");
  }

  status = cublasSetVector(N2, sizeof(C[0]), C, 1, internal->dev_c, 1);

  if (status != CUBLAS_STATUS_SUCCESS) {
      fprintf(stderr, "!!!! device access error (write C)\n");
  }

  status = cublasSgemm(internal->handle,
    CUBLAS_OP_N,
    CUBLAS_OP_N,
    1, N, N,
    &alpha, internal->dev_a, 1, internal->dev_b,
    N, &beta, internal->dev_c, 1);

  if (status != CUBLAS_STATUS_SUCCESS) {
      fprintf(stderr, "!!!! kernel execution error.\n");
  }
}

} // namespace core

