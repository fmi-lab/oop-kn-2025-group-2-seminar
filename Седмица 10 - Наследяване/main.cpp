#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <cstring>
#include <ostream>
#include <variant>

class Person {
public:
  Person(const char* name, const char* email, unsigned age)
    : name(new char[strlen(name) + 1]{}),
      email(new char[strlen(email) + 1]{}),
      age(age) {
    strcpy(this->name, name);
    strcpy(this->email, email);
  }

  Person(const Person& other)
    : name(new char[strlen(other.name) + 1]{}),
      email(new char[strlen(other.email) + 1]{}),
      age(other.age) {
    strcpy(name, other.name);
    strcpy(email, other.email);
  }

  virtual ~Person() {
    delete [] name;
    delete [] email;
  }

  Person& operator=(const Person& other) {
    Person copy(other);
    swap(copy);
    
    return *this;
  }

  void print() const {
    std::cout << "Name: " << name << '\n'
              << "Email: " << email << '\n'
              << "Age: " << age << '\n';
  }

  void send_mail(const char* message) const {
    std::ofstream inbox(email, std::ios::app);
    this->greet(inbox) << '\n' << message << '\n';
    inbox.close();
  }

  void view_inbox() const {
    std::ifstream inbox(email);

    // while (!inbox.eof()) {
    //   char buff[100]{};
    //   inbox.getline(buff, 100);
    //   std::cout << buff << '\n';
    // }

    std::cout << inbox.rdbuf() << '\n';

    inbox.close();
  }

private:
  char* name, *email;
  unsigned age;

protected:
  void swap(Person& other) {
    using std::swap;
    swap(name, other.name);
    swap(email, other.email);
    swap(age, other.age);
  }

  virtual std::ostream& greet(std::ostream& os) const {
    return os << "To: " << name;
  }
};

class Student : public Person {
public:
  Student(
    const char* name, 
    const char* email,
    unsigned age,
    const char* fn
  ) : Person(name, email, age), fn(new char[strlen(fn) + 1]{}) {
    strcpy(this->fn, fn);
  }

  Student(const Student& other)
    : Person(other), fn(new char[strlen(other.fn) + 1]{}) {
    strcpy(fn, other.fn);
  }

  ~Student() {
    delete [] fn;
  }

  Student& operator=(const Student& other) {
    Student copy(other);
    swap(copy);

    return *this;
  }

  void print() const {
    Person::print();
    std::cout << "Faculty number: " << fn << '\n';
  }

private:
  char* fn;

  void swap(Student& other) {
    using std::swap;
    Person::swap(other);
    swap(fn, other.fn);
  }

  std::ostream& greet(std::ostream& os) const final {
    return Person::greet(os) << ", " << fn;
  }
};

int main() {
  // Person p("Pesho", "pesho@email.com", 20);
  // p.send_mail("Zdr kpr");
  // p.send_mail("Ko staa");

  // p.print();
  // p.view_inbox();

  Student s("Marko", "marko@gmail.com", 19, "3MI0824534");
  s.print();
  s.send_mail("Zdr kp");
  s.view_inbox();
}