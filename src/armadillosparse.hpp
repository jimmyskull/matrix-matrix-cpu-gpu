#ifndef ARMADILLO_SPARSE_HPP_
#define ARMADILLO_SPARSE_HPP_

#include <armadillo>

#include "algorithm.hpp"

namespace core {

class ArmadilloSparse : public Algorithm {
 public:
  ArmadilloSparse() : Algorithm() {};

  ~ArmadilloSparse() = default;

  virtual void Init(const reader::Entry& entry);

  virtual void Compute();

  const std::string name() const { return "armad-sparse"; }

 private:
  arma::SpMat<float> a;
  arma::SpMat<float> b;
  arma::SpMat<float> c;
};

};

#endif  // ARMADILLO_SPARSE_HPP_
