#ifndef S21_STACK_H
#define S21_STACK_H

#include <fstream>
#include <initializer_list>
#include <iostream>
#include <utility>

namespace s21 {

template <class T>
class Node {
 public:
  T data;
  Node *prev;
  Node *next;

 public:
  Node(T data);
};

template <class T>
class Stack {
 public:
  Node<T> *head;
  Node<T> *tail;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Stack();
  Stack(std::initializer_list<value_type> items);
  Stack(const Stack &q);
  Stack(Stack &&q) noexcept;
  ~Stack();

  Stack &operator=(Stack &&q) noexcept;

  const_reference top();
  bool empty() const;
  size_type size() const;
  void clear();

  Node<T> *push(const_reference data);
  void pop();
  void swap(Stack &other);

  template <typename... Args>
  void insert_many_back(Args &&...args);
};

#include "stack.tpp"

}  // namespace s21

#endif  // STACK_H
