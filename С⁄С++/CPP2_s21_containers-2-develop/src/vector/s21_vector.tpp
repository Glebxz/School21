#ifndef S21_VECTOR_TPP
#define S21_VECTOR_TPP

template <class T>
vector<T>::vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

template <class T>
vector<T>::vector(size_type n)
    : m_data(new value_type[n]), m_size(n), m_capacity(n) {}

template <class T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : m_data(new value_type[items.size()]),
      m_size(items.size()),
      m_capacity(items.size()) {
  std::copy(items.begin(), items.end(), m_data);
}

template <class T>
vector<T>::vector(const vector &v)
    : m_data(new value_type[v.m_size]),
      m_size(v.m_size),
      m_capacity(v.m_capacity) {
  std::copy(v.m_data, v.m_data + v.m_size, m_data);
}

template <class T>
vector<T>::vector(vector &&v)
    : m_data(v.m_data), m_size(v.m_size), m_capacity(v.m_capacity) {
  v.m_data = nullptr;
  v.m_size = 0;
  v.m_capacity = 0;
}

template <class T>
vector<T>::~vector() {
  delete[] m_data;
  m_data = nullptr;
  m_size = 0;
  m_capacity = 0;
}

template <class T>
vector<T> &vector<T>::operator=(vector &&v) {
  if (this != &v) {
    delete[] m_data;
    m_data = v.m_data;
    m_size = v.m_size;
    m_capacity = v.m_capacity;
    v.m_data = nullptr;
    v.m_size = 0;
    v.m_capacity = 0;
  }
  return *this;
}

template <class T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= m_size) {
    throw std::out_of_range("Requested index is out of range(at)");
  }
  return m_data[pos];
}

template <class T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  if (pos >= m_size) {
    throw std::out_of_range("Requested index is out of range(operator[])");
  }
  return m_data[pos];
}

template <class T>
typename vector<T>::const_reference vector<T>::front() {
  return m_data[0];
}

template <class T>
typename vector<T>::const_reference vector<T>::back() {
  return m_data[m_size - 1];
}

template <class T>
T *vector<T>::data() {
  return m_data;
}

template <class T>
typename vector<T>::iterator vector<T>::begin() {
  return m_data;
}

template <class T>
typename vector<T>::iterator vector<T>::end() {
  return m_data + m_size;
}

template <class T>
bool vector<T>::empty() {
  return m_size == 0;
}

template <class T>
typename vector<T>::size_type vector<T>::size() {
  return m_size;
}

template <class T>
typename vector<T>::size_type vector<T>::max_size() {
  return std::numeric_limits<size_type>::max();
}

template <class T>
void vector<T>::reserve(size_type size) {
  if (size > m_capacity) {
    value_type *new_data = new value_type[size];
    std::copy(m_data, m_data + m_size, new_data);
    delete[] m_data;
    m_data = new_data;
    m_capacity = size;
  }
}

template <class T>
typename vector<T>::size_type vector<T>::capacity() {
  return m_capacity;
}

template <class T>
void vector<T>::shrink_to_fit() {
  if (m_capacity > m_size) {
    value_type *new_data = new value_type[m_size];
    std::copy(m_data, m_data + m_size, new_data);
    delete[] m_data;
    m_data = new_data;
    m_capacity = m_size;
  }
}

template <class T>
void vector<T>::clear() {
  m_size = 0;
}

template <class T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  int index = pos - m_data;
  if (m_size == m_capacity) {
    reserve(m_size == 0 ? 1 : m_size * 2);
    pos = m_data + index;
  }
  m_size++;
  std::copy_backward(pos, m_data + m_size - 1, m_data + m_size);
  *pos = value;
  return pos;
}

template <class T>
void vector<T>::erase(iterator pos) {
  std::copy(pos + 1, m_data + m_size, pos);
  m_size--;
}

template <class T>
void vector<T>::push_back(const_reference value) {
  if (m_size == m_capacity) {
    reserve(m_size == 0 ? 1 : m_size * 2);
  }
  m_size++;
  *(end() - 1) = value;
}

template <class T>
void vector<T>::pop_back() {
  m_size--;
}

template <class T>
void vector<T>::swap(vector &other) {
  if (this != &other) {
    std::swap(m_data, other.m_data);
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
  }
}

template <class T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  if (pos < m_data || pos > m_data + m_size) {
    throw std::out_of_range("Invalid position for insert.");
  }
  int index = pos - m_data;
  size_type num_of_args = sizeof...(Args);
  if (m_size + num_of_args > m_capacity) {
    reserve(std::max(m_capacity * 2, m_size + num_of_args));
  }
  std::move(m_data + index, m_data + m_size, m_data + index + num_of_args);
  ((m_data[index++] = std::forward<Args>(args)), ...);
  m_size += num_of_args;
  return m_data + index;
}

template <class T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  (void)insert_many(end(), args...);
}

#endif  // S21_VECTOR_TPP
