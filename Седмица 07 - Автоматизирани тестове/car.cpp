#include "car.hpp"

unsigned Car::id = 0;

Car::Car(const char* brand, const char* model, double average_speed)
    : brand(new char[strlen(brand) + 1]{}),
      model(new char[strlen(model) + 1]{}),
      average_speed(average_speed),
      distance(0),
      current_id(++id) {
    strcpy(this->brand, brand);
    strcpy(this->model, model);
  }

const char* const Car::get_brand() const {
  return brand;
}

const char* const Car::get_model() const {
  return model;
}

double Car::traveled_distance() const {
  return distance;
}

unsigned Car::get_id() const {
  return current_id;
}

Car::~Car() {
  delete[] brand;
  delete[] model;
}

Car::Car(const Car& other) 
  : brand(new char[strlen(other.brand) + 1]{}),
    model(new char[strlen(other.model) + 1]{}),
    average_speed(other.average_speed),
    distance(0),
    current_id(++id) {
  strcpy(brand, other.brand);
  strcpy(model, other.model);
}
