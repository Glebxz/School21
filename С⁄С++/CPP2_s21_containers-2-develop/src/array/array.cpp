#include "array.h"

#include <iostream>

using namespace S21;

int main() {
  Array<int, 10> arr;

  std::cout << arr.size();
  std::cout << arr.max_size();
  return 0;
}
