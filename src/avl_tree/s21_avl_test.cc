#include <gtest/gtest.h>
#include <math.h>

#include "s21_avl_tree.h"

TEST(AvlInsert, insertTest) {
  s21::avl<int, int> avl_tree;
  avl_tree.insert(5, 50);
  EXPECT_EQ(avl_tree.get_root()->key_val.first, 5);
  EXPECT_EQ(avl_tree.get_root()->key_val.second, 50);
}

TEST(AvlInsert, AvlInsert_1) {
  s21::avl<int, int> avl_tree;
  avl_tree.insert(5, 50);
  avl_tree.insert(6, 50);
  avl_tree.insert(7, 50);
  avl_tree.insert(8, 50);
  avl_tree.insert(9, 50);
  EXPECT_EQ(avl_tree.get_root()->key_val.first, 6);
  EXPECT_EQ(avl_tree.get_root()->key_val.second, 50);
}

TEST(AvlConstructor, DefaultConstructor1) {
  s21::avl<int, int> avl_tree{{1, 50}, {2, 60}, {3, 70}};
  s21::avl<int, int>::iterator it;
  it = avl_tree.begin();
  EXPECT_TRUE(it->first == 1);
}

TEST(AvlConstructor, CopyConstructor1) {
  s21::avl<int, int> avl_tree{{1, 50}, {2, 60}, {3, 70}};
  s21::avl<int, int>::iterator it(avl_tree.begin());
  EXPECT_TRUE(it->first == 1);
}

TEST(AvlDefault, CheckBalance) {
  s21::avl<int, int> avl_tree = {
      {1, 50},  {2, 60},  {3, 70},  {4, 70},  {5, 70},  {6, 70},
      {7, 70},  {8, 70},  {9, 70},  {10, 70}, {11, 70}, {12, 70},
      {13, 70}, {14, 70}, {15, 70}, {16, 70}, {17, 70}, {18, 70},
      {19, 70}, {20, 70}, {21, 70}, {22, 70}, {23, 70}, {24, 70}};

  EXPECT_EQ(avl_tree.get_root()->key_val.first, 16);
  EXPECT_EQ(avl_tree.get_root()->right_->key_val.first, 20);
  EXPECT_EQ(avl_tree.get_root()->left_->key_val.first, 8);
}

TEST(AvlRemove, RemoveTest_1) {
  s21::avl<int, int> avl_tree = {
      {5, 50},  {6, 60},  {8, 70},  {9, 70},  {10, 70}, {11, 70},
      {12, 70}, {13, 70}, {14, 70}, {15, 70}, {16, 70}, {17, 70},
      {18, 70}, {19, 70}, {20, 70}, {21, 70}, {22, 70}, {23, 70},
      {24, 70}, {25, 70}, {26, 70}, {27, 70}, {28, 70}, {29, 70}};
  avl_tree.remove(5);
  avl_tree.remove(14);
  auto it = avl_tree.begin();
  EXPECT_EQ(it->first, 6);
}

TEST(AvlRemove, SizeCheckTest) {
  s21::avl<int, int> avl_tree = {
      {5, 50},  {6, 60},  {8, 70},  {9, 70},  {10, 70}, {11, 70},
      {12, 70}, {13, 70}, {14, 70}, {15, 70}, {16, 70}, {17, 70},
      {18, 70}, {19, 70}, {20, 70}, {21, 70}, {22, 70}, {23, 70},
      {24, 70}, {25, 70}, {26, 70}, {27, 70}, {28, 70}, {29, 70}};

  avl_tree.remove(5);
  avl_tree.remove(14);
  EXPECT_EQ(avl_tree.size(), 22);
}

TEST(AvlConstructor, CreateTreeWithDefaultConstructor) {
  s21::avl<int, int> avl_tree;
  avl_tree.insert(5, 50);
  avl_tree.insert(6, 50);
  avl_tree.insert(7, 50);
  avl_tree.insert(8, 50);
  avl_tree.insert(9, 50);
  avl_tree.insert(10, 50);
  avl_tree.insert(11, 50);
  avl_tree.insert(12, 50);
  avl_tree.insert(13, 50);
  avl_tree.insert(14, 50);
  avl_tree.insert(15, 50);
  avl_tree.insert(16, 50);
  avl_tree.insert(17, 50);
  avl_tree.insert(18, 50);

  auto it = avl_tree.begin();
  EXPECT_EQ(it->first, 5);
}

