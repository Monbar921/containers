#include "Tree.h"

using namespace s21;

template <class T>
Tree<T>::Tree() {}

template <class T>
Tree<T>::~Tree() {

  freeTree();
  
}

template <class T>
typename Tree<T>::Node *Tree<T>::initializeNode(Node *node, Node *nodeParent,
                                                Node *nodeLeft, Node *nodeRight,
                                                int value, NodeColor color) {
  node = new Node;
  node->data = value;
  node->parent = nodeParent;
  node->left = nodeLeft;
  node->right = nodeRight;
  node->color = color;
  return node;
}

template <class T>
void Tree<T>::insert(T key) {
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
    treeSize++;
  } else {
    if (node != nullptr) {
      delete node;
    }
  }
}

template <class T>
typename Tree<T>::Node *Tree<T>::findGrandparent(Node *node) {
  Node *grandparent = nullptr;
  if (node != nullptr && node->parent != nullptr) {
    grandparent = node->parent->parent;
  }
  return grandparent;
}

template <class T>
typename Tree<T>::Node *Tree<T>::findUncle(Node *node) {
  Node *grandparent = findGrandparent(node);
  Node *uncle = nullptr;
  if (grandparent != nullptr) {
    if (node->parent == grandparent->left) {
      uncle = grandparent->right;
    } else {
      uncle = grandparent->left;
    }
  }
  return uncle;
}

template <class T>
typename Tree<T>::Node *Tree<T>::findSibling(Node *node) {
  Node *output = nullptr;
  if (node == node->parent->left) {
    output = node->parent->right;
  } else {
    output = node->parent->left;
  }
  return output;
}

template <class T>
void Tree<T>::insertRebalance(Node *node) {
  if (node->parent == nullptr) {
    node->color = BLACK;
  } else {
    if (node->parent->color == RED) {
      uncleAndParentRed(node);
    }
  }
}

template <class T>
void Tree<T>::uncleAndParentRed(Node *node) {
  Node *uncle = findUncle(node);
  Node *grandparent = nullptr;
  if ((uncle != nullptr) && (uncle->color == RED)) {
    node->parent->color = BLACK;
    uncle->color = BLACK;
    grandparent = findGrandparent(node);
    grandparent->color = RED;
    insertRebalance(grandparent);
  } else {
    rotateTreeRightChild(node);
  }
}

