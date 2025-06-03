#pragma once

#include <iostream>
#include <cstdint>

namespace three_dimensional_array {

class ThreeDimensionalArray {
 private:
  class TdaViewX;
  class TdaViewY;
  class TdaViewZ;

 public:
  ThreeDimensionalArray(size_t x, size_t y, size_t z);
  ThreeDimensionalArray(const ThreeDimensionalArray& arr);
  ThreeDimensionalArray(ThreeDimensionalArray&& arr) noexcept;
  ~ThreeDimensionalArray();

  ThreeDimensionalArray& operator=(const ThreeDimensionalArray& arr);
  ThreeDimensionalArray& operator=(ThreeDimensionalArray&& arr) noexcept;

  uint32_t GetValue(size_t x, size_t y, size_t z) const;
  void SetValue(size_t x, size_t y, size_t z, int value);

  static ThreeDimensionalArray make_array(size_t x, size_t y, size_t z);

  TdaViewX operator[](size_t key);
  ThreeDimensionalArray operator*(uint8_t val) const;
  ThreeDimensionalArray operator+(const ThreeDimensionalArray& arr) const;
  ThreeDimensionalArray operator-(const ThreeDimensionalArray& arr) const;

  friend std::ostream& operator<<(std::ostream& st, const TdaViewX& arr);
  friend std::ostream& operator<<(std::ostream& st, const TdaViewY& arr);
  friend std::ostream& operator<<(std::ostream& st, const ThreeDimensionalArray& arr);
  friend std::istream& operator>>(std::istream& st, TdaViewZ arr);

 private:
  class TdaViewX {
   public:
    TdaViewX(ThreeDimensionalArray& arr, size_t x);

    TdaViewY operator[](size_t key);

    friend std::ostream& operator<<(std::ostream& st, const TdaViewX& arr);
    friend std::ostream& operator<<(std::ostream& st, const ThreeDimensionalArray& arr);

   private:
    ThreeDimensionalArray& arr_;
    size_t x_;
  };

  class TdaViewY {
   public:
    TdaViewY(ThreeDimensionalArray& arr, size_t x, size_t y);

    TdaViewZ operator[](size_t key);
    friend std::ostream& operator<<(std::ostream& st, const TdaViewY& arr);

   private:
    ThreeDimensionalArray& arr_;
    size_t x_;
    size_t y_;
  };

  class TdaViewZ {
   public:
    TdaViewZ(ThreeDimensionalArray& arr, size_t x, size_t y, size_t z);

    operator uint32_t() const;

    TdaViewZ& operator=(int value);

    friend std::istream& operator>>(std::istream& st, ThreeDimensionalArray::TdaViewZ arr);

   private:
    ThreeDimensionalArray& arr_;
    size_t x_;
    size_t y_;
    size_t z_;
  };

  uint8_t* bytes_;

  size_t size_x_;
  size_t size_y_;
  size_t size_z_;

  static const int kBitsCount_ = 17;
  static const uint8_t kFullBitMask_ = 0b11111111;
  static const int kByteSize_ = 8;
};

std::ostream& operator<<(std::ostream& st, const ThreeDimensionalArray::TdaViewX& arr);
std::ostream& operator<<(std::ostream& st, const ThreeDimensionalArray::TdaViewY& arr);
std::ostream& operator<<(std::ostream& st, const ThreeDimensionalArray& arr);
std::istream& operator>>(std::istream& st, ThreeDimensionalArray::TdaViewZ arr);

} // three_dimensional_array
