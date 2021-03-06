#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <sys/stat.h>
#include <vector>

#include "cmdparse.hpp"
#include "verbose_cout.hpp"
#include "fileobj.hpp"
/*!
 * \file main.cpp
 * \brief main program file
 *
 * Contains the main function
 */

enum operation_modes {
  MODE_EMPTY,
  MODE_CHECK,
  MODE_EXTRACT,
  MODE_INJECT,
};

struct options {
  bool verbose = false;
  int mode = 0;

  std::string file_path = "";
};
struct options opt;

verbose_cout vcout() {
  if (opt.verbose)
    return verbose_cout(std::cout.rdbuf());
  else
    return verbose_cout();
}

/*!
 * \enum handler_return
 * Enumeration of int return codes returned by the handler function.
 *
 * \var handler_return::PROG_QUIT
 * Indicates that the user quit the program using the \b quit argument.
 *
 * \var handler_return::PROG_PASS
 * Indicates that the programm passed without any errors.
 *
 * \var handler_return::PROG_ERR_NOT_ENOUGH_ARGUMENTS
 * Indicates that the user didn't supply enough arguments to the program.
 *
 * \var handler_return::PROG_ERR_FILE_NOT_FOUND
 * Indicates that the program couldn't locate (or access) the given file.
 */
enum handler_return {
  PROG_QUIT = -1,
  PROG_PASS = 0,
  PROG_ERR_NOT_ENOUGH_ARGUMENTS = 1,
  PROG_ERR_FILE_NOT_FOUND = 404,
};

/*!
 * Parses command line input and forwards return values of executed functoins.
 *u
 * \param argc Amount of arguments passed.
 * \param argv Array of command line arguments.
 *
 * \return Forwarded return values of executed functions, or returns \ref
 *PROG_ERR_NOT_ENOUGH_ARGUMENTS if the amount of arguments passed is
 *insufficient.
 */
int handler(int const &argc, char *const *argv) {
  if (argc < 3 && true == false) {
#ifdef CONFIG__ALLOW_INTERACTIVE
    bool interactive = true;

    std::string file_path;
    std::cout << "Enter file path to operate on: ";
    std::cin >> file_path;

    FileObj file(file_path);
    u while (interactive) {
      std::string input;
      std::cout << "Enter command: ";
      std::cin >> input;

      if (input == "check") {
        file.check_for_hidden_data(JPEG);
      } else if (input == "extract") {

      } else if (input == "quit") {
        return PROG_QUIT;
      }

      std::cout << "\n";
    }

    return PROG_PASS;
#else
    std::cout << "Too few arguments." << std::endl;
    return PROG_ERR_NOT_ENOUGH_ARGUMENTS;
#endif
  }

  std::vector<cmdparse::arg> arguments;
  std::vector<cmdparse::arg_match> received_arguments;

  arguments.push_back(cmdparse::arg{.name = "verbose",
                                    .description = "",
                                    .required = false,
                                    .takes_parameter = false,
                                    .shortOption = 'v',
                                    .longOption = "verbose"});
  arguments.push_back(cmdparse::arg{.name = "file",
                                    .description = "",
                                    .required = true,
                                    .takes_parameter = true,
                                    .longOption = "file"});
  arguments.push_back(cmdparse::arg{.name = "mode",
                                    .description = "",
                                    .required = false,
                                    .takes_parameter = true,
                                    .longOption = "mode"});

  received_arguments = cmdparse::parse(argc, argv, arguments);

  for (auto elem : received_arguments) {
    if (elem.option_name == "verbose")
      opt.verbose = true;
    else if (elem.option_name == "mode") {
      if (elem.caught_argument == "check")
        opt.mode = MODE_CHECK;
      if (elem.caught_argument == "extract")
        opt.mode = MODE_EXTRACT;
    } else if (elem.option_name == "file") {
      struct stat sb;
      if (stat(elem.caught_argument.c_str(), &sb) == -1) {
        std::cerr << "File not found, aborting..." << std::endl;
        return PROG_ERR_FILE_NOT_FOUND;
      } else {
        vcout() << "File path appears to be valid"
                << "\n";
        opt.file_path = elem.caught_argument;
      }
    }
  }

  FileObj fob;

  if (opt.verbose) {
    for (auto elem : received_arguments) {
      vcout() << "Given parameter: " << elem.option_name << "\n"
              << "Valid          : " << (elem.valid ? "yes" : "no") << "\n"
              << "Caught argument: " << (elem.caught_argument == "" ? "NONE" : elem.caught_argument) << "\n\n";
    }
  }

  if(opt.mode != MODE_EMPTY) {
    vcout() << "Given mode is:" << opt.mode << "\n";
    fob.set_file(opt.file_path);
  }

  switch (opt.mode) {
  case MODE_EMPTY:
    break;
  case MODE_CHECK:
    fob.check_for_hidden_data();
    break;
  case MODE_EXTRACT:
    fob.extract(false);
    break;
  default:
    break;
  }

  return 0;
}

int main(int argc, char *argv[]) {
#ifdef DEBUG__SHOW_STAT_INFO
  struct stat test;
  stat(argv[0], &test);

  std::cout << "------------ GENERAL INFORMATION ------------"
            << "\n"
            << "Argument count: " << argc << "\n"
            << "Executable name/location: " << argv[0] << "\n"
            << "------------ sys/stat.h ------------"
            << "\n"
            << "Executable device number: " << test.st_dev << "\n"
            << "Executable inode number: " << test.st_ino << "\n"
            << "Executable mode: " << test.st_mode << "\n"
            << "Executable size (according to stat): "
            << static_cast<float>(test.st_size) / 1000 / 1000 << " MB \n"
            << "------------------------------------"
            << "\n";

  getchar();
#else
  handler(argc, argv);
#endif
  return 0;
}
