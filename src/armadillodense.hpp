#ifndef ARMADILLO_DENSE_HPP_
#define ARMADILLO_DENSE_HPP_

#include <armadillo>

#include "algorithm.hpp"

namespace core {

class ArmadilloDense : public Algorithm {
 public:
  ArmadilloDense() : Algorithm() {};

  ~ArmadilloDense() = default;

  virtual void Init(const reader::Entry& entry);

  virtual void Compute();

  const std::string name() const { return "armad-dense "; }

 private:
  arma::Mat<float> a;
  arma::Mat<float> b;
  arma::Mat<float> c;
};

};

#endif  // ARMADILLO_DENSE_HPP_
