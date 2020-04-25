#include "cmdparse.hpp"

namespace cmdparse {
    std::vector<cmdparse::arg_match> parse(const int &argc, char *const argv_raw[], const std::vector<cmdparse::arg> &possible_args)
    {
        std::vector<cmdparse::argv_meta> argv;
        argv.reserve(argc);

        for(int argc_i = 0; argc_i<argc; ++argc_i)
            argv.push_back(cmdparse::argv_meta{argv_raw[argc_i]});

        std::vector<cmdparse::arg_match>      detected_args;

        for(int i = 0; i<argc; ++i)
        {
            if(!argv[i].identified && (argv[i].value.substr(0, 2) == "--" || argv[i].value.substr(0, 1) == "-"))
            {
                for(size_t j = 0; j < possible_args.size(); ++j)
                {
                    if(argv[i].value.substr(2, argv[i].value.size()) == possible_args[j].longOption || argv[i].value.substr(1, 2) == possible_args[j].shortOption)
                    {
                        detected_args.push_back(cmdparse::arg_match{.option_name = possible_args[j].name, .option_id = j, .valid = true});
                        argv[i].identified = true;
                    }
                    else
                        continue;

                    if(i != argc-1 && argv[i+1].value.substr(0, 1) != "-")
                    {
                        if(possible_args[j].takes_parameter == true)
                        {
                            detected_args.rbegin()->caught_argument = argv[i+1].value;
                            argv[i+1].identified = true;
                        }
                    }
                }
            }
        }
        for(int i = 0; i<argc; ++i)
        {
            if(!argv[i].identified && (argv[i].value.substr(0, 2) == "--" || argv[i].value.substr(0, 1) == "-"))
            {
                detected_args.push_back(cmdparse::arg_match{.option_name = argv[i].value, .option_id = 0, .valid = false});

                if(i != argc-1 && argv[i+1].value.substr(0, 1) != "-")
                {
                    detected_args.rbegin()->caught_argument = argv[i+1].value;
                    argv[i+1].identified = true;
                }
            }
        }

        return detected_args;
    }
}
