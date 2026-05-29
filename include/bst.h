// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <utility>
#include <algorithm>

template <typename T>
class BST {
 private:
  struct Node {
    T value;
    int count;
    Node* left;
    Node* right;

    explicit Node(const T& val)
        : value(val), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  Node* insertNode(Node* node, const T& val) {
    if (node == nullptr) {
      return new Node(val);
    }

    if (val < node->value) {
      node->left = insertNode(node->left, val);
    } else if (val > node->value) {
      node->right = insertNode(node->right, val);
    } else {
      node->count++;
    }

    return node;
  }

  int computeHeight(Node* node) const {
    if (node == nullptr) {
      return -1;
    }

    int leftHeight = computeHeight(node->left);
    int rightHeight = computeHeight(node->right);

    return 1 + std::max(leftHeight, rightHeight);
  }

  Node* searchNode(Node* node, const T& val) const {
    if (node == nullptr || node->value == val) {
      return node;
    }

    if (val < node->value) {
      return searchNode(node->left, val);
    }

    return searchNode(node->right, val);
  }

  void traverse(Node* node, std::vector<std::pair<T, int>>& items) const {
    if (node == nullptr) {
      return;
    }

    traverse(node->left, items);
    items.push_back(std::make_pair(node->value, node->count));
    traverse(node->right, items);
  }

  void clearTree(Node* node) {
    if (node == nullptr) {
      return;
    }

    clearTree(node->left);
    clearTree(node->right);
    delete node;
  }

 public:
  BST() : root(nullptr) {}

  ~BST() {
    clearTree(root);
  }

  void insert(const T& val) {
    root = insertNode(root, val);
  }

  int depth() const {
    return computeHeight(root);
  }

  int search(const T& val) const {
    Node* result = searchNode(root, val);
    if (result == nullptr) {
      return 0;
    }
    return result->count;
  }

  void collectInfo(std::vector<std::pair<T, int>>& items) const {
    traverse(root, items);
  }

  std::vector<std::pair<T, int>> getAllElements() const {
    std::vector<std::pair<T, int>> result;
    traverse(root, result);
    return result;
  }

  bool empty() const {
    return root == nullptr;
  }
};

#endif  // INCLUDE_BST_H_
