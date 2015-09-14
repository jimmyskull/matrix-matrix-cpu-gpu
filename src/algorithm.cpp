#include "algorithm.hpp"

#include <cstring>
#include <cstddef>

#include "random.hpp"
#include "reader.hpp"
#include "util.hpp"

namespace core {

Algorithm::Algorithm() : entry(), A(nullptr), B(nullptr), C(nullptr) {

}

void Algorithm::Init(const reader::Entry& entry) {
  int N = entry.vertices;
  this->entry = entry;
  A = new double[N * N];
  B = new double[N * N];
  C = new double[N * N];
  memset(A, 0x0, N * N * sizeof(double));
  memset(B, 0x0, N * N * sizeof(double));
  memset(C, 0x0, N * N * sizeof(double));
  core::Random random;
  random.generate(N, A);
  util::read_sqmatrix(entry.filename, N, B);
}

void Algorithm::Finalize() {
  delete[] A;
  delete[] B;
  delete[] C;
  A = nullptr;
  B = nullptr;
  C = nullptr;
}

}  // namespace core
