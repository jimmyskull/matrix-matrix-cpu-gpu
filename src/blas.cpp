#include "blas.hpp"

#include <cblas.h>

namespace core {

void BLASSqMult::Compute() {
  blasint N = static_cast<blasint>(entry.vertices);

  // C = alpha * A x B + beta * C
  cblas_sgemm(CblasRowMajor,
              CblasNoTrans,
              CblasTrans,
              N, // m
              N, // n
              N, // k
              1, // alpha
              A, // A: m rows by k columns
              N, // k
              B, // B: k rows by n columns
              N, //
              0, // beta
              C, // C: m rows by n columns
              N);
}

}  // namespace core