TEST(AvlConstructor, CreateTreeDefault) {
  s21::avl<int, int> avl_tree;
  avl_tree.insert(5, 50);
  avl_tree.insert(6, 50);
  avl_tree.insert(7, 50);
  avl_tree.insert(8, 50);
  avl_tree.insert(9, 50);
  avl_tree.insert(10, 50);
  avl_tree.insert(11, 50);
  avl_tree.insert(12, 50);
  avl_tree.insert(13, 50);
  avl_tree.insert(14, 50);
  avl_tree.insert(15, 50);
  avl_tree.insert(16, 50);
  avl_tree.insert(17, 50);
  avl_tree.insert(18, 50);

  avl_tree.remove(8);
  auto it = avl_tree.begin();
  for (int i = 0; i <= it->first; ++i) {
    if (i == it->first) {
      EXPECT_EQ(i, it->first);
    }
  }
}

TEST(AvlConstructor, AnyType) {
  s21::avl<double, double> avl_tree;
  avl_tree.insert(5.1, 50);
  avl_tree.insert(6.1, 50);
  avl_tree.insert(7.1, 50);
  avl_tree.insert(8.1, 50);
  avl_tree.insert(9.1, 50);
  avl_tree.insert(1.10, 50);
  avl_tree.insert(1.11, 50);
  avl_tree.insert(1.12, 50);
  avl_tree.insert(1.13, 50);
  avl_tree.insert(1.14, 50);
  avl_tree.insert(1.15, 50);
  avl_tree.insert(1.16, 50);
  avl_tree.insert(1.17, 50);
  avl_tree.insert(1.18, 50);

  auto it = avl_tree.end();
  --it;
  EXPECT_EQ(9.1, it->first);
}

TEST(AvlConstructor, AnyType_1) {
  s21::avl<double, double> avl_tree;
  avl_tree.insert(5.1, 50);
  avl_tree.insert(6.1, 50);
  avl_tree.insert(7.1, 50);
  avl_tree.insert(8.1, 50);
  avl_tree.insert(9.1, 50);
  avl_tree.insert(1.10, 50);
  avl_tree.insert(1.11, 50);
  avl_tree.insert(1.12, 50);
  avl_tree.insert(1.13, 50);
  avl_tree.insert(1.14, 50);
  avl_tree.insert(1.15, 50);
  avl_tree.insert(1.16, 50);
  avl_tree.insert(1.17, 50);
  avl_tree.insert(1.18, 50);
  auto it = avl_tree.begin();
  EXPECT_EQ(1.10, it->first);
}

TEST(AvlFind, FindDefault) {
  s21::avl<int, int> avl_tree = {{10, 10}, {7, 10},  {12, 10}, {4, 10},
                                 {8, 10},  {11, 10}, {15, 10}, {2, 10},
                                 {6, 10},  {9, 10},  {16, 10}, {5, 10}};
  auto it = avl_tree.find(6);
  avl_tree.remove(7);
  EXPECT_EQ(6, it->first);
}

TEST(AvlInsert, InsertWrongValue) {
  s21::avl<int, int> avl_tree = {{5, 50}, {6, 60}, {7, 70}};

  std::pair<typename s21::avl<int, int>::iterator, bool> result =
      avl_tree.insert(5, 40);

  ASSERT_EQ(result.first->first, 5);
  ASSERT_EQ(result.first->second, 50);
  EXPECT_FALSE(result.second);
}

TEST(AvlInsert, InsertWrongValue_1) {
  s21::avl<int, int> avl_tree = {{5, 50}, {6, 60}, {7, 70}};

  std::pair<typename s21::avl<int, int>::iterator, bool> result =
      avl_tree.insert(5, 40);

  ASSERT_EQ(result.first->first, 5);
  ASSERT_EQ(result.first->second, 50);
  EXPECT_FALSE(result.second);
}

TEST(AvlInsert, InsertWrongValue_2) {
  s21::avl<int, int> avl_tree = {{5, 50}, {6, 60}, {7, 70}};

  std::pair<typename s21::avl<int, int>::iterator, bool> result =
      avl_tree.insert(8, 80);

  ASSERT_EQ(result.first->first, 8);
  ASSERT_EQ(result.first->second, 80);
  EXPECT_TRUE(result.second);
}

