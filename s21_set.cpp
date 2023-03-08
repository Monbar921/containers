#include "s21_set.h"

using namespace s21;

template <class T>
s21_set<T>::s21_set() {

}

template <class T>
void s21_set<T>::insert(T key) {
    SetInterface<T>::tree.insert(key);    
}

template <class T>
void s21_set<T>::erase(T key) {
    
}

template <class T>
size_t s21_set<T>::size() {
    return SetInterface<T>::tree.treeSize;
}

template <class T>
bool s21_set<T>::empty() {
    return (SetInterface<T>::tree.treeSize == 0) ? true : false;
}
