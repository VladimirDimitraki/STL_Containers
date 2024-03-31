#include "s21_map.h"

#include <gtest/gtest.h>

#include <map>

TEST(MapConstructors, Default) {
  s21::map<int, int> own;
  std::map<int, int> orig;

  EXPECT_EQ(own.size(), orig.size());
}

TEST(MapConstructors, InitializerListInt) {
  s21::map<int, int> own = {{5, 50}, {6, 60}, {7, 70}};
  std::map<int, int> orig = {{5, 50}, {6, 60}, {7, 70}};

  EXPECT_EQ(own.size(), orig.size());
  EXPECT_EQ(own.begin()->first, orig.begin()->first);
}

TEST(MapConstructors, InitializerListFloat) {
  s21::map<float, float> own = {{5.4, 50.1}, {1.6, 6.0}, {7, 70}};
  std::map<float, float> orig = {{5.4, 50.1}, {1.6, 6.0}, {7, 70}};

  EXPECT_EQ(own.size(), orig.size());
  EXPECT_EQ(own.begin()->first, orig.begin()->first);
}

TEST(MapConstructors, InitializerListString) {
  s21::map<std::string, int> own = {{"Amir", 50}, {"Ivan", 60}, {"Vova", 70}};
  std::map<std::string, int> orig = {{"Amir", 50}, {"Ivan", 60}, {"Vova", 70}};

  EXPECT_EQ(own.size(), orig.size());
  EXPECT_EQ(own.begin()->first, orig.begin()->first);
}

TEST(MapConstructors, CopyConstructor) {
  s21::map<int, int> A = {{5, 50}, {6, 60}, {7, 70}};
  s21::map<int, int> copied = A;
  EXPECT_EQ(A.size(), copied.size());
}

TEST(MapConstructors, CopyAssingent) {
  s21::map<int, int> A = {{5, 50}, {6, 60}, {7, 70}};
  s21::map<int, int> copied;
  copied = A;
  EXPECT_EQ(A.size(), copied.size());
}

TEST(MapConstructors, MoveConstructor) {
  s21::map<int, int> A = {{5, 50}, {6, 60}, {7, 70}};
  s21::map<int, int> expected = {{5, 50}, {6, 60}, {7, 70}};
  s21::map<int, int> moved = std::move(A);
  EXPECT_TRUE(A.empty());
  EXPECT_EQ(expected.size(), moved.size());
}

TEST(MapConstructors, MoveAssigment) {
  s21::map<int, int> A = {{5, 50}, {6, 60}, {7, 70}};
  s21::map<int, int> expected = {{5, 50}, {6, 60}, {7, 70}};
  s21::map<int, int> moved;
  moved = std::move(A);
  EXPECT_TRUE(A.empty());
  EXPECT_EQ(expected.size(), moved.size());
}

TEST(MapIterator, MapIteratorPlus) {
  s21::map<int, int> A = {{5, 50}, {6, 60}, {7, 70}, {8, 80}};
  auto itr = A.begin();
  itr++;
  EXPECT_EQ(itr->first, 6);
  EXPECT_EQ(itr->second, 60);
  ++itr;
  EXPECT_EQ(itr->first, 7);
  EXPECT_EQ(itr->second, 70);
}

TEST(MapIterator, MapIteratorMinus) {
  s21::map<int, int> A = {{5, 50}, {6, 60}, {7, 70}, {8, 80}};
  auto itr = A.end();
  --itr;
  EXPECT_EQ(itr->first, 8);
  EXPECT_EQ(itr->second, 80);
  itr--;
  EXPECT_EQ(itr->first, 7);
  EXPECT_EQ(itr->second, 70);
}

TEST(MapIterator, MapIteratorString) {
  s21::map<std::string, std::string> A = {{"Amir", "raisinib"},
                                          {"Ivan", "rachelga"},
                                          {"Vladimir", "melaniad"},
                                          {"No name", "No nickname"}};
  auto itr = A.begin();
  EXPECT_EQ(itr->first, "Amir");
  EXPECT_EQ(itr->second, "raisinib");
  ++itr;
  EXPECT_EQ(itr->first, "Ivan");
  EXPECT_EQ(itr->second, "rachelga");
}

TEST(MapIterator, MapIteratorStringDec) {
  s21::map<std::string, std::string> A = {{"Amir", "raisinib"},
                                          {"Ivan", "rachelga"},
                                          {"Vladimir", "melaniad"},
                                          {"No name", "No nickname"}};
  auto itr = A.begin();
  --itr;
  EXPECT_TRUE(itr == A.end());
}

