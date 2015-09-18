#ifndef EIGEND_HPP_
#define EIGEND_HPP_

#include <functional>
#include <Eigen/Dense>

#include "algorithm.hpp"

namespace core {

class EigenDense : public Algorithm {
 public:
  EigenDense() : Algorithm() {};

  ~EigenDense() = default;

  virtual void Init(const reader::Entry& entry);

  virtual void Compute();

  const std::string name() const { return "eigen-dense "; }

 private:
  Eigen::MatrixXd a;
  Eigen::MatrixXd b;
  Eigen::MatrixXd c;
};

};

#endif  // EIGEND_HPP_
