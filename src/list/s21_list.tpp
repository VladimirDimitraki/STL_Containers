#include "s21_list.h"

namespace s21 {

template <typename T>
list<T>::list() : head_(nullptr), end_(nullptr), fake_(nullptr), list_size_(0) {
  Node *fake_node = new Node();
  fake_ = head_ = end_ = fake_node;
  fake_node->next = head_;
  fake_node->prev = end_;
}

template <typename T>
list<T>::list(list::size_type n)
    : head_(nullptr), end_(nullptr), fake_(nullptr), list_size_(0) {
  for (size_type i = 0; i < n; ++i) {
    push_back(value_type());
  }
}

/// @brief Constructs the container with the contents of the initializer list
/// items.
/// @param items
template <typename T>
list<T>::list(const std::initializer_list<value_type> &items)
    : head_(nullptr), end_(nullptr), fake_(nullptr), list_size_(0) {
  for (const auto &i : items) {
    push_back(i);
  }
}

/// Copy constructor
template <typename T>
list<T>::list(const list<T> &other)
    : head_(nullptr), end_(nullptr), fake_(nullptr), list_size_(0) {
  for (const auto &i : other) {
    push_back(i);
  }
}

/// @brief Move constructor
/// @param other
template <typename T>
list<T>::list(list<T> &&other) noexcept {
  if (this != &other) {
    head_ = other.head_;
    end_ = other.end_;
    fake_ = other.fake_;
    list_size_ = other.list_size_;

    other.head_ = other.end_ = other.fake_ = nullptr;
    other.list_size_ = 0;
  }
}

/// @brief Copy assignment operator. Replaces the contents with a copy of the
/// contents of other.
/// @param other
/// @return
template <typename T>
list<T> list<T>::operator=(const list<T> &other) {
  if (this != &other) {
    clear();
    for (const auto &i : other) {
      push_back(i);
    }
  }
  return *this;
}

/// @brief Move assignment operator. Replaces the contents with those of other
/// using move semantics.
/// @param other
/// @return
template <typename T>
list<T> list<T>::operator=(list<T> &&other) noexcept {
  if (this != &other) {
    clear();
    head_ = other.head_;
    end_ = other.end_;
    fake_ = other.fake_;
    list_size_ = other.list_size_;

    other.head_ = other.end_ = other.fake_ = nullptr;
    other.list_size_ = 0;
  }
  return *this;
}

/// @brief
/// @param items
/// @return
template <typename T>
list<T> list<T>::operator=(std::initializer_list<value_type> const &items) {
  clear();
  for (const auto &i : items) {
    push_back(i);
  }
  return *this;
}

/// Destructor
template <typename T>
list<T>::~list() {
  clear();
}

/// OPERATORS

template <class T>
bool list<T>::operator==(const list<T> &other) const {
  bool is_equal = false;
  is_equal = (size() == other.size());

  const_iterator it_1 = cbegin();
  const_iterator it_2 = other.cbegin();

  while (is_equal && it_1 != cend() && it_2 != other.cend()) {
    is_equal = *it_1++ == *it_2++;
  }
  return is_equal;
}

template <class T>
bool list<T>::operator!=(const list<T> &other) const {
  return !(*this == other);
}

/// Iterator

template <typename T>
typename list<T>::iterator list<T>::begin() {
  return iterator(head_);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(fake_);
}

template <typename T>
typename list<T>::const_iterator list<T>::begin() const {
  return const_iterator(head_);
}

template <typename T>
typename list<T>::const_iterator list<T>::end() const {
  return const_iterator(fake_);
}

template <typename T>
typename list<T>::const_iterator list<T>::cbegin() const {
  return const_iterator(head_);
}

template <typename T>
typename list<T>::const_iterator list<T>::cend() const {
  return const_iterator(fake_);
}

/// @brief Appends the given element val to the end of the container
/// @param val the value of the element to prepend
template <typename T>
void list<T>::push_back(const list::value_type &val) {
  Node *new_node = new Node(val);
  Node *fake_node;
  if (list_size_ == 0) {
    fake_node = (fake_ == nullptr ? new Node() : fake_);
    new_node->next = new_node->prev = fake_node;
    fake_node->next = fake_node->prev = new_node;
    head_ = end_ = new_node;
    fake_ = fake_node;
  } else {
    new_node->prev = end_;
    end_->next = new_node;
    new_node->next = fake_;
    fake_->prev = new_node;
    end_ = new_node;
  }
  list_size_++;
}

/// @brief Prepends the given element val to the beginning of the container.
/// @param val the value of the element to prepend
template <typename T>
void list<T>::push_front(const list::value_type &val) {
  Node *new_node = (Node *)new Node(val);
  Node *fake_node;
  if (list_size_ == 0) {
    fake_node = (fake_ == nullptr ? new Node() : fake_);
    new_node->next = new_node->prev = fake_node;
    fake_node->next = fake_node->prev = new_node;
    head_ = end_ = new_node;
    fake_ = fake_node;
  } else {
    new_node->next = head_;
    head_->prev = new_node;
    new_node->prev = fake_;
    fake_->next = new_node;
    head_ = new_node;
  }
  list_size_++;
}

/// @brief Removes the last element of the container.
template <typename T>
void list<T>::pop_back() {
  if (list_size_ > 0) {
    Node *tmp = end_;
    end_ = fake_->prev = end_->prev;
    delete tmp;
    list_size_--;
    if (!list_size_) {
      delete fake_;
      fake_ = head_ = end_ = nullptr;
    } else {
      end_->next = fake_;
    }
  }
}

/// @brief Removes the first element of the container.
template <typename T>
void list<T>::pop_front() {
  if (list_size_ > 0) {
    Node *tmp = head_;
    head_ = fake_->next = head_->next;
    delete tmp;
    list_size_--;
    if (!list_size_) {
      delete fake_;
      fake_ = head_ = end_ = nullptr;
    } else {
      head_->prev = fake_;
    }
  }
}

/// CAPACITY

/// @brief Checks whether the container is empty
template <typename T>
bool list<T>::empty() {
  return size() == 0;
}

/// @brief Returns the number of elements
template <typename T>
typename list<T>::size_type list<T>::size() const {
  return list_size_;
}

/// @brief Returns the maximum possible number of elements
template <typename T>
typename list<T>::size_type list<T>::max_size() {
  return std::numeric_limits<size_type>::max() / 2 / sizeof(Node);
}

///  Element access

/// @brief Returns a reference to the first element in the container.
template <typename T>
typename list<T>::reference list<T>::front() {
  if (head_ == nullptr) {
    throw std::out_of_range("list is empty.");
  }
  return head_->data;
}

/// @brief Returns a const reference to the first element in the container.
template <typename T>
typename list<T>::const_reference list<T>::front() const {
  return head_->data;
}

/// @brief Returns a reference to the last element in the container.
template <typename T>
typename list<T>::reference list<T>::back() {
  if (end_ == nullptr) {
    throw std::out_of_range("list is empty.");
  }
  return end_->data;
}

/// @brief Returns a const reference to the last element in the container.
template <typename T>
typename list<T>::const_reference list<T>::back() const {
  return end_->data;
}

/// Modifiers

/// @brief Erases all elements from the container.
template <typename T>
void list<T>::clear() {
  while (list_size_ != 0 && fake_ != nullptr) {
    pop_back();
  }
  if (fake_ != nullptr) {
    delete fake_;
    fake_ = head_ = end_ = nullptr;
  }
}

/// @brief Inserts value before pos.
/// @param pos iterator before which the content will be inserted
/// @param value element value to insert
/// @return Iterator pointing to the inserted value.
template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node *new_node;

