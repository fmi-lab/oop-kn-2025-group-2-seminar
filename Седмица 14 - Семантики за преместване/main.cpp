#include <iostream>
#include <utility>
#include "../Седмица 03 - Голяма четворка/student.hpp"

template <typename T>
class UniquePointer {
public:
  UniquePointer(T* pointer) : pointer(pointer) {}
  UniquePointer(const UniquePointer& other) = delete;
  UniquePointer<T>& operator=(const UniquePointer& other) = delete;
  UniquePointer(UniquePointer&& other)
    : pointer(std::exchange(other.pointer, nullptr)) {}
  UniquePointer<T>& operator=(UniquePointer&& other) {
    UniquePointer<T> copy(std::move(other));
    std::swap(pointer, copy.pointer);

    return *this;
  }
  ~UniquePointer() {
    delete pointer;
  }

  T& operator*() {
    return *pointer;
  }

  const T& operator*() const {
    return *pointer;
  }

  T* operator->() const {
    return pointer;
  }

private:
  T* pointer;
};

int main() {
  UniquePointer<Student> ptr = new Student("Pesho", 1, 2, 810245, 5.50);

  (*ptr).info();
  ptr->info();
  return 0;
}