TEST(MapFind, FindAndModify) {
  s21::map<std::string, std::string> A = {{"Amir", "raisinib"},
                                          {"Ivan", "rachelga"},
                                          {"Vladimir", "melaniad"},
                                          {"Margo", "unknown"}};
  auto it = A.find("Margo");
  EXPECT_EQ(it->second, "unknown");
  it->second = "dreamcat";
  EXPECT_EQ(A.find("Margo")->second, "dreamcat");
}

TEST(MapFind, JustFind) {
  s21::map<int, std::string> A = {
      {1, "raisinib"}, {2, "rachelga"}, {3, "melaniad"}, {4, "dreamcat"}};
  auto it = A.find(2);
  EXPECT_EQ(it->second, "rachelga");
}

TEST(MapFind, FindNonExistendKey) {
  s21::map<std::string, std::string> A = {
      {"Amir", "raisinib"}, {"Ivan", "rachelga"}, {"Vladimir", "melaniad"}};
  auto it = A.find("Margo");
  EXPECT_TRUE(it == A.end());
}

TEST(MapClear, Test1) {
  s21::map<std::string, std::string> A = {{"Amir", "raisinib"},
                                          {"Ivan", "rachelga"},
                                          {"Vladimir", "melaniad"},
                                          {"Margo", "unknown"}};
  A.clear();
  EXPECT_EQ(A.size(), 0);
  EXPECT_TRUE(A.empty());
}

TEST(MapClear, Test2) {
  s21::map<std::string, std::string> A = {{"Amir", "raisinib"},
                                          {"Ivan", "rachelga"},
                                          {"Vladimir", "melaniad"},
                                          {"Margo", "unknown"}};
  A.clear();
  EXPECT_EQ(A.size(), 0);
}

TEST(MapClear, ClearEmptyMap) {
  s21::map<std::string, std::string> my_map;
  my_map.clear();
  EXPECT_EQ(my_map.size(), 0);
}

TEST(MapAt, Test0) {
  s21::map<int, int> a{{1, 10}, {2, 20}, {3, 30}};
  std::map<int, int> b{{1, 10}, {2, 20}, {3, 30}};

  EXPECT_EQ(a.at(2), b.at(2));
  EXPECT_EQ(a.at(2), 20);
  EXPECT_ANY_THROW(a.at(5));
  EXPECT_ANY_THROW(b.at(5));
}

TEST(MapSquareBrackets, Test0) {
  s21::map<int, int> a{{1, 10}, {2, 20}, {3, 30}};
  std::map<int, int> b{{1, 10}, {2, 20}, {3, 30}};
  b[2] = 5;
  a[2] = 5;
  EXPECT_EQ(a[2], 5);
  EXPECT_EQ(b[2], 5);
}

TEST(MapSquareBrackets, Test1) {
  s21::map<int, int> a{{1, 10}, {2, 20}, {3, 30}};
  std::map<int, int> b{{1, 10}, {2, 20}, {3, 30}};

  b[4] = 5;
  a[4] = 5;
  EXPECT_EQ(a[4], 5);
  EXPECT_EQ(b[4], 5);
  EXPECT_EQ(a[3], 30);
  EXPECT_EQ(b[3], 30);
}

TEST(MapSquareBrackets, Test2) {
  s21::map<std::string, std::string> a = {{"Amir", "raisinib"},
                                          {"Ivan", "rachelga"},
                                          {"Vladimir", "melaniad"},
                                          {"Margo", "unknown"}};
  EXPECT_EQ(a["Ivan"], "rachelga");
}

TEST(MapSquareBrackets, Test3) {
  s21::map<std::string, std::string> a = {
      {"Amir", "raisinib"}, {"Ivan", "rachelga"}, {"Vladimir", "melaniad"}};
  a["Margo"] = "dreamcat";
  EXPECT_EQ(a["Margo"], "dreamcat");
}

TEST(MapInsert, BaseInsert) {
  s21::map<std::string, std::string> my_map = {{"Amir", "raisinib"}};
  auto insert_res = my_map.insert({"Ivan", "rachelga"});
  EXPECT_TRUE(insert_res.second);
  EXPECT_EQ(insert_res.first->first, "Ivan");
  EXPECT_EQ(insert_res.first->second, "rachelga");
}

