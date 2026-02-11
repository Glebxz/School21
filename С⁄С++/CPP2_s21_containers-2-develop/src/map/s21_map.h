#ifndef S21_MAP_H
#define S21_MAP_H

#include "../rb_tree/red-black-tree.h"

namespace s21 {

template <typename Key, typename T, typename Compare = std::less<Key>>
class map : public BinaryTree<Key, std::pair<const Key, T>, Compare> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename BinaryTree<Key, value_type, Compare>::iterator;
  using size_type = size_t;
  using BinaryTree<Key, value_type, Compare>::BinaryTree;

  map(std::initializer_list<value_type> const &items) {
    for (const value_type &item : items) {
      insert(item);
    }
  }

  T &at(const Key &key) {
    iterator iter = this->find(key);
    if (iter == this->end()) {
      throw std::out_of_range("Key not found");
    }
    return (*iter).second;
  }

  T &operator[](const Key &key) {
    iterator iter = this->find(key);
    if (iter == this->end()) {
      iter = this->insert(std::make_pair(key, T())).first;
    }
    return (*iter).second;
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    return this->InsertUnique(value.first, value);
  }

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return this->InsertUnique(key, std::make_pair(key, obj));
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    iterator it = this->find(key);
    if (it != this->end()) {
      (*it).second = obj;
      return {it, false};
    }
    return this->InsertUnique(key, std::make_pair(key, obj));
  }

  void merge(map &other) {
    if (this != &other) {
      for (auto it = other.begin(); it != other.end(); ++it) {
        this->InsertUnique((*it).first, *it);
      }
    }
  }

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    vector<std::pair<iterator, bool>> result;

    (result.push_back(this->InsertUnique(args.first, args)), ...);

    return result;
  }
};

}  // namespace s21

#endif
