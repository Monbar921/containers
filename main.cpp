// #include "SetInterface.h"
// #include "Tree.h"
// #include "Tree.cpp"
#include "s21_set.h"
#include "s21_set.cpp"

using namespace s21;

#include <set>
// #include <iostream>

int main() {

  // std::set<int> df;
  // df.insert(100);
  // df.insert(3);
  // df.clear();
  // std::cout << df.size() << "\n";


  s21_set<int> ddd;

  std::cout << ddd.size() << "\n";
    std::cout << ddd.empty() << "\n";
  ddd.insert(100);
  ddd.clear();
  // ddd.erase(100);
    std::cout << ddd.size() << "\n";
    std::cout << ddd.empty() << "\n";

  // Tree<int> tree;
  // // // tree.set(12);
  // // // std::cout << tree.max<int>(1, 2) << "\n";
  // tree.insert(100);
  // tree.erase(100);
  // tree.insert(56);
  // tree.insert(100);
  // tree.insert(1009);
  // tree.insert(12);
  // tree.insert(3);
  // tree.insert(55);
  // // // tree.insert(5);

  // // // tree.erase(3);
  // // // tree.erase(12);
  // // // tree.erase(55);
  // // tree.erase(100);
  // // // tree.erase(1009);
  // tree.printTree();
  // std::cout << tree.empty() << "\n";

//   std::set<int> aa;
//   aa.insert(100);
//     aa.insert(100);
//       aa.insert(100);
// aa.erase();
//       std::cout << aa.size();
}