  if (pos == begin()) {
    push_front(value);
    new_node = head_;
  } else if (pos == end()) {
    push_back(value);
    new_node = end_;
  } else {
    new_node = new Node(value);
    Node *current_pos = pos.GetNode();

    new_node->next = current_pos;
    new_node->prev = current_pos->prev;

    current_pos->prev->next = new_node;
    current_pos->prev = new_node;
    list_size_++;
  }
  return iterator(new_node);
}

/// @brief Erases the specified elements from the container.
/// @param pos iterator to the element to remove
/// @return Iterator following the last removed element.
template <typename T>
typename list<T>::iterator list<T>::erase(iterator pos) {
  Node *last_pos = fake_;
  if (pos == begin()) {
    pop_front();
    last_pos = head_;
  } else if (pos == --end()) {
    pop_back();
    last_pos = fake_;
  } else if (pos != end()) {
    Node *current_pos = pos.GetNode();
    current_pos->prev->next = current_pos->next;
    current_pos->next->prev = current_pos->prev;
    last_pos = current_pos->next;
    delete current_pos;
    list_size_--;
  }
  return iterator(last_pos);
}

/// @brief Exchanges the contents of the container with those of other.
/// @param other container to exchange the contents with
template <typename T>
void list<T>::swap(list<T> &other) {
  if (this != &other) {
    Node *tmp_head_ = head_;
    Node *tmp_end_ = end_;
    Node *tmp_fake_ = fake_;
    size_type tmp_list_size_ = list_size_;

    head_ = other.head_;
    end_ = other.end_;
    fake_ = other.fake_;
    list_size_ = other.list_size_;

    other.head_ = tmp_head_;
    other.end_ = tmp_end_;
    other.fake_ = tmp_fake_;
    other.list_size_ = tmp_list_size_;
  }
}

