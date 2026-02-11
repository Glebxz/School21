#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <fstream>
#include <initializer_list>
#include <iostream>
#include <utility>

namespace s21 {

template <class T, size_t N>
class Array {
 private:
  T data_[N] = {};
  size_t size_ = N;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Array();
  Array(std::initializer_list<value_type> const &items);
  Array(const Array &a);
  Array(Array &&a) noexcept;
  ~Array() = default;

  Array &operator=(Array &&a) noexcept;

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();
  iterator begin();
  iterator end();
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void swap(Array &other);
  void fill(const_reference value);
};

#include "array.tpp"

}  // namespace s21

#endif  // ARRAY_H
