#ifndef BLAS_HPP_
#define BLAS_HPP_

#include "algorithm.hpp"

namespace core {

class BLASSqMult : public Algorithm {
 public:
  BLASSqMult() : Algorithm() {};

  ~BLASSqMult() = default;

  virtual void Compute();

  const std::string name() const { return "blas        "; }
};

};

#endif  // BLAS_HPP_