TEST(MapInsert, InsertExistingKey) {
  s21::map<std::string, std::string> my_map = {{"Amir", "raisinib"},
                                               {"Ivan", "rachelga"}};
  auto insert_res = my_map.insert({"Ivan", "Liyaskin"});
  EXPECT_FALSE(insert_res.second);
  EXPECT_EQ(insert_res.first->first, "Ivan");
  EXPECT_EQ(insert_res.first->second, "rachelga");
}

TEST(MapInsert, InsertInEmptyMap) {
  s21::map<std::string, std::string> my_map;
  auto insert_res = my_map.insert({"Ivan", "rachelga"});
  EXPECT_TRUE(insert_res.second);
  EXPECT_EQ(my_map.size(), 1);
  EXPECT_EQ(insert_res.first->first, "Ivan");
  EXPECT_EQ(insert_res.first->second, "rachelga");
}

TEST(MapInsert, InsertMultipleElements) {
  s21::map<std::string, std::string> my_map;

  my_map.insert({"Ivan", "rachelga"});
  my_map.insert({"Amir", "raisinib"});
  my_map.insert({"Vladimir", "melaniad"});

  EXPECT_EQ(my_map.size(), 3);
  EXPECT_EQ(my_map["Ivan"], "rachelga");
  EXPECT_EQ(my_map["Vladimir"], "melaniad");
  EXPECT_EQ(my_map["Amir"], "raisinib");
}

TEST(MapInsertByKeyVal, BaseInsert) {
  s21::map<std::string, std::string> my_map = {{"Amir", "raisinib"}};
  auto insert_res = my_map.insert("Ivan", "rachelga");
  EXPECT_TRUE(insert_res.second);
  EXPECT_EQ(insert_res.first->first, "Ivan");
  EXPECT_EQ(insert_res.first->second, "rachelga");
}

TEST(MapInsertByKeyVal, InsertExistingKey) {
  s21::map<std::string, std::string> my_map = {{"Amir", "raisinib"},
                                               {"Ivan", "rachelga"}};
  auto insert_res = my_map.insert("Ivan", "Liyaskin");
  EXPECT_FALSE(insert_res.second);
  EXPECT_EQ(insert_res.first->first, "Ivan");
  EXPECT_EQ(insert_res.first->second, "rachelga");
}

TEST(MapInsertByKeyVal, InsertInEmptyMap) {
  s21::map<std::string, std::string> my_map;
  auto insert_res = my_map.insert("Ivan", "rachelga");
  EXPECT_TRUE(insert_res.second);
  EXPECT_EQ(my_map.size(), 1);
  EXPECT_EQ(insert_res.first->first, "Ivan");
  EXPECT_EQ(insert_res.first->second, "rachelga");
}

TEST(MapInsertByKeyVal, InsertMultipleElements) {
  s21::map<std::string, std::string> my_map;

  my_map.insert("Ivan", "rachelga");
  my_map.insert("Amir", "raisinib");
  my_map.insert("Vladimir", "melaniad");

  EXPECT_EQ(my_map.size(), 3);
  EXPECT_EQ(my_map["Ivan"], "rachelga");
  EXPECT_EQ(my_map["Vladimir"], "melaniad");
  EXPECT_EQ(my_map["Amir"], "raisinib");
}

TEST(MapInsertOrAssign, AssignValue) {
  s21::map<std::string, std::string> my_map = {{"Amir", "unknown"},
                                               {"Ivan", "unknown"}};

  auto insert_res = my_map.insert_or_assign("Ivan", "rachelga");
  EXPECT_EQ(my_map["Ivan"], "rachelga");
  EXPECT_FALSE(insert_res.second);
}

TEST(MapInsertOrAssign, InsertValue) {
  s21::map<std::string, std::string> my_map = {{"Amir", "unknown"},
                                               {"Ivan", "unknown"}};
  auto insert_res = my_map.insert_or_assign("Vladimir", "melaniad");
  EXPECT_TRUE(insert_res.second);
  EXPECT_EQ(my_map["Vladimir"], "melaniad");
}

TEST(MapInsertOrAssign, MultipleInsertOrAssign) {
  s21::map<std::string, std::string> my_map = {{"Amir", "unknown"},
                                               {"Ivan", "unknown"}};
  my_map.insert_or_assign("Amir", "raisinib");
  my_map.insert_or_assign("Vladimir", "melaniad");
  my_map.insert_or_assign("Ivan", "rachelga");
  my_map.insert_or_assign("Arsen", "danialle");

  EXPECT_EQ(my_map["Vladimir"], "melaniad");
  EXPECT_EQ(my_map["Amir"], "raisinib");
  EXPECT_EQ(my_map["Ivan"], "rachelga");
  EXPECT_EQ(my_map["Arsen"], "danialle");
  EXPECT_EQ(my_map.size(), 4);
}

