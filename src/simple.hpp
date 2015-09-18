#ifndef SIMPLE_HPP_
#define SIMPLE_HPP_

#include "algorithm.hpp"

namespace core {

class Simple : public Algorithm {
 public:
  Simple() : Algorithm() {};

  ~Simple() = default;

  virtual void Compute();

  const std::string name() const { return "simple      "; }
};

};

#endif  // SIMPLE_HPP_
