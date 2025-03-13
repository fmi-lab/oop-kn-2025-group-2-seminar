#include <cmath>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>

class Polynomial {
public:
  Polynomial() : coefficients(nullptr), degree(-1), capacity(0) {}
  Polynomial(const double* coefficients, std::size_t size)
    : coefficients(new double[size]), degree(size - 1), capacity(size) {
    for (std::size_t i = 0; i < size; ++i) {
      this->coefficients[i] = coefficients[i];
    }
  }

  Polynomial(const Polynomial& other)
    : coefficients(new double[other.capacity]),
      degree(other.degree),
      capacity(other.capacity) {
    for (std::size_t i = 0; i < other.degree + 1; ++i) {
      coefficients[i] = other.coefficients[i];
    }
  }

  ~Polynomial() {
    delete [] coefficients;
  }

  Polynomial& operator=(const Polynomial& other) {
    Polynomial copy(other);
    swap(copy);

    return *this;
  }

  void add_coefficient(double coefficient) {
    if (degree + 1 == capacity) {
      resize();
    }

    coefficients[++degree] = coefficient;
  }

  double operator()(double x) const {
    double result = 0;

    for (std::size_t i = 0; i < degree + 1; ++i) {
      result += coefficients[i] * std::pow(x, i);
    }

    return result;
  }

  double operator[](std::size_t i) const {
    if (i > degree) {
      return 0;
    }

    return coefficients[i];
  }

  Polynomial operator+(const Polynomial& other) const {
    Polynomial result;

    for (std::size_t i = 0; i < std::max(degree, other.degree) + 1; ++i) {
      result.add_coefficient((*this)[i] + other[i]);
    }

    for (int i = std::max(degree, other.degree); i >= 0 && result.coefficients[i] == 0; --i) {
      --result.degree;
    }

    return result;
  }

  friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    for (int i = poly.degree; i >= 1; --i) {
      os << poly[i] << " * x^" << i << " + ";
    }

    os << poly[0] << '\n';
    return os;
  }
  
private:
  double* coefficients;
  int degree;
  std::size_t capacity;

  void swap(Polynomial& other) {
    using std::swap;

    swap(coefficients, other.coefficients);
    swap(degree, other.degree);
    swap(capacity, other.capacity);
  }

  void resize() {
    if (capacity == 0) {
      capacity = 1;
    }

    double* new_coefficients = new double[capacity *= 2];
    for (std::size_t i = 0; i < degree + 1; ++i) {
      new_coefficients[i] = coefficients[i];
    }

    delete [] coefficients;
    coefficients = new_coefficients;
  }
};

int main() {
  double arr[] = {2, 4, 5, 1};
  Polynomial poly;
  Polynomial other(arr, 4);
  
  poly.add_coefficient(3);
  poly.add_coefficient(1);
  poly.add_coefficient(2);
  std::cout << poly(2) << '\n';
  std::cout << poly[0] << '\n';

  std::cout << poly + other;
  return 0;
}