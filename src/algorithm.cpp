#include "algorithm.hpp"

#include <cstring>
#include <cstddef>

#include "random.hpp"
#include "reader.hpp"
#include "util.hpp"

namespace core {

Algorithm::Algorithm() : entry(), A(nullptr), B(nullptr), C(nullptr) {

}

Algorithm::~Algorithm() {

}

void Algorithm::Init(const reader::Entry& entry) {
  int N = entry.vertices;
  this->entry = entry;
  A = new float[N * N];
  B = new float[N * N];
  C = new float[N * N];
  memset(A, 0x0, N * N * sizeof(float));
  memset(B, 0x0, N * N * sizeof(float));
  memset(C, 0x0, N * N * sizeof(float));
  core::Random random;
  random.generate(N * N, A);
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
