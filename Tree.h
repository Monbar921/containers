#ifndef SRC_TREE_H_
#define SRC_TREE_H_

#include <iostream>
// #include <cstring>

namespace s21 {
template<class T>
class Tree {
  enum NodeColor { BLACK, RED };

  struct Node {
    T data;
    Node* parent;
    Node* left;
    Node* right;
    NodeColor color;
  };

 public:
  Tree();
  ~Tree();

  void insert(T key);
  void erase(T key);
  size_t size();
  bool empty();


  void printTree();

 private:
  // data members
  size_t setSize = 0;
  Node* root = nullptr;

  // help functions
  Node* initializeNode(Node* node, Node* nodeParent, Node* nodeLeft,
                       Node* nodeRight, int value, NodeColor color);

  void insertRebalance(Node* node);
  void deleteNode(Node** node);

  void nodeIsRoot(Node* node);
  void uncleAndParentRed(Node* node);
  Node* findGrandparent(Node* node);
  Node* findUncle(Node* node);
  Node* findSibling(Node *n);
  void rotateTreeRightChild(Node* node);
  void rotateTreeLeftChild(Node* node);
  void rotateTreeLeft(Node* node);
  void rotateTreeRight(Node* node);
  void transplantNodes(Node* whatReplace, Node* toReplace);
  void eraseFunction(Node* findNode);
  Node* findMax(Node *node);
  void changeNodes(Node* findNode, Node* child);
  void deleteRebalance(Node* node);
  void deleteCase1(Node* node);
  void deleteCase2(Node* node);
  void deleteCase3(Node* node);
  void deleteCase4(Node* node);
  void deleteCase5(Node* node);

  void videoRebalance(Node *findNode);

  void printHelper(Node* printNode, std::string indent, bool isRight);
  void freeTree();

};

}  // namespace s21

#endif  // SRC_TREE_H_