TEST(MapErase, EmptyMap) {
  s21::map<int, int> my_map;
  EXPECT_EQ(0, my_map.size());
  my_map.erase(my_map.begin());
  EXPECT_EQ(0, my_map.size());
}

TEST(MapErase, ExistingElement) {
  s21::map<int, int> my_map = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_EQ(3, my_map.size());
  my_map.erase(++my_map.begin());
  EXPECT_EQ(2, my_map.size());
  EXPECT_FALSE(my_map.contains(2));
}

TEST(MapErase, AllElements) {
  s21::map<int, int> my_map = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_EQ(3, my_map.size());
  my_map.erase(my_map.begin());
  my_map.erase(my_map.begin());
  my_map.erase(my_map.begin());
  EXPECT_EQ(0, my_map.size());
}

TEST(MapErase, ReturnValue) {
  s21::map<int, std::string> my_map = {
      {1, "raisinib"}, {2, "rachelga"}, {3, "melaniad"}};
  auto it = my_map.begin();
  EXPECT_EQ(it->first, 1);
  it = my_map.erase(it);
  EXPECT_EQ(it->first, 2);
}

TEST(MapErase, EraseSearchedElements) {
  s21::map<std::string, std::string> my_map = {{"Amir", "raisinib"},
                                               {"Ivan", "rachelga"},
                                               {"Vladimir", "melaniad"},
                                               {"Margo", "unknown"}};
  my_map.erase(my_map.find("Margo"));
  EXPECT_FALSE(my_map.contains("Margo"));
}

TEST(MapContains, EmptyMap) {
  s21::map<int, std::string> my_map;
  EXPECT_FALSE(my_map.contains(5));
}

TEST(MapContains, SingleElementPresent) {
  s21::map<int, std::string> my_map = {{1, "one"}};
  EXPECT_TRUE(my_map.contains(1));
}

TEST(MapContains, SingleElementAbsent) {
  s21::map<int, std::string> my_map = {{1, "one"}};
  EXPECT_FALSE(my_map.contains(2));
}

TEST(MapContains, MultipleElementsPresent) {
  s21::map<char, int> my_map = {{'a', 1}, {'b', 2}, {'c', 3}};
  EXPECT_TRUE(my_map.contains('b'));
}

TEST(MapContains, MultipleElementsAbsent) {
  s21::map<char, int> my_map = {{'a', 1}, {'b', 2}, {'c', 3}};
  EXPECT_FALSE(my_map.contains('d'));
}

TEST(MapMaxSize, IntTest) {
  s21::map<int, int> my_map = {{1, 10}, {2, 20}};
  std::map<int, int> org_map = {{1, 10}, {2, 20}};
  EXPECT_EQ(my_map.max_size(), org_map.max_size());
}

TEST(MapMaxSize, DoubleTest) {
  s21::map<double, double> my_map;
  std::map<double, double> org_map;
  EXPECT_EQ(my_map.max_size(), org_map.max_size());
}

TEST(MapMaxSize, StringTest) {
  s21::map<std::string, std::string> my_map;
  std::map<std::string, std::string> org_map;
  EXPECT_EQ(my_map.max_size(), org_map.max_size());
}

TEST(MapMaxSize, LongLongTest) {
  s21::map<long long, long long> my_map;
  std::map<long long, long long> org_map;
  EXPECT_EQ(my_map.max_size(), org_map.max_size());
}

TEST(MapSwapTest, SwapEmptyMaps) {
  s21::map<int, std::string> map1;
  s21::map<int, std::string> map2;
}
//   map1.swap(map2);

//   EXPECT_TRUE(map1.empty());
//   EXPECT_TRUE(map2.empty());
// }

TEST(MapSwapTest, SwapEmptyMapWithNonEmptyMap) {
  s21::map<int, std::string> map1;
  s21::map<int, std::string> map2 = {{1, "one"}, {2, "two"}, {3, "three"}};

  map1.swap(map2);

  EXPECT_EQ(map1.size(), 3);
  EXPECT_TRUE(map2.empty());
}

