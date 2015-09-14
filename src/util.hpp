#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <fstream>
#include <string>

namespace util {

void read_sqmatrix(std::ifstream& input, int dim, double* output);

void read_sqmatrix(std::string filename, int dim, double* output);

// Extract the path of |filename|.
std::string extract_path(const std::string& filename);

// Check whether |filename| exists or not.
bool exists(const std::string& filename);

// Ensure the path of |filename| exists.
bool ensure_path(const std::string& filename);

}  // namespace util

#endif  // UTIL_HPP_

