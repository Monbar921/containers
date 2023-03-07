#include "Tree.h"

using namespace s21;

Tree::Tree() {}

template<typename Type> Type Tree::max(Type a, Type b)
{
	return (a >= b ? a : b);
}

Tree::~Tree() { freeTree(); }
// Tree::~Tree() {  }

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
    if (node != nullptr) {
      delete node;
    }
  }
}

Tree::Node *Tree::findGrandparent(Node *node) {
  Node *grandparent = nullptr;
  if (node != nullptr && node->parent != nullptr) {
    grandparent = node->parent->parent;
  }
  return grandparent;
}

Tree::Node *Tree::findUncle(Node *node) {
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

Tree::Node *Tree::findSibling(Node *node) {
  Node *output = nullptr;
  if (node == node->parent->left) {
    output = node->parent->right;
  } else {
    output = node->parent->left;
  }
  return output;
}

void Tree::insertRebalance(Node *node) {
  if (node->parent == nullptr) {
    node->color = BLACK;
  } else {
    if (node->parent->color == RED) {
      uncleAndParentRed(node);
    }
  }
}

void Tree::uncleAndParentRed(Node *node) {
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

void Tree::erase(int key) {
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

    if (findNode == nullptr) {
      std::cout << "Key not found in the tree" << std::endl;
    } else {
      eraseFunction(findNode);
    }
  }
}

void Tree::deleteRebalance(Node *node) {
  if (node->parent != nullptr) {
    deleteCase1(node);
  }
}

void Tree::deleteCase1(Node *node) {
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

void Tree::deleteCase2(Node *node) {
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

void Tree::deleteCase3(Node *node) {
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

void Tree::deleteCase4(Node *node) {
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

void Tree::deleteCase5(Node *node) {
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

void Tree::eraseFunction(Node *findNode) {
  if (findNode->left == nullptr && findNode->right == nullptr) {
    Node *parent = findNode->parent;
    if (findNode->color == BLACK) {
      deleteRebalance(findNode);
    }
    if (findNode == parent->left) {
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

void Tree::videoRebalance(Node *findNode) {}

void Tree::changeNodes(Node *findNode, Node *child) {
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
  // std::cerr << findNode->data << " " << findNode->parent->data << " " <<
  // findNode->left << " " << findNode->right << " " << "\n";
}

Tree::Node *Tree::findMax(Node *node) {
  Node *temp = node;
  while (temp->right != nullptr) {
    temp = temp->right;
  }
  return temp;
}

void Tree::deleteNode(Node **node) {
  delete *node;
  *node = nullptr;
}

void Tree::transplantNodes(Node *whatReplace, Node *toReplace) {
  if (whatReplace->parent == nullptr) {
    root = toReplace;
  } else if (whatReplace == whatReplace->parent->left) {
    whatReplace->parent->left = toReplace;
  } else {
    whatReplace->parent->right = toReplace;
  }
  toReplace->parent = whatReplace->parent;
}

void Tree::printTree() {
  if (root != nullptr) {
    std::string temp = "";
    printHelper(root, temp, true);
  }
}

void Tree::printHelper(Node *printNode, std::string indent, bool isRight) {
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

void Tree::freeTree() {
  Node *temp = root;
  while ((root->left != nullptr || root->right != nullptr) && temp != nullptr) {
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
  delete root;
}
