#include "./red-black-tree.h"

template <typename Key, typename Val, typename Compare>
void BinaryTree<Key, Val, Compare>::generateDotFile(Node *root,
                                                    std::ofstream &file) {
  if (!root) return;
  if (root->left_) {
    file << "    " << root->key_ << " -> " << root->left_->key_
         << " [color=" << (root->left_->color_ == 0 ? "red" : "black")
         << "];\n";
    generateDotFile(root->left_, file);
  }
  if (root->right_) {
    file << "    " << root->key_ << " -> " << root->right_->key_
         << " [color=" << (root->right_->color_ == 0 ? "red" : "black")
         << "];\n";
    generateDotFile(root->right_, file);
  }
}

template <typename Key, typename Val, typename Compare>
void BinaryTree<Key, Val, Compare>::exportToDot(Node *root) {
  std::ofstream file("rbtree.dot");
  file << "digraph G {\n";
  file << "    node [fontcolor=black];\n";
  generateDotFile(root, file);
  file << "}\n";
  file.close();
}