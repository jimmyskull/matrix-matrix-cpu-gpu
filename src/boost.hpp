#ifndef BOOST_HPP_
#define BOOST_HPP_

#include <boost/numeric/ublas/matrix.hpp>

#include "algorithm.hpp"

namespace core {

class BoostSqMult : public Algorithm {
 public:
  BoostSqMult() : Algorithm() {};

  ~BoostSqMult() = default;

  virtual void Init(const reader::Entry& entry);

  virtual void Compute();

  const std::string name() const { return "boost       "; }

 private:
  boost::numeric::ublas::matrix<double> a;
  boost::numeric::ublas::matrix<double> b;
  boost::numeric::ublas::matrix<double> c;
};

};

#endif  // BOOST_HPP_
