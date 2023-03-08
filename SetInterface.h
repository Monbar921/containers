#ifndef SRC_SETINTERFACE_H_
#define SRC_SETINTERFACE_H_
#include "Tree.h"
// #include "Tree.cpp"
namespace s21 {

template <class T>
class SetInterface {
 public:
  // virtual void insert(T key);
  // virtual void erase(T key);
  size_t size(){
   return tree.treeSize;
  }
  // virtual bool empty();

 private:
  Tree<T> tree;
  // data members
};

}  // namespace s21

#endif  // SRC_SETINTERFACE_H_