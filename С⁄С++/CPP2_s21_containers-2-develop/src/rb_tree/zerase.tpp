#include "./red-black-tree.h"

template <typename Key, typename Val, typename Compare>
void BinaryTree<Key, Val, Compare>::erase(iterator pos) {
  Node *node = pos.current_node_ptr_;
  if (node != nullptr && node != &end_node_) {
    if (node->left_ != nullptr && node->right_ != nullptr) {
      Node *node_right_min = GetMin(node->right_);
      NodeSwap(node, node_right_min);
    }
    if (node->color_ == Black &&
        (node->left_ == nullptr || node->right_ == nullptr) &&
        (node->left_ != nullptr || node->right_ != nullptr)) {
      BlackOneRedKidDelete(node);
    } else {
      if (node->color_ == Black && node->left_ == nullptr &&
          node->right_ == nullptr) {
        BlackZeroKidDelete(node);
      }
      if (node != root_ptr_) {
        if (node->parent_->left_ == node) {
          node->parent_->left_ = nullptr;
        } else {
          node->parent_->right_ = nullptr;
        }
      } else {
        root_ptr_ = nullptr;
      }
    }
    delete node;
  }
}

template <typename Key, typename Val, typename Compare>
void BinaryTree<Key, Val, Compare>::BlackOneRedKidDelete(Node *node) {
  if (node == root_ptr_) {
    root_ptr_ = node->left_ != nullptr ? node->left_ : node->right_;
    root_ptr_->parent_ = nullptr;
    root_ptr_->color_ = Black;
  } else if (node->parent_->left_ == node) {
    if (node->left_ != nullptr) {
      node->parent_->left_ = node->left_;
      node->left_->parent_ = node->parent_;
      node->left_->color_ = Black;
    } else {
      node->parent_->left_ = node->right_;
      node->right_->parent_ = node->parent_;
      node->right_->color_ = Black;
    }
  } else {
    if (node->right_ != nullptr) {
      node->parent_->right_ = node->right_;
      node->right_->parent_ = node->parent_;
      node->right_->color_ = Black;
    } else {
      node->parent_->right_ = node->left_;
      node->left_->parent_ = node->parent_;
      node->left_->color_ = Black;
    }
  }
}

template <typename Key, typename Val, typename Compare>
void BinaryTree<Key, Val, Compare>::BlackZeroKidDelete(Node *node) {
  if (node == root_ptr_) return;
  if (GetBrother(node) == nullptr ||
      GetBrother(node)->color_ == Black) {  // Брат черный
    if ((GetBrother(node)->left_ == nullptr ||
         GetBrother(node)->left_->color_ == Black) &&
        (GetBrother(node)->right_ == nullptr ||
         GetBrother(node)->right_->color_ == Black)) {
      // У черного брата оба ребенка черные
      GetBrother(node)->color_ = Red;
      if (node->parent_ != root_ptr_ && node->parent_->color_ == Black) {
        BlackZeroKidDelete(node->parent_);
      } else if (node != root_ptr_) {
        node->parent_->color_ = Black;
      }
    } else if (node == node->parent_->right_) {
      // правая нода, у черного брата один из детей красный
      if (node->parent_->left_->left_ != nullptr &&
          node->parent_->left_->left_->color_ == Red) {
        node->parent_->left_->left_->color_ = Black;
        RightRoute(node->parent_->left_);
      } else {
        LeftRoute(node->parent_->left_->right_);
        node->parent_->left_->left_->color_ = Black;
        RightRoute(node->parent_->left_);
      }
      node->parent_->color_ = Black;
    } else {
      // левая нода, у черного брата один из детей красный
      if (node->parent_->right_->right_ != nullptr &&
          node->parent_->right_->right_->color_ == Red) {
        node->parent_->right_->right_->color_ = Black;
        LeftRoute(node->parent_->right_);
      } else {
        RightRoute(node->parent_->right_->left_);
        node->parent_->right_->right_->color_ = Black;
        LeftRoute(node->parent_->right_);
      }
      node->parent_->color_ = Black;
    }
  } else {  // Брат красный
    if (node == node->parent_->right_) {
      RightRoute(node->parent_->left_);
    } else {
      LeftRoute(node->parent_->right_);
    }
    BlackZeroKidDelete(node);
  }
}

template <typename Key, typename Val, typename Compare>
void BinaryTree<Key, Val, Compare>::NodeSwap(Node *node_deleted,
                                             Node *node_new) {
  if (node_deleted->parent_ != nullptr) {
    if (node_deleted->parent_->left_ == node_deleted) {
      node_deleted->parent_->left_ = node_new;
    } else {
      node_deleted->parent_->right_ = node_new;
    }
  } else {
    root_ptr_ = node_new;
  }
  if (node_new->parent_->left_ == node_new) {
    node_new->parent_->left_ = node_deleted;
  } else {
    node_new->parent_->right_ = node_deleted;
  }
  std::swap(node_deleted->parent_, node_new->parent_);
  std::swap(node_deleted->left_, node_new->left_);
  std::swap(node_deleted->right_, node_new->right_);
  if (node_new != root_ptr_) {
    std::swap(node_deleted->color_, node_new->color_);
  }
  if (node_deleted->left_ != nullptr) {
    node_deleted->left_->parent_ = node_deleted;
  }
  if (node_deleted->right_ != nullptr) {
    node_deleted->right_->parent_ = node_deleted;
  }
  if (node_new->left_ != nullptr) {
    node_new->left_->parent_ = node_new;
  }
  if (node_new->right_ != nullptr) {
    node_new->right_->parent_ = node_new;
  }
}

template <typename Key, typename Val, typename Compare>
typename BinaryTree<Key, Val, Compare>::Node *&
BinaryTree<Key, Val, Compare>::GetBrother(Node *node) {
  if (node->parent_->left_ == node) {
    return node->parent_->right_;
  } else {
    return node->parent_->left_;
  }
}