/// OPERATIONS

/// @brief Merges other into *this.
/// @param other another container to merge
template <typename T>
void list<T>::merge(list<T> &other) {
  if (this == &other) return;

  Node *curr_this = fake_;
  Node *curr_other = other.head_;

  while (curr_this->next != fake_ && curr_other != other.fake_) {
    if (curr_this->next->data > curr_other->data) {
      Node *tmp_node = curr_other;
      curr_other = curr_other->next;

      tmp_node->prev = curr_this;
      tmp_node->next = curr_this->next;

      curr_this->next->prev = tmp_node;
      curr_this->next = tmp_node;
    } else {
      curr_this = curr_this->next;
    }
  }

  if (curr_other != other.fake_) {
    curr_this->next = curr_other;
    curr_other->prev = curr_this;
    other.fake_->prev->next = fake_;
    fake_->prev = other.fake_->prev;
  }

  head_ = fake_->next;
  end_ = fake_->prev;
  list_size_ += other.list_size_;

  delete other.fake_;
  other.head_ = other.end_ = other.fake_ = nullptr;
  other.list_size_ = 0;
}

/// @brief Transfers elements from one list to another.
/// @param pos element before which the content will be inserted
/// @param other another container to transfer the content from
template <typename T>
void list<T>::splice(list<T>::iterator pos, list<T> &other) {
  if (this == &other || other.size() == 0) return;

  Node *tmp_curr = pos.GetNode();

  other.head_->prev = tmp_curr->prev;
  tmp_curr->prev->next = other.head_;

  other.end_->next = tmp_curr;
  tmp_curr->prev = other.end_;

  head_ = fake_->next;
  end_ = fake_->prev;
  list_size_ += other.list_size_;

  delete other.fake_;
  other.head_ = other.end_ = other.fake_ = nullptr;
  other.list_size_ = 0;
}

/// @brief Reverses the order of the elements in the container.
template <typename T>
void list<T>::reverse() {
  Node *tmp_next = fake_->next;
  Node *tmp_curr = fake_;
  for (bool stop = false; !stop;) {
    if (tmp_next == fake_) {
      stop = true;
    }
    tmp_curr->next = tmp_curr->prev;
    tmp_curr->prev = tmp_next;

    tmp_curr = tmp_next;
    tmp_next = tmp_curr->next;
  }
  end_ = fake_->prev;
  head_ = fake_->next;
}

/// @brief Removes all consecutive duplicate elements from the container.
template <typename T>
void list<T>::unique() {
  iterator current(head_);
  iterator next;
  while (current != end()) {
    next = current;
    ++next;
    while (*current == *next && next != end()) {
      next = erase(next);
    }
    ++current;
  }
}

/// @brief Sorts the elements and preserves the order of equivalent elements.
/// No references or iterators become invalidated.
template <typename T>
void list<T>::sort() {
  if (list_size_ <= 1) return;

  size_type middle_idx = list_size_ / 2;
  size_type second_size = list_size_ - middle_idx;
  Node *second_head = head_;
  Node *second_end = fake_->prev;

  for (size_type i = 0; i < middle_idx; ++i) {
    second_head = second_head->next;
  }

  end_ = second_head->prev;
  end_->next = fake_;
  fake_->prev = end_;
  list_size_ = middle_idx;

  list<T> right_half;
  right_half.head_ = second_head;
  right_half.end_ = second_end;

  right_half.fake_->next = right_half.head_;
  right_half.fake_->prev = right_half.end_;

  right_half.end_->next = right_half.fake_;
  right_half.head_->prev = right_half.fake_;
  right_half.list_size_ = second_size;

  this->sort();
  right_half.sort();

  merge(right_half);
}

}  // namespace s21
