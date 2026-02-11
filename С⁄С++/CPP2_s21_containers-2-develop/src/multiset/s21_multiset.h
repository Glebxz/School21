#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include "../rb_tree/red-black-tree.h"

namespace s21 {

template <typename Key, typename Compare = std::less<Key>>
class multiset : public BinaryTree<Key, Key, Compare> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename BinaryTree<Key, Key, Compare>::iterator;
  using const_iterator = typename BinaryTree<Key, Key, Compare>::iterator;
  using size_type = size_t;
  using BinaryTree<Key, Key, Compare>::BinaryTree;

  multiset(std::initializer_list<value_type> const &items) {
    for (const value_type &item : items) {
      this->InsertEqual(item, item);
    }
  }

  iterator insert(const value_type &value) {
    return this->InsertEqual(value, value);
  }

  void merge(multiset<Key, Compare> &other) {
    if (this != &other) {
      for (auto it = other.begin(); it != other.end(); ++it) {
        this->InsertEqual(*it, *it);
      }
    }
  }

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    vector<std::pair<iterator, bool>> result;

    (result.push_back(
         {this->InsertEqual(std::forward<Args>(args), std::forward<Args>(args)),
          true}),
     ...);

    return result;
  }
};

}  // namespace s21

#endif
