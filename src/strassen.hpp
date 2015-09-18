#ifndef STRASSEN_HPP_
#define STRASSEN_HPP_

#include "algorithm.hpp"

namespace core {

class Strassen : public Algorithm {
 public:
  Strassen() : Algorithm() {};

  ~Strassen() = default;

  virtual void Compute();

  const std::string name() const { return "strassen    "; }
};

};

#endif  // STRASSEN_HPP_
