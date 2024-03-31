#include "S21_vector_test.h"

/*#########################  CONSTUCTORS  #########################*/

TEST(VectorConstructorDefoult, Test1) {
  s21::vector<int> v;
  std::vector<int> v2;
  EXPECT_EQ(v.size(), v2.size());
}

TEST(VectorConstructorParam, Test1) {
  s21::vector<double> v = {1.1, 1.2, 1.3};
  std::vector<double> v2 = {1.1, 1.2, 1.3};
  EXPECT_EQ(v.size(), v2.size());
  EXPECT_EQ(v.at(2), v2.at(2));
}

TEST(VectorConstructorCopy, Test1) {
  s21::vector<int> v = {5};
  s21::vector<int> v2(v);
  EXPECT_EQ(v.size(), v2.size());
  EXPECT_EQ(v.at(0), v2.at(0));

  std::vector<int> v3 = {5};

  std::vector<int> v4(v3);
  EXPECT_EQ(v2.size(), v4.size());
  EXPECT_EQ(v2.at(0), v4.at(0));
}

TEST(VectorConstructorMove, Test1) {
  s21::vector<int> v = {5};
  s21::vector<int> v2(std::move(v));

  EXPECT_EQ(v2.at(0), 5);
}

TEST(VectorDestructor, Test1) {
  bool ok_ = false;
  {
    s21::vector<int> v = {1, 5};
    ok_ = true;
  }
  EXPECT_TRUE(ok_);
}

/*#########################  OPERATOR  ###########################*/

TEST(VetcorOperatorCopy, Test1) {
  s21::vector<int> v = {100};
  s21::vector<int> v2 = v;

  std::vector<int> v3 = {100};
  std::vector<int> v4 = v3;

  EXPECT_EQ(v4.at(0), v2.at(0));
  EXPECT_EQ(v3.at(0), v.at(0));
}

TEST(VetcorOperatorMove, Test1) {
  s21::vector<int> v = {199};
  s21::vector<int> v2;
  v2 = std::move(v);

  std::vector<int> v3 = {199};
  std::vector<int> v4;
  v4 = (std::move(v3));

  EXPECT_EQ(v4.at(0), v2.at(0));
  EXPECT_EQ(v3.size(), 0);
  EXPECT_EQ(v.size(), 0);
}

TEST(VectorOperatorSquareBrackets, Test1) {
  s21::vector<int> v = {1, 9, 9};
  std::vector<int> v2 = {1, 9, 9};
  v[1] = 2;
  v2[1] = 2;
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v2[1], 2);
}

TEST(VectorOperatorSquareBrackets, Test2) {
  s21::vector<int> v = {1, 9, 9};
  std::vector<int> v2 = {1, 9, 9};

  EXPECT_EQ(v[1], v2[1]);
}

/*######################### LIB FUNC  ###########################*/

TEST(VectorTestAt, Test1) {
  s21::vector<int> v = {199};
  std::vector<int> v2 = {199};
  ASSERT_ANY_THROW(v.at(1));
  ASSERT_ANY_THROW(v2.at(1));
}

TEST(VectorTestAt, Test2) {
  s21::vector<int> v = {199};
  std::vector<int> v2 = {199};
  ASSERT_EQ(v2.at(0), v.at(0));
}

TEST(VectorTestAt, Test3) {
  s21::vector<int> v = {199};
  std::vector<int> v2 = {199};
  ASSERT_ANY_THROW(v2.at(-1));
  ASSERT_ANY_THROW(v.at(-1));
}

TEST(VectorTestFront, Test1) {
  s21::vector<char> v = {'a', 'b', 'c'};
  std::vector<char> v2 = {'a', 'b', 'c'};
  ASSERT_EQ(v.front(), 'a');
  ASSERT_EQ(v2.front(), v.front());
}

TEST(VectorTestFront, Test2) {
  s21::vector<char> v;
  ASSERT_ANY_THROW(v.front());
}

TEST(VectorTestBack, Test1) {
  s21::vector<char> v = {'a', 'b'};
  ASSERT_EQ(v.back(), 'b');
}

TEST(VectorTestBack, Test2) {
  s21::vector<char> v;
  ASSERT_ANY_THROW(v.back());
}

TEST(VectorTestData, Test1) {
  std::vector<char> v2 = {'a', 'b', 'c'};
  s21::vector<char> v = {'a', 'b', 'c'};

  EXPECT_EQ(*v2.data(), *v.data());
  EXPECT_EQ(*v.data(), 'a');
}

TEST(VectorTestIsempty, Test1) {
  s21::vector<char> v;
  std::vector<char> v1;
  ASSERT_TRUE(v1.empty());
  ASSERT_TRUE(v.empty());
}

