#include "s21_vector.h"

template <class T>
vector<T>::vector() : v_size_(0U), v_capacity_(0U), v_arr_(nullptr) {}

template <class T>
vector<T>::vector(std::initializer_list<value_type> const &items) {
  v_arr_ = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    v_arr_[i] = *it;
    i++;
  }
  v_size_ = items.size();
  v_capacity_ = items.size();
}

template <class T>
vector<T>::vector(size_type n)
    : v_size_(n), v_capacity_(n), v_arr_(n ? new T[n] : nullptr) {}

template <class T>
vector<T>::vector(const vector &v) {
  this->Initvector(v.v_size_);
  *this = v;
}

template <class T>
vector<T>::vector(vector &&other) {
  v_size_ = other.v_size_;
  v_capacity_ = other.v_capacity_;
  v_arr_ = other.v_arr_;

  other.v_size_ = 0;
  other.v_capacity_ = 0;
  other.v_arr_ = nullptr;
}

template <class T>
vector<T>::~vector() {
  delete[] v_arr_;
  v_arr_ = nullptr;
  v_size_ = 0;
  v_capacity_ = 0;
}

template <class T>
T &vector<T>::operator[](size_t i) {
  return i > v_capacity_
             ? throw std::out_of_range("out of limit vector operator[]")
             : v_arr_[i];
}

template <class T>
const T &vector<T>::front() {
  Emptyvector();
  return v_arr_[0];
}

template <class T>
const T &vector<T>::back() {
  Emptyvector();
  return v_arr_[this->size() - 1];
}

template <class T>
typename vector<T>::iterator vector<T>::data() {
  v_arr_ == nullptr ? throw std::out_of_range("Pointer is null") : 0;
  return iterator{v_arr_};
}

template <class T>
void vector<T>::reserve(size_type size_capacity) {
  T *new_arr = new T[size_capacity];
  for (size_type i = 0; i < v_size_; ++i) {
    new (new_arr + i) T(v_arr_[i]);
  }
  delete[] v_arr_;
  v_capacity_ = size_capacity;
  v_arr_ = new_arr;
}

template <class T>
void vector<T>::shrink_to_fit() {
  if (v_capacity_ > v_size_) {
    T *new_arr = new T[v_size_];
    for (size_type i = 0; i < v_size_; ++i) {
      new (new_arr + i) T(v_arr_[i]);
    }
    delete[] v_arr_;
    v_capacity_ = v_size_;
    v_arr_ = new_arr;
  }
}

template <class T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  if (pos > end() || pos < begin()) {
    throw std::out_of_range("out of limits vector");
  }
  size_type insert_pos = pos - begin();

  if (v_capacity_ == v_size_)
    reserve(v_capacity_ = (v_capacity_ ? v_capacity_ * 2 : 1));

  for (size_t i = v_size_; i > insert_pos; --i) {
    v_arr_[i] = v_arr_[i - 1];
  }

  v_arr_[insert_pos] = value;
  ++v_size_;
  return begin() + insert_pos;
}

template <class T>
void vector<T>::erase(vector<T>::iterator pos) {
  (empty() || pos < begin() || pos > end())
      ? throw std::out_of_range("Is empty")
      : 0;
  size_type del_pos = pos - begin();
  (v_arr_ + del_pos)->~T();

  for (auto i = del_pos; i < v_size_ - 1; ++i) {
    v_arr_[i] = v_arr_[i + 1];
  }
  --v_size_;
}

template <class T>
void vector<T>::pop_back() {
  Emptyvector();
  --v_size_;
  (v_arr_ + v_size_)->~T();
}

template <class T>
void vector<T>::clear() {
  delete[] v_arr_;
  v_arr_ = nullptr;
  v_size_ = 0;
}

template <class T>
T &vector<T>::at(size_type i) {
  if (i >= this->size()) {
    throw std::out_of_range("access to the non-existent element");
  }
  return v_arr_[i];
}

template <class T>
vector<T> &vector<T>::operator=(const vector<T> &v) {
  if (this != &v) {
    delete[] v_arr_;
    v_size_ = 0;
    v_capacity_ = 0;
    Initvector(v.v_size_);
    for (size_type i = 0; i < v.v_size_; i++) {
      v_arr_[i] = v.v_arr_[i];
    }
  }
  return *this;
}

template <class T>
vector<T> &vector<T>::operator=(vector<T> &&other) noexcept {
  if (this != &other) {
    delete[] v_arr_;
    v_size_ = other.v_size_;
    v_capacity_ = other.v_capacity_;
    v_arr_ = other.v_arr_;
    other.v_size_ = 0;
    other.v_capacity_ = 0;
    other.v_arr_ = nullptr;
  }
  return *this;
}

template <class T>
void vector<T>::push_back(value_type value) {
  if (v_size_ >= v_capacity_) {
    reserve(v_capacity_ = (v_capacity_ ? v_capacity_ * 2 : 1));
  }
  new (v_arr_ + v_size_) T(value);
  ++v_size_;
}

template <class T>
void vector<T>::swap(vector<T> &other) {
  if (this != &other) {
    size_t v_size_tmp = v_size_;
    size_t v_capacity_tmp = v_capacity_;
    T *v_arr_tmp = v_arr_;

    v_arr_ = other.v_arr_;
    v_size_ = other.v_size_;
    v_capacity_ = other.v_capacity_;

    other.v_arr_ = v_arr_tmp;
    other.v_size_ = v_size_tmp;
    other.v_capacity_ = v_capacity_tmp;
  }
}
