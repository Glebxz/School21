#ifndef S21_QUEUE_H
#define S21_QUEUE_H

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
class Queue {
 public:
  Node<T> *head;
  Node<T> *tail;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Queue();
  Queue(std::initializer_list<value_type> items);
  Queue(const Queue &q);
  Queue(Queue &&q) noexcept;
  ~Queue();

  Queue &operator=(Queue &&q) noexcept;

  const_reference front();
  const_reference back();
  bool empty() const;
  size_type size() const;
  void clear();

  Node<T> *push(const_reference data);
  void pop();
  void swap(Queue &other);

  template <typename... Args>
  void insert_many_back(Args &&...args);
};

#include "queue.tpp"

}  // namespace s21

#endif  // QUEUE_H