TEST(AvlOperator, OperatorTest) {
  s21::avl<int, int> avl_tree = {{5, 50}, {6, 60}, {7, 70}};
  s21::avl<int, int> copie_tree(avl_tree);

  EXPECT_EQ(avl_tree.size(), copie_tree.size());
}

TEST(AvlOperator, operator_move) {
  s21::avl<int, int> avl_tree = {{5, 50}, {6, 60}, {7, 70}};
  s21::avl<int, int> copied_tree = std::move(avl_tree);
}

TEST(AvlConstructor, ConstructorInitList) {
  s21::avl<int, int> avl_tree = {{5, 50}, {6, 60}, {7, 70}};
  s21::avl<int, int> copied_tree(avl_tree);
  auto it = copied_tree.begin();
  EXPECT_EQ(it->first, 5);
}

TEST(AvlConstructor, CopyConstructorIntTest) {
  s21::avl<int, int> avl_tree = {{5, 50}, {6, 60}, {7, 70}};
  s21::avl<int, int> copied_tree(avl_tree);
  auto it = copied_tree.begin();
  EXPECT_EQ(it->first, 5);
}

TEST(AvlConstructor, CopyConstructorDoubleTest) {
  s21::avl<double, double> avl_tree = {{3.5, 35.5}, {6.7, 67.7}, {9.1, 91.9}};
  s21::avl<double, double> copied_tree(avl_tree);
  auto it = copied_tree.begin();
  EXPECT_DOUBLE_EQ(it->first, 3.5);
}

TEST(AvlConstructor, CopyConstructorStringTest) {
  s21::avl<std::string, int> avl_tree = {
      {"apple", 10}, {"banana", 20}, {"orange", 30}};
  s21::avl<std::string, int> copied_tree(avl_tree);
  auto it = copied_tree.begin();
  EXPECT_EQ(it->first, "apple");
}

TEST(AvlOperator, OperatorCopy) {
  s21::avl<std::string, int> avl_tree = {
      {"apple", 10}, {"banana", 20}, {"orange", 30}};
  s21::avl<std::string, int> copy_tree;
  copy_tree = avl_tree;
}

TEST(AvlOperator, OperatorMove) {
  s21::avl<std::string, int> avl_tree = {
      {"apple", 10}, {"banana", 20}, {"orange", 30}};
  s21::avl<std::string, int> copy_tree;
  copy_tree = std::move(avl_tree);
}

TEST(AvlOperator, IncrementOperatorTest2) {
  s21::avl<std::string, std::string> avl_tree = {
      {"apple", "red"}, {"banana", "yellow"}, {"orange", "orange"}};

  auto it = avl_tree.begin();

  ++it;
  EXPECT_EQ(it->first, "banana");
  EXPECT_EQ(it->second, "yellow");
}

TEST(AvlOperator, DecrementOperatorTest1) {
  s21::avl<std::string, std::string> avl_tree = {
      {"apple", "red"}, {"banana", "yellow"}, {"orange", "orange"}};

  auto it = avl_tree.end();
  --it;
  EXPECT_EQ(it->first, "orange");
  EXPECT_EQ(it->second, "orange");
}

TEST(AvlOperator, DecrementOperatorTest2) {
  s21::avl<std::string, std::string> avl_tree = {
      {"apple", "red"}, {"banana", "yellow"}, {"orange", "orange"}};

  auto it = avl_tree.begin();

  EXPECT_EQ(it->first, "apple");
}

TEST(AvlOperator, DecrementStringTest3) {
  s21::avl<std::string, std::string> avl_tree = {
      {"apple", "red"}, {"banana", "yellow"}, {"orange", "orange"}};

  auto it = avl_tree.begin();

  avl_tree.insert("orange", "SUPERPUPERORANGE");

  EXPECT_EQ(it->first, "apple");
}

TEST(AvlOperator, DecrementgetMaxVal) {
  s21::avl<std::string, std::string> avl_tree = {
      {"apple", "red"}, {"banana", "yellow"}, {"orange", "orange"}};
  auto it = avl_tree.end();
  --it;
  EXPECT_EQ(avl_tree.get_max_value()->key_val.first, it->first);
}

