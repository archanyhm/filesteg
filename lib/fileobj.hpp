#ifndef FILEOBJ_HPP
#define FILEOBJ_HPP

#include <iostream>
#include <fstream>
#include <sys/stat.h>

/*!
 * \enum file_type
 * \brief The file_type enum
 */
enum file_type {
    JPEG
};

class FileObj
{
public:    
    FileObj(std::string file_path);
    FileObj();
    ~FileObj();

    bool set_file(std::string file_path);

    bool check_for_hidden_data(file_type f);
    bool extract(std::string outfile = "");

private:    
    std::string     t_file_path;
    std::ifstream   t_input_stream;

    bool            valid_file;
    struct stat     sb_in;
};

#endif // FILEOBJ_HPP
