#ifndef SORTED_HPP
#define SORTED_HPP

#include <cstddef>
#include <functional>
#include <ostream>
#include <string>
#include <variant>

template <typename T>
class Sorted {
public:
  explicit Sorted(std::size_t capacity = 0);
  Sorted(const T* data, std::size_t size);
  Sorted(const Sorted& other);
  Sorted<T>& operator=(const Sorted& other);
  ~Sorted();

  Sorted<T>& add(const T& element);

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os, const Sorted<U>& arr);

  template <typename U>
  friend void swap(Sorted<U>& first, Sorted<U>& second);

  const T& operator[](std::size_t index) const;
  T& operator[](std::size_t index);

  template <typename U>
  Sorted<U> map(const std::function<U(const T&)>&) const;

private:
  T* data;
  std::size_t size, capacity;

  void insert(const T& element);
  void resize();
};

template <typename T>
Sorted<T>::Sorted(const Sorted& other) 
  : data(new T[other.capacity]),
    size(0),
    capacity(other.capacity) {
  for (std::size_t i = 0; i < other.size; ++i) {
    add(other.data[i]);
  } 
}

template <typename T>
Sorted<T>& Sorted<T>::operator=(const Sorted& other) {
  Sorted<T> copy(other);
  swap(copy, *this);

  return *this;
}

template <typename T>
Sorted<T>::~Sorted() {
  delete [] data;
}

template <typename T>
void swap(Sorted<T>& first, Sorted<T>& second) {
  using std::swap;

  swap(first.data, second.data);
  swap(first.size, second.size);
  swap(first.capacity, second.capacity);
}

template <typename T>
Sorted<T>::Sorted(std::size_t capacity)
  : data(new T[capacity]),
    size(0),
    capacity(capacity) {}

template <typename T>
Sorted<T>::Sorted(const T* data, std::size_t size)
  : data(new T[size]),
    size(0),
    capacity(size) {
  for (std::size_t i = 0; i < size; ++i) {
    add(data[i]);
  }
}

template <typename T>
void Sorted<T>::insert(const T& element) {
  data[size] = element;

  for (int i = size - 1; i >= 0; --i) {
    if (data[i] > element) {
      std::swap(data[i], data[i + 1]);
    }
  }

  ++size;
}

template <typename T>
Sorted<T>& Sorted<T>::add(const T& element) {
  if (size == capacity) {
    resize();
  }

  insert(element);

  return *this;
}

template <typename T>
void Sorted<T>::resize() {
  if (capacity == 0) {
    ++capacity;
  }

  T* new_data = new T[capacity *= 2];
  for (std::size_t i = 0; i < size; ++i) {
    new_data[i] = data[i];
  }

  delete [] data;
  data = new_data;
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const Sorted<U>& arr) {
  for (std::size_t i = 0; i < arr.size; ++i) {
    os << arr.data[i] << ' ';
  }
  return os << '\n';
}

template <typename T>
const T& Sorted<T>::operator[](std::size_t index) const {
  return data[index];
}

template <typename T>
T& Sorted<T>::operator[](std::size_t index) {
  return data[index];
}

template <typename T>
template <typename U>
Sorted<U> Sorted<T>::map(const std::function<U(const T&)>& f) const {
  Sorted<U> result;

  for (std::size_t i = 0; i < size; ++i) {
    result.add(f(data[i]));
  }

  return result;
}

#endif