#include "s21_set_test.h"

TEST(SetTestDestructor, Test0) {
  bool r = false;

  {
    s21::set<int> set_s21{100, 200};
    r = true;
  }

  ASSERT_TRUE(r);
}

TEST(SetTestConstructorDefault, Test0) {
  std::set<int> set_std;
  s21::set<int> set_s21;

  ASSERT_EQ(set_s21.size(), set_std.size());
}

TEST(SetTestConstructorInitList, Test0) {
  std::set<int> set_std = {1, 2};
  s21::set<int> set_s21 = {1, 2};

  s21::avl<int, int>::avl_iterator it = set_s21.begin();

  ASSERT_EQ(set_s21.size(), set_std.size());
  ASSERT_EQ(it->first, 1);
  ASSERT_EQ(it->second, 1);
}

// TEST(SetTestOperatorEq, Test0) {
//   std::set<int> set_std_0;
//   std::set<int> set_std_1;
//   s21::set<int> set_s21_0;
//   s21::set<int> set_s21_1;
//
//   ASSERT_TRUE(set_s21_1 == set_s21_0);
//   ASSERT_TRUE(set_std_0 == set_std_1);
// }

TEST(SetTestOperatorAssignment, Test0) {
  std::set<int> set_std_0{1, 2, 3, 4};
  std::set<int> set_std_1;
  s21::set<int> set_s21_0{1, 2, 3, 4};
  s21::set<int> set_s21_1;

  set_s21_1 = set_s21_0;
  set_std_1 = set_std_0;

  ASSERT_EQ(set_s21_1.size(), 4);
  ASSERT_EQ(set_std_1.size(), 4);
}

TEST(SetTestConstructorCopy, Test0) {
  std::set<int> set_std_0{1, 2, 3};
  std::set<int> set_std_1(set_std_0);
  s21::set<int> set_s21_0{1, 2, 3};
  s21::set<int> set_s21_1(set_s21_0);

  s21::avl<int, int>::avl_iterator it = set_s21_1.begin();

  ASSERT_EQ(set_std_1.size(), set_std_0.size());
  ASSERT_EQ(set_s21_0.size(), 3);
  ASSERT_EQ(it->second, 1);
}

TEST(SetTestOperatorMove, Test0) {
  std::set<int> set_std_0{1, 2, 3};
  std::set<int> set_std_1;
  set_std_1 = std::move(set_std_0);
  s21::set<int> set_s21_0{1, 2, 3};
  s21::set<int> set_s21_1;
  set_s21_1 = std::move(set_s21_0);

  s21::avl<int, int>::avl_iterator it = set_s21_1.begin();

  ASSERT_EQ(it->second, 1);
  ASSERT_EQ(set_std_1.size(), 3);
  ASSERT_EQ(set_s21_1.size(), 3);
}

TEST(SetTestConstructorMove, Test0) {
  std::set<int> set_std_0{1, 2, 3};
  std::set<int> set_std_1(std::move(set_std_0));
  s21::set<int> set_s21_0{1, 2, 3};
  s21::set<int> set_s21_1(std::move(set_s21_0));

  s21::avl<int, int>::avl_iterator it = set_s21_1.begin();

  ASSERT_EQ(it->second, 1);
  ASSERT_EQ(set_std_1.size(), 3);
  ASSERT_EQ(set_s21_1.size(), 3);
}

TEST(SetTestBegin, Test0) {
  std::set<int> set_std{1, 2, 3};
  s21::set<int> set_s21{1, 2, 3};

  s21::avl<int, int>::avl_iterator it = set_s21.begin();
  std::set<int>::iterator it_std = set_std.begin();

  ASSERT_EQ(it->second, 1);
  ASSERT_EQ(*it_std, 1);
}

TEST(SetTestEnd, Test0) {
  std::set<int> set_std{1, 2, 3};
  s21::set<int> set_s21{1, 2, 3};

  s21::avl<int, int>::avl_iterator it = set_s21.end();
  std::set<int>::iterator it_std = set_std.end();
  --it;
  ASSERT_EQ(it->second, 3);
  ASSERT_EQ(*it_std, 3);
}

TEST(SetTestEmpty, Test0) {
  std::set<int> set_std;
  s21::set<int> set_s21;

  ASSERT_TRUE(set_s21.empty());
  ASSERT_TRUE(set_std.empty());

  std::set<int> set_std_1{1};
  s21::set<int> set_s21_1{1};

  ASSERT_FALSE(set_std_1.empty());
  ASSERT_FALSE(set_s21_1.empty());
}

TEST(SetTestInsert, Test0) {
  std::set<int> set_std;
  s21::set<int> set_s21;

  ASSERT_EQ(set_s21.size(), 0);
  ASSERT_EQ(set_std.size(), 0);

  set_s21.insert(1);
  set_std.insert(1);

  ASSERT_EQ(set_s21.size(), 1);
  ASSERT_EQ(set_std.size(), 1);
}