template <class T>
void Tree<T>::rotateTreeRightChild(Node *node) {
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

template <class T>
void Tree<T>::rotateTreeLeftChild(Node *node) {
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

template <class T>
void Tree<T>::rotateTreeLeft(Node *node) {
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

template <class T>
void Tree<T>::rotateTreeRight(Node *node) {
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

template <class T>
void Tree<T>::erase(T key) {
  if (root != nullptr) {
    Node *tempTree = root;
    Node *findNode = nullptr;
    while (tempTree != nullptr) {
      if (tempTree->data == key) {
        findNode = tempTree;
        break;
      }
      if (tempTree->data <= key) {
        tempTree = tempTree->right;
      } else {
        tempTree = tempTree->left;
      }
    }

    if (findNode != nullptr) {
      eraseFunction(findNode);
      treeSize--;
      if(treeSize == 0) {
        root = nullptr;
      }
    }
  }
}

template <class T>
void Tree<T>::deleteRebalance(Node *node) {
  if (node->parent != nullptr) {
    deleteCase1(node);
  }
}

template <class T>
void Tree<T>::deleteCase1(Node *node) {
  Node *sibling = findSibling(node);

  if (sibling->color == RED) {
    node->parent->color = RED;
    sibling->color = BLACK;
    if (node == node->parent->left) {
      rotateTreeLeft(node->parent);
    } else {
      rotateTreeRight(node->parent);
    }
  }

  deleteCase2(node);
}

template <class T>
void Tree<T>::deleteCase2(Node *node) {
  Node *sibling = findSibling(node);
  if (node->parent->color == BLACK && sibling->color == BLACK &&
      ((sibling->left == nullptr || sibling->left->color == BLACK) &&
       (sibling->right == nullptr || sibling->right->color == BLACK))) {
    sibling->color = RED;
    deleteRebalance(node->parent);
  } else {
    deleteCase3(node);
  }
}

template <class T>
void Tree<T>::deleteCase3(Node *node) {
  Node *sibling = findSibling(node);

  if (node->parent->color == RED && sibling->color == BLACK &&
      (sibling->left == nullptr || sibling->left->color == BLACK) &&
      (sibling->right == nullptr || sibling->right->color == BLACK)) {
    sibling->color = RED;
    node->parent->color = BLACK;
  } else {
    deleteCase4(node);
  }
}

template <class T>
void Tree<T>::deleteCase4(Node *node) {
  Node *sibling = findSibling(node);
  if (sibling->color == BLACK) {
    if (node == node->parent->left &&
        (sibling->right == nullptr || sibling->right->color == BLACK) &&
        sibling->left->color == RED) {
      sibling->color = RED;
      sibling->left->color = BLACK;
      rotateTreeRight(sibling);
    } else if (node == node->parent->right && sibling->left->color == BLACK &&
               sibling->right->color == RED) {
      sibling->color = RED;
      sibling->right->color = BLACK;
      rotateTreeLeft(sibling);
    }
  }
  deleteCase5(node);
}

template <class T>
void Tree<T>::deleteCase5(Node *node) {
  Node *sibling = findSibling(node);
  sibling->color = node->parent->color;
  node->parent->color = BLACK;
  if (node == node->parent->left) {
    sibling->right->color = BLACK;
    rotateTreeLeft(node->parent);
  } else {
    sibling->left->color = BLACK;
    rotateTreeRight(node->parent);
  }
}

template <class T>
void Tree<T>::eraseFunction(Node *findNode) {
  if (findNode->left == nullptr && findNode->right == nullptr) {
    Node *parent = findNode->parent;
    if (findNode->color == BLACK) {

      deleteRebalance(findNode);
    }
    std::cerr << findNode->data << "\n";
    if(parent == nullptr){
      deleteNode(&findNode);
    }else if (findNode == parent->left) {
      deleteNode(&findNode);
      parent->left = nullptr;
    } else {
      deleteNode(&findNode);
      parent->right = nullptr;
    }
  } else if (findNode->left == nullptr && findNode->right != nullptr) {
    changeNodes(findNode, findNode->right);
  } else if (findNode->left != nullptr && findNode->right == nullptr) {
    changeNodes(findNode, findNode->left);
  } else {
    Node *maxNode = findMax(findNode->left);
    findNode->data = maxNode->data;
    eraseFunction(maxNode);
  }
}

template <class T>
void Tree<T>::videoRebalance(Node *findNode) {}

template <class T>
void Tree<T>::changeNodes(Node *findNode, Node *child) {
  Node *findParent = findNode->parent;
  if (findParent->left == findNode) {
    findParent->left = child;
  } else {
    findParent->right = child;
  }
  delete findNode;
  findNode = child;
  findNode->parent = findParent;
  findNode->color = BLACK;

  if (findParent == nullptr) {
    root = findNode;
  }
}

template <class T>
typename Tree<T>::Node *Tree<T>::findMax(Node *node) {
  Node *temp = node;
  while (temp->right != nullptr) {
    temp = temp->right;
  }
  return temp;
}

template <class T>
void Tree<T>::deleteNode(Node **node) {
  delete *node;
  *node = nullptr;
}

template <class T>
void Tree<T>::transplantNodes(Node *whatReplace, Node *toReplace) {
  if (whatReplace->parent == nullptr) {
    root = toReplace;
  } else if (whatReplace == whatReplace->parent->left) {
    whatReplace->parent->left = toReplace;
  } else {
    whatReplace->parent->right = toReplace;
  }
  toReplace->parent = whatReplace->parent;
}

template <class T>
void Tree<T>::printTree() {
  if (root != nullptr) {
    std::string temp = "";
    printHelper(root, temp, true);
  }
}

template <class T>
void Tree<T>::printHelper(Node *printNode, std::string indent, bool isRight) {
  if (printNode != nullptr) {
    std::cerr << indent;
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

template <class T>
void Tree<T>::freeTree() {
  Node *temp = root;
  while (temp != nullptr && (root->left != nullptr || root->right != nullptr)) {
    if (temp->left != nullptr) {
      temp = temp->left;
    } else if (temp->left == nullptr && temp->right != nullptr) {
      temp = temp->right;
    } else {
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
  if (root != nullptr) {
    delete root;
    root = nullptr;
  }
}
