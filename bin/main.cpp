#include <iostream>
#include "lib/ThreeDimensionalArray.h"

using namespace three_dimensional_array;

int main() {
  ThreeDimensionalArray arr = ThreeDimensionalArray(3, 3, 1);
  for (int i = 0; i < 8; ++i) {
    std::cin >> arr[i / 3][i % 3][0];
  }
  std::cout << arr << '\n';
  std::cout << arr[0][1] << '\n';
  arr[0][1][0] = 1;
  std::cout << arr << '\n';
  for (int i = 0; i < 5; ++i) {
    std::cin >> arr[i / 3][i % 3][0];
  }
  std::cout << arr << '\n';

  return 0;
}
