#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_
#include "SetInterface.h"

namespace s21 {
template <class T>
class s21_set : public SetInterface<T> {
 public:
  s21_set();
  void insert(T key) override;
  void erase(T key) override;
  size_t size() override;
  bool empty() override;

 private:
};
}  // namespace s21

#endif  // SRC_S21_SET_H_