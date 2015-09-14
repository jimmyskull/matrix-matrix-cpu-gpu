#ifndef STRASSEN_HPP_
#define STRASSEN_HPP_

#include "algorithm.hpp"

namespace core {

class StrassenSqMult : public Algorithm {
 public:
  StrassenSqMult() : Algorithm() {};

  ~StrassenSqMult() = default;

  virtual void Compute();

  const std::string name() const { return "strassen    "; }
};

};

#endif  // STRASSEN_HPP_
