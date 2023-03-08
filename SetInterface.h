#ifndef SRC_SETINTERFACE_H_
#define SRC_SETINTERFACE_H_
#include "Tree.cpp"
#include "Tree.h"
namespace s21 {

template <class T>
class SetInterface {
  template <class>
  friend class s21_set;

 public:
  virtual void insert(const T& value) = 0;
  virtual void erase(T key) = 0;
  virtual size_t size() = 0;
  virtual bool empty() = 0;
  virtual void clear() = 0;
 private:
  Tree<T> tree;
  size_t x;
  // data members
};

}  // namespace s21

#endif  // SRC_SETINTERFACE_H_