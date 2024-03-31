#ifndef CPP2_S21_CONTAINERS_SRC_LIST_S21_LIST_H_
#define CPP2_S21_CONTAINERS_SRC_LIST_S21_LIST_H_

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {

template <class T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  class ListIterator {
   public:
    using pointer_type = typename list<T>::Node *;
    using value_type = T;
    using reference_type = T &;

    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

    ListIterator() noexcept : current_node_(nullptr) {}
    ListIterator(pointer_type node) : current_node_(node) {}

    ListIterator(const ListIterator &other) = default;

    ListIterator &operator=(const ListIterator &other) = default;

    reference_type operator*() const { return current_node_->data; }

    bool operator==(const ListIterator &other) const {
      return (current_node_ == other.current_node_);
    }

    bool operator!=(const ListIterator &other) const {
      return !(current_node_ == other.current_node_);
    }

    ListIterator &operator++() {
      current_node_ = current_node_->next;
      return *this;
    }

    ListIterator operator++(int) {
      ListIterator tmp = *this;
      current_node_ = current_node_->next;
      return tmp;
    }

    ListIterator &operator--() {
      current_node_ = current_node_->prev;
      return *this;
    }

    ListIterator operator--(int) {
      ListIterator tmp = *this;
      current_node_ = current_node_->prev;
      return tmp;
    }

    pointer_type GetNode() const { return current_node_; }

   protected:
    pointer_type current_node_;
  };

  class ListConstIterator {
   public:
    using pointer_type = const typename list<T>::Node *;
    using value_type = T;
    using reference_type = const T &;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

    ListConstIterator() noexcept : current_node_() {}
    ListConstIterator(pointer_type node) : current_node_(node) {}

    ListConstIterator(const ListConstIterator &other) = default;
    ListConstIterator &operator=(const ListConstIterator &other) = default;

    reference_type operator*() const { return current_node_->data; }

    bool operator==(const ListConstIterator &other) const {
      return (current_node_ == other.current_node_);
    }

    bool operator!=(const ListConstIterator &other) const {
      return !(current_node_ == other.current_node_);
    }

    ListConstIterator &operator++() {
      current_node_ = current_node_->next;
      return *this;
    }

    ListConstIterator operator++(int) {
      ListConstIterator tmp = *this;
      current_node_ = current_node_->next;
      return tmp;
    }

    ListConstIterator &operator--() {
      current_node_ = current_node_->prev;
      return *this;
    }

    ListConstIterator operator--(int) {
      ListConstIterator tmp = *this;
      current_node_ = current_node_->prev;
      return tmp;
    }
    pointer_type GetNode() const { return current_node_; }

   protected:
    pointer_type current_node_;
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  // Сonstructors

  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &other);
  list(list &&other) noexcept;

  list operator=(const list &other);
  list operator=(list &&other) noexcept;
  list operator=(std::initializer_list<value_type> const &items);

  ~list();

  // Operators

  bool operator==(const list &other) const;
  bool operator!=(const list &other) const;

  // Iterators

  iterator begin();
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;

  // Element access

  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;

  // Capacity

  bool empty();
  size_type size() const;
  size_type max_size();

  // Modifiers

  void clear();
  void push_back(const value_type &val);
  void pop_back();
  void push_front(const value_type &val);
  void pop_front();
  iterator insert(iterator pos, const_reference value);
  iterator erase(iterator pos);
  void swap(list &other);

  // Operations

  void merge(list &other);
  void splice(iterator pos, list &other);
  void sort();
  void reverse();
  void unique();

 private:
  typedef struct Node {
    value_type data;
    Node *prev;
    Node *next;

    Node() : data(), prev(nullptr), next(nullptr) {}
    Node(const value_type &value) : data(value), prev(nullptr), next(nullptr) {}
  } Node;

  Node *head_;
  Node *end_;
  Node *fake_;

  size_type list_size_;
};

}  // namespace s21

#include "s21_list.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_LIST_S21_LIST_H_