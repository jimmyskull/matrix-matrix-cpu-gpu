#ifndef BLAS_HPP_
#define BLAS_HPP_

#include "algorithm.hpp"

namespace core {

class BLAS : public Algorithm {
 public:
  BLAS() : Algorithm() {};

  ~BLAS() = default;

  virtual void Compute();

  const std::string name() const { return "blas        "; }
};

};

#endif  // BLAS_HPP_
