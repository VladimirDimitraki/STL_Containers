#include "s21_set.h"

namespace s21 {

template <class Key>
set<Key>::set(const set<Key> &other) {
  set_ = other.set_;
}

template <class Key>
set<Key>::set(set<Key> &&other) noexcept {
  set_ = std::move(other.set_);
}

template <class Key>
set<Key>::set(std::initializer_list<value_type> const &items) {
  for (auto &it : items) {
    set_.insert(it, it);
  }
}

template <class Key>
set<Key> &set<Key>::operator=(const set<Key> &other) {
  set_ = other.set_;
  return *this;
}

template <class Key>
set<Key> &set<Key>::operator=(set<Key> &&other) noexcept {
  set_ = std::move(other.set_);
  return *this;
}

template <class Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const Key &value) {
  return set_.insert(value, value);
}

template <class Key>
typename set<Key>::iterator set<Key>::erase(iterator pos) {
  return set_.erase(pos);
}

template <class Key>
void set<Key>::swap(set &other) {
  set_.swap(other.set_);
}

template <class Key>
void set<Key>::merge(set<Key> &other) {
  set_.merge(other.set_);
}

template <class Key>
typename set<Key>::iterator set<Key>::find(const Key &key) {
  set<Key>::iterator it = set_.find(key);
  set<Key>::iterator iter = set_.end();
  if (it->first != key) return iter;
  return set_.find(key);
}

template <class Key>
bool set<Key>::contains(const Key &key) {
  set<Key>::iterator it = set_.find(key);
  return it->first == key;
}

}  // namespace s21