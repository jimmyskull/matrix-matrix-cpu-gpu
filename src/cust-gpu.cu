#include "cust-gpu.hpp"

#include <stdexcept>
#include <iostream>

#include <cusp/coo_matrix.h>
#include <cusp/multiply.h>

namespace core {

struct CustGPUInternals {
   cusp::coo_matrix<std::size_t, double, cusp::host_memory> host_a;
   cusp::coo_matrix<std::size_t, double, cusp::host_memory> host_b;
   cusp::coo_matrix<std::size_t, double, cusp::host_memory> host_c;

   // cusp::coo_matrix<size_t, double, cusp::device_memory> dev_a;
   // cusp::coo_matrix<size_t, double, cusp::device_memory> dev_b;
   // cusp::coo_matrix<size_t, double, cusp::device_memory> dev_c;
};

CustGPUSqMult::CustGPUSqMult() : Algorithm() {
  internal = new CustGPUInternals;
}

CustGPUSqMult::~CustGPUSqMult() {
  delete internal;
}

void CustGPUSqMult::Init(const reader::Entry& entry) {
  Algorithm::Init(entry);
  // std::size_t N = static_cast<std::size_t>(entry.vertices);

  // std::size_t na = 0, nb = 0, nc = 0;  // Number of entries

  // for (std::size_t i = 0; i < N; ++i) {
  //   for (std::size_t j = 0; j < N; ++j) {
  //     if (A[i * N + j] - 0.0 > 1e-10) {
  //       na++;
  //     }
  //     if (B[i * N + j] - 0.0 > 1e-10) {
  //       nb++;
  //     }
  //     if (C[i * N + j] - 0.0 > 1e-10) {
  //       nc++;
  //     }
  //   }
  // }

  // internal->host_a.resize(N, N, na);
  // internal->host_b.resize(N, N, nb);
  // internal->host_c.resize(N, N, N * N);

  // // internal->dev_a.resize(N, N, na);
  // // internal->dev_b.resize(N, N, nb);
  // // internal->dev_c.resize(N, N, nc);

  // std::size_t ca = 0, cb = 0, cc = 0;  // Current index

  // for (std::size_t i = 0; i < N; ++i) {
  //   for (std::size_t j = 0; j < N; ++j) {
  //     if (A[i * N + j] - 0.0 > 1e-10) {
  //       internal->host_a.row_indices[ca] = i;
  //       internal->host_a.column_indices[ca] = j;
  //       internal->host_a.values[ca] = A[i * N + j];
  //       ca++;
  //     }
  //     if (B[i * N + j] - 0.0 > 1e-10) {
  //       internal->host_a.row_indices[cb] = i;
  //       internal->host_a.column_indices[cb] = j;
  //       internal->host_a.values[cb] = B[i * N + j];
  //       cb++;
  //     }
  //     if (C[i * N + j] - 0.0 > 1e-10) {
  //       internal->host_a.row_indices[cc] = i;
  //       internal->host_a.column_indices[cc] = j;
  //       internal->host_a.values[cc] = C[i * N + j];
  //       cc++;
  //     }
  //   }
  // }

  // if (na != ca) {
  //   std::cerr << na << " != " << ca << "\n";
  //   throw std::runtime_error("Invalid COO fill (host_a)");
  // }


  // if (!cusp::is_valid_matrix(internal->host_a, std::cerr))
  //   throw std::runtime_error("Invalid COO (host_a)");

  // if (!cusp::is_valid_matrix(internal->host_b, std::cerr))
  //   throw std::runtime_error("Invalid COO (host_b)");

  // if (!cusp::is_valid_matrix(internal->host_c, std::cerr))
  //   throw std::runtime_error("Invalid COO (host_c)");

  // internal->dev_a = internal->host_a;
  // internal->dev_b = internal->host_b;
  // internal->dev_c = internal->host_c;
}

void CustGPUSqMult::Compute() {
  int N = static_cast<int>(entry.vertices);

  int na = 0, nb = 0, nc = 0;  // Number of entries

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (A[i * N + j] - 0.0 > 1e-10) {
        na++;
      }
      if (B[i * N + j] - 0.0 > 1e-10) {
        nb++;
      }
      if (C[i * N + j] - 0.0 > 1e-10) {
        nc++;
      }
    }
  }

   cusp::coo_matrix<int, float, cusp::host_memory> host_a(N, N, na);
   cusp::coo_matrix<int, float, cusp::host_memory> host_b(N, N, nb);
   cusp::coo_matrix<int, float, cusp::host_memory> host_c(N, N, N * N);

  // internal->dev_a.resize(N, N, na);
  // internal->dev_b.resize(N, N, nb);
  // internal->dev_c.resize(N, N, nc);

  int ca = 0, cb = 0, cc = 0;  // Current index

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (A[i * N + j] - 0.0 > 1e-10) {
        host_a.row_indices[ca] = i;
        host_a.column_indices[ca] = j;
        host_a.values[ca] = static_cast<float>(A[i * N + j]);
        ca++;
      }
      if (B[i * N + j] - 0.0 > 1e-10) {
        host_a.row_indices[cb] = i;
        host_a.column_indices[cb] = j;
        host_a.values[cb] = static_cast<float>(B[i * N + j]);
        cb++;
      }
      if (C[i * N + j] - 0.0 > 1e-10) {
        host_a.row_indices[cc] = i;
        host_a.column_indices[cc] = j;
        host_a.values[cc] = static_cast<float>(C[i * N + j]);
        cc++;
      }
    }
  }

  if (na != ca) {
    std::cerr << na << " != " << ca << "\n";
    throw std::runtime_error("Invalid COO fill (host_a)");
  }


  if (!cusp::is_valid_matrix(host_a, std::cerr))
    throw std::runtime_error("Invalid COO (host_a)");

  if (!cusp::is_valid_matrix(host_b, std::cerr))
    throw std::runtime_error("Invalid COO (host_b)");

  if (!cusp::is_valid_matrix(host_c, std::cerr))
    throw std::runtime_error("Invalid COO (host_c)");

   cusp::coo_matrix<int, float, cusp::device_memory> dev_a(internal->host_a);
   cusp::coo_matrix<int, float, cusp::device_memory> dev_b(internal->host_b);
   cusp::coo_matrix<int, float, cusp::device_memory> dev_c(internal->host_c);

  cusp::multiply(dev_a, dev_b, dev_c);
 // cusp::multiply(internal->dev_a, internal->dev_b, internal->dev_c);
}

} // namespace core

