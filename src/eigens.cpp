#include "eigens.hpp"

#include <functional>
#include <Eigen/Sparse>

namespace core {

void EigenSparse::Init(const reader::Entry& entry) {
  Algorithm::Init(entry);
  std::size_t N = static_cast<std::size_t>(entry.vertices);

  a.resize(N, N);
  b.resize(N, N);
  c.resize(N, N);
  a.setZero();
  b.setZero();
  c.setZero();
  for (std::size_t i = 0; i < N; ++i) {
    for (std::size_t j = 0; j < N; ++j) {
      if (A[i * N + j])
        a.insert(i, j) = A[i * N + j];
      if (B[i * N + j])
        b.insert(i, j) = B[i * N + j];
      if (C[i * N + j])
        c.insert(i, j) = C[i * N + j];
    }
  }
}

void EigenSparse::Compute() {
  c = a * b;
}

}  // namespace core