TEST(SetTestInsert, Test1) {
  std::set<int> set_std{1};
  s21::set<int> set_s21{1};

  set_s21.insert(2);
  set_std.insert(2);

  ASSERT_EQ(set_s21.size(), 2);
  ASSERT_EQ(set_std.size(), 2);
}

TEST(SetTestInsert, Test2) {
  std::set<int> set_std{1};
  s21::set<int> set_s21{1};

  set_s21.insert(1);
  set_std.insert(1);

  ASSERT_EQ(set_s21.size(), 1);
  ASSERT_EQ(set_std.size(), 1);
}

TEST(SetTestInsert, Test3) {
  std::set<int> set_std{1, 2, 3, 4};
  s21::set<int> set_s21{1, 2, 3, 4};

  auto pair_std = set_std.insert(4);
  bool insert_result_std = pair_std.second;

  auto pair_s21 = set_s21.insert(4);
  bool insert_result_s21 = pair_s21.second;

  ASSERT_EQ(set_s21.size(), 4);
  ASSERT_EQ(set_std.size(), 4);

  ASSERT_EQ(insert_result_s21, false);
  ASSERT_EQ(insert_result_std, false);
}

TEST(SetTestInsert, Test4) {
  s21::set<int> set_s21{1};
  std::set<int> std_set{1};
  auto it = set_s21.begin();
  auto it2 = std_set.begin();
  set_s21.erase(it);
  std_set.erase(it2);
  ASSERT_EQ(set_s21.size(), 0);
}

TEST(set_test_max_size, IntMaxSize) {
  s21::set<int> s21_;
  std::set<int> std_;
  ASSERT_EQ(s21_.max_size(), std_.max_size());
}

TEST(SetTestErase, Test0) {
  std::set<int> set_std{1, 2, 3, 4};
  s21::set<int> set_s21{1, 2, 3, 4};

  s21::avl<int, int>::avl_iterator it = set_s21.end();
  std::set<int>::iterator it_std = set_std.end();

  --it;
  --it_std;
  --it;
  --it_std;

  set_std.erase(it_std);
  set_s21.erase(it);

  ASSERT_EQ(set_std.size(), 3);
  ASSERT_EQ(set_s21.size(), 3);
}

TEST(SetTestErase, Test1) {
  std::set<int> set_std{1, 2, 3};
  s21::set<int> set_s21{1, 2, 3};

  s21::avl<int, int>::avl_iterator it = set_s21.begin();
  std::set<int>::iterator it_std = set_std.begin();

  it_std = set_std.erase(it_std);
  it = set_s21.erase(it);

  ASSERT_EQ(it->first, 2);
  ASSERT_EQ(*it_std, 2);

  ASSERT_EQ(set_std.size(), 2);
  ASSERT_EQ(set_s21.size(), 2);
}

TEST(SetTestClear, Test0) {
  std::set<int> set_std{1};
  s21::set<int> set_s21{1};

  set_s21.clear();
  set_std.clear();

  ASSERT_TRUE(set_std.empty());
  ASSERT_TRUE(set_s21.empty());

  ASSERT_EQ(set_s21.size(), 0);
  ASSERT_EQ(set_std.size(), 0);
}

TEST(SetTestClear, Test1) {
  std::set<int> set_std{1, 2, 3};
  s21::set<int> set_s21{1, 2, 3};

  ASSERT_EQ(set_s21.size(), 3);
  ASSERT_EQ(set_std.size(), 3);

  set_s21.clear();
  set_std.clear();

  ASSERT_TRUE(set_std.empty());
  ASSERT_TRUE(set_s21.empty());

  ASSERT_EQ(set_s21.size(), 0);
  ASSERT_EQ(set_std.size(), 0);
}

TEST(SetTestClear, Test2) {
  std::set<int> set_std;
  s21::set<int> set_s21;

  set_s21.clear();
  set_std.clear();

  ASSERT_TRUE(set_std.empty());
  ASSERT_TRUE(set_s21.empty());

  ASSERT_EQ(set_s21.size(), 0);
  ASSERT_EQ(set_std.size(), 0);
}

TEST(SetTestMerge, Test0) {
  std::set<int> set_std{1, 2};
  std::set<int> set_std_0{4, 5};
  s21::set<int> set_s21{1, 2};
  s21::set<int> set_s21_0{4, 5};
  set_std.merge(set_std_0);
  set_s21.merge(set_s21_0);
  s21::set<int>::iterator it = set_s21.end();
  std::set<int>::iterator it_0 = set_std.end();

  --it;
  ASSERT_EQ(it->first, 5);
  ASSERT_EQ(*(--it_0), 5);
}

TEST(SetTestMerge, Test1) {
  std::set<int> set_std{1, 2};
  std::set<int> set_std_0{2, 5};
  s21::set<int> set_s21{1, 2};
  s21::set<int> set_s21_0{2, 5};
  set_std.merge(set_std_0);
  set_s21.merge(set_s21_0);
  s21::set<int>::iterator it = set_s21.begin();
  std::set<int>::iterator it_0 = set_std.begin();

  ++it;
  ASSERT_EQ(it->first, 2);
  ASSERT_EQ(*(++it_0), 2);

  ASSERT_EQ(set_s21.size(), 3);
  ASSERT_EQ(set_std.size(), 3);
}

