#include "./red-black-tree.h"

template <typename Key, typename Val, typename Compare>
class BinaryTree<Key, Val, Compare>::BinaryTreeConstIterator {
 private:
  Node *current_node_ptr_ = nullptr;
  Node *end_node_ptr_ = nullptr;

 public:
  const value_type &operator*();
  const_iterator &operator++();
  const_iterator &operator--();
  bool operator==(const const_iterator &iter) const;
  bool operator!=(const const_iterator &iter) const;
  friend class BinaryTree;
};

template <typename Key, typename Val, typename Compare>
bool BinaryTree<Key, Val, Compare>::BinaryTreeConstIterator::operator==(
    const const_iterator &iter) const {
  return this->current_node_ptr_ == iter.current_node_ptr_;
}

template <typename Key, typename Val, typename Compare>
bool BinaryTree<Key, Val, Compare>::BinaryTreeConstIterator::operator!=(
    const const_iterator &iter) const {
  return this->current_node_ptr_ != iter.current_node_ptr_;
}

template <typename Key, typename Val, typename Compare>
const typename BinaryTree<Key, Val, Compare>::value_type &
BinaryTree<Key, Val, Compare>::BinaryTreeConstIterator::operator*() {
  const value_type &rtrn_value = current_node_ptr_->value_;
  return rtrn_value;
}

template <typename Key, typename Val, typename Compare>
typename BinaryTree<Key, Val, Compare>::const_iterator &
BinaryTree<Key, Val, Compare>::BinaryTreeConstIterator::operator++() {
  if (current_node_ptr_ != nullptr && current_node_ptr_ != end_node_ptr_) {
    if (current_node_ptr_->right_ != nullptr) {
      current_node_ptr_ = current_node_ptr_->right_;
      while (current_node_ptr_->left_ != nullptr) {
        current_node_ptr_ = current_node_ptr_->left_;
      }
    } else {
      while (current_node_ptr_->parent_ != nullptr &&
             current_node_ptr_ == current_node_ptr_->parent_->right_) {
        current_node_ptr_ = current_node_ptr_->parent_;
      }
      current_node_ptr_ = current_node_ptr_->parent_;
    }
  }
  if (current_node_ptr_ == nullptr) {
    current_node_ptr_ = end_node_ptr_;
  }
  return *this;
}

template <typename Key, typename Val, typename Compare>
typename BinaryTree<Key, Val, Compare>::const_iterator &
BinaryTree<Key, Val, Compare>::BinaryTreeConstIterator::operator--() {
  if (current_node_ptr_ != nullptr) {
    if (current_node_ptr_->left_ != nullptr) {
      current_node_ptr_ = current_node_ptr_->left_;
      while (current_node_ptr_->right_ != nullptr) {
        current_node_ptr_ = current_node_ptr_->right_;
      }
    } else {
      while (current_node_ptr_->parent_ != nullptr &&
             current_node_ptr_ == current_node_ptr_->parent_->left_) {
        current_node_ptr_ = current_node_ptr_->parent_;
      }
      current_node_ptr_ = current_node_ptr_->parent_;
    }
  }
  return *this;
}
