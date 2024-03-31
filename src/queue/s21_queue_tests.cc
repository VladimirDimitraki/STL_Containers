#include "gtest/gtest.h"
#include "s21_queue.h"

TEST(QueueTest, EmptyQueue) {
  s21::queue<int> queue;
  EXPECT_TRUE(queue.empty());
  EXPECT_EQ(queue.size(), 0);
}

TEST(QueueTest, ConstructorWithInitializerList) {
  s21::queue<int> queue = {1, 2, 3, 4};

  EXPECT_EQ(queue.size(), 4);
  EXPECT_EQ(queue.front(), 1);
  EXPECT_EQ(queue.back(), 4);
}

TEST(QueueTest, ConstructorWithEmptyInitializerList) {
  s21::queue<int> queue = {};

  EXPECT_TRUE(queue.empty());
  EXPECT_EQ(queue.size(), 0);
}

TEST(QueueTest, CopyConstructorWithNonEmptyQueue) {
  s21::queue<int> original = {1, 2, 3};
  s21::queue<int> copied(original);

  EXPECT_EQ(copied.size(), 3);
  EXPECT_EQ(copied.front(), 1);
  EXPECT_EQ(copied.back(), 3);
}

TEST(QueueTest, CopyConstructorWithEmptyQueue) {
  s21::queue<int> original;
  s21::queue<int> copied(original);

  EXPECT_TRUE(copied.empty());
  EXPECT_EQ(copied.size(), 0);
}

TEST(QueueTest, MoveConstructorWithNonEmptyQueue) {
  s21::queue<int> original = {1, 2, 3};
  s21::queue<int> moved(std::move(original));

  EXPECT_TRUE(original.empty());
  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(moved.front(), 1);
  EXPECT_EQ(moved.back(), 3);
}

TEST(QueueTest, MoveConstructorWithEmptyQueue) {
  s21::queue<int> original;
  s21::queue<int> moved(std::move(original));

  EXPECT_TRUE(original.empty());
  EXPECT_TRUE(moved.empty());
  EXPECT_EQ(moved.size(), 0);
}

TEST(QueueTest, MoveAssignmentWithNonEmptyQueue) {
  s21::queue<int> original = {1, 2, 3};
  s21::queue<int> moved;
  moved = std::move(original);

  EXPECT_TRUE(original.empty());
  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(moved.front(), 1);
  EXPECT_EQ(moved.back(), 3);
}

TEST(QueueTest, MoveAssignmentWithEmptyQueue) {
  s21::queue<int> original;
  s21::queue<int> moved;
  moved = std::move(original);

  EXPECT_TRUE(original.empty());
  EXPECT_TRUE(moved.empty());
  EXPECT_EQ(moved.size(), 0);
}

TEST(QueueTest, PushEmptyQueue) {
  s21::queue<int> q;
  q.push(42);

  EXPECT_EQ(q.size(), 1);
  EXPECT_EQ(q.front(), 42);
  EXPECT_EQ(q.back(), 42);
}

TEST(QueueTest, PushNonEmptyQueue) {
  s21::queue<int> q = {1, 2, 3};
  q.push(4);

  EXPECT_EQ(q.size(), 4);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 4);
}

TEST(QueueTest, ConstFront) {
  s21::queue<int> q = {1, 2, 3};
  const int el_front = q.front();
  const int el_back = q.back();
  EXPECT_EQ(el_front, 1);
  EXPECT_EQ(el_back, 3);
}

TEST(QueueTest, PopNonEmptyQueue) {
  s21::queue<int> q = {1, 2, 3};
  q.pop();

  EXPECT_EQ(q.size(), 2);
  EXPECT_EQ(q.front(), 2);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, PopEmptyQueue) {
  s21::queue<int> q;

  EXPECT_NO_THROW(q.pop());
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, SwapTwoNonEmptyQueues) {
  s21::queue<int> q1 = {1, 2, 3};
  s21::queue<int> q2 = {4, 5, 6};
  q1.swap(q2);

  EXPECT_EQ(q1.size(), 3);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q1.front(), 4);
  EXPECT_EQ(q1.back(), 6);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, SwapNonEmptyAndEmptyQueue) {
  s21::queue<int> q1 = {1, 2, 3};
  s21::queue<int> q2;
  q1.swap(q2);

  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, SwapTwoEmptyQueues) {
  s21::queue<int> q1;
  s21::queue<int> q2;
  q1.swap(q2);

  EXPECT_TRUE(q1.empty());
  EXPECT_TRUE(q2.empty());
}

TEST(QueueTest, PushAndPop) {
  s21::queue<int> queue;
  queue.push(42);
  EXPECT_FALSE(queue.empty());
  EXPECT_EQ(queue.size(), 1);
  EXPECT_EQ(queue.front(), 42);
  EXPECT_EQ(queue.back(), 42);

  queue.pop();
  EXPECT_TRUE(queue.empty());
  EXPECT_EQ(queue.size(), 0);
}

TEST(QueueTest, FrontAndBack) {
  s21::queue<int> queue;
  queue.push(1);
  queue.push(2);
  queue.push(3);

  EXPECT_EQ(queue.front(), 1);
  EXPECT_EQ(queue.back(), 3);

  queue.pop();

  EXPECT_EQ(queue.front(), 2);
  EXPECT_EQ(queue.back(), 3);
}

TEST(QueueTest, MoveConstructor) {
  s21::queue<int> original;
  original.push(1);
  original.push(2);

  s21::queue<int> moved(std::move(original));

  EXPECT_TRUE(original.empty());
  EXPECT_EQ(original.size(), 0);
  EXPECT_EQ(moved.front(), 1);
  EXPECT_EQ(moved.back(), 2);
}

TEST(QueueTest, MoveAssignmentOperator) {
  s21::queue<int> original;
  original.push(1);
  original.push(2);

  s21::queue<int> moved;
  moved = std::move(original);

  EXPECT_TRUE(original.empty());
  EXPECT_EQ(original.size(), 0);
  EXPECT_EQ(moved.front(), 1);
  EXPECT_EQ(moved.back(), 2);
}

TEST(QueueTest, Swap) {
  s21::queue<int> queue1;
  s21::queue<int> queue2;

  queue1.push(1);
  queue1.push(2);

  queue2.push(3);
  queue2.push(4);

  queue1.swap(queue2);

  EXPECT_EQ(queue1.front(), 3);
  EXPECT_EQ(queue1.back(), 4);
  EXPECT_EQ(queue2.front(), 1);
  EXPECT_EQ(queue2.back(), 2);
}
