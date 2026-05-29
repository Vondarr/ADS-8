// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "bst.h"

namespace {

bool isValidChar(char ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

char toLowercase(char ch) {
  if (ch >= 'A' && ch <= 'Z') {
    return ch + ('a' - 'A');
  }
  return ch;
}

}  // namespace

void makeTree(BST<std::string>& tree, const char* source) {
  std::ifstream input(source);
  if (!input.is_open()) {
    std::cerr << "Cannot open file" << std::endl;
    return;
  }

  std::string buffer;
  char curChar;
  while (input.get(curChar)) {
    if (isValidChar(curChar)) {
      buffer.push_back(toLowercase(curChar));
    } else {
      if (!buffer.empty()) {
        tree.insert(buffer);
        buffer.clear();
      }
    }
  }
  if (!buffer.empty()) {
    tree.insert(buffer);
  }
  input.close();
}

bool compareByFreq(const std::pair<std::string, int>& a,
                   const std::pair<std::string, int>& b) {
  return a.second > b.second;
}

void printFreq(BST<std::string>& voc) {
  std::vector<std::pair<std::string, int>> items;
  voc.collectInfo(items);
  std::sort(items.begin(), items.end(), compareByFreq);

  std::ofstream output("result/freq.txt");
  for (const auto& entry : items) {
    if (output.is_open()) {
      output << entry.first << " - " << entry.second << std::endl;
    }
    std::cout << entry.first << " - " << entry.second << std::endl;
  }
  output.close();
}
