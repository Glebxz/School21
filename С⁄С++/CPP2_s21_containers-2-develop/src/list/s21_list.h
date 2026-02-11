#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace s21 {

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  list &operator=(list &&l);
  ~list();

  size_type size() const { return Size; };
  bool empty() const { return Size == 0; };

  reference operator[](size_type index);
  const_reference operator[](size_type index) const;

  void push_back(const_reference value);
  void push_front(const_reference value);
  void pop_back();
  void pop_front();
  void clear();
  void swap(list &other);
  void merge(list &other);
  void reverse();
  void unique();

  class ListIterator;

  ListIterator begin();
  ListIterator end();

  class ListConstIterator;

  ListConstIterator cbegin() const;
  ListConstIterator cend() const;

  ListIterator insert(ListIterator pos, const_reference value);
  void erase(ListIterator pos);
  void splice(ListConstIterator pos, list &other);
  void sort();

 private:
  class Node {
   public:
    Node *pNext;
    Node *pPrev;
    value_type data;

    Node(value_type data = value_type(), Node *pNext = nullptr,
         Node *pPrev = nullptr);
  };

  size_type Size;
  Node *head;
  Node *tail;
};

#include "s21_list.tpp"

}  // namespace s21

#endif
