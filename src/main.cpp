// Copyright 2021 NNTU-CS
#include <string>
#include "bst.h"

void makeTree(BST<std::string>&, const char*);
void printFreq(BST<std::string>&);

int main() {
  BST<std::string> vocabulary;
  makeTree(vocabulary, "src/war_peace.txt");
  printFreq(vocabulary);
  return 0;
}
