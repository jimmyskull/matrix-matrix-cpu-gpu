#include "simple.hpp"

#include "reader.hpp"

namespace core {

void SimpleSqMult::Compute() {
  std::size_t N = static_cast<std::size_t>(entry.vertices);

  for(std::size_t i = 0; i < N; i++) {
    for(std::size_t j = 0; j < N; j++) {
      const double* a = A + i * N + j;
      const double* b = B + j * N;
      double* c = C + i * N;

      double* cMax = c + N;
      while(c < cMax) {
        *c++ += (*a) * (*b++);
      }
    }
  }
}

}  // namespace core
