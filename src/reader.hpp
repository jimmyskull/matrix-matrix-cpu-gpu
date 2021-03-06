// Copyright © 2015, Paulo Urio.
#ifndef READER_H_
#define READER_H_

#include <cstddef>

#include <string>
#include <vector>

namespace reader {

struct Entry {
  Entry();

  Entry(const std::string& directory, std::ifstream &input);

  ~Entry();

  const std::string str() const;

  std::string filename;
  int vertices;
  float probability;
  float density;
};

class FileList {
public:
  typedef std::vector<Entry>::const_iterator const_iterator;

  FileList(const std::string filename);

  FileList();

  ~FileList();

  void read_list(const std::string& directory, std::ifstream &input);

  const_iterator begin() const { return list_.begin(); }

  const_iterator end() const { return list_.end(); }

  std::size_t count() const { return list_.size(); }

private:
  std::vector<Entry> list_;
};

} // namespace reader

#endif // READER_H_
