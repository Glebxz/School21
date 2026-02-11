#include "./red-black-tree.h"

template <typename Key, typename Val, typename Compare>
class BinaryTree<Key, Val, Compare>::Node {
 public:
  key_type key_;
  value_type value_;
  Color color_ = Red;
  Node *parent_ = nullptr;
  Node *left_ = nullptr;
  Node *right_ = nullptr;
  Node(key_type key, value_type value) : key_{key}, value_{value} {}
  Node() {}
  friend class BinaryTreeIterator;
};

template <typename Key, typename Val, typename Compare>
typename BinaryTree<Key, Val, Compare>::iterator
BinaryTree<Key, Val, Compare>::begin() {
  iterator iter = end();
  iter.current_node_ptr_ = GetMin(root_ptr_);
  if (iter.current_node_ptr_ == nullptr) {
    iter.current_node_ptr_ = iter.end_node_ptr_;
  }
  return iter;
}

template <typename Key, typename Val, typename Compare>
typename BinaryTree<Key, Val, Compare>::iterator
BinaryTree<Key, Val, Compare>::end() {
  end_node_.parent_ = GetMax(root_ptr_);
  iterator iter;
  iter.current_node_ptr_ = &end_node_;
  iter.end_node_ptr_ = &end_node_;
  return iter;
}

template <typename Key, typename Val, typename Compare>
bool BinaryTree<Key, Val, Compare>::empty() {
  return root_ptr_ == nullptr ? true : false;
}

template <typename Key, typename Val, typename Compare>
typename BinaryTree<Key, Val, Compare>::size_type
BinaryTree<Key, Val, Compare>::size() {
  return CheckSize(root_ptr_);
}

template <typename Key, typename Val, typename Compare>
typename BinaryTree<Key, Val, Compare>::size_type
BinaryTree<Key, Val, Compare>::CheckSize(Node *node) {
  if (node == nullptr) {
    return 0;
  }
  return 1 + CheckSize(node->left_) + CheckSize(node->right_);
}

template <typename Key, typename Val, typename Compare>
typename BinaryTree<Key, Val, Compare>::size_type
BinaryTree<Key, Val, Compare>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(Node);
}

template <typename Key, typename Val, typename Compare>
void BinaryTree<Key, Val, Compare>::clear() {
  RecurseDelete(root_ptr_);
  root_ptr_ = nullptr;
  end_node_.parent_ = nullptr;
}

template <typename Key, typename Val, typename Compare>
void BinaryTree<Key, Val, Compare>::RecurseDelete(Node *node) {
  if (node == nullptr) {
    return;
  }
  RecurseDelete(node->left_);
  RecurseDelete(node->right_);
  delete node;
}

template <typename Key, typename Val, typename Compare>
void BinaryTree<Key, Val, Compare>::swap(BinaryTree<Key, Val, Compare> &other) {
  std::swap(this->root_ptr_, other.root_ptr_);
  Node tmp = this->end_node_;
  this->end_node_.parent_ = other.end_node_.parent_;
  other.end_node_.parent_ = tmp.parent_;
}

template <typename Key, typename Val, typename Compare>
typename BinaryTree<Key, Val, Compare>::size_type
BinaryTree<Key, Val, Compare>::count(const Key &key) {
  size_type count = 0;
  for (iterator iter = this->begin(); iter != this->end(); ++iter) {
    count += *iter == key ? 1 : 0;
  }
  return count;
}

template <typename Key, typename Val, typename Compare>
typename BinaryTree<Key, Val, Compare>::iterator
BinaryTree<Key, Val, Compare>::find(const key_type &key) {
  iterator iter = end();
  iter.current_node_ptr_ = root_ptr_;
  Compare comparator;
  while (iter.current_node_ptr_ != nullptr) {
    if (!comparator(key, iter.current_node_ptr_->key_) &&
        !comparator(iter.current_node_ptr_->key_, key)) {
      break;
    }
    if (comparator(key, iter.current_node_ptr_->key_)) {
      iter.current_node_ptr_ = iter.current_node_ptr_->left_;
    } else {
      iter.current_node_ptr_ = iter.current_node_ptr_->right_;
    }
  }
  if (iter.current_node_ptr_ == nullptr) {
    iter.current_node_ptr_ = &end_node_;
  }
  return iter;
}

template <typename Key, typename Val, typename Compare>
bool BinaryTree<Key, Val, Compare>::contains(const key_type &key) {
  return find(key) != end();
}
template <typename Key, typename Val, typename Compare>
std::pair<typename BinaryTree<Key, Val, Compare>::iterator,
          typename BinaryTree<Key, Val, Compare>::iterator>
BinaryTree<Key, Val, Compare>::equal_range(const Key &key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
}

template <typename Key, typename Val, typename Compare>
typename BinaryTree<Key, Val, Compare>::iterator
BinaryTree<Key, Val, Compare>::lower_bound(const Key &key) {
  iterator iter = end();
  Node *current = root_ptr_;
  Node *result = nullptr;
  Compare comparator;
  while (current != nullptr) {
    if (comparator(current->key_, key)) {
      current = current->right_;
    } else {
      result = current;
      current = current->left_;
    }
  }
  if (result != nullptr) {
    iter.current_node_ptr_ = result;
  }
  return iter;
}

template <typename Key, typename Val, typename Compare>
typename BinaryTree<Key, Val, Compare>::iterator
BinaryTree<Key, Val, Compare>::upper_bound(const Key &key) {
  iterator iter = end();
  Node *current = root_ptr_;
  Node *result = nullptr;
  while (current != nullptr) {
    if (CompareKeys(current->key_, key) == 1) {
      result = current;
      current = current->left_;
    } else {
      current = current->right_;
    }
  }
  if (result != nullptr) {
    iter.current_node_ptr_ = result;
  }
  return iter;
}

template <typename Key, typename Val, typename Compare>
typename BinaryTree<Key, Val, Compare>::Node *
BinaryTree<Key, Val, Compare>::GetMin(Node *node) {
  Node *begin_ptr = node;
  if (begin_ptr != nullptr) {
    while (begin_ptr->left_ != nullptr) {
      begin_ptr = begin_ptr->left_;
    }
  }
  return begin_ptr;
}

template <typename Key, typename Val, typename Compare>
typename BinaryTree<Key, Val, Compare>::Node *
BinaryTree<Key, Val, Compare>::GetMax(Node *node) {
  Node *begin_ptr = node;
  if (begin_ptr != nullptr) {
    while (begin_ptr->right_ != nullptr) {
      begin_ptr = begin_ptr->right_;
    }
  }
  return begin_ptr;
}
