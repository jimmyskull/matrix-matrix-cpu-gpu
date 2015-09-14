#ifndef CUST_GPU_HPP_
#define CUST_GPU_HPP_

#include <string>

#include "algorithm.hpp"

namespace core {

class CustGPUSqMult : public Algorithm {
 public:
  CustGPUSqMult();

  ~CustGPUSqMult();

  virtual void Init(const reader::Entry& entry);

  virtual void Compute();

  const std::string name() const { return "cust-gpu    "; }

 private:
  struct CustGPUInternals* internal;
};

};

#endif  // CUST_GPU_HPP_

