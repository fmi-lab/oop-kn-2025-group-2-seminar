#include "student.hpp"
#include <cstring>
#include <iostream>
#include <utility>

Student::Student(
  const char* name, 
  unsigned year, 
  unsigned group,
  unsigned fn,
  double average_grade
) : name(new char[strlen(name) + 1]{}),
    year(year),
    group(group),
    fn(fn),
    average_grade(average_grade) {
  strcpy(this->name, name);
}

Student::Student(const Student& other) 
: name(new char[strlen(other.name) + 1]{}),
  year(other.year),
  group(other.group),
  fn(other.fn),
  average_grade(other.average_grade) {
  strcpy(name, other.name);
}

// Student& Student::operator=(const Student& other) {
//   if (this != &other) {
//     delete[] name;
//     name = new char[strlen(other.name) + 1]{};
//     strcpy(name, other.name);
//     year = other.year;
//     group = other.group;
//     fn = other.fn;
//     average_grade = other.average_grade;
//   }

//   return *this;
// }

// copy-and-swap idiom
Student& Student::operator=(const Student& other) {
  Student copy(other);
  swap(copy);

  return *this;
}

Student::Student(Student&& other)
  : name(std::exchange(other.name, nullptr)),
    year(std::move(other.year)),
    group(std::move(other.group)),
    fn(std::move(other.fn)),
    average_grade(std::move(other.average_grade)) {}

Student& Student::operator=(Student&& other) {
  Student copy(std::move(other));
  swap(copy);
  
  return *this;
}

void Student::swap(Student& other) {
  using std::swap;

  swap(name, other.name);
  swap(year, other.year);
  swap(group, other.group);
  swap(fn, other.fn);
  swap(average_grade, other.average_grade);
}

void Student::info() const {
  std::cout << "Name: " << name << '\n'
            << "Year: " << year << '\n'
            << "Group: " << group << '\n'
            << "Faculty number: " << fn << '\n'
            << "Average grade: " << average_grade << '\n';
}