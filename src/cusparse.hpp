#ifndef CUSPARSE_HPP_
#define CUSPARSE_HPP_

#include <string>

#include "algorithm.hpp"

namespace core {

class CUSPARSE : public Algorithm {
 public:
  CUSPARSE();

  ~CUSPARSE();

  virtual void Init(const reader::Entry& entry);

  virtual void Compute();

  virtual void Finalize();

  const std::string name() const { return "cusparse     "; }

 private:
  struct CUSPARSEInternals* internal;
};

};

#endif  // CUSPARSE_HPP_

