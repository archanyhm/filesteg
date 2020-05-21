#ifndef JPEG__IDENTIFY_H
#define JPEG__IDENTIFY_H

#include "jpeg__config.hpp"
#include <array>

namespace filesteg { namespace JPEG {

int identify(std::array<char, 64> const &file_begin);

}}

#endif // JPEG__IDENTIFY_H
