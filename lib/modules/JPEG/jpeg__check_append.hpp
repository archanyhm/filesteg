#ifndef JPEG__CHECK_APPEND_H
#define JPEG__CHECK_APPEND_H

#include "return_types.hpp"
#include "fileobj.hpp"

#include <fstream>
#include <mutex>

namespace filesteg { namespace JPEG {

int check_for_appended_data(FileObj &fob);

}}

#endif // JPEG__CHECK_APPEND_H
