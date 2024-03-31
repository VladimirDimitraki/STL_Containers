#include "s21_avl_tree.h"

namespace s21 {

template <typename Key, typename Value>
avl<Key, Value>::avl() : root_(nullptr), size_tree_(0), fake_() {}

template <typename Key, typename Value>
avl<Key, Value>::avl(const avl &other) : avl() {
  root_ = clone_tree(other.root_);
  size_tree_ = other.size_tree_;
}

template <typename Key, typename Value>
avl<Key, Value>::avl(avl &&other) noexcept {
  if (this != &other) {
    root_ = other.root_;
    size_tree_ = other.size_tree_;
    other.root_ = nullptr;
    other.size_tree_ = 0;
  }
}

template <typename Key, typename Value>
avl<Key, Value> &avl<Key, Value>::operator=(const avl &other) {
  if (this != &other) {
    destroy_tree();
    root_ = clone_tree(other.root_);
    size_tree_ = other.size_tree_;
  }
  return *this;
}

template <typename Key, typename Value>
avl<Key, Value> &avl<Key, Value>::operator=(avl &&other) noexcept {
  if (this != &other) {
    destroy_tree();

    root_ = other.root_;
    size_tree_ = other.size_tree_;

    other.root_ = nullptr;
    other.size_tree_ = 0;
  }
  return *this;
}

template <typename Key, typename Value>
avl<Key, Value>::avl(
    std::initializer_list<std::pair<const Key, Value>> initList)
    : root_(nullptr), size_tree_(0), fake_() {
  for (const auto &pair : initList) {
    insert(pair.first, pair.second);
  }
}

template <typename Key, typename Value>
avl<Key, Value>::~avl() {
  destroy_tree();
}

template <typename Key, typename Value>
typename avl<Key, Value>::size_type avl<Key, Value>::size() const {
  return size_tree_;
}

// клонирование дерева
template <typename Key, typename Value>
typename avl<Key, Value>::Node *avl<Key, Value>::clone_tree(
    avl<Key, Value>::Node *node) {
  if (node == nullptr) {
    return nullptr;
  } else {
    Node *clone_node = new Node(node->key_val.first, node->key_val.second);
    clone_node->left_ = clone_tree(node->left_);
    clone_node->right_ = clone_tree(node->right_);
    return clone_node;
  }
}

// Работа с высотами
template <typename Key, typename Value>
int avl<Key, Value>::get_height(Node *node) {
  return node == nullptr ? -1 : node->height;
}

template <typename Key, typename Value>
void avl<Key, Value>::update_height(Node *node) {
  if (node != nullptr) {
    node->height =
        1 + std::max(get_height(node->left_), get_height(node->right_));
    update_height(node->left_);
    update_height(node->right_);
  }
}

// Работа с узлами
template <typename Key, typename Value>
std::pair<typename avl<Key, Value>::iterator, bool> avl<Key, Value>::insert(
    const Key &key, const Value &value) {
  bool inserted = true;
  size_type current_size = size_tree_;
  root_ = insert_node(root_, key, value);

  inserted = (current_size < size_tree_);

  return std::make_pair(find(key), inserted);
}

/// @brief
/// @tparam Key Value
/// @param
template <typename Key, typename Value>
typename avl<Key, Value>::Node *avl<Key, Value>::insert_node(
    Node *node, const Key &key, const Value &value) {
  if (node == nullptr) {
    node = new Node(key, value);
    size_tree_++;
  } else {
    if (key < node->key_val.first) {
      Node *tmp = insert_node(node->left_, key, value);
      tmp->parent_ = node;
      node->left_ = tmp;
    } else if (key > node->key_val.first) {
      Node *tmp = insert_node(node->right_, key, value);
      tmp->parent_ = node;
      node->right_ = tmp;
    }
  }
  update_height(node);
  return overload_balance(node);
}

template <typename Key, typename Value>
typename avl<Key, Value>::Node *avl<Key, Value>::get_max_value() {
  return get_max(root_);
}

template <typename Key, typename Value>
typename avl<Key, Value>::Node *avl<Key, Value>::get_min_value() {
  return get_min(root_);
}

// функция по поиску ключа
template <typename Key, typename Value>
typename avl<Key, Value>::Node *avl<Key, Value>::root_find(Node *node,
                                                           Key key) {
  bool flag = false;
  while (node->key_val.first != key && !flag) {
    if (key < node->key_val.first && node->left_ != nullptr) {
      node = node->left_;
    } else if (key > node->key_val.first && node->right_ != nullptr) {
      node = node->right_;
    } else if (node->key_val.first != key) {
      flag = true;
    }
  }

  return (flag ? nullptr : node);
}

template <typename Key, typename Value>
typename avl<Key, Value>::iterator avl<Key, Value>::find(Key key) {
  if (!root_) {
    return iterator(&fake_, *this);
  }
  Node *tmp = root_find(root_, key);
  return iterator((tmp != nullptr ? tmp : &fake_), *this);
}

template <typename Key, typename Value>
void avl<Key, Value>::remove(const Key &key) {
  root_ = delete_node(root_, key);
}

/// @brief
/// @param
/// @tparam Key, Value
template <typename Key, typename Value>
typename avl<Key, Value>::Node *avl<Key, Value>::delete_node(Node *node,
                                                             const Key &key) {
  if (node == nullptr) {
    return nullptr;
  } else if (key > node->key_val.first) {  // поиск эл-та
    Node *tmp = delete_node(node->right_, key);
    node->right_ = tmp;
    if (tmp != nullptr) tmp->parent_ = node;

  } else if (key < node->key_val.first) {
    Node *tmp = delete_node(node->left_, key);
    node->left_ = tmp;
    if (tmp != nullptr) tmp->parent_ = node;
  } else {  // удаляем найденный эл-т
    Node *parent = node->parent_;
    Node *left = node->left_;
    Node *right = node->right_;
    delete node;
    node = nullptr;
    size_tree_--;
    if (left == nullptr) {
      return right;
    }
    Node *min = get_max(left);
    Node *tmp = find_delete(left);
    min->left_ = tmp;
    if (tmp != nullptr) tmp->parent_ = min;
    min->right_ = right;
    if (right != nullptr) right->parent_ = min;
    min->parent_ = parent;
    return overload_balance(min);
  }
  update_height(node);
  return overload_balance(node);
}

template <typename Key, typename Value>
typename avl<Key, Value>::Node *avl<Key, Value>::find_delete(Node *node) {
  if (node->right_ == nullptr) {
    return node->left_;
  } else {
    Node *tmp = find_delete(node->right_);
    node->right_ = tmp;
    if (tmp != nullptr) tmp->parent_ = node;
  }
  return overload_balance(node);
}

template <typename Key, typename Value>
typename avl<Key, Value>::Node *avl<Key, Value>::clear_node(Node *node) {
  if (node != nullptr) {
    clear_node(node->right_);
    clear_node(node->left_);
    delete node;
  }
  return nullptr;
}

template <typename Key, typename Value>
void avl<Key, Value>::destroy_tree() {
  if (root_ != nullptr) {
    clear_node(root_);
    size_tree_ = 0;
    root_ = nullptr;
  }
}

template <typename Key, typename Value>
typename avl<Key, Value>::Node *avl<Key, Value>::get_min(Node *node) {
  if (node != nullptr) {
    while (node->left_ != nullptr) {
      node = node->left_;
    }
  } else {
    node = &fake_;
  }
  return node;
}

template <typename Key, typename Value>
typename avl<Key, Value>::Node *avl<Key, Value>::get_max(Node *node) {
  if (node != nullptr) {
    while (node->right_ != nullptr) {
      node = node->right_;
    }
  } else {
    node = &fake_;
  }
  return node;
}

template <typename Key, typename Value>
typename avl<Key, Value>::Node *avl<Key, Value>::get_root() {
  return root_;
}

template <typename Key, typename Value>
int avl<Key, Value>::check_height(Node *node) {
  int check_height = get_height(node->right_) - get_height(node->left_);
  return check_height;
}

template <typename Key, typename Value>
typename avl<Key, Value>::Node *avl<Key, Value>::right_rotate(Node *node) {
  Node *buffer = node->left_;
  node->left_ = buffer->right_;
  if (buffer->right_ != nullptr) {
    buffer->right_->parent_ = node;
  }

  buffer->parent_ = node->parent_;
  node->parent_ = buffer;
  buffer->right_ = node;
  update_height(node);
  update_height(buffer);
  return buffer;
}

template <typename Key, typename Value>
typename avl<Key, Value>::Node *avl<Key, Value>::left_rotate(Node *node) {
  Node *buffer = node->right_;
  node->right_ = buffer->left_;
  if (buffer->left_ != nullptr) {
    buffer->left_->parent_ = node;
  }

  buffer->parent_ = node->parent_;
  node->parent_ = buffer;
  buffer->left_ = node;
  update_height(node);
  update_height(buffer);
  return buffer;
}

template <typename Key, typename Value>
typename avl<Key, Value>::Node *avl<Key, Value>::overload_balance(Node *node) {
  // update_height(node);
  if (check_height(node) == 2) {
    if (check_height(node->right_) < 0) {
      node->right_ = right_rotate(node->right_);
    }
    return left_rotate(node);
  }
  if (check_height(node) == -2) {
    if (check_height(node->left_) > 0) {
      node->left_ = left_rotate(node->left_);
    }
    return right_rotate(node);
  }
  return node;
}

template <typename Key, typename Value>
typename avl<Key, Value>::iterator avl<Key, Value>::begin() {
  return iterator(get_min(root_), *this);
}

template <typename Key, typename Value>
typename avl<Key, Value>::iterator avl<Key, Value>::end() {
  return iterator(&fake_, *this);
}

template <typename Key, typename Value>
bool avl<Key, Value>::operator==(avl<Key, Value> &other) {
  bool is_eq = false;
  is_eq = (size() == other.size());
  avl_iterator it_1 = begin();
  avl_iterator it_2 = other.begin();
  while (is_eq && it_1 != end() && it_2 != other.end()) {
    is_eq = *it_1++ == *it_2++;
  }
  return is_eq;
}

template <typename Key, typename Value>
typename avl<Key, Value>::avl_iterator &
avl<Key, Value>::avl_iterator::move_forward() {
  if (current_ == tree_ptr_->get_max(tree_ptr_->root_)) {
    current_ = &tree_ptr_->fake_;
  } else if (current_ == &tree_ptr_->fake_) {
    current_ = tree_ptr_->get_min(tree_ptr_->root_);
  } else if (current_->right_ != nullptr) {
    current_ = tree_ptr_->get_min(current_->right_);
  } else if (current_->parent_ != nullptr &&
             current_->key_val.first < current_->parent_->key_val.first) {
    current_ = current_->parent_;
  } else if (current_->parent_ != nullptr &&
             current_->key_val.first > current_->parent_->key_val.first) {
    while (current_->key_val.first > current_->parent_->key_val.first &&
           current_->parent_ != nullptr) {
      current_ = current_->parent_;
    }
    current_ = current_->parent_;
  }
  return *this;
}

template <typename Key, typename Value>
typename avl<Key, Value>::avl_iterator &
avl<Key, Value>::avl_iterator::move_back() {
  if (current_ == tree_ptr_->get_min(tree_ptr_->root_)) {
    current_ = &tree_ptr_->fake_;
  } else if (current_ == &tree_ptr_->fake_) {
    current_ = tree_ptr_->get_max(tree_ptr_->root_);
  } else if (current_->left_ != nullptr) {
    current_ = tree_ptr_->get_max(current_->left_);
  } else if (current_->parent_ != nullptr &&
             current_->key_val.first > current_->parent_->key_val.first) {
    current_ = current_->parent_;
  } else if (current_->parent_ != nullptr &&
             current_->key_val.first < current_->parent_->key_val.first) {
    while (current_->key_val.first < current_->parent_->key_val.first &&
           current_->parent_ != nullptr) {
      current_ = current_->parent_;
    }
    current_ = current_->parent_;
  }
  return *this;
}

template <typename Key, typename Value>
void avl<Key, Value>::swap(avl<Key, Value> &other) {
  Node *tmp_root = root_;
  root_ = other.root_;
  other.root_ = tmp_root;

  size_type tmp_size = size_tree_;
  size_tree_ = other.size_tree_;
  other.size_tree_ = tmp_size;
}

template <typename Key, typename Value>
void avl<Key, Value>::merge(avl<Key, Value> &other) {
  if (this == &other) return;
  for (s21::avl<Key, Value>::iterator i = other.begin(); i != other.end();) {
    auto insert_res = insert(i->first, i->second);
    if (insert_res.second) {
      i = other.erase(i);
    } else {
      i++;
    }
  }
}

template <typename Key, typename Value>
typename avl<Key, Value>::iterator avl<Key, Value>::erase(iterator pos) {
  auto ret_val = pos;
  ret_val++;
  remove(pos->first);
  return ret_val;
}

}  // namespace s21
