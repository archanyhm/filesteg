#ifndef CMDPARSE_H
#define CMDPARSE_H

#include <vector>
#include <string>
#include <iostream>

namespace cmdparse
{
    struct arg {
        std::string name;
        std::string description;

        bool        required        = false;
        bool        takes_parameter = true;

        std::string shortOption;
        std::string longOption;
    };

    struct arg_match {
        std::string option_name;
        std::string caught_argument;
        size_t      option_id;
        bool        valid;
    };

    struct argv_meta {
        std::string value;
        bool        identified = false;
    };

    std::vector<cmdparse::arg_match> parse(const int &argc, char *const argv[], const std::vector<cmdparse::arg> &possible_args);
}

#endif // CMDPARSE_H
