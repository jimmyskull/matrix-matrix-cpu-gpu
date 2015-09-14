// Copyright © 2015, Paulo Urio.
#ifndef READER_H_
#define READER_H_

#include <cstddef>

#include <string>
#include <vector>

namespace reader {

struct Entry {
  Entry() = default;

  Entry(const std::string& directory, std::ifstream &input);

  ~Entry() = default;

  const std::string str() const;

  std::string filename;
  int vertices;
  double probability;
  double density;
};

class FileList {
public:
  typedef std::vector<Entry>::const_iterator const_iterator;

  FileList(const std::string filename);

  FileList() = default;

  ~FileList() = default;

  void read_list(const std::string& directory, std::ifstream &input);

  const_iterator begin() const { return list_.cbegin(); }

  const_iterator end() const { return list_.cend(); }

  std::size_t count() const { return list_.size(); }

private:
  std::vector<Entry> list_;
};

} // namespace reader

#endif // READER_H_
