#include <algorithm>
#include <cstddef>
#include <iostream>
#include <optional>
#include <vector>

class Cloneable {
public:
  virtual Cloneable *clone() const = 0;
};

class MathExpression : public Cloneable {
public:
  virtual double evaluate() const = 0;
  virtual void print() const noexcept = 0;
  virtual MathExpression *clone() const = 0;
  virtual ~MathExpression() = default;
};

class Constant : public MathExpression {
public:
  Constant(double value) : value(value) {}

  double evaluate() const final { return value; }

  void print() const noexcept final {
    if (value < 0) {
      std::cout << '(' << value << ')';
    } else {
      std::cout << value;
    }
  }

  Constant *clone() const final { return new Constant(*this); }

private:
  double value;
};

class Sum : public MathExpression {
public:
  Sum() {}
  Sum(const Sum &other) {
    for (const MathExpression *expression : other.expressions) {
      expressions.push_back(expression->clone());
    }
  }
  ~Sum() {
    for (const MathExpression *expression : expressions) {
      delete expression;
    }
  }
  Sum &operator=(const Sum &other) {
    Sum copy(other);
    std::swap(expressions, copy.expressions);

    return *this;
  }

  double evaluate() const {
    double result = 0;

    for (const MathExpression *expresssion : expressions) {
      result += expresssion->evaluate();
    }

    return result;
  }

  void print() const noexcept {
    std::cout << '(';
    for (std::size_t i = 0; i < expressions.size() - 1; ++i) {
      expressions[i]->print();
      std::cout << " + ";
    }

    expressions.back()->print();
    std::cout << ')';
  }

  Sum &add(const MathExpression &expression) {
    expressions.push_back(expression.clone());
    return *this;
  }

  Sum *clone() const final { return new Sum(*this); }

private:
  std::vector<MathExpression *> expressions;
};

class Product : public MathExpression {
public:
  Product() {}
  Product(const Product &other) {
    for (const MathExpression *expression : other.expressions) {
      expressions.push_back(expression->clone());
    }
  }
  ~Product() {
    for (const MathExpression *expression : expressions) {
      delete expression;
    }
  }
  Product &operator=(const Product &other) {
    Product copy(other);
    std::swap(expressions, copy.expressions);

    return *this;
  }

  double evaluate() const {
    double result = 1;

    for (const MathExpression *expresssion : expressions) {
      result *= expresssion->evaluate();
    }

    return result;
  }

  void print() const noexcept {
    std::cout << '(';
    for (std::size_t i = 0; i < expressions.size() - 1; ++i) {
      expressions[i]->print();
      std::cout << " * ";
    }

    expressions.back()->print();
    std::cout << ')';
  }

  Product &add(const MathExpression &expression) {
    expressions.push_back(expression.clone());
    return *this;
  }

  Product *clone() const final { return new Product(*this); }

private:
  std::vector<MathExpression *> expressions;
};

class Power : public MathExpression {
public:
  Power(const MathExpression& base, int exponent)
    : base(base.clone()), exponent(exponent) {}

  Power(const Power& other)
    : base(other.base->clone()),
      exponent(other.exponent) {}
  
  ~Power() {
    delete base;
  }

  Power& operator=(const Power& other) {
    Power copy(other);
    std::swap(base, copy.base);
    std::swap(exponent, copy.exponent);

    return *this;
  }

  double evaluate() const {
    double base_value = base->evaluate(), result = 1;

    int exponent_copy = exponent;
    if (exponent_copy < 0) {
      exponent_copy = -exponent_copy;
      base_value = 1 / base_value;
    }

    while (exponent_copy != 0) {
      if (exponent_copy % 2 == 0) {
        base_value *= base_value;
        exponent_copy /= 2;
      } else {
        result *= base_value;
        --exponent_copy;
      }
    }

    return result;
  }

  void print() const noexcept {
    std::cout << '(';
    base->print();
    std::cout << " ^ ";

    if (exponent < 0) {
      std::cout << '(' << exponent << ')';
    } else {
      std::cout << exponent;
    }

    std::cout << ')';
  }

  Power *clone() const {
    return new Power(*this);
  }

private:
  MathExpression* base;
  int exponent;
};

int main() {
  Constant c1 = 5;
  Constant c2 = 7;
  Sum s1;
  s1.add(c1).add(c2);
  Constant c3 = -8;
  Product p1;
  Power pw(s1, -2);
  p1.add(pw).add(c3);

  p1.print();
  std::cout << '\n' << p1.evaluate() << '\n';
  return 0;
}