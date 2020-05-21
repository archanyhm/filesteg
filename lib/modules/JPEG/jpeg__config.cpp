#include "jpeg__config.hpp"

#include <vector>
#include <map>
#include <string>

namespace filesteg { namespace JPEG {

const char ident[] = {static_cast<char>(0xFF), static_cast<char>(0xD8), static_cast<char>(0xFF)};
const char EOI[]   = {static_cast<char>(0xFF), static_cast<char>(0xD9)};

}}
