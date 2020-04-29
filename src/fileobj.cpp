#include "fileobj.hpp"

#include <regex>

FileObj::FileObj(std::string file_path)
{
    this->set_file(file_path);
}

FileObj::FileObj()
{

}

FileObj::~FileObj()
{
    t_input_stream.close();
}

bool FileObj::set_file(std::string file_path)
{
    this->t_input_stream.open(file_path);

    if(!t_input_stream.is_open())
    {
        std::cerr << "File doesn't exist or isn't readable" << std::endl;
        this->t_input_stream.close();
        this->t_file_path = "";
        return false;
    }
    else
    {
        this->t_file_path = file_path;
        stat(t_file_path.c_str(), &sb_in);
        this->valid_file = true;

        return true;
    }
}

bool FileObj::check_for_hidden_data(file_type f)
{
    if(!this->valid_file)
        return false;

    uint8_t magic_number[2];
    switch(f)
    {
    case JPEG:
        magic_number[0] = 0xFF;
        magic_number[1] = 0xD9;
        break;
    }

    if(this->t_input_stream.is_open())
    {
        char readBuf            = 0;
        std::streamoff  EOI_pos = 0;

        /* Read until we encounter 0xFF. Then, check if the next byte is 0xD9 */
        while(t_input_stream)
        {
            this->t_input_stream.get(readBuf);

            if(static_cast<uint8_t>(readBuf) == magic_number[0])
            {
                //std::cout << "0xFF Byte Match at " << file.tellg() << std::endl;
                this->t_input_stream.get(readBuf);
                if(static_cast<uint8_t>(readBuf) == magic_number[1])
                {
                    EOI_pos = this->t_input_stream.tellg();
                    std::cout << "0xFFD9 found at " << EOI_pos << std::endl;
                    break;
                }
            }
        }


        if(EOI_pos >= sb_in.st_size)
        {
            std::cout << "EOF reached. No embedded data found." << std::endl;
            this->t_input_stream.close();
            return false;
        }
        else
        {
            std::cout << this->sb_in.st_size - EOI_pos << " bytes exceeding the EOI found." << std::endl;
            return true;
        }
    }

    return false;
}

bool FileObj::extract(bool overwrite, std::string outfile)
{
    if(!this->valid_file)
        return false;

    if(outfile == "")
    {
        outfile = std::regex_replace(this->t_file_path, std::regex(".jpg"), ".dat");
    }

    struct stat sb_out;

    if(stat(outfile.c_str(), &sb_out) == 0 && !overwrite)
    {
        std::cerr << "Outfile already exists." << std::endl;
        return false;
    }

    if(!this->check_for_hidden_data(JPEG))
    {
        return false;
    }

    /* Extracts hidden data to an external file */
    std::ofstream output_stream(std::regex_replace(this->t_file_path, std::regex(".jpg"), ".dat"), std::ios::out|std::ios::binary);
    while(this->t_input_stream)
    {
        output_stream.put(this->t_input_stream.get());
    }

    return true;
}
