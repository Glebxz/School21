#include "./red-black-tree.h"

template <typename Key, typename Val, typename Compare>
BinaryTree<Key, Val, Compare>::BinaryTree(
    const BinaryTree<Key, Val, Compare> &other) {
  this->root_ptr_ = RecurseClone(other.root_ptr_);
  this->end_node_.parent_ = GetMax(this->root_ptr_);
}

template <typename Key, typename Val, typename Compare>
BinaryTree<Key, Val, Compare> &BinaryTree<Key, Val, Compare>::operator=(
    const BinaryTree<Key, Val, Compare> &other) {
  if (this == &other) {
    return *this;
  }
  if (this->root_ptr_ != nullptr) {
    RecurseDelete(this->root_ptr_);
  }
  this->root_ptr_ = RecurseClone(other.root_ptr_);
  this->end_node_.parent_ = GetMax(this->root_ptr_);
  return *this;
}

template <typename Key, typename Val, typename Compare>
typename BinaryTree<Key, Val, Compare>::Node *
BinaryTree<Key, Val, Compare>::RecurseClone(Node *node, Node *parent) {
  if (node == nullptr) {
    return nullptr;
  }
  Node *new_node = new Node(node->key_, node->value_);
  new_node->color_ = node->color_;
  new_node->parent_ = parent;
  new_node->left_ = RecurseClone(node->left_, new_node);
  new_node->right_ = RecurseClone(node->right_, new_node);
  return new_node;
}

template <typename Key, typename Val, typename Compare>
BinaryTree<Key, Val, Compare>::BinaryTree(
    BinaryTree<Key, Val, Compare> &&other) {
  root_ptr_ = other.root_ptr_;
  end_node_.parent_ = other.end_node_.parent_;
  other.root_ptr_ = nullptr;
}

template <typename Key, typename Val, typename Compare>
BinaryTree<Key, Val, Compare> &BinaryTree<Key, Val, Compare>::operator=(
    BinaryTree<Key, Val, Compare> &&other) {
  if (this == &other) {
    return *this;
  }
  RecurseDelete(this->root_ptr_);
  root_ptr_ = other.root_ptr_;
  end_node_.parent_ = other.end_node_.parent_;
  other.root_ptr_ = nullptr;
  return *this;
}

template <typename Key, typename Val, typename Compare>
BinaryTree<Key, Val, Compare>::~BinaryTree() {
  RecurseDelete(root_ptr_);
}