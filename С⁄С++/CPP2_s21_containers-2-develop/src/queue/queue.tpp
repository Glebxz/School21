#include <stdexcept>

template <class T>
Node<T>::Node(T data) {
  this->data = data;
  this->prev = this->next = nullptr;
}

template <class T>
Queue<T>::Queue() : head(nullptr), tail(nullptr) {}

template <class T>
Queue<T>::Queue(std::initializer_list<value_type> items)
    : head(nullptr), tail(nullptr) {
  for (const auto &item : items) {
    this->push(item);
  }
}

template <class T>
Queue<T>::Queue(const Queue &q) : head(nullptr), tail(nullptr) {
  Node<T> *ptr = q.head;

  while (ptr != nullptr) {
    this->push(ptr->data);
    ptr = ptr->next;
  }
}

template <class T>
Queue<T>::Queue(Queue &&q) noexcept : head(q.head), tail(q.tail) {
  q.head = nullptr;
  q.tail = nullptr;
}

template <class T>
Queue<T>::~Queue() {
  clear();
}

template <class T>
Queue<T> &Queue<T>::operator=(Queue &&q) noexcept {
  if (this != &q) {
    clear();

    head = q.head;
    tail = q.tail;

    q.head = nullptr;
    q.tail = nullptr;
  }
  return *this;
}

template <class T>
typename Queue<T>::const_reference Queue<T>::front() {
  if (head == nullptr) {
    throw std::out_of_range("Empty queue");
  }
  return head->data;
}

template <class T>
typename Queue<T>::const_reference Queue<T>::back() {
  if (tail == nullptr) {
    throw std::out_of_range("Empty queue");
  }
  return tail->data;
}

template <class T>
bool Queue<T>::empty() const {
  return this->head == nullptr;
}

template <class T>
typename Queue<T>::size_type Queue<T>::size() const {
  size_t len = 0;

  for (Node<T> *ptr = this->head; ptr != nullptr; ptr = ptr->next) {
    len++;
  }

  return len;
}

template <class T>
void Queue<T>::clear() {
  while (head != nullptr) pop();
}

template <class T>
Node<T> *Queue<T>::push(const_reference data) {
  Node<T> *ptr = new Node<T>(data);
  ptr->prev = tail;
  if (head != nullptr) tail->next = ptr;

  tail = ptr;

  if (head == nullptr) head = ptr;

  return ptr;
}

template <class T>
void Queue<T>::pop() {
  if (head == nullptr) return;

  Node<T> *ptr = head->next;
  if (ptr != nullptr)
    ptr->prev = nullptr;
  else
    tail = nullptr;

  delete head;
  head = ptr;
}

template <class T>
void Queue<T>::swap(Queue &other) {
  std::swap(this->head, other.head);
  std::swap(this->tail, other.tail);
}

template <class T>
template <typename... Args>
void Queue<T>::insert_many_back(Args &&...args) {
  (this->push(std::forward<Args>(args)), ...);
}
