#include "jpeg__identify.hpp"
#include <iostream>


namespace filesteg { namespace JPEG {

int identify(std::array<char, 64> const &file_begin) {
  if(file_begin[0] == ident[0] && file_begin[1] == ident[1] && file_begin[2] == ident[2])
  {
    std::cout << "File appears to be a JPEG" << std::endl;
  }

  return 0;
}}}
