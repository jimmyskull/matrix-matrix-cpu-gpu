#include "cust-cpu.hpp"

#include <cusp/array2d.h>
#include <cusp/multiply.h>

namespace core {

struct CustCPUInternals {
   cusp::array2d<float, cusp::host_memory> a;
   cusp::array2d<float, cusp::host_memory> b;
   cusp::array2d<float, cusp::host_memory> c;
};

CustCPU::CustCPU() : Algorithm() {
  internal = new CustCPUInternals;
}

CustCPU::~CustCPU() {
  delete internal;
}

void CustCPU::Init(const reader::Entry& entry) {
  Algorithm::Init(entry);
  std::size_t N = static_cast<std::size_t>(entry.vertices);

  internal->a.resize(N, N);
  internal->b.resize(N, N);
  internal->c.resize(N, N);

  for (std::size_t i = 0; i < N; ++i) {
    for (std::size_t j = 0; j < N; ++j) {
      internal->a(i, j) = A[i * N + j];
      internal->b(i, j) = B[i * N + j];
      internal->c(i, j) = C[i * N + j];
    }
  }
}

void CustCPU::Compute() {
  cusp::multiply(internal->a, internal->b, internal->c);
}

} // namespace core

