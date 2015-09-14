// Copyright © 2015, Paulo Urio.
#include "reader.hpp"

#include <cstddef>

#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

namespace reader {

Entry::Entry(const std::string& directory, std::ifstream &input) {
  input >> filename >> vertices >> probability >> density;
  filename.erase(remove(filename.begin(), filename.end(), '\"'),
                 filename.end());
  filename = directory + '/' + filename;
}

const std::string Entry::str() const {
  std::stringstream ss;
  ss << "Entry<filename='" << filename << "', ";
  ss << "probability=" << probability << ", ";
  ss << "density=" << density << ">";
  return ss.str();
}

FileList::FileList(const std::string filename) {
  std::string directory;
  std::ifstream file(filename);
  const std::size_t last_slash_idx = filename.rfind('/');

  if (std::string::npos != last_slash_idx) {
    directory = filename.substr(0, last_slash_idx);
  }
  read_list(directory, file);
  file.close();
}

void FileList::read_list(const std::string& directory, std::ifstream &input) {
  if (!input.is_open())
    return;

  list_.clear();
  while (!input.eof()) {
    Entry e(directory, input);
    if (!e.filename.empty())
      list_.push_back(e);
  }
}

} // namespace reader
