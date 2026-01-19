#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

std::vector<std::string> split_str(const std::string &s,
                                   const std::string &delimiter) {
  std::stringstream ss(s);
  std::istream_iterator<std::string> begin(ss);
  std::istream_iterator<std::string> end;
  std::vector<std::string> v(begin, end);
  std::copy(v.begin(), v.end(),
            std::ostream_iterator<std::string>(std::cout, delimiter.c_str()));
  return v;
}

bool is_directory(const std::string &path) {
  struct stat s;
  if (stat(path.c_str(), &s) == 0) {
    // S_ISDIR checks mode bit
    if (S_ISDIR(s.st_mode))
      return true;
  }
  return false;
}

int main(int argc, char *argv[]) {
  if (argc < 2 || std::string(argv[1]).empty()) {
    std::cerr << "usage: " << argv[0] << " <database>" << std::endl;
    return 1;
  }

  std::string path = argv[1];
  std::string itext;

  try {
    if (is_directory(path))
      throw std::runtime_error("path is a directory, not a file");
    if (access(path.c_str(), R_OK) != 0)
      throw std::runtime_error("path could not be read");

    std::ifstream ifile(argv[1]);

    if (!ifile.is_open())
      throw std::runtime_error("can't open the file");

    std::ostringstream oss;
    oss << ifile.rdbuf();
    itext = oss.str();
  } catch (const std::exception &e) {
    std::cerr << "error: could not read file: " << e.what()
              << std::endl;
    return 1;
  }

  std::vector<std::string> lines = split_str(itext, "\n");
  std::cerr << std::endl << lines[0] << std::endl;

  return 0;
}
