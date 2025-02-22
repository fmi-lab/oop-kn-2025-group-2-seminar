#include <cstddef>
#include <iostream>

template <typename T>
bool is_fixed_point(T(*func)(T), T point) {
  return func(point) == point;
}

int times5(int n) {
  return n * 5;
}

template <typename T, typename U, typename S>
auto composition(U(*f1)(T), S(*f2)(U)) {
  return [f1, f2](T point){
    return f2(f1(point));
  };
}

template <typename T>
auto derivative(T(*f)(T)) {
  constexpr double EPSILON = 1e-6;

  return [f, EPSILON](T x){
    return (f(x + EPSILON) - f(x)) / EPSILON;
  };
}

template <typename T, typename U>
U* map(const T* arr, std::size_t size, U(*f)(T)) {
  U* result = new U[size];

  for (std::size_t i = 0; i < size; ++i) {
    result[i] = f(arr[i]);
  }

  return result;
}

template <typename T>
void print(const T arr[], std::size_t size) {
  for (std::size_t i = 0; i < size; ++i) {
    std::cout << arr[i] << ' ';
  }
  std::cout << '\n';
}

template <typename T>
void resize(T*& arr, std::size_t old_size, std::size_t new_size) {
  T* new_arr = new T[new_size];

  for (std::size_t i = 0; i < old_size; ++i) {
    new_arr[i] = arr[i];
  }

  delete [] arr;
  arr = new_arr;
}

template <typename T>
T* filter(const T* arr, std::size_t size, bool(*predicate)(T)) {
  std::size_t new_size = 0;
  T* result = new T[new_size];

  for (std::size_t i = 0; i < size; ++i) {
    if (predicate(arr[i])) {
      resize(result, new_size, new_size + 1);
      result[new_size++] = arr[i];
    }
  }

  return result;
}

template <typename T, typename U>
U reduce(U(*f)(T, U), U nv, const T* arr, std::size_t size) {
  if (size == 0) {
    return nv;
  }

  return f(*arr, reduce(f, nv, arr + 1, size - 1));
}

int main() {
  int arr[] = {1, 2, 3, 4, 5};
  std::cout << reduce<int, int>([](int curr, int res){
      return res * curr;
  }, 1, arr, 5) << '\n'; // -> 120
  return 0;
}