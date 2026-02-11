#include "./red-black-tree.h"

template <typename Key, typename Val, typename Compare>
std::pair<typename BinaryTree<Key, Val, Compare>::iterator, bool>
BinaryTree<Key, Val, Compare>::InsertUnique(const key_type &key,
                                            const value_type &value) {
  Node *new_node_ptr = new Node(key, value);
  bool check_insert = true;
  if (root_ptr_ != nullptr) {
    Node *current_node_ptr = root_ptr_;
    while (1) {
      if (CompareKeys(new_node_ptr->key_, current_node_ptr->key_) == -1) {
        if (current_node_ptr->left_ == nullptr) {
          current_node_ptr->left_ = new_node_ptr;
          new_node_ptr->parent_ = current_node_ptr;
          BalanceTree(new_node_ptr);
          break;
        } else {
          current_node_ptr = current_node_ptr->left_;
        }
      } else if (CompareKeys(new_node_ptr->key_, current_node_ptr->key_) == 1) {
        if (current_node_ptr->right_ == nullptr) {
          current_node_ptr->right_ = new_node_ptr;
          new_node_ptr->parent_ = current_node_ptr;
          BalanceTree(new_node_ptr);
          break;
        } else {
          current_node_ptr = current_node_ptr->right_;
        }
      } else {
        delete new_node_ptr;
        new_node_ptr = current_node_ptr;
        check_insert = false;
        break;
      }
    }
  } else {
    root_ptr_ = new_node_ptr;
    root_ptr_->color_ = Black;
  }
  iterator iter = end();
  iter.current_node_ptr_ = new_node_ptr;
  std::pair rtrn(iter, check_insert);
  return rtrn;
}

template <typename Key, typename Val, typename Compare>
typename BinaryTree<Key, Val, Compare>::iterator
BinaryTree<Key, Val, Compare>::InsertEqual(const key_type &key,
                                           const value_type &value) {
  Node *new_node_ptr = new Node(key, value);
  if (root_ptr_ != nullptr) {
    Node *current_node_ptr = root_ptr_;
    Compare comparator;
    while (1) {
      if (comparator(new_node_ptr->key_, current_node_ptr->key_)) {
        if (current_node_ptr->left_ == nullptr) {
          current_node_ptr->left_ = new_node_ptr;
          break;
        } else {
          current_node_ptr = current_node_ptr->left_;
        }
      } else {
        if (current_node_ptr->right_ == nullptr) {
          current_node_ptr->right_ = new_node_ptr;
          break;
        } else {
          current_node_ptr = current_node_ptr->right_;
        }
      }
    }
    new_node_ptr->parent_ = current_node_ptr;
  } else {
    root_ptr_ = new_node_ptr;
    root_ptr_->color_ = Black;
  }
  BalanceTree(new_node_ptr);
  iterator iter = end();
  iter.current_node_ptr_ = new_node_ptr;
  return iter;
}

template <typename Key, typename Val, typename Compare>
int BinaryTree<Key, Val, Compare>::CompareKeys(const key_type &key1,
                                               const key_type &key2) {
  Compare comparator;
  if (!comparator(key1, key2) && !comparator(key2, key1)) {
    return 0;
  } else if (comparator(key1, key2)) {
    return -1;
  } else {
    return 1;
  }
}

template <typename Key, typename Val, typename Compare>
void BinaryTree<Key, Val, Compare>::BalanceTree(Node *node) {
  if (node == root_ptr_) {
    node->color_ = Black;
    return;
  } else if (node->parent_->color_ == Black) {
    return;
  } else if (node->parent_->parent_->left_ != nullptr &&
             node->parent_->parent_->right_ != nullptr &&
             node->parent_->parent_->left_->color_ == Red &&
             node->parent_->parent_->right_->color_ == Red) {
    SwapColors(node);
    BalanceTree(node->parent_->parent_);
  } else {
    if (node->parent_ == node->parent_->parent_->left_) {
      if (node == node->parent_->left_) {
        RightRoute(node->parent_);
      } else {
        LeftRoute(node);
        RightRoute(node);
      }
    } else {
      if (node == node->parent_->right_) {
        LeftRoute(node->parent_);
      } else {
        RightRoute(node);
        LeftRoute(node);
      }
    }
  }
}

template <typename Key, typename Val, typename Compare>
void BinaryTree<Key, Val, Compare>::SwapColors(Node *node) {
  node->parent_->parent_->color_ = Red;
  if (node->parent_->parent_->right_ != nullptr) {
    node->parent_->parent_->right_->color_ = Black;
  }
  if (node->parent_->parent_->left_ != nullptr) {
    node->parent_->parent_->left_->color_ = Black;
  }
}

template <typename Key, typename Val, typename Compare>
void BinaryTree<Key, Val, Compare>::RightRoute(Node *node) {
  node->color_ = node->parent_->color_;
  node->parent_->color_ = Red;
  if (node->parent_->parent_ != nullptr) {
    if (node->parent_->parent_->left_ == node->parent_) {
      node->parent_->parent_->left_ = node;
    } else {
      node->parent_->parent_->right_ = node;
    }
  } else {
    root_ptr_ = node;
  }
  node->parent_->left_ = node->right_;
  if (node->right_ != nullptr) {
    node->right_->parent_ = node->parent_;
  }
  node->right_ = node->parent_;
  node->parent_ = node->parent_->parent_;
  if (node->right_ != nullptr) {
    node->right_->parent_ = node;
  }
}

template <typename Key, typename Val, typename Compare>
void BinaryTree<Key, Val, Compare>::LeftRoute(Node *node) {
  node->color_ = node->parent_->color_;
  node->parent_->color_ = Red;
  if (node->parent_->parent_ != nullptr) {
    if (node->parent_->parent_->right_ == node->parent_) {
      node->parent_->parent_->right_ = node;
    } else {
      node->parent_->parent_->left_ = node;
    }
  } else {
    root_ptr_ = node;
  }
  node->parent_->right_ = node->left_;
  if (node->left_ != nullptr) {
    node->left_->parent_ = node->parent_;
  }
  node->left_ = node->parent_;
  node->parent_ = node->parent_->parent_;
  if (node->left_ != nullptr) {
    node->left_->parent_ = node;
  }
}
