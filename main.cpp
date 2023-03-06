#include "Tree.h"

using namespace s21;

// #include <set>
// #include <iostream>

int main() {
  Tree tree;
  tree.insert(100);
  tree.insert(56);
  tree.insert(100);
  tree.insert(1009);
  tree.insert(12);
  tree.insert(3);
  tree.insert(55);
  tree.insert(5);

  tree.erase(3);
    // tree.insert(3);
  // tree.printTree();
}