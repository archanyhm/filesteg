#ifndef VERBOSE_COUT_HPP
#define VERBOSE_COUT_HPP

#include <iostream>

class verbose_cout : public std::ostream {
public:
  verbose_cout() {}
  verbose_cout(std::streambuf *sbuf) : std::ios(sbuf), std::ostream(sbuf) {}
  verbose_cout(verbose_cout &&other) : verbose_cout(other.rdbuf()) {}
};

#endif // VERBOSE_COUT_HPP
