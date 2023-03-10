#ifndef SRC_TREE_H_
#define SRC_TREE_H_

#include <iostream>
// #include <cstring>

namespace s21 {
class Tree {
  enum NodeColor { BLACK, RED };

  struct Node {
    int data;
    Node* parent;
    Node* left;
    Node* right;
    NodeColor color;
  };

 public:
  Tree();
  ~Tree();

  void insert(int key);
  void printTree();

 private:
  // data members

  int heitht = 0;
  Node* root = nullptr;

  // help functions
  Node* initializeNode(Node* node, Node* nodeParent, Node* nodeLeft,
                       Node* nodeRight, int value, NodeColor color);

  void insertRebalance(Node* node);
  void deleteNode(Node* node);

  void nodeIsRoot(Node* node);
  void uncleAndParentRed(Node* node);
  Node* findGrandparent(Node* node);
  Node* findUncle(Node* node);
  void rotateTreeRightChild(Node* node);
  void rotateTreeLeftChild(Node* node);
  void rotateTreeLeft(Node* node);
  void rotateTreeRight(Node* node);

  void printHelper(Node* printNode, std::string indent, bool isRight);
};
}  // namespace s21

#endif  // SRC_TREE_H_