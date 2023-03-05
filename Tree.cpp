#include "Tree.h"

using namespace s21;

Tree::Tree() {}

Tree::~Tree() { freeTree(); }

void Tree::deleteNode(Node *node) {
  // if (node->left != nullptr) {
  //   delete node->left;
  // }
  // if (node->right != nullptr) {
  //   delete node->right;
  // }

  if (node != nullptr) {
    delete node;
  }
}

Tree::Node *Tree::initializeNode(Node *node, Node *nodeParent, Node *nodeLeft,
                                 Node *nodeRight, int value, NodeColor color) {
  node = new Node;
  node->data = value;
  node->parent = nodeParent;
  node->left = nodeLeft;
  node->right = nodeRight;
  node->color = color;
  return node;
}

void Tree::insert(int key) {
  Node *node = initializeNode(node, nullptr, nullptr, nullptr, key, RED);

  Node *y = nullptr;
  Node *x = this->root;
  bool is_exist = false;
  while (x != nullptr) {
    y = x;
    if (x->data == node->data) {
      is_exist = true;
      break;
    }
    if (node->data < x->data) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  if (!is_exist) {
    node->parent = y;
    if (y == nullptr) {
      root = node;
    } else if (node->data < y->data) {
      y->left = node;
    } else {
      y->right = node;
    }
    insertRebalance(node);
  } else {
    deleteNode(node);
  }
}

Tree::Node *Tree::findGrandparent(Node *node) {
  Node *grandparent = NULL;
  if (node != NULL && node->parent != NULL) {
    grandparent = node->parent->parent;
  }
  return grandparent;
}

Tree::Node *Tree::findUncle(Node *node) {
  Node *grandparent = findGrandparent(node);
  Node *uncle = NULL;
  if (grandparent != NULL) {
    if (node->parent = grandparent->left) {
      uncle = grandparent->right;
    } else {
      uncle = grandparent->left;
    }
  }
  return uncle;
}

void Tree::insertRebalance(Node *node) {
  if (node->parent == nullptr) {
    node->color = BLACK;
  } else {
    if (node->parent->color == RED) {
      std::cout << "dfdfd\n";
      uncleAndParentRed(node);
    }
  }
}

void Tree::uncleAndParentRed(Node *node) {
  Node *uncle = findUncle(node);
  Node *grandparent = NULL;
  if ((uncle != NULL) && (uncle->color == RED)) {
    node->parent->color = BLACK;
    uncle->color = BLACK;
    grandparent = findGrandparent(node);
    grandparent->color = RED;
    insertRebalance(grandparent);
  } else {
    rotateTreeRightChild(node);
  }
}

void Tree::rotateTreeRightChild(Node *node) {
  Node *grandparent = findGrandparent(node);
  if (grandparent != nullptr) {
    if ((node == node->parent->right) && (node->parent == grandparent->left)) {
      rotateTreeLeft(node->parent);
      node = node->left;
    } else if ((node == node->parent->left) &&
               (node->parent == grandparent->right)) {
      rotateTreeRight(node->parent);
      node = node->right;
    }
    rotateTreeLeftChild(node);
  }
}

void Tree::rotateTreeLeftChild(Node *node) {
  Node *grandparent = findGrandparent(node);
  if (grandparent != nullptr) {
    node->parent->color = BLACK;
    grandparent->color = RED;
    if ((node == node->parent->left) && (node->parent == grandparent->left)) {
      rotateTreeRight(grandparent);
    } else if ((node == node->parent->left) &&
               (node->parent == grandparent->right)) {
      rotateTreeLeft(grandparent);
    }
  }
}

void Tree::rotateTreeLeft(Node *node) {
  Node *pivot = node->right;
  pivot->parent = node->parent;
  if (node->parent != nullptr) {
    if (node->parent->left == node) {
      node->parent->left = pivot;
    } else {
      node->parent->right = pivot;
    }
  }

  node->right = pivot->left;
  if (pivot->left != nullptr) {
    pivot->left->parent = node;
  }

  node->parent = pivot;
  pivot->left = node;
}

void Tree::rotateTreeRight(Node *node) {
  Node *pivot = node->left;
  pivot->parent = node->parent;
  if (node->parent != nullptr) {
    if (node->parent->left == node) {
      node->parent->left = pivot;
    } else {
      node->parent->right = pivot;
    }
  }

  node->left = pivot->right;
  if (pivot->right != nullptr) {
    pivot->right->parent = node;
  }
  node->parent = pivot;
  pivot->right = node;
}

void Tree::printTree() {
  if (root != nullptr) {
    std::string temp = "";
    printHelper(root, temp, true);
  }
}

void Tree::printHelper(Node *printNode, std::string indent, bool isRight) {
  if (printNode != nullptr) {
    std::cout << indent;
    if (isRight) {
      std::cout << "R----";
      indent += "   ";
    } else {
      std::cout << "L----";
      indent += "|  ";
    }

    std::string sColor = printNode->color ? "RED" : "BLACK";
    std::cout << printNode->data << "(" << sColor << ")" << std::endl;
    printHelper(printNode->left, indent, false);
    printHelper(printNode->right, indent, true);
  }
}

void Tree::freeTree() {
  Node *temp = root;
  while ((root->left != nullptr || root->right != nullptr)) {
    if (temp->left != nullptr) {
      temp = temp->left;
    } else if (temp->left == nullptr && temp->right != nullptr) {
      temp = temp->right;
    } else {
      std::cerr << "jojho\n" << temp->data << "\n";
      Node *temp_parent = temp->parent;
      bool is_left_child = true;
      if (temp_parent->right == temp) {
        is_left_child = false;
      }
      delete temp;
      temp = temp_parent;
      if (is_left_child) {
        temp->left = nullptr;
      } else {
        temp->right = nullptr;
      }
    }
  }
  delete root;
}