#ifndef CUBLAS_HPP_
#define CUBLAS_HPP_

#include <string>

#include "algorithm.hpp"

namespace core {

class CUBLAS : public Algorithm {
 public:
  CUBLAS();

  ~CUBLAS();

  virtual void Init(const reader::Entry& entry);

  virtual void Compute();

  virtual void Finalize();

  const std::string name() const { return "cublas      "; }

 private:
  struct CUBLASGPUInternals* internal;
};

};

#endif  // CUBLAS_HPP_