TEST(AvlOperator, DecrementgetMinVal) {
  s21::avl<std::string, std::string> avl_tree = {
      {"apple", "red"}, {"banana", "yellow"}, {"orange", "orange"}};
  auto it = avl_tree.begin();
  EXPECT_EQ(avl_tree.get_min_value()->key_val.first, it->first);
}

TEST(AvlFind, MaxValueIntTest) {
  s21::avl<int, int> avl_tree = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_EQ(avl_tree.get_max_value()->key_val.first, 3);
}

TEST(AvlFind, MinValueDoubleTest) {
  s21::avl<double, double> avl_tree = {{1.5, 15.5}, {2.7, 27.7}, {3.9, 39.9}};
  EXPECT_EQ(avl_tree.get_min_value()->key_val.first, 1.5);
}

TEST(AvlFind, MaxValueStringTest) {
  s21::avl<std::string, int> avl_tree = {
      {"apple", 10}, {"banana", 20}, {"orange", 30}};
  EXPECT_EQ(avl_tree.get_max_value()->key_val.first, "orange");
}

TEST(AvlFind, MinValueCharTest) {
  s21::avl<char, int> avl_tree = {{'a', 1}, {'b', 2}, {'c', 3}};
  EXPECT_EQ(avl_tree.get_min_value()->key_val.first, 'a');
}

TEST(AvlRemove, NotFoundKeyTest) {
  s21::avl<int, int> avl_tree = {{1, 10}, {2, 20}, {3, 30}};
  auto it = avl_tree.begin();
  avl_tree.remove(0);
  EXPECT_FALSE(avl_tree.end() == it);
}

TEST(AvlRemove, RemoveEmtyTree) {
  s21::avl<int, int> avl_tree = {{1, 10}};
  auto it = avl_tree.begin();
  avl_tree.remove(1);
  EXPECT_FALSE(avl_tree.end() == it);
}

TEST(AvlRemove, RemoveEmtyTree1) {
  s21::avl<int, int> avl_tree = {{1, 10}, {2, 10}};
  auto it = avl_tree.begin();
  avl_tree.remove(1);
  avl_tree.remove(2);
  EXPECT_FALSE(avl_tree.end() == it);
}

TEST(AvlRemove, RemoveEmtyTree2) {
  s21::avl<int, int> avl_tree = {{1, 10}, {2, 10}, {3, 10}};
  auto it = avl_tree.begin();
  avl_tree.remove(2);
  avl_tree.remove(1);
  avl_tree.remove(3);
  EXPECT_FALSE(avl_tree.end() == it);
}

TEST(AvlRemove, TestMax1) {
  s21::avl<int, int> avl_tree;
  for (int i = 0, j = 0; i < 1000; ++i, j++) {
    avl_tree.insert(i, j);
  }
  avl_tree.remove(1);
  auto it = avl_tree.begin();
  for (int i = 0; i < 1000; ++i) {
    ++it;
  }
  //
}

TEST(AvlRemove, TestMin1) {
  s21::avl<int, int> avl_tree;
  for (int i = 0, j = 0; i < 1000; ++i, j++) {
    avl_tree.insert(i, j);
  }
  avl_tree.remove(1);
  auto it = avl_tree.begin();
  for (int i = 1000; i > 0; --i) {
    --it;
  }
}

TEST(AvlRemove, TestMin2) {
  s21::avl<int, int> avl_tree{{1, 10}, {2, 20}};
  avl_tree.remove(1);
}

TEST(AvlFind, KeyNotFound1) {
  s21::avl<int, int> avl_tree{{1, 10}, {2, 20}, {3, 30}};
  EXPECT_TRUE(avl_tree.find(13) == avl_tree.end());
}

TEST(AvlOperator, Compare) {
  s21::avl<int, int> avl_tree_1{{1, 10}, {2, 20}, {3, 30}};
  s21::avl<int, int> avl_tree_2{{1, 10}, {2, 20}, {3, 30}};
  EXPECT_TRUE(avl_tree_1 == avl_tree_2);
}

TEST(AvlOperator, EmptyTrees) {
  s21::avl<int, int> avl_tree_1;
  s21::avl<int, int> avl_tree_2;
  EXPECT_TRUE(avl_tree_1 == avl_tree_2);
}

TEST(AvlOperator, EmptyWithNonEmpty) {
  s21::avl<int, int> avl_tree_1;
  s21::avl<int, int> avl_tree_2{{1, 10}, {2, 20}, {3, 30}};
  EXPECT_FALSE(avl_tree_1 == avl_tree_2);
}

