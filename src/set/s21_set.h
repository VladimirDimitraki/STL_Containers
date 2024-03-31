#ifndef CPP2_S21_CONTAINERS_SRC_SET_S21_SET_H_
#define CPP2_S21_CONTAINERS_SRC_SET_S21_SET_H_

#include <cstddef>
#include <utility>

#include "../avl_tree/s21_avl_tree.h"

namespace s21 {

template <class Key>

class set {
 public:
  using Node = typename avl<Key, Key>::Node *;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename avl<Key, Key>::avl_iterator;
  using const_iterator = const typename avl<Key, Key>::avl_iterator;
  using size_type = size_t;

  set() = default;
  set(std::initializer_list<value_type> const &items);
  set(const set &other);
  set(set &&other) noexcept;
  ~set() = default;
  set &operator=(const set &other);
  set &operator=(set &&other) noexcept;

  iterator begin() { return set_.begin(); }
  iterator end() { return set_.end(); }
  bool empty() { return set_.size() == 0; }
  size_type size() { return set_.size(); }
  size_type max_size() {
    std::cout << sizeof(std::pair<int, int>) << std::endl;
    return std::numeric_limits<size_type>::max() /
           sizeof(typename avl<Key, Key>::Node) / 2;
  }
  void clear() { set_.destroy_tree(); }
  std::pair<iterator, bool> insert(const value_type &value);
  iterator erase(iterator pos);
  void swap(set &other);
  void merge(set &other);
  iterator find(const Key &key);
  bool contains(const Key &key);

 private:
  avl<Key, Key> set_;
};

}  // namespace s21

#include "s21_set.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_S21_SET_H_
