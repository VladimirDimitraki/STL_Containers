#ifndef CPP2_S21_CONTAINERS_SRC_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_SRC_S21_VECTOR_H_

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {

template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  template <bool IsConst>
  class iterator_base {
   public:
    using p_type = std::conditional_t<IsConst, const T *, T *>;
    using r_type = std::conditional_t<IsConst, const T &, T &>;

    iterator_base() : ptr_(nullptr) {}
    iterator_base(T *ptr_) : ptr_(ptr_) {}
    iterator_base(const iterator_base &) = default;
    iterator_base(iterator_base &&) = default;

    iterator_base &operator=(const iterator_base &) = default;
    iterator_base &operator=(iterator_base &&) = default;

    r_type operator*() { return *ptr_; }
    p_type operator->() { return ptr_; }

    iterator_base &operator++() {
      ++ptr_;
      return *this;
    }
    iterator_base operator++(int) {
      iterator_base tmp(*this);
      ++(*this);
      return tmp;
    }
    iterator_base operator--(int) {
      iterator_base tmp(*this);
      --(*this);
      return tmp;
    }
    iterator_base &operator--() {
      --ptr_;
      return *this;
    }
    size_type operator-(const iterator_base &other) const {
      return ptr_ - other.ptr_;
    }
    iterator_base operator-(const size_type n) const {
      return iterator_base(ptr_ - n);
    }
    iterator_base operator+(const size_type n) const {
      return iterator_base{ptr_ + n};
    }
    bool operator==(const iterator_base &other) const {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const iterator_base &other) const {
      return ptr_ != other.ptr_;
    }
    bool operator>(const iterator_base &other) const {
      return ptr_ > other.ptr_;
    }
    bool operator<(const iterator_base &other) const {
      return ptr_ < other.ptr_;
    }

   private:
    T *ptr_;

  };  // class iterator

 public:
  using iterator = iterator_base<false>;
  using const_iterator = iterator_base<true>;

  vector();
  vector(std::initializer_list<value_type> const &items);
  vector(size_type n);
  vector(const vector &v);
  vector(vector &&other);

  vector<T> &operator=(const vector<T> &v);
  vector<T> &operator=(vector<T> &&v) noexcept;

  ~vector();

  // Element access
  reference at(size_type i);
  reference operator[](size_type i);

  const_reference front();
  const_reference back();
  iterator data();

  // Vector Iterators
  iterator begin() { return iterator{v_arr_}; }
  iterator end() { return iterator{v_arr_ + v_size_}; }
  const_iterator cbegin() const { return const_iterator{v_arr_}; }
  const_iterator cend() const { return const_iterator{v_arr_ + v_size_}; }

  // Vector Capacity
  bool empty() { return !v_size_; }
  size_type size() { return v_size_; }
  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
  }
  void reserve(size_type size_capacity);
  size_type capacity() { return v_capacity_; }
  void shrink_to_fit();

  // Vector Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(value_type v);
  void pop_back();
  void swap(vector<T> &other);

  void Emptyvector() {
    empty() ? throw std::out_of_range("vector is empty") : 0;
  }

 private:
  size_t v_size_;
  size_t v_capacity_;
  T *v_arr_;

  void Initvector(size_type v) {
    v_size_ = v;
    v_capacity_ = v;
    v_arr_ = v ? new T[v] : nullptr;
  }
};

#include "s21_vector.tpp"

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_VECTOR_H_
