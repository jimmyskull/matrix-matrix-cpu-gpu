#ifndef EIGENS_HPP_
#define EIGENS_HPP_

#include <functional>
#include <Eigen/Sparse>

#include "algorithm.hpp"

namespace core {

class EigenSparseSqMult : public Algorithm {
 public:
  EigenSparseSqMult() : Algorithm() {};

  ~EigenSparseSqMult() = default;

  virtual void Init(const reader::Entry& entry);

  virtual void Compute();

  const std::string name() const { return "eigen-sparse"; }

 private:
  Eigen::SparseMatrix<float, 1, int> a;
  Eigen::SparseMatrix<float, 1, int> b;
  Eigen::SparseMatrix<float, 1, int> c;
};

};

#endif  // EIGENS_HPP_