TEST(VectorTestIsempty, Test2) {
  s21::vector<int> v = {1};
  std::vector<int> v1 = {0};
  ASSERT_FALSE(v1.empty());
  ASSERT_FALSE(v.empty());
}

TEST(VectorTestMaxSize, Test2) {
  s21::vector<double> v;
  std::vector<double> v1;
  s21::vector<long unsigned int> v0;
  std::vector<long unsigned int> v2;
  ASSERT_EQ(v1.max_size(), v.max_size());
  ASSERT_EQ(v0.max_size(), v2.max_size());
}

TEST(VectorTestCapacity, Test1) {
  s21::vector<char> v = {'a', 'b', 'c'};
  std::vector<char> v2 = {'a', 'b', 'c'};
  v2.push_back('p');
  v.push_back('p');
  ASSERT_EQ(v2.capacity(), v.capacity());
}

TEST(VectorTestShrinkToFit, Test1) {
  std::vector<int> v = {1, 2, 3};
  s21::vector<int> v1 = {1, 2, 3};

  v.push_back(4);
  v.push_back(5);
  v.push_back(6);
  v.push_back(7);
  v.push_back(8);
  v.push_back(9);
  v.shrink_to_fit();

  v1.push_back(4);
  v1.push_back(5);
  v1.push_back(6);
  v1.push_back(7);
  v1.push_back(8);
  v1.push_back(9);
  v1.shrink_to_fit();

  ASSERT_EQ(v1.capacity(), v.capacity());
}

TEST(VectorTestPushBack, Test0) {
  s21::vector<char> v;
  std::vector<char> v2;
  v2.push_back('p');
  v.push_back('p');
  ASSERT_EQ(v2.capacity(), v.capacity());
}

TEST(VectorTestClear, Test1) {
  std::vector<int> v = {1, 2, 3};
  s21::vector<int> v1 = {1, 2, 3};
  v.clear();
  v1.clear();

  ASSERT_EQ(v.capacity(), v1.capacity());
  ASSERT_EQ(v.size(), v1.size());
}

/*########################### ITERATOR ############################*/

TEST(VectorTestIterator, Test1) {
  s21::vector<int> v{1, 2};
  s21::vector<int>::iterator it = v.begin();

  ASSERT_EQ(*(++it), 2);
}

TEST(VectorTestIterator, Test2) {
  s21::vector<int> v{1, 2};
  s21::vector<int>::iterator it = v.begin();
  ASSERT_EQ(*(it++), 1);
  ASSERT_EQ(*it, 2);
}

TEST(VectorTestIterator, Test3) {
  s21::vector<int> v{1, 2};
  s21::vector<int>::iterator it = v.end();
  --it;
  ASSERT_EQ(*it, 2);

  s21::vector<int> v1{1, 2};
  s21::vector<int>::iterator it2 = v1.end();

  ASSERT_EQ(*(--it2), 2);
}

TEST(VectorTestIterator, Test4) {
  s21::vector<int> v{1, 2};
  s21::vector<int>::iterator it = v.end();
  --it;
  ASSERT_EQ(*it, 2);

  s21::vector<int> v1{1, 2};
  s21::vector<int>::iterator it2 = v1.end();

  ASSERT_EQ(*(--it2), 2);
}

TEST(VectorTestIterator, Test5) {
  s21::vector<int> v{1, 2};
  s21::vector<int>::iterator it = v.end();
  s21::vector<int> v1{1, 2};
  s21::vector<int>::iterator it2 = v.end();

  std::vector<int> v2{1, 2};
  std::vector<int>::iterator it3 = v2.begin();
  std::vector<int> v3{1, 2};
  std::vector<int>::iterator it4 = v2.begin();

  ASSERT_TRUE(it == it2);
  ASSERT_TRUE(it3 == it4);
}

TEST(VectorTestIterator, Test6) {
  s21::vector<int> v{1, 2};
  s21::vector<int>::iterator it = v.end();
  s21::vector<int> v1{1, 2};
  s21::vector<int>::iterator it2 = v.end();

  std::vector<int> v2{1, 2};
  std::vector<int>::iterator it3 = v2.begin();
  std::vector<int> v3{1, 2};
  std::vector<int>::iterator it4 = v2.begin();

  ASSERT_FALSE(it != it2);
  ASSERT_FALSE(it3 != it4);
}

TEST(VectorTestConstIterator, Test0) {
  std::vector<char> v0{'a', 'b', 'c'};
  std::vector<char>::const_iterator it0 = v0.begin();
  ASSERT_EQ(*(++it0), 'b');

  s21::vector<char> v1{'a', 'b', 'c'};
  s21::vector<char>::const_iterator it1 = v1.cbegin();
  ASSERT_EQ(*(++it1), 'b');
}

