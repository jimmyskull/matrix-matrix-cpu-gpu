// Copyright © 2015, Paulo Urio.
#ifndef METHOD_H_
#define METHOD_H_

#include <cstdlib>

#include <functional>
#include <map>
#include <string>
#include <iterator>
#include <iostream>

namespace core {

typedef std::function<void()> MethodFunction;

class Methods {
 public:
  // Associates |name| to a |function|.
  void add(std::string name, MethodFunction function) {
    list_[name] = function;
  }

  // Call the function associated to |name|.
  void call(std::string name) const {
    if (exists(name)) {
      list_.find(name)->second();
    } else {
      std::cerr << "Error: " << name << " method does not exist.\n";
      std::exit(1);
    }
  }

 private:
  // Check whether |name| is registered or not.
  bool exists(std::string name) const {
    auto ret = list_.find(name);
    return ret != std::end(list_);
  }

  std::map<std::string, MethodFunction> list_;
};

}  // namespace ip

#endif  // METHOD_H_
