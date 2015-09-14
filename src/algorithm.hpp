
#ifndef ALGORITHM_HPP_
#define ALGORITHM_HPP_

#include <string>

#include "reader.hpp"

namespace core {

class Algorithm {
 public:
  Algorithm();

  virtual ~Algorithm();

  virtual void Init(const reader::Entry& entry);

  virtual void Compute() = 0;

  virtual void Finalize();

  virtual const std::string name() const = 0;

 protected:
  reader::Entry entry;

  double* A;  // First
  double* B;  // Second
  double* C;  // Result
};

}  // namespace core

#endif  // ALGORITHM_HPP_