TEST(VectorTEstInsert, Test0) {
  s21::vector<char> v{'a', 'b', 'c'};
  v.insert(v.begin(), 'D');

  std::vector<char> v1{'a', 'b', 'c'};
  v1.insert(v1.begin(), 'D');

  ASSERT_EQ(*v.begin(), *v1.begin());
}

TEST(VectorTEstInsert, Test1) {
  s21::vector<char> v{'a', 'b', 'c'};
  v.insert(v.begin() + 1, 'D');

  std::vector<char> v1{'a', 'b', 'c'};
  v1.insert(v1.begin() + 1, 'D');

  ASSERT_EQ(*(v.begin() + 1), *(v1.begin() + 1));
  ASSERT_EQ(*(v.begin() + 1), 'D');
}

TEST(VectorTEstInsert, Test2) {
  s21::vector<char> v0{'X', 'Y', 'Z'};
  s21::vector<char> v1{'O'};

  v0.insert(v0.begin() + 1, *v1.begin());

  std::vector<char> v3{'X', 'Y', 'Z'};
  std::vector<char> v2{'O'};

  v3.insert(v3.begin() + 1, *v2.begin());

  ASSERT_EQ(*v0.begin(), *v3.begin());
  ASSERT_EQ(*(v0.begin() + 1), 'O');
  ASSERT_EQ(*(v3.begin() + 1), 'O');
}

TEST(VectorTEstInsert, Test3) {
  s21::vector<char> v;
  std::vector<char> v1;

  v1.insert(v1.begin(), 'M');
  v.insert(v.begin(), 'M');

  ASSERT_EQ(*v.begin(), 'M');
  ASSERT_EQ(*v1.begin(), 'M');
}

TEST(VectorTEstInsert, Test4) {
  s21::vector<char> v;
  std::vector<char> v1;

  v1.insert(v1.begin(), 'M');
  v.insert(v.begin(), 'M');

  ASSERT_EQ(*v.begin(), 'M');
  ASSERT_EQ(*v1.begin(), 'M');
}

TEST(VectorTEstInsert, Test5) {
  s21::vector<char> v{'a', 'b', 'c'};
  ASSERT_ANY_THROW(v.insert(v.begin() + 5, 'D'));
}

TEST(VectorTestSwap, Test0) {
  s21::vector<int> v{1};
  s21::vector<int> v0{2};
  std::vector<int> v1{3};
  std::vector<int> v2{4};

  v.swap(v0);
  v1.swap(v2);

  ASSERT_EQ(v0.at(0), 1);
  ASSERT_EQ(v.at(0), 2);
  ASSERT_EQ(v1.at(0), 4);
  ASSERT_EQ(v2.at(0), 3);
}

TEST(VectorTestErase, Test0) {
  std::vector<int> v2{1, 2, 3, 4};
  s21::vector<int> v1{1, 2, 3, 4};
  v2.erase(v2.begin() + 2);
  v1.erase(v1.begin() + 2);

  ASSERT_EQ(*(v1.begin() + 2), 4);
  ASSERT_EQ(*(v2.begin() + 2), 4);
}

TEST(VectorTestErase, Test1) {
  std::vector<int> v2{1, 2, 3, 4};
  s21::vector<int> v1{1, 2, 3, 4};
  v2.erase(v2.begin());
  v1.erase(v1.begin());

  ASSERT_EQ(*(v1.begin()), 2);
  ASSERT_EQ(*(v2.begin()), 2);
}

TEST(VectorTestIteratorDefaultConstructor, Test0) {
  s21::vector<int>::iterator it;
  ASSERT_EQ(it, nullptr);
}

TEST(VectorTestIteratorCopyConstructor, Test0) {
  s21::vector<int> v{1, 2, 3};
  s21::vector<int>::iterator it1 = v.begin();
  s21::vector<int>::iterator it(it1);
  ASSERT_EQ(*it, 1);
}

TEST(VectorTestIteratorCopyOperator, Test0) {
  s21::vector<int> v{1, 2, 3};
  s21::vector<int>::iterator it1 = v.begin();
  s21::vector<int>::iterator it;
  it = it1;
  ASSERT_EQ(*it, 1);
}

TEST(VectorTestIteratorMinusPostIcriment, Test0) {
  s21::vector<int> v{1, 2, 3};
  s21::vector<int>::iterator it1 = v.end();
  it1--;
  ASSERT_EQ(*it1, 3);
}

TEST(VectorTestIteratorMinus, Test0) {
  s21::vector<int> v{1, 2, 3};
  s21::vector<int>::iterator it1 = v.end() - 1;
  ASSERT_EQ(*it1, 3);
}

TEST(VectorConstructorParam, Test0) {
  int n = 10;
  s21::vector<int> v(n);
  ASSERT_EQ(v.size(), 10);
}

TEST(VectorPopBack, Test0) {
  s21::vector<int> v{1, 2};
  v.pop_back();
  ASSERT_EQ(v[0], 1);
}