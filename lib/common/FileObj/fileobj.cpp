#include "fileobj.hpp"

#include <regex>

FileObj::FileObj(std::string file_path) { this->set_file(file_path); }

FileObj::FileObj() {}

FileObj::~FileObj() { t_filestream.close(); }

bool FileObj::set_file(std::string file_path) {
  if(stat(file_path.c_str(), &this->sb_in) == -1) {
    std::cerr << "File does not exist." << std::endl;
    return false;
  } else {
    this->t_file_path = file_path;
    return true;
  }

  return false;
}

bool FileObj::check_for_hidden_data() {
  if (!this->valid_file)
    return false;

  return false;
}

bool FileObj::extract(bool overwrite, std::string outfile) {
  if (!this->valid_file)
    return false;

  if (outfile == "") {
    outfile = std::regex_replace(this->t_file_path, std::regex(".jpg"), ".dat");
  }

  struct stat sb_out;

  if (stat(outfile.c_str(), &sb_out) == 0 && !overwrite) {
    std::cerr << "Outfile already exists." << std::endl;
    return false;
  }

  if (!this->check_for_hidden_data()) {
    return false;
  }

  /* Extracts hidden data to an external file */
  std::ofstream output_stream(
      std::regex_replace(this->t_file_path, std::regex(".jpg"), ".dat"),
      std::ios::out | std::ios::binary);
  while (this->t_filestream) {
    output_stream.put(this->t_filestream.get());
  }

  return true;
}
