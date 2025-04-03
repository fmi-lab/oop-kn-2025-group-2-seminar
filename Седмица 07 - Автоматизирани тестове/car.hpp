#ifndef CAR_HPP
#define CAR_HPP

#include <cstring>

class Car {
public:
  Car(const char* brand, const char* model, double average_speed);
  Car(const Car& other);

  const char* const get_brand() const;
  const char* const get_model() const;
  double traveled_distance() const;
  unsigned get_id() const;

  ~Car();
private:
  char *brand, *model;
  unsigned current_id;
  double average_speed, distance;

  static unsigned id;
};

#endif