TEST(SetTestMerge, Test2) {
  std::set<int> set_std{1};
  std::set<int> set_std_0{1};
  s21::set<int> set_s21{1};
  s21::set<int> set_s21_0{1};
  set_std.merge(set_std_0);
  set_s21.merge(set_s21_0);
  s21::set<int>::iterator it = set_s21.begin();
  std::set<int>::iterator it_0 = set_std.begin();
  ASSERT_EQ(it->first, 1);
  ASSERT_EQ(*it_0, 1);

  ASSERT_EQ(set_s21.size(), 1);
  ASSERT_EQ(set_std.size(), 1);
}

TEST(SetTestMerge, Test3) {
  std::set<char> set_std{'A', 'B', 'E'};
  std::set<char> set_std_0{'C', 'D', 'E', 'F'};
  s21::set<char> set_s21{'A', 'B', 'E'};
  s21::set<char> set_s21_0{'C', 'D', 'E', 'F'};
  set_std.merge(set_std_0);
  set_s21.merge(set_s21_0);
  // A,B,C,D,E,F

  ASSERT_EQ(set_s21_0.begin()->first, 'E');
  ASSERT_EQ(*set_std_0.begin(), 'E');
}

TEST(SetTestMerge, Test4) {
  std::set<char> set_std{'A', 'B', 'E'};
  std::set<char> set_std_0{'C', 'D', 'E', 'F'};
  s21::set<char> set_s21{'A', 'B', 'E'};
  s21::set<char> set_s21_0{'C', 'D', 'E', 'F'};
  set_std.merge(set_std_0);
  set_s21.merge(set_s21_0);
  s21::set<char>::iterator it = set_s21.begin();
  std::set<char>::iterator it_0 = set_std.begin();
  // A,B,C,D,E,F
  ++it;
  ++it;
  ++it_0;
  ASSERT_EQ(it->first, 'C');
  ASSERT_EQ(*(++it_0), 'C');
  s21::set<char>::iterator it_1 = set_s21.end();
  std::set<char>::iterator it_0_1 = set_std.end();
  --it_1;
  --it_1;
  --it_0_1;
  ASSERT_EQ(it_1->first, 'E');
  ASSERT_EQ(*(--it_0_1), 'E');
  ASSERT_EQ(set_s21.size(), 6);
  ASSERT_EQ(set_std.size(), 6);
}

TEST(SetTestFind, Test0) {
  std::set<char> set_std_0{'C', 'D', 'E', 'F'};
  s21::set<char> set_s21_0{'C', 'D', 'E', 'F'};

  s21::set<char>::iterator it = set_s21_0.find('E');
  std::set<char>::iterator it_0 = set_std_0.find('E');

  ASSERT_EQ(it->first, 'E');
  ASSERT_EQ(*it_0, 'E');
}

TEST(SetTestFind, Test1) {
  std::set<char> set_std_0{'C', 'D', 'E', 'F'};
  s21::set<char> set_s21_0{'C', 'D', 'E', 'F'};

  s21::set<char>::iterator it = set_s21_0.find('X');
  std::set<char>::iterator it_0 = set_std_0.find('X');

  --it;
  ASSERT_EQ(it->first, 'F');
  ASSERT_EQ(it_0, set_std_0.end());
}

TEST(SetTestContains, Test0) {
  s21::set<char> set_s21_0{'C', 'D', 'E', 'F'};
  ASSERT_TRUE(set_s21_0.contains('D'));
  ASSERT_FALSE(set_s21_0.contains('Y'));
}

TEST(SetSwapContainer, SimpleSwapTest) {
  s21::set<int> s21_1{1, 2, 3, 4};
  s21::set<int> s21_2{3, 2, 1};
  s21_1.swap(s21_2);
  auto it = s21_1.begin();
  auto it1 = s21_2.end();
  --it1;

  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it1->first, 4);
}

TEST(SetSwapContainer, SimpleSwapTest1) {
  s21::set<int> s21_1{9, 8};
  s21::set<int> s21_2{2, 1};
  s21_1.swap(s21_2);
  auto it1 = s21_1.begin();
  auto it2 = s21_2.begin();

  EXPECT_EQ(it1->first, 1);
  EXPECT_EQ(it2->first, 8);
}

TEST(SetSwapContainer, SimpleSwapTest2) {
  s21::set<int> s21_1{9, 8};
  s21::set<int> s21_2{2, 1};
  s21_1.swap(s21_2);
  auto it1 = s21_1.end();
  --it1;
  auto it2 = s21_2.end();
  --it2;

  EXPECT_EQ(it1->first, 2);
  EXPECT_EQ(it2->first, 9);
}
