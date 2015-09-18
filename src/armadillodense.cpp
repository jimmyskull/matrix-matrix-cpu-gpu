#include "armadillodense.hpp"

#include <cstddef>

#include <armadillo>

namespace core {

void ArmadilloDense::Init(const reader::Entry& entry) {
  Algorithm::Init(entry);
  std::size_t N = static_cast<std::size_t>(entry.vertices);

  a.resize(N, N);
  b.resize(N, N);
  c.resize(N, N);
  for (std::size_t i = 0; i < N; ++i) {
    for (std::size_t j = 0; j < N; ++j) {
      a(i, j) = A[i * N + j];
      b(i, j) = B[i * N + j];
      c(i, j) = C[i * N + j];
    }
  }
}

void ArmadilloDense::Compute() {
  c = a * b;
}

} // namespace core
