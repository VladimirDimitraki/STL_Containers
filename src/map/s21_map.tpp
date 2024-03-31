#include "s21_map.h"

namespace s21 {
template <typename Key, typename Value>
map<Key, Value>::map() : avl_tree_() {}

template <typename Key, typename Value>
map<Key, Value>::map(std::initializer_list<value_type> const &items)
    : avl_tree_(items) {}

template <typename Key, typename Value>
map<Key, Value>::map(const map &other) : map() {
  if (this != &other) {
    avl_tree_ = other.avl_tree_;
  }
}

template <typename Key, typename Value>
map<Key, Value>::map(map &&other) noexcept
    : avl_tree_(std::move(other.avl_tree_)) {}

template <typename Key, typename Value>
map<Key, Value> &map<Key, Value>::operator=(const map &other) {
  if (this != &other) {
    avl_tree_.destroy_tree();
    avl_tree_ = other.avl_tree_;
  }
  return *this;
}

template <typename Key, typename Value>
map<Key, Value> &map<Key, Value>::operator=(map &&other) noexcept {
  if (this != &other) {
    avl_tree_.destroy_tree();
    avl_tree_ = std::move(other.avl_tree_);
  }
  return *this;
}

// Element access

/// @brief Returns a reference to the mapped value of the element with specified
/// key. If no such element exists, an exception of type std::out_of_range is
/// thrown.
/// @param key the key of the element to find
/// @return A reference to the mapped value of the requested element.
template <typename Key, typename Value>
typename map<Key, Value>::mapped_type &map<Key, Value>::at(const Key &key) {
  auto tmp = avl_tree_.find(key);
  if (tmp == end()) {
    throw std::out_of_range("Index out of range");
  }
  return (tmp->second);
}

/// @brief Returns a reference to the value that is mapped to a key equivalent
/// to key or x respectively, performing an insertion if such key does not
/// already exist.
/// @param key 	the key of the element to find
/// @return A reference to the mapped value of the new element if no element
/// with key key existed. Otherwise, a reference to the mapped value of the
/// existing element whose key is equivalent to key.
template <typename Key, typename Value>
typename map<Key, Value>::mapped_type &map<Key, Value>::operator[](
    const Key &key) {
  auto tmp = avl_tree_.find(key);
  if (tmp == end()) {
    auto res = avl_tree_.insert(key, Value());  // премию
    tmp = res.first;
  }
  return tmp->second;
}

// Iterators

/// @brief Returns an iterator to the first element of the map.
/// If the map is empty, the returned iterator will be equal to end().
template <typename Key, typename Value>
typename map<Key, Value>::iterator map<Key, Value>::begin() {
  return avl_tree_.begin();
}

/// @brief Returns an iterator to the element following the last element of the
/// map. This element acts as a placeholder; attempting to access it results in
/// undefined behavior.
template <typename Key, typename Value>
typename map<Key, Value>::iterator map<Key, Value>::end() {
  return avl_tree_.end();
}

// Capasity

/// @brief Checks if the container has no elements.
/// @return true if the container is empty, false otherwise.
template <typename Key, typename Value>
bool map<Key, Value>::empty() {
  return !size();
}

/// @brief Returns the number of elements in the container.
template <typename Key, typename Value>
typename map<Key, Value>::size_type map<Key, Value>::size() {
  return avl_tree_.size();
}

/// @brief Returns the maximum number of elements the container is able to hold
/// due to system or library implementation limitations.
template <typename Key, typename Value>
typename map<Key, Value>::size_type map<Key, Value>::max_size() {
  return std::numeric_limits<size_type>::max() / 2 /
         sizeof(typename avl<Key, Key>::Node);
}

// Modifiers

/// @brief Erases all elements from the container. After this call, size()
/// returns zero. Invalidates any references, pointers, and iterators referring
/// to contained elements. Any past-the-end iterator remains valid.
template <typename Key, typename Value>
void map<Key, Value>::clear() {
  avl_tree_.destroy_tree();
}

/// @brief Inserts element(s) into the container, if the container doesn't
/// already contain an element with an equivalent key.
/// @param value element to insert (In the form of a pair {key, value})
/// @return A pair consisting of an iterator to the inserted element (or to the
/// element that prevented the insertion) and a bool value set to true if and
/// only if the insertion took place.
template <typename Key, typename Value>
std::pair<typename map<Key, Value>::iterator, bool> map<Key, Value>::insert(
    const value_type &value) {
  return avl_tree_.insert(value.first, value.second);
}

/// @brief Inserts value by key
/// @param key a unique key to insert
/// @param obj a value to insert by key
/// @return pair of iterator to where the element is in the container and bool
/// denoting whether the insertion took place
template <typename Key, typename Value>
std::pair<typename map<Key, Value>::iterator, bool> map<Key, Value>::insert(
    const key_type &key, const mapped_type &obj) {
  return avl_tree_.insert(key, obj);
}

/// @brief Inserts an element if such a key does not exist, otherwise assigns a
/// value based on an existing key
/// @param key the key used both to look up and to insert if not found
/// @param obj the value to insert or assign
/// @return The bool component is true if the insertion took place and false if
/// the assignment took place. The iterator component is pointing at the element
/// that was inserted or updated.
template <typename Key, typename Value>
std::pair<typename map<Key, Value>::iterator, bool>
map<Key, Value>::insert_or_assign(const Key &key, const Value &obj) {
  auto insert_res = avl_tree_.insert(key, obj);
  if (insert_res.second == false) {
    insert_res.first->second = obj;
  }
  return insert_res;
}

/// @brief Removes the element at pos.
/// @param pos iterator to the element to remove
template <typename Key, typename Value>
typename map<Key, Value>::iterator map<Key, Value>::erase(
    typename map<Key, Value>::iterator pos) {
  return avl_tree_.erase(pos);
}

/// @brief Exchanges the contents of the container with those of other. Does not
/// invoke any move, copy, or swap operations on individual elements. All
/// iterators and references remain valid. The end() iterator is invalidated.
/// @param other container to exchange the contents with
template <typename Key, typename Value>
void map<Key, Value>::swap(map &other) {
  avl_tree_.swap(other.avl_tree_);
}

/// @brief Transfers elements from the map `other` to the current map, retaining
/// only unique elements. If there is an element in the current map with a key
/// equivalent to the key of an element in `other`, then that element is not
/// transferred from `other`.
/// @param other The container to merge elements from.
template <typename Key, typename Value>
void map<Key, Value>::merge(map<Key, Value> &other) {
  avl_tree_.merge(other.avl_tree_);
}

// Lookup

/// @brief Finds an element with key equivalent to key.
/// @param key 	key value of the element to search for
/// @return An iterator to the requested element.
/// If no such element is found, past-the-end (see end()) iterator is returned.
template <typename Key, typename Value>
typename map<Key, Value>::iterator map<Key, Value>::find(const Key &key) {
  return avl_tree_.find(key);
}

/// @brief Checks if there is an element with key equivalent to key in the
/// container.
/// @param key 	key value of the element to search for
/// @return true if there is such an element, otherwise false.
template <typename Key, typename Value>
bool map<Key, Value>::contains(const Key &key) {
  bool result = (avl_tree_.find(key) != end());
  return result;
}

}  // namespace s21