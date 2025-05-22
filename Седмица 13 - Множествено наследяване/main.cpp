#include <iostream>
#include <string.h>

class A {
public:
  virtual void foo() const = 0;
  virtual void bar() const = 0;
};

class B : virtual public A {
public:
  void foo() const final {
    bar();
  }
};

class C : virtual public A {
public:
  void bar() const final {
    std::cout << "bar\n";
  } 
};

class D : public B, public C {};

int main() {
  D* d = new D;
  B* b = d;
  C* c = d;

  d->foo(); // bar
  b->foo(); // bar
  c->foo(); // bar

  delete d;
  return 0;
};
