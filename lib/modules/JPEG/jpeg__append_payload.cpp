#include "jpeg__append_payload.hpp"
#include <fstream>

namespace filesteg::JPEG {

int append_payload(FileObj &fob, std::string payload, bool copy_file, std::string copy_file_path) {
  std::lock_guard<std::mutex> guard(fob.t_filestream_mutex);

  if(fob.t_filestream.is_open()) {
    fob.t_filestream.close();
  }

  if(copy_file) {
    fob.t_filestream.open(fob.t_file_path, std::ios::in | std::ios::binary);
    std::ofstream copy_filestream(copy_file_path, std::ios::binary);

    if(!copy_filestream || !fob.t_filestream)
      return -1; // Unexpected error

    copy_filestream << fob.t_filestream.rdbuf();
    copy_filestream.write(payload.c_str(), payload.size());

    return 1;
  } else {
    fob.t_filestream.open(fob.t_file_path, std::ios::out | std::ios::binary | std::ios::app);

    if(!fob.t_filestream)
      return -1; // Unexpected error

    fob.t_filestream.write(payload.c_str(), payload.size());

    return 1;
  }

  return 0;
}

int append_payload_from_file(FileObj &fob, std::string payload_file_path, bool copy_file, std::string copy_file_path, bool swallow_payload_file) {
  std::lock_guard<std::mutex> guard(fob.t_filestream_mutex);

  if(fob.t_filestream.is_open()) {
    fob.t_filestream.close();
  }

  if(copy_file) {
    fob.t_filestream.open(fob.t_file_path, std::ios::in | std::ios::binary);
    std::ofstream copy_filestream(copy_file_path, std::ios::binary);
    std::ifstream payload_filestream(payload_file_path, std::ios::binary);


    if(!copy_filestream || !fob.t_filestream || !payload_filestream)
      return -1; // Unexpected error

    copy_filestream << fob.t_filestream.rdbuf() << payload_filestream.rdbuf();

    fob.t_filestream.close();
    copy_filestream.close();
    payload_filestream.close();

    if(swallow_payload_file) {
      std::remove(payload_file_path.c_str());
    }

    return 1;
  }

  return 0;
}

}