TEST(AvlOperator, DifferentSizes) {
  s21::avl<int, int> avl_tree_1{{1, 10}, {2, 20}};
  s21::avl<int, int> avl_tree_2{{1, 10}, {2, 20}, {3, 30}};
  EXPECT_FALSE(avl_tree_1 == avl_tree_2);
}

TEST(AvlOperator, DifferentOrder) {
  s21::avl<int, int> avl_tree_1{{1, 10}, {2, 20}, {3, 30}};
  s21::avl<int, int> avl_tree_2{{3, 30}, {2, 20}, {1, 10}};
  EXPECT_TRUE(avl_tree_1 == avl_tree_2);
}

TEST(AvlOperator, DifferentTypes) {
  s21::avl<double, double> avl_tree_int{{1, 10}, {2, 20}, {3, 30}};
  s21::avl<double, double> avl_tree_double{
      {1.1, 10.1}, {2.2, 20.2}, {3.3, 30.3}};
  EXPECT_FALSE(avl_tree_int == avl_tree_double);
}

TEST(AvlOperator, SameStringTypes) {
  s21::avl<std::string, int> avl_tree_string{
      {"one", 10}, {"two", 20}, {"three", 30}};
  s21::avl<std::string, int> avl_tree_string_same{
      {"one", 10}, {"two", 20}, {"three", 30}};
  EXPECT_TRUE(avl_tree_string == avl_tree_string_same);
}

TEST(AvlOperator, DiferensStringTypes) {
  s21::avl<std::string, int> avl_tree_string{{"one", 10}, {"two", 20}};
  s21::avl<std::string, int> avl_tree_string_same{
      {"one", 10}, {"two", 20}, {"three", 30}};
  EXPECT_FALSE(avl_tree_string == avl_tree_string_same);
}

TEST(AvlOperator, IdenticalTrees) {
  s21::avl<int, int> avl_tree_1{{1, 10}, {2, 20}, {3, 30}};
  s21::avl<int, int> avl_tree_2{{1, 10}, {2, 20}, {3, 30}};
  EXPECT_TRUE(avl_tree_1 == avl_tree_2);
}

TEST(AvlFind, KeyNotFound) {
  s21::avl<int, int> avl_tree{{1, 10}, {2, 20}, {3, 30}};
  EXPECT_TRUE(avl_tree.find(0) == avl_tree.end());
}

TEST(AvlFind, KeyNotFound2) {
  s21::avl<int, int> avl_tree{{1, 10}, {2, 20}, {3, 30}};
  EXPECT_TRUE(avl_tree.find(0) == avl_tree.end());
}

TEST(AvlFind, KeyNotFoundString) {
  s21::avl<std::string, int> avl_tree{
      {"apple", 10}, {"banana", 20}, {"orange", 30}};
  EXPECT_TRUE(avl_tree.find("pear") == avl_tree.end());
}

TEST(AvlFind, KeyNotFoundFloat) {
  s21::avl<float, int> avl_tree{{1.5f, 10}, {2.5f, 20}, {3.5f, 30}};
  EXPECT_TRUE(avl_tree.find(4.5f) == avl_tree.end());
}

TEST(AvlFind, RootIsEmpty) {
  s21::avl<int, int> avl_tree;
  EXPECT_TRUE(avl_tree.find(10) == avl_tree.end());
}

TEST(AvlFind, EmptyMaxValue) {
  s21::avl<int, int> avl_tree;
  EXPECT_TRUE(avl_tree.get_max_value()->key_val.first == avl_tree.end()->first);
}

