#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../libs/doctest.h"
#include "../Седмица 06 - Шаблони на класове/sorted.hpp"

class UniqueTestFixture {
public:
  UniqueTestFixture() {
    int data[] = {5, 3, 2, 1, 4};
    arr = Sorted<int>(data, 5);
  }

protected:
  Sorted<int> arr;
};

TEST_SUITE("Test") {
  TEST_CASE_FIXTURE(UniqueTestFixture, "Test with beforeEach") {
    CHECK(arr.length() == 5);
    arr.add(6);
    CHECK(arr.length() == 6);
  }
  
  TEST_CASE_FIXTURE(UniqueTestFixture, "Another test with beforeEach") {
    CHECK(arr.length() == 5);
  }
}