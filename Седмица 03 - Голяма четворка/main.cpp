#include <iostream>
#include "student.hpp"

int main() {
  Student student("Ivan", 1, 2, 80145, 5.25);
  student.info();

  Student copy(student);
  copy.info();

  Student pesho("Pesho", 2, 1, 84102, 4.37);
  student = pesho;

  student.info();
  return 0;
}