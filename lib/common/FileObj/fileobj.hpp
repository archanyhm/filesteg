#ifndef FILEOBJ_HPP
#define FILEOBJ_HPP

#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <mutex>

/*!
 * \enum file_type
 * \brief The file_type enum
 */
enum file_type { JPEG };

class FileObj {
public:
  std::string t_file_path;
  std::mutex t_filestream_mutex;
  std::fstream t_filestream;
  file_type t_file_type;
  bool valid_file;
  struct stat sb_in;


  FileObj(std::string file_path);
  FileObj();
  ~FileObj();

  bool is_verbose = false;

  bool set_file(std::string file_path);

  bool check_for_hidden_data();
  bool extract(bool overwrite = true, std::string outfile = "");

};

#endif // FILEOBJ_HPP
