#include "simple.hpp"

#include "reader.hpp"

namespace core {

void SimpleSqMult::Compute() {
  std::size_t N = static_cast<std::size_t>(entry.vertices);

  for(std::size_t i = 0; i < N; i++) {
    for(std::size_t j = 0; j < N; j++) {
      const float* a = A + i * N + j;
      const float* b = B + j * N;
      float* c = C + i * N;

      float* cMax = c + N;
      while(c < cMax) {
        *c++ += (*a) * (*b++);
      }
    }
  }
}

}  // namespace core
