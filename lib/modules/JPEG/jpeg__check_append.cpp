#include "jpeg__check_append.hpp"
#include "fileobj.hpp"

#include <iostream>
#include <array>

namespace filesteg { namespace JPEG {

int check_for_appended_data(FileObj &fob) {
  std::lock_guard<std::mutex> guard(fob.t_filestream_mutex);

  char read_buffer[64];
  bool skipflag = false;
  std::streamoff EndOfImage_bytes_offset = 0;
  std::streamoff read_bytes = 0;

  if (fob.t_filestream.is_open()) {
    fob.t_filestream.close();
  }

  fob.t_filestream.open(fob.t_file_path.c_str(), std::ios::in | std::ios::binary);

  if(!fob.t_filestream)
    return FUNC_INVALID_FILE;

  /* Read until we encounter 0xFF. Then, check if the next byte is 0xD9 */
  while (fob.t_filestream) {
    fob.t_filestream.read(read_buffer, 64);

    if(!skipflag == true) {
      for(size_t i = 0; i<=sizeof(read_buffer)-1; ++i)
      {
        ++read_bytes;

        std::cout << i << std::endl;

        if(read_buffer[i] == EOI[0])
        {
          std::cout << "0xFF byte found at offset " << read_bytes - 1 << std::endl;

          if(i+1 < sizeof(read_buffer) - 1 && read_buffer[i+1] == EOI[1])
          {
            std::cout << "0xFF 0xD9 bytes found at offset " << read_bytes - 1 << std::endl;
            EndOfImage_bytes_offset = read_bytes - 1;
            ++read_bytes;
            skipflag = true;
            break;
          } else if (i+1 <= sizeof(read_buffer) -1) {
            char temp_buffer = 0;
            fob.t_filestream.get(temp_buffer);
            if(fob.t_filestream.eofbit) {
              break;
            }

            if(temp_buffer == EOI[1]) {
              std::cout << "0xFF 0xD9 bytes found at offset " << read_bytes - 1 << std::endl;
              EndOfImage_bytes_offset = read_bytes - 1;
              ++read_bytes;
              skipflag = true;
              break;
            }
          }
        }
      }
    }
  }

  if (read_bytes >= fob.sb_in.st_size) {
    std::cout << "EOF reached. No appended data found." << std::endl;
    fob.t_filestream.close();
    return FUNC_NO_MATCH;
  } else {
    std::cout << fob.sb_in.st_size - read_bytes
              << " bytes exceeding the EOI found." << std::endl;
    return FUNC_SUCCESS;
  }
}}}

