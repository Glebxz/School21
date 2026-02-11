#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace s21 {
template <class T>
class vector {
 public:
  // member types
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 private:
  // members
  value_type *m_data;
  size_type m_size;
  size_type m_capacity;

 public:
  // public methods
  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);
  ~vector();
  vector &operator=(vector &&v);

  reference at(size_type pos);
  reference operator[](size_type pos);

  const_reference front();
  const_reference back();
  value_type *data();

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void reserve(size_type size);
  size_type capacity();

  void shrink_to_fit();
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
};
#include "s21_vector.tpp"

}  // namespace s21

#endif  // S21_VECTOR_H