TEST(MapSwapTest, SwapNonEmptyMapWithEmptyMap) {
  s21::map<int, std::string> map1 = {{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> map2;

  map1.swap(map2);

  EXPECT_EQ(map2.size(), 3);
  EXPECT_TRUE(map1.empty());
}

TEST(MapSwapTest, SwapNonEmptyMaps) {
  s21::map<int, std::string> map1 = {{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> map2 = {{4, "four"}, {5, "five"}};

  size_t size_map1 = map1.size();
  size_t size_map2 = map2.size();

  map1.swap(map2);

  EXPECT_EQ(map1.size(), size_map2);
  EXPECT_EQ(map2.size(), size_map1);
}

TEST(MapSwapTest, ValidIteratorsAfterSwap) {
  s21::map<int, std::string> map1 = {{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> map2 = {{4, "four"}, {5, "five"}};

  auto it_map1_begin = map1.begin();
  auto it_map2_begin = map2.begin();

  map1.swap(map2);

  EXPECT_TRUE(it_map1_begin == map2.begin());
  EXPECT_TRUE(it_map2_begin == map1.begin());
}

TEST(MapTestMerge, Test0) {
  s21::map<int, std::string> a{{1, "apple"}, {5, "pear"}, {10, "banana"}};
  s21::map<int, std::string> c{
      {2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};
  std::map<int, std::string> b{{1, "apple"}, {5, "pear"}, {10, "banana"}};
  std::map<int, std::string> d{
      {2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};

  b.merge(d);
  a.merge(c);

  EXPECT_EQ(a[5], "pear");
  EXPECT_EQ(b[5], "pear");
}

TEST(MapTestMerge, Test1) {
  s21::map<int, std::string> a{{1, "apple"}, {5, "pear"}, {10, "banana"}};
  s21::map<int, std::string> c{
      {2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};

  a.merge(c);

  EXPECT_EQ(a[2], "zorro");
  EXPECT_EQ(a[4], "batman");
  EXPECT_EQ(a[5], "pear");
  EXPECT_EQ(a[8], "alpaca");
}

TEST(MapTestMerge, Test2) {
  s21::map<int, std::string> a{{1, "apple"}, {5, "pear"}, {10, "banana"}};
  s21::map<int, std::string> c{
      {2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};

  a.merge(c);

  EXPECT_EQ(a.size(), 6);
}

TEST(MapTestMerge, Test3) {
  s21::map<int, std::string> a{{1, "apple"}, {5, "pear"}, {10, "banana"}};
  s21::map<int, std::string> c{
      {2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};

  a.merge(c);

  EXPECT_EQ(a[1], "apple");
}

TEST(MapMergeTest, MergeEmptyMaps) {
  s21::map<int, std::string> map1;
  s21::map<int, std::string> map2;

  map1.merge(map2);

  EXPECT_TRUE(map1.empty());
  EXPECT_TRUE(map2.empty());
}

TEST(MapMergeTest, MergeNonEmptyMapIntoEmptyMap) {
  s21::map<int, std::string> map1;
  s21::map<int, std::string> map2 = {{1, "one"}, {2, "two"}, {3, "three"}};

  map1.merge(map2);

  EXPECT_EQ(map1.size(), 3);
  EXPECT_TRUE(map2.empty());
}

TEST(MapMergeTest, MergeNonEmptyMapIntoNonEmptyMap) {
  s21::map<int, std::string> map1 = {{1, "one"}, {2, "two"}};
  s21::map<int, std::string> map2 = {{3, "three"}, {4, "four"}};

  map1.merge(map2);

  EXPECT_EQ(map1.size(), 4);
  EXPECT_EQ(map1[1], "one");
  EXPECT_EQ(map1[2], "two");
  EXPECT_EQ(map1[3], "three");
  EXPECT_EQ(map1[4], "four");

  EXPECT_TRUE(map2.empty());
}

TEST(MapMergeTest, MergeWithDuplicates) {
  s21::map<int, std::string> map1 = {{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> map2 = {{3, "3"}, {4, "four"}};

  map1.merge(map2);

  EXPECT_EQ(map1.size(), 4);
  EXPECT_EQ(map1[1], "one");
  EXPECT_EQ(map1[2], "two");
  EXPECT_EQ(map1[3], "three");
  EXPECT_EQ(map1[4], "four");

  EXPECT_EQ(map2.size(), 1);
  EXPECT_EQ(map2[3], "3");
}

TEST(MapMergeTest, SelfMerge) {
  s21::map<int, std::string> my_map = {{1, "one"}, {2, "two"}};

  my_map.merge(my_map);

  EXPECT_EQ(my_map.size(), 2);

  EXPECT_EQ(my_map[1], "one");
  EXPECT_EQ(my_map[2], "two");
}
