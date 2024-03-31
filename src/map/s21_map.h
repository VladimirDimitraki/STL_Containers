#ifndef CPP2_S21_CONTAINERS_SRC_MAP_S21_MAP_H_
#define CPP2_S21_CONTAINERS_SRC_MAP_S21_MAP_H_

#include <cmath>
#include <initializer_list>
#include <iostream>
#include <limits>

#include "../avl_tree/s21_avl_tree.h"

namespace s21 {

template <typename Key, typename Value>
class map {
 public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const key_type, mapped_type>;
  using size_type = std::size_t;
  using reference = value_type &;
  using const_reference = const value_type &;

  using iterator = typename avl<Key, Value>::iterator;
  using const_iterator = typename avl<Key, Value>::const_iterator;

  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &other);
  map(map &&other) noexcept;
  map &operator=(const map &other);
  map &operator=(map &&other) noexcept;

  ~map() = default;

  /// Element access

  mapped_type &at(const Key &key);
  mapped_type &operator[](const Key &key);

  /// Iterators

  iterator begin();
  iterator end();

  /// Capasity

  bool empty();
  size_type size();
  size_type max_size();

  /// Modifiers

  void clear();
  std::pair<iterator, bool> insert(const_reference value);
  std::pair<iterator, bool> insert(const key_type &key, const mapped_type &obj);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const Value &obj);
  iterator erase(iterator pos);
  void swap(map &other);
  void merge(map &other);

  /// Lookup
  iterator find(const Key &key);
  bool contains(const Key &key);

  void print_() { avl_tree_.print_avl(avl_tree_.get_root()); }

 private:
  avl<Key, Value> avl_tree_;
};  // class map
}  // namespace s21

#include "s21_map.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_MAP_S21_MAP_H_
