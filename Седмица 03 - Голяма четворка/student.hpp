#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <optional>
#include <type_traits>
class Student {
public:
  Student(
    const char* name, 
    unsigned year, 
    unsigned group,
    unsigned fn,
    double average_grade
  );

  Student(const Student& other);
  Student& operator=(const Student& other);
  Student(Student&& other);
  Student& operator=(Student&& other);
  ~Student() {
    delete [] name;
  }

  void info() const;

private:
  char* name;
  unsigned year, group, fn;
  double average_grade;

  void swap(Student& other);
};

#endif