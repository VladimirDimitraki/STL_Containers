#ifndef CPP2_S21_CONTAINERS_SRC_QUEUE_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_SRC_QUEUE_S21_QUEUE_H_

#include "../list/s21_list.h"

namespace s21 {

template <class T, class Container = s21::list<T>>
class queue {
 public:
  using container_type = Container;
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

  queue() : container_() {}
  queue(std::initializer_list<value_type> const &items) : container_(items) {}
  queue(const queue &q) : container_(q.container_) {}
  queue(queue &&q) : container_(std::move(q.container_)) {}

  queue &operator=(queue &&q) noexcept {
    container_ = std::move(q.container_);
    return *this;
  }

  ~queue() { container_.clear(); }

  /// Element access

  reference front() { return container_.front(); }
  const_reference front() const { return container_.front(); }

  reference back() { return container_.back(); }
  const_reference back() const { return container_.back(); }

  /// Capacity

  bool empty() { return container_.empty(); }
  size_type size() { return container_.size(); }

  /// Modifiers

  void push(const_reference value) { return container_.push_back(value); }
  void pop() { return container_.pop_front(); }
  void swap(queue &other) { return container_.swap(other.container_); }

 protected:
  Container container_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_QUEUE_S21_QUEUE_H_