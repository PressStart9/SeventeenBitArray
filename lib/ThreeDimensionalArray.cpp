#include "ThreeDimensionalArray.h"

namespace three_dimensional_array {

ThreeDimensionalArray::TdaViewX::TdaViewX(ThreeDimensionalArray& arr, size_t x)
  : arr_(arr), x_(x) {
}

ThreeDimensionalArray::TdaViewY ThreeDimensionalArray::TdaViewX::operator[](size_t key) {
  return {arr_, x_, key};
}

ThreeDimensionalArray::TdaViewY::TdaViewY(ThreeDimensionalArray& arr, size_t x, size_t y)
  : arr_(arr), x_(x), y_(y) {}

ThreeDimensionalArray::TdaViewZ ThreeDimensionalArray::TdaViewY::operator[](size_t key) {
  return {arr_, x_, y_, key};
}

ThreeDimensionalArray::TdaViewZ::TdaViewZ(ThreeDimensionalArray& arr, size_t x, size_t y, size_t z)
  : arr_(arr), x_(x), y_(y), z_(z) {
}

ThreeDimensionalArray::TdaViewZ::operator uint32_t() const {
  return arr_.GetValue(x_, y_, z_);
}

ThreeDimensionalArray::TdaViewZ& ThreeDimensionalArray::TdaViewZ::operator=(int value) {
  arr_.SetValue(x_, y_, z_, value);
  return *this;
}

ThreeDimensionalArray::ThreeDimensionalArray(size_t x, size_t y, size_t z) : size_x_(x), size_y_(y), size_z_(z) {
  bytes_ = new uint8_t[(x * y * z * 17) / 8 + 1] {0};
}

ThreeDimensionalArray::ThreeDimensionalArray(const ThreeDimensionalArray& arr)
    : size_x_(arr.size_x_), size_y_(arr.size_y_), size_z_(arr.size_z_) {
  size_t line_size = (size_x_ * size_y_ * size_z_ * 17) / 8 + 1;
  bytes_ = new uint8_t[line_size];
  for (size_t i = 0; i < line_size; ++i) {
    bytes_[i] = arr.bytes_[i];
  }
}

uint32_t ThreeDimensionalArray::GetValue(size_t x, size_t y, size_t z) const {
  size_t i = kBitsCount_ * size_z_ * size_y_ * x + kBitsCount_ * size_z_ * y + kBitsCount_ * z;
  auto start_byte = i / kByteSize_;
  auto start_bit = i % kByteSize_;
  uint32_t result = (bytes_[start_byte] & (kFullBitMask_ >> start_bit)) << (kBitsCount_ - kByteSize_ + start_bit);
  result += bytes_[start_byte + 1] << (kBitsCount_ - 2 * kByteSize_ + start_bit);
  result += bytes_[start_byte + 2] >> (3 * kByteSize_ - kBitsCount_ - start_bit);
  return result;
}

void ThreeDimensionalArray::SetValue(size_t x, size_t y, size_t z, int value) {
  size_t i = kBitsCount_ * size_z_ * size_y_ * x + kBitsCount_ * size_z_ * y + kBitsCount_ * z;
  auto start_byte = i / kByteSize_;
  auto start_bit = i % kByteSize_;
  bytes_[start_byte] |= (kFullBitMask_ >> start_bit);
  bytes_[start_byte] &= (kFullBitMask_ << (kByteSize_ - start_bit)) + uint8_t(value >> (kBitsCount_ - kByteSize_ + start_bit));
  bytes_[start_byte + 1] |= kFullBitMask_;
  bytes_[start_byte + 1] &= uint8_t(value >> (kBitsCount_ - 2 * kByteSize_ + start_bit));
  bytes_[start_byte + 2] |= (kFullBitMask_ << (3 * kByteSize_ - kBitsCount_ - start_bit));
  bytes_[start_byte + 2] &= (kFullBitMask_ >> (kBitsCount_ - 2 * kByteSize_ + start_bit))
      + (uint8_t(value) << (3 * kByteSize_ - kBitsCount_ - start_bit));
}

ThreeDimensionalArray ThreeDimensionalArray::make_array(size_t x, size_t y, size_t z) {
  return {x, y, z};
}

ThreeDimensionalArray::TdaViewX ThreeDimensionalArray::operator[](size_t key) {
  return {*this, key};
}

std::ostream& operator<<(std::ostream& st, const ThreeDimensionalArray::TdaViewY& arr) {
  st << '[';
  for (size_t k = 0; k < arr.arr_.size_z_ - 1; ++k) {
    st << arr.arr_.GetValue(arr.x_, arr.y_, k) << ", ";
  }
  st << arr.arr_.GetValue(arr.x_, arr.y_, arr.arr_.size_z_ - 1) << "]";

  return st;
}

std::ostream& operator<<(std::ostream& st, const ThreeDimensionalArray::TdaViewX& arr) {
  std::cout << '[';
  for (size_t j = 0; j < arr.arr_.size_y_ - 1; ++j) {
    st << ThreeDimensionalArray::TdaViewY(arr.arr_, arr.x_, j);
    std::cout << ", ";
  }
  st << ThreeDimensionalArray::TdaViewY(arr.arr_, arr.x_, arr.arr_.size_y_ - 1);
  std::cout << ']';

  return st;
}

std::ostream& operator<<(std::ostream& st, const ThreeDimensionalArray& arr) {
  std::cout << '[';
  for (size_t i = 0; i < arr.size_x_ - 1; ++i) {
    st << ThreeDimensionalArray::TdaViewX(const_cast<ThreeDimensionalArray&>(arr), i);
    std::cout << ", ";
  }
  st << ThreeDimensionalArray::TdaViewX(const_cast<ThreeDimensionalArray&>(arr), arr.size_x_ - 1);
  std::cout << ']';

  return st;
}

std::istream& operator>>(std::istream& st, ThreeDimensionalArray::TdaViewZ arr) {
  int val;
  st >> val;

  arr.arr_.SetValue(arr.x_, arr.y_, arr.z_, val);

  return st;
}

ThreeDimensionalArray ThreeDimensionalArray::operator*(uint8_t val) const {
  ThreeDimensionalArray arr = ThreeDimensionalArray(size_x_, size_y_, size_z_);
  for (size_t x = 0; x < size_x_; ++x) {
    for (size_t y = 0; y < size_y_; ++y) {
      for (size_t z = 0; z < size_z_; ++z) {
        arr.SetValue(x, y, z, static_cast<int>(GetValue(x, y, z)) * val);
      }
    }
  }

  return arr;
}

ThreeDimensionalArray ThreeDimensionalArray::operator+(const ThreeDimensionalArray& arr) const {
  ThreeDimensionalArray res = ThreeDimensionalArray(size_x_, size_y_, size_z_);
  for (size_t x = 0; x < size_x_; ++x) {
    for (size_t y = 0; y < size_y_; ++y) {
      for (size_t z = 0; z < size_z_; ++z) {
        res.SetValue(x, y, z, static_cast<int>((GetValue(x, y, z) + arr.GetValue(x, y, z))));
      }
    }
  }

  return res;
}

ThreeDimensionalArray ThreeDimensionalArray::operator-(const ThreeDimensionalArray& arr) const {
  ThreeDimensionalArray res = ThreeDimensionalArray(size_x_, size_y_, size_z_);
  for (size_t x = 0; x < size_x_; ++x) {
    for (size_t y = 0; y < size_y_; ++y) {
      for (size_t z = 0; z < size_z_; ++z) {
        res.SetValue(x, y, z, static_cast<int>((GetValue(x, y, z) - arr.GetValue(x, y, z))));
      }
    }
  }

  return res;
}

ThreeDimensionalArray::~ThreeDimensionalArray() {
  delete[] bytes_;
}
ThreeDimensionalArray& ThreeDimensionalArray::operator=(const ThreeDimensionalArray &arr) {
  delete[] bytes_;
  size_x_ = arr.size_x_;
  size_y_ = arr.size_y_;
  size_z_ = arr.size_z_;
  size_t line_size = (size_x_ * size_y_ * size_z_ * 17) / 8 + 1;
  bytes_ = new uint8_t[line_size];
  for (size_t i = 0; i < line_size; ++i) {
    bytes_[i] = arr.bytes_[i];
  }
  return *this;
}

}  // namespace three_dimensional_array
