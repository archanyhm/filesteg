#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <string>
#include <regex>

#include "fileobj.hpp"
/*!
  * \file main.cpp
  * \brief main program file
  *
  * Contains the main function
*/

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
*/
enum handler_return {
    PROG_QUIT = -1,
    PROG_PASS = 0,
    PROG_ERR_NOT_ENOUGH_ARGUMENTS = 1,
};


/*!
* Parses command line input and forwards return values of executed functoins.
*u
* \param argc Amount of arguments passed.
* \param argv Array of command line arguments.
*
* \return Forwarded return values of executed functions, or returns \ref PROG_ERR_NOT_ENOUGH_ARGUMENTS if the amount of arguments passed is insufficient.
*/
int handler(int const &argc, char *const *argv)
{
    if(argc < 3)
    {
#ifdef CONFIG__ALLOW_INTERACTIVE
        bool interactive = true;

        std::string file_path;
        std::cout << "Enter file path to operate on: ";
        std::cin >> file_path;

        FileObj file(file_path);

        while(interactive)
        {
            std::string input;
            std::cout << "Enter command: ";
            std::cin >> input;



            if(input == "check")
            {
                file.check_for_hidden_data(JPEG);
            }
            else if(input == "extract")
            {

            }
            else if(input == "quit")
            {
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

    FileObj file(argv[2]);

    if(strcmp(argv[1], "check"))
    {
        file.check_for_hidden_data(JPEG);
    }

    if(strcmp(argv[1], "exatract"))
    {

    }
    else if(strcmp(argv[1], "quit"))
    {
        return PROG_QUIT;
    }

    return 0;
}

int main(int argc, char *argv[])
{

#ifdef DEBUG__SHOW_STAT_INFO
    struct stat test;
    stat(argv[0], &test);

    std::cout << "------------ GENERAL INFORMATION ------------" << "\n"
              << "Argument count: " << argc << "\n"
              << "Executable name/location: " << argv[0] << "\n"
              << "------------ sys/stat.h ------------" << "\n"
              << "Executable device number: " << test.st_dev << "\n"
              << "Executable inode number: " << test.st_ino << "\n"
              << "Executable mode: " << test.st_mode << "\n"
              << "Executable size (according to stat): " << static_cast<float>(test.st_size)/1000/1000 << " MB \n"
              << "------------------------------------" << "\n";

    getchar();
#else
    handler(argc, argv);
#endif
    return 0;
}
