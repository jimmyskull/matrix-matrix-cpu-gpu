#ifndef CUST_CPU_HPP_
#define CUST_CPU_HPP_

#include <string>

#include "algorithm.hpp"

namespace core {

class CustCPUSqMult : public Algorithm {
 public:
  CustCPUSqMult();

  ~CustCPUSqMult();

  virtual void Init(const reader::Entry& entry);

  virtual void Compute();

  const std::string name() const { return "cust-cpu    "; }

 private:
  struct CustCPUInternals* internal;
};

};

#endif  // CUST_CPU_HPP_

