#include <stdexcept>

template <class T, size_t N>
Array<T, N>::Array() = default;

template <class T, size_t N>
Array<T, N>::Array(std::initializer_list<value_type> const &items) {
  if (items.size() > N) {
    throw std::out_of_range("Too many items");
  }
  size_t i = 0;
  for (auto it = items.begin(); it != items.end() && i < size_; ++it, ++i) {
    data_[i] = *it;
  }
}

template <class T, size_t N>
Array<T, N>::Array(const Array &a) {
  for (size_t i = 0; i < N; ++i) {
    data_[i] = a.data_[i];
  }
}

template <class T, size_t N>
Array<T, N>::Array(Array &&a) noexcept = default;

template <class T, size_t N>
Array<T, N> &Array<T, N>::operator=(Array &&a) noexcept {
  if (this != &a) {
    for (size_t i = 0; i < N; ++i) {
      data_[i] = a.data_[i];
    }
  }
  return *this;
}

template <class T, size_t N>
typename Array<T, N>::reference Array<T, N>::at(size_type pos) {
  if (pos > N - 1) {
    throw std::out_of_range("Wrong index");
  }
  return data_[pos];
}

template <class T, size_t N>
typename Array<T, N>::reference Array<T, N>::operator[](size_type pos) {
  return data_[pos];
}

template <class T, size_t N>
typename Array<T, N>::const_reference Array<T, N>::front() {
  return data_[0];
}

template <class T, size_t N>
typename Array<T, N>::const_reference Array<T, N>::back() {
  return data_[N - 1];
}

template <class T, size_t N>
typename Array<T, N>::iterator Array<T, N>::data() {
  return data_;
}

template <class T, size_t N>
typename Array<T, N>::iterator Array<T, N>::begin() {
  return data_;
}

template <class T, size_t N>
typename Array<T, N>::iterator Array<T, N>::end() {
  return data_ + size_;
}

template <class T, size_t N>
bool Array<T, N>::empty() const {
  if (size_ == 0) return true;
  bool empty = true;

  for (size_t i = 0; i < N && empty; ++i) {
    if (data_[i] != 0) empty = false;
  }

  return empty;
}

template <class T, size_t N>
typename Array<T, N>::size_type Array<T, N>::size() const {
  return size_;
}

template <class T, size_t N>
typename Array<T, N>::size_type Array<T, N>::max_size() const {
  return size_;
}

template <class T, size_t N>
void Array<T, N>::swap(Array &other) {
  for (size_t i = 0; i < size_; ++i) {
    std::swap(data_[i], other.data_[i]);
  }
}

template <class T, size_t N>
void Array<T, N>::fill(const_reference value) {
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = value;
  }
}
