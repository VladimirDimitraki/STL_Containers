#ifndef CPP2_S21_CONTAINERS_SRC_AVL_TREE_S21_AVL_TREE_H_
#define CPP2_S21_CONTAINERS_SRC_AVL_TREE_S21_AVL_TREE_H_

#include <cmath>
#include <iostream>

namespace s21 {

template <typename Key, typename Value>
class avl {
 public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const key_type, mapped_type>;
  using size_type = std::size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using tree_type_ret = avl<Key, Value>;

  struct Node {
    value_type key_val;
    int height = 0;
    Node *left_ = nullptr;
    Node *right_ = nullptr;
    Node *parent_ = nullptr;

    Node() : key_val(), height(0) {}

    Node(Key key, Value value)
        : key_val(key, value),
          height(0),
          left_(nullptr),
          right_(nullptr),
          parent_(nullptr) {}
  };

  class avl_iterator {
   public:
    using ptr_node = typename avl<Key, Value>::Node *;
    using tree_type = avl<Key, Value>;
    using avl_ptr = s21::avl<Key, Value>::avl_iterator;

    avl_iterator() : current_(nullptr), tree_ptr_(nullptr){};
    avl_iterator(const avl_iterator &) = default;
    avl_iterator(ptr_node node, tree_type &tree)
        : current_(node), tree_ptr_(&tree){};

    ~avl_iterator() = default;

    value_type operator*() const { return current_->key_val; };
    value_type *operator->() const { return &(current_->key_val); };

    avl_iterator &operator++() { return this->move_forward(); }

    avl_iterator operator++(int) {
      avl_ptr return_node = *this;
      this->move_forward();
      return return_node;
    }

    avl_iterator &operator--() { return this->move_back(); }

    avl_iterator operator--(int) {
      avl_ptr return_node = *this;
      this->move_back();
      return return_node;
    }

    bool operator==(const avl_iterator &other) {
      return (current_ == other.current_);
    }

    bool operator!=(const avl_iterator &other) {
      return (current_ != other.current_);
    }

    avl_iterator &operator=(const avl_iterator &other) {
      if (this != &other) {
        current_ = other.current_;
      }
      return *this;
    }

    avl_iterator &move_forward();
    avl_iterator &move_back();

   protected:
    ptr_node current_;
    tree_type *tree_ptr_;
  };
  using iterator = avl_iterator;
  using const_iterator = avl_iterator;

  avl();
  avl(const avl &other);
  avl(avl &&other) noexcept;
  avl(std::initializer_list<value_type> initList);
  avl &operator=(const avl &other);
  avl &operator=(avl &&other) noexcept;

  ~avl();

  bool operator==(avl<Key, Value> &other);

  // работа с узлами

  iterator find(Key key);
  std::pair<iterator, bool> insert(const Key &key, const Value &value);

  void destroy_tree();
  void remove(const Key &key);

  // Get

  Node *get_root();
  Node *get_min_value();
  Node *get_max_value();

  // Функционал Итератора

  iterator begin();
  iterator end();

  // Функция для рекурсивного вывода AVL-дерева

  void print_avl(Node *root, int space = 0, int count = 10);

  // Размер дерева

  size_type size() const;

  void merge(avl<Key, Value> &other);
  void swap(avl<Key, Value> &other);
  iterator erase(iterator pos);

 protected:
  // Поиск элемента

  Node *root_find(Node *node, Key key);

  // удаление

  Node *delete_node(Node *node, const Key &key);
  Node *find_delete(Node *node);
  Node *clear_node(Node *node);

  // работа с высотами узлов

  int get_height(Node *node);
  void update_height(Node *node);
  int check_height(Node *node);

  // вставка узла

  Node *insert_node(Node *node, const Key &key, const Value &value);

  // Работа со значениями узлов

  Node *get_min(Node *node);
  Node *get_max(Node *node);

  // Балансировка

  Node *right_rotate(Node *node);
  Node *left_rotate(Node *node);
  Node *overload_balance(Node *node);

  // клонирование и перенос дерева

  Node *clone_tree(Node *node);

 private:
  Node *root_;
  size_type size_tree_;
  Node fake_;
};

}  // namespace s21

#include "s21_avl_tree.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_AVL_TREE_S21_AVL_TREE_H_
