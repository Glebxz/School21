#ifndef RBT_H
#define RBT_H

#include <fstream>
#include <functional>
#include <iostream>
#include <limits>

#include "../vector/s21_vector.h"

namespace s21 {

template <typename Key, typename Val, typename Compare = std::less<Key>>
class BinaryTree {
 public:
  using key_type = Key;
  using value_type = Val;
  using reference = value_type &;
  using const_reference = const value_type &;
  class BinaryTreeIterator;
  class BinaryTreeConstIterator;
  using iterator = BinaryTreeIterator;
  using const_iterator = BinaryTreeConstIterator;
  using size_type = size_t;
  enum Color { Red = 0, Black = 1 };

  BinaryTree() = default;
  BinaryTree(const BinaryTree<Key, Val, Compare> &other);
  BinaryTree<Key, Val, Compare> &operator=(
      const BinaryTree<Key, Val, Compare> &other);
  BinaryTree(BinaryTree<Key, Val, Compare> &&other);
  BinaryTree<Key, Val, Compare> &operator=(
      BinaryTree<Key, Val, Compare> &&other);
  ~BinaryTree();

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  void erase(iterator pos);
  void swap(BinaryTree<Key, Val, Compare> &other);

  size_type count(const Key &key);
  iterator find(const key_type &key);
  bool contains(const key_type &key);
  std::pair<iterator, iterator> equal_range(const Key &key);
  iterator lower_bound(const Key &key);
  iterator upper_bound(const Key &key);

  void graf() { exportToDot(root_ptr_); }

 protected:
  iterator InsertEqual(const key_type &key, const value_type &value);
  std::pair<BinaryTree<Key, Val, Compare>::iterator, bool> InsertUnique(
      const key_type &key, const value_type &value);
  int CompareKeys(const key_type &key1, const key_type &key2);
  void mergeEqual(BinaryTree<Key, Val, Compare> &other);
  void mergeUnique(BinaryTree<Key, Val, Compare> &other);
  template <typename... Args>
  vector<std::pair<iterator, bool>> insertManyEqual(Args &&...args);
  template <typename... Args>
  vector<std::pair<iterator, bool>> insertManyUnique(Args &&...args);

 private:
  class Node;

  Node *root_ptr_ = nullptr;
  Node end_node_;

  Node *GetMin(Node *node);
  Node *GetMax(Node *node);
  size_type CheckSize(Node *node);
  void RecurseDelete(Node *node);
  Node *RecurseClone(Node *node, Node *parent = nullptr);

  void insertNode(Node *node);
  void insertUniqueNodeAndRecord(
      const std::pair<Key, Val> &p,
      s21::vector<std::pair<iterator, bool>> &result);
  void insertEqualNodeAndRecord(const std::pair<Key, Val> &p,
                                s21::vector<std::pair<iterator, bool>> &result);

  void BalanceTree(Node *node);
  void SwapColors(Node *node);
  void RightRoute(Node *node);
  void LeftRoute(Node *node);

  Node *&GetBrother(Node *node);
  void BlackZeroKidDelete(Node *node);
  void BlackOneRedKidDelete(Node *node);
  void NodeSwap(Node *node_deleted, Node *node_new);

  void generateDotFile(Node *root, std::ofstream &file);
  void exportToDot(Node *root);
};

#include "./const-iterator.tpp"
#include "./constructors.tpp"
#include "./insert.tpp"
#include "./iterator.tpp"
#include "./print.tpp"
#include "./red-black-tree.tpp"
#include "./zerase.tpp"

}  // namespace s21

#endif
