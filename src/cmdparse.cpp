#include "cmdparse.hpp"

namespace cmdparse {
    std::vector<cmdparse::arg_match> parse(const int &argc, char *const argv[], const std::vector<cmdparse::arg> &possible_args)
    {
        std::vector<cmdparse::arg_match>      detected_args;

        for(int i = 0; i<argc; ++i)
        {
            std::string argv_std = argv[i];
            if(argv_std.substr(0, 2) == "--" || argv_std.substr(0, 1) == "-")
            {
                for(size_t j = 0; j<possible_args.size(); ++j)
                {
                    if(argv_std.substr(2, argv_std.size()) == possible_args[j].longOption || argv_std.substr(1, 2) == possible_args[j].shortOption)
                    {
                        detected_args.push_back(cmdparse::arg_match{.option_name = possible_args[j].name, .option_id = j, .valid = true});
                    }
                    else
                    {
                        detected_args.push_back(cmdparse::arg_match{.option_name = argv_std, .option_id = 0, .valid = false});
                    }

                    if(i == argc-1)
                        break;

                    if(std::string(argv[i+1]).substr(0, 1) != "-")
                    {
                        if(possible_args[j].takes_parameter == true)
                            detected_args.rbegin()->caught_argument = argv[i+1];
                    }
                }
            }
        }

        return detected_args;
    }
}
