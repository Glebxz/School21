#include <stdexcept>

template <class T>
Node<T>::Node(T data) {
  this->data = data;
  this->prev = this->next = nullptr;
}

template <class T>
Stack<T>::Stack() : head(nullptr), tail(nullptr) {}

template <class T>
Stack<T>::Stack(std::initializer_list<value_type> items)
    : head(nullptr), tail(nullptr) {
  for (const auto &item : items) {
    this->push(item);
  }
}

template <class T>
Stack<T>::Stack(const Stack &q) : head(nullptr), tail(nullptr) {
  Node<T> *ptr = q.head;

  while (ptr != nullptr) {
    this->push(ptr->data);
    ptr = ptr->next;
  }
}

template <class T>
Stack<T>::Stack(Stack &&q) noexcept : head(q.head), tail(q.tail) {
  q.head = nullptr;
  q.tail = nullptr;
}

template <class T>
Stack<T>::~Stack() {
  clear();
}

template <class T>
Stack<T> &Stack<T>::operator=(Stack &&q) noexcept {
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
typename Stack<T>::const_reference Stack<T>::top() {
  if (tail == nullptr) {
    throw std::out_of_range("Empty stack");
  }
  return tail->data;
}

template <class T>
bool Stack<T>::empty() const {
  return this->head == nullptr;
}

template <class T>
typename Stack<T>::size_type Stack<T>::size() const {
  size_t len = 0;

  for (Node<T> *ptr = this->head; ptr != nullptr; ptr = ptr->next) {
    len++;
  }

  return len;
}

template <class T>
void Stack<T>::clear() {
  while (head != nullptr) pop();
}

template <class T>
Node<T> *Stack<T>::push(const_reference data) {
  Node<T> *ptr = new Node<T>(data);
  ptr->prev = tail;
  if (head != nullptr) tail->next = ptr;

  tail = ptr;

  if (head == nullptr) head = ptr;

  return ptr;
}

template <class T>
void Stack<T>::pop() {
  if (tail == nullptr) return;

  Node<T> *ptr = tail->prev;
  if (ptr != nullptr)
    ptr->next = nullptr;
  else
    head = nullptr;

  delete tail;
  tail = ptr;
}

template <class T>
void Stack<T>::swap(Stack &other) {
  std::swap(this->head, other.head);
  std::swap(this->tail, other.tail);
}

template <class T>
template <typename... Args>
void Stack<T>::insert_many_back(Args &&...args) {
  (this->push(std::forward<Args>(args)), ...);
}
