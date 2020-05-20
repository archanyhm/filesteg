#ifndef CMDPARSE_H
#define CMDPARSE_H

#include <iostream>
#include <string>
#include <vector>

namespace cmdparse {
struct arg {
  std::string name;
  std::string description;

  bool required = false;
  bool takes_parameter = true;

  char shortOption = 0;
  std::string longOption = "";
};

struct arg_match {
  std::string option_name = "";
  std::string caught_argument = "";
  size_t option_id = 0;
  bool valid = false;
};

struct argv_meta {
  std::string value = "";
  bool identified = false;
};

std::vector<cmdparse::arg_match>
parse(const int &argc, char *const argv[],
      const std::vector<cmdparse::arg> &possible_args);
} // namespace cmdparse

#endif // CMDPARSE_H
