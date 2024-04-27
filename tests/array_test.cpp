#include <lib/ThreeDimensionalArray.h>
#include <gtest/gtest.h>
#include <sstream>


using namespace three_dimensional_array;

TEST(ArrayTestSuite, EmptyTest) {
  ThreeDimensionalArray arr = ThreeDimensionalArray::make_array(1, 1, 1);

  ASSERT_EQ(int(arr[0][0][0]), 0);
}

TEST(ArrayTestSuite, ChangeValueTest) {
  ThreeDimensionalArray arr = ThreeDimensionalArray::make_array(1, 1, 1);
  arr[0][0][0] = 1;

  ASSERT_EQ(int(arr[0][0][0]), 1);
}

TEST(ArrayTestSuite, ChangeMultipleValuesTest) {
  ThreeDimensionalArray arr = ThreeDimensionalArray::make_array(2, 2, 2);
  arr[0][0][0] = 1;
  arr[0][0][1] = 1087;
  arr[0][1][0] = 1231;
  arr[0][1][1] = 22;
  arr[1][0][0] = 64316;
  arr[1][0][1] = 11111;
  arr[1][1][0] = 0;
  arr[1][1][1] = 303;

  ASSERT_EQ(int(arr[0][0][0]), 1);
  ASSERT_EQ(int(arr[0][0][1]), 1087);
  ASSERT_EQ(int(arr[0][1][0]), 1231);
  ASSERT_EQ(int(arr[0][1][1]), 22);
  ASSERT_EQ(int(arr[1][0][0]), 64316);
  ASSERT_EQ(int(arr[1][0][1]), 11111);
  ASSERT_EQ(int(arr[1][1][0]), 0);
  ASSERT_EQ(int(arr[1][1][1]), 303);
}

TEST(ArrayTestSuite, ConstructionCopyTest) {
  ThreeDimensionalArray arr = ThreeDimensionalArray::make_array(2, 2, 2);
  arr[0][0][0] = 1;
  arr[0][0][1] = 1087;
  arr[0][1][0] = 1231;
  arr[0][1][1] = 22;
  arr[1][0][0] = 64316;
  arr[1][0][1] = 11111;
  arr[1][1][0] = 0;
  arr[1][1][1] = 303;

  ThreeDimensionalArray arr2 = arr;

  ASSERT_EQ(int(arr2[0][0][0]), 1);
  ASSERT_EQ(int(arr2[0][0][1]), 1087);
  ASSERT_EQ(int(arr2[0][1][0]), 1231);
  ASSERT_EQ(int(arr2[0][1][1]), 22);
  ASSERT_EQ(int(arr2[1][0][0]), 64316);
  ASSERT_EQ(int(arr2[1][0][1]), 11111);
  ASSERT_EQ(int(arr2[1][1][0]), 0);
  ASSERT_EQ(int(arr2[1][1][1]), 303);
}

TEST(ArrayTestSuite, MultiplyTest) {
  ThreeDimensionalArray arr = ThreeDimensionalArray::make_array(2, 2, 2);
  arr[0][0][0] = 1;
  arr[0][0][1] = 1087;
  arr[0][1][0] = 1231;
  arr[0][1][1] = 22;
  arr[1][0][0] = 64316;
  arr[1][0][1] = 11111;
  arr[1][1][0] = 0;
  arr[1][1][1] = 303;

  ThreeDimensionalArray arr2 = arr * 2;

  ASSERT_EQ(int(arr2[0][0][0]), 2);
  ASSERT_EQ(int(arr2[0][0][1]), 2174);
  ASSERT_EQ(int(arr2[0][1][0]), 2462);
  ASSERT_EQ(int(arr2[0][1][1]), 44);
  ASSERT_EQ(int(arr2[1][0][0]), 128632);
  ASSERT_EQ(int(arr2[1][0][1]), 22222);
  ASSERT_EQ(int(arr2[1][1][0]), 0);
  ASSERT_EQ(int(arr2[1][1][1]), 606);
}

TEST(ArrayTestSuite, AddingTest) {
  ThreeDimensionalArray arr = ThreeDimensionalArray::make_array(2, 2, 2);
  arr[0][0][0] = 1;
  arr[0][0][1] = 1087;
  arr[0][1][0] = 1231;
  arr[0][1][1] = 22;
  arr[1][0][0] = 64316;
  arr[1][0][1] = 11111;
  arr[1][1][0] = 0;
  arr[1][1][1] = 303;

  ThreeDimensionalArray arr2 = ThreeDimensionalArray::make_array(2, 2, 2);
  arr2[0][0][0] = 17;
  arr2[0][0][1] = 1187;
  arr2[0][1][0] = 1411;
  arr2[0][1][1] = 1112;
  arr2[1][0][0] = 616;
  arr2[1][0][1] = 111;
  arr2[1][1][0] = 0;
  arr2[1][1][1] = 0;

  ThreeDimensionalArray arr3 = arr + arr2;

  ASSERT_EQ(int(arr3[0][0][0]), 18);
  ASSERT_EQ(int(arr3[0][0][1]), 2274);
  ASSERT_EQ(int(arr3[0][1][0]), 2642);
  ASSERT_EQ(int(arr3[0][1][1]), 1134);
  ASSERT_EQ(int(arr3[1][0][0]), 64932);
  ASSERT_EQ(int(arr3[1][0][1]), 11222);
  ASSERT_EQ(int(arr3[1][1][0]), 0);
  ASSERT_EQ(int(arr3[1][1][1]), 303);
}

TEST(ArrayTestSuite, SubstractingTest) {
  ThreeDimensionalArray arr = ThreeDimensionalArray::make_array(2, 2, 2);
  arr[0][0][0] = 1;
  arr[0][0][1] = 1087;
  arr[0][1][0] = 1231;
  arr[0][1][1] = 22;
  arr[1][0][0] = 616;
  arr[1][0][1] = 111;
  arr[1][1][0] = 0;
  arr[1][1][1] = 0;

  ThreeDimensionalArray arr2 = ThreeDimensionalArray::make_array(2, 2, 2);
  arr2[0][0][0] = 17;
  arr2[0][0][1] = 1187;
  arr2[0][1][0] = 1411;
  arr2[0][1][1] = 1112;
  arr2[1][0][0] = 64316;
  arr2[1][0][1] = 11111;
  arr2[1][1][0] = 0;
  arr2[1][1][1] = 303;

  ThreeDimensionalArray arr3 = arr2 - arr;

  ASSERT_EQ(int(arr3[0][0][0]), 16);
  ASSERT_EQ(int(arr3[0][0][1]), 100);
  ASSERT_EQ(int(arr3[0][1][0]), 180);
  ASSERT_EQ(int(arr3[0][1][1]), 1090);
  ASSERT_EQ(int(arr3[1][0][0]), 63700);
  ASSERT_EQ(int(arr3[1][0][1]), 11000);
  ASSERT_EQ(int(arr3[1][1][0]), 0);
  ASSERT_EQ(int(arr3[1][1][1]), 303);
}