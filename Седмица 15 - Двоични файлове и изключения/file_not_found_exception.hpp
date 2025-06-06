#ifndef FILE_NOT_FOUND_EXCEPTION_HPP
#define FILE_NOT_FOUND_EXCEPTION_HPP

#include <exception>
#include <string>

class FileNotFoundException : public std::exception {
public:
  FileNotFoundException(const char *message) : message(message) {}

  const char *what() const noexcept final { return message; }

private:
  const char *message;
};

#endif