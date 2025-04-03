#include <cstring>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../libs/doctest.h"
#include "car.hpp"

class CarFixture {
public:
  CarFixture(): car1(Car(brand, model, 47.5)) {
    car2 = new Car(car1);
  }

  ~CarFixture() {
    delete car2;
  }

protected:
    const char* brand = "porsche";
    const char* model = "911 GT3S";

    Car car1;
    Car* car2;
};

TEST_SUITE("Car") {
  TEST_CASE("constructor") {
    SUBCASE("creates correct car") {
      const char* brand = "mazda";
      const char* model = "rx7";
      Car car(brand, model, 150);
  
      CHECK(strcmp(car.get_brand(), brand) == 0);
      CHECK(strcmp(car.get_model(), model) == 0);
      CHECK_EQ(car.traveled_distance(), doctest::Approx(0));
    }

    SUBCASE("id increments with every new car") {
      Car car1("golf", "mk4", 89.4);
      Car car2("ferrari", "f40", 96.5);
  
      CHECK_EQ(car1.get_id() + 1, car2.get_id());
    }
  }

  TEST_CASE_FIXTURE(CarFixture, "copy constructor") {
    SUBCASE("copies data correctly") {
      CHECK(strcmp(car1.get_brand(), car2->get_brand()) == 0);
      CHECK(strcmp(car1.get_model(), car2->get_model()) == 0);
      CHECK_EQ(car2->traveled_distance(), doctest::Approx(0));
      CHECK_NE(car1.get_id(), car2->get_id());
    }

    SUBCASE("makes deep copy") {
      delete car2;
      car2 = nullptr;

      CHECK(strcmp(car1.get_brand(), brand) == 0);
      CHECK(strcmp(car1.get_model(), model) == 0);
    }
  }
}