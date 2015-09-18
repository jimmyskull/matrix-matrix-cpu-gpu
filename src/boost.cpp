#include "boost.hpp"

#include <cstddef>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/operation.hpp>

namespace core {

void Boost::Init(const reader::Entry& entry) {
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

void Boost::Compute() {
  boost::numeric::ublas::axpy_prod(a, b, c);
}

} // namespace core
