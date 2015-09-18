#include "armadillosparse.hpp"

#include <cstddef>

#include <armadillo>

namespace core {

void ArmadilloSparse::Init(const reader::Entry& entry) {
  Algorithm::Init(entry);
  std::size_t N = static_cast<std::size_t>(entry.vertices);

  a.resize(N, N);
  b.resize(N, N);
  c.resize(N, N);
  for (std::size_t i = 0; i < N; ++i) {
    for (std::size_t j = 0; j < N; ++j) {
      if (A[i * N + j] > 1e-7)
        a(i, j) = A[i * N + j];
      if (B[i * N + j] > 1e-7)
        b(i, j) = B[i * N + j];
      if (C[i * N + j] > 1e-7)
        c(i, j) = C[i * N + j];
    }
  }
}

void ArmadilloSparse::Compute() {
  c = a * b;
}

} // namespace core