TEST(AvlTestMerge, Test0) {
  s21::avl<int, std::string> a{{1, "apple"}, {5, "pear"}, {10, "banana"}};
  s21::avl<int, std::string> c{
      {2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};

  a.merge(c);

  EXPECT_EQ(a.size(), 6);
}

TEST(AvlMergeTest, MergeEmptyAvls) {
  s21::avl<int, std::string> avl1;
  s21::avl<int, std::string> avl2;

  avl1.merge(avl2);

  EXPECT_TRUE(avl1.size() == 0);
  EXPECT_TRUE(avl2.size() == 0);
}

TEST(AvlMergeTest, MergeNonEmptyAvlIntoEmptyAvl) {
  s21::avl<int, std::string> avl1;
  s21::avl<int, std::string> avl2 = {{1, "one"}, {2, "two"}, {3, "three"}};

  avl1.merge(avl2);

  EXPECT_EQ(avl1.size(), 3);
  EXPECT_TRUE(avl2.size() == 0);
}

TEST(AvlMergeTest, MergeNonEmptyAvlIntoNonEmptyAvl) {
  s21::avl<int, std::string> avl1 = {{1, "one"}, {2, "two"}};
  s21::avl<int, std::string> avl2 = {{3, "three"}, {4, "four"}};

  avl1.merge(avl2);

  EXPECT_EQ(avl1.size(), 4);
  EXPECT_TRUE(avl1.find(1)->second == "one");
  EXPECT_TRUE(avl1.find(2)->second == "two");
  EXPECT_TRUE(avl1.find(3)->second == "three");
  EXPECT_TRUE(avl1.find(4)->second == "four");

  EXPECT_TRUE(avl2.size() == 0);
}

TEST(AvlMergeTest, MergeWithDuplicates) {
  s21::avl<int, std::string> avl1 = {{1, "one"}, {2, "two"}, {3, "three"}};
  s21::avl<int, std::string> avl2 = {{3, "3"}, {4, "four"}};

  avl1.merge(avl2);

  EXPECT_EQ(avl1.size(), 4);
  EXPECT_TRUE(avl1.find(1)->second == "one");
  EXPECT_TRUE(avl1.find(2)->second == "two");
  EXPECT_TRUE(avl1.find(3)->second == "three");
  EXPECT_TRUE(avl1.find(4)->second == "four");

  EXPECT_EQ(avl2.size(), 1);
  EXPECT_EQ(avl2.find(3)->second, "3");
}

TEST(AvlMergeTest, SelfMerge) {
  s21::avl<int, std::string> my_avl = {{1, "one"}, {2, "two"}};

  my_avl.merge(my_avl);

  EXPECT_EQ(my_avl.size(), 2);

  EXPECT_TRUE(my_avl.find(1)->second == "one");
  EXPECT_TRUE(my_avl.find(2)->second == "two");
}

TEST(AvlSwapTest, SwapEmptyAvls) {
  s21::avl<int, std::string> avl1;
  s21::avl<int, std::string> avl2;

  avl1.swap(avl2);

  EXPECT_TRUE(avl1.size() == 0);
  EXPECT_TRUE(avl2.size() == 0);
}

TEST(AvlSwapTest, SwapEmptyAvlWithNonEmptyAvl) {
  s21::avl<int, std::string> avl1;
  s21::avl<int, std::string> avl2 = {{1, "one"}, {2, "two"}, {3, "three"}};

  avl1.swap(avl2);

  EXPECT_EQ(avl1.size(), 3);
  EXPECT_TRUE(avl2.size() == 0);
}

TEST(AvlSwapTest, SwapNonEmptyAvlWithEmptyAvl) {
  s21::avl<int, std::string> avl1 = {{1, "one"}, {2, "two"}, {3, "three"}};
  s21::avl<int, std::string> avl2;

  avl1.swap(avl2);

  EXPECT_EQ(avl2.size(), 3);
  EXPECT_TRUE(avl1.size() == 0);
}

TEST(AvlSwapTest, SwapNonEmptyAvls) {
  s21::avl<int, std::string> avl1 = {{1, "one"}, {2, "two"}, {3, "three"}};
  s21::avl<int, std::string> avl2 = {{4, "four"}, {5, "five"}};

  size_t size_avl1 = avl1.size();
  size_t size_avl2 = avl2.size();

  avl1.swap(avl2);

  EXPECT_EQ(avl1.size(), size_avl2);
  EXPECT_EQ(avl2.size(), size_avl1);
}

TEST(AvlSwapTest, ValidIteratorsAfterSwap) {
  s21::avl<int, std::string> avl1 = {{1, "one"}, {2, "two"}, {3, "three"}};
  s21::avl<int, std::string> avl2 = {{4, "four"}, {5, "five"}};

  auto it_avl1_begin = avl1.begin();
  auto it_avl2_begin = avl2.begin();

  avl1.swap(avl2);

  EXPECT_TRUE(it_avl1_begin == avl2.begin());
  EXPECT_TRUE(it_avl2_begin == avl1.begin());
}