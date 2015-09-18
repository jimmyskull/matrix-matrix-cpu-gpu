#ifndef BOOST_HPP_
#define BOOST_HPP_

#include <boost/numeric/ublas/matrix.hpp>

#include "algorithm.hpp"

namespace core {

class Boost : public Algorithm {
 public:
  Boost() : Algorithm() {};

  ~Boost() = default;

  virtual void Init(const reader::Entry& entry);

  virtual void Compute();

  const std::string name() const { return "boost       "; }

 private:
  boost::numeric::ublas::matrix<float> a;
  boost::numeric::ublas::matrix<float> b;
  boost::numeric::ublas::matrix<float> c;
};

};

#endif  // BOOST_HPP_
