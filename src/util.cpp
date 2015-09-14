#include "util.hpp"

#include <sys/stat.h>

#include <fstream>
#include <stdexcept>
#include <string>

#include "range.h"

namespace util {

void read_sqmatrix(std::ifstream& input, int dim, double* output) {
  using util::lang::range;

  if (!input.is_open()) {
    throw std::runtime_error("Could not open file");
  }

  for (int i : range(0, dim)) {
    char c;
    for (int j : range(0, dim)) {
      input >> c;
      output[i * dim + j] = c == '1'? 1.0: 0.0;
    }
  }
}

void read_sqmatrix(std::string filename, int dim, double* output) {
  std::ifstream file(filename);
  read_sqmatrix(file, dim, output);
  file.close();
}

static const char kDirectorySeparator = '/';

std::string extract_path(const std::string& filename) {
  const size_t last_slash_idx = filename.rfind(kDirectorySeparator);
  std::string directory;

  if (std::string::npos != last_slash_idx) {
    directory = filename.substr(0, last_slash_idx);
  }
  return directory;
}

bool exists(const std::string& filename) {
  struct stat buffer;

  return (stat(filename.c_str(), &buffer) == 0);
}

bool ensure_path(const std::string& filename) {
  std::string directory = extract_path(filename);
  int ret = 1;

  if (directory.size() > 0 && !exists(directory)) {
    ret = mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  }
  return ret == 0;
}

}  // namespace util
