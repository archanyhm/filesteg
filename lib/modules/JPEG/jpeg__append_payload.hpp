#ifndef JPEG__APPEND_PAYLOAD_H
#define JPEG__APPEND_PAYLOAD_H

#include "fileobj.hpp"
#include "jpeg__config.hpp"
#include "return_types.hpp"

namespace filesteg::JPEG {

int append_payload(FileObj &fob,
                   std::string payload,
                   bool copy_file = true,
                   std::string copy_file_path = "");

int append_payload_from_file(FileObj &fob,
                             std::string payload_file_path,
                             bool copy_file = true,
                             std::string copy_file_path = "",
                             bool swallow_payload_file = false);

} // namespace filesteg::JPEG

#endif // JPEG__APPEND_PAYLOAD_H
