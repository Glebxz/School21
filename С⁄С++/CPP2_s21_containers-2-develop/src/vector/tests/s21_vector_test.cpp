#ifndef S21_VECTOR_TEST_CPP
#define S21_VECTOR_TEST_CPP

#include "../s21_vector.h"

#include "gtest/gtest.h"

using namespace s21;

TEST(vectorTest, defaultConstructor) {
  s21::vector<int> x;
  EXPECT_EQ((size_t)0, x.size());
}

TEST(vectorTest, parameterizedConstructor) {
  s21::vector<int> x(5);
  EXPECT_EQ((size_t)5, x.size());
}

TEST(vectorTest, initializerListConstructor) {
  s21::vector<int> x = {1, 2, 3};
  EXPECT_EQ(x.size(), (size_t)3);
}

TEST(vectorTest, copyConstructor) {
  s21::vector<int> x = {1, 2, 3};
  s21::vector<int> y(x);
  EXPECT_EQ(y.size(), (size_t)3);
  EXPECT_EQ(x.size(), (size_t)3);
}

TEST(vectorTest, moveConstructor) {
  s21::vector<int> x = {1, 2, 3};
  s21::vector<int> y(std::move(x));
  EXPECT_EQ(y.size(), (size_t)3);
  EXPECT_EQ(x.size(), (size_t)0);
}

TEST(vectorTest, operatorEqual) {
  s21::vector<int> x = {1, 2, 3};
  s21::vector<int> y = x;
  EXPECT_EQ(y.size(), (size_t)3);
  EXPECT_EQ(x.size(), (size_t)3);
}

TEST(vectorTest, operatorEqual2) {
  s21::vector<int> x;
  x = {1, 2, 3};
  EXPECT_EQ(x.size(), (size_t)3);
}

TEST(vectorTest, at) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_THROW(v.at(3), std::out_of_range);
  EXPECT_EQ(v.at(0), 1);
}

TEST(vectorTest, operatorAccessesElement) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_THROW(v[3], std::out_of_range);
  EXPECT_EQ(v[0], 1);
}

TEST(vectorTest, front) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_EQ(v.front(), 1);
}

TEST(vectorTest, back) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_EQ(v.back(), 3);
}

TEST(vectorTest, data) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_EQ(v.data()[1], 2);
}

TEST(vectorTest, begin) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_EQ(*v.begin(), 1);
}

TEST(vectorTest, end) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_EQ(*(v.end() - 1), 3);
}

TEST(vectorTest, empty) {
  s21::vector<int> v;
  EXPECT_TRUE(v.empty());
}

TEST(vectorTest, size) {
  s21::vector<int> x(5);
  EXPECT_EQ(x.size(), (size_t)5);
}

TEST(vectorTest, MaxSize) {
  s21::vector<int> x;
  EXPECT_EQ((bool)x.max_size(), true);
}

TEST(vectorTest, capacity) {
  s21::vector<char> x = {'D', 'e', 'n'};
  EXPECT_EQ((size_t)3, x.capacity());
}

TEST(vectorTest, reserve) {
  s21::vector<int> v = {1, 2, 3};
  v.reserve(10);
  EXPECT_EQ(v.capacity(), (size_t)10);
}

TEST(vectorTest, shrinkToFit) {
  s21::vector<int> v = {1, 2, 3};
  v.reserve(10);
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), (size_t)3);
}

TEST(vectorTest, clear) {
  s21::vector<int> v{1, 2, 3};
  v.clear();
  EXPECT_TRUE(v.empty());
}

TEST(vectorTest, insert) {
  s21::vector<int> v = {1, 2, 3};
  v.insert(v.end(), 15);
  EXPECT_EQ(v.size(), (size_t)4);
  EXPECT_EQ(v.at(3), 15);
}

TEST(vectorTest, erase) {
  s21::vector<int> v = {1, 2, 3};
  v.erase(v.begin());
  EXPECT_EQ(v.size(), (size_t)2);
  EXPECT_EQ(v.at(0), 2);
}

TEST(vectorTest, pushBack) {
  s21::vector<int> v = {1, 2, 3};
  v.push_back(16);
  EXPECT_EQ(v.size(), (size_t)4);
  EXPECT_EQ(v.at(3), 16);
}

TEST(vectorTest, popBack) {
  s21::vector<int> v = {1, 2, 3};
  v.pop_back();
  EXPECT_EQ(v.size(), (size_t)2);
  EXPECT_EQ(*(v.end() - 1), 2);
}

TEST(vectorTest, swap) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = {4, 5, 6};
  v1.swap(v2);
  EXPECT_EQ(v1.at(0), 4);
  EXPECT_EQ(v2.at(2), 3);
}

TEST(vectorTest, insert_many_1) {
  s21::vector<int> vector_int{1, 4};
  s21::vector<std::string> vector_string{"Hello", ","};

  auto pos_int = vector_int.begin() + 1;
  auto pos_string = vector_string.begin() + 1;

  vector_int.insert_many(pos_int, 2, 3);
  vector_string.insert_many(pos_string, "world", "!");

  EXPECT_EQ(vector_int[1], 2);
  EXPECT_EQ(vector_int[2], 3);

  EXPECT_EQ(vector_string[1], "world");
  EXPECT_EQ(vector_string[2], "!");
}

TEST(vectorTest, insert_many_2) {
  s21::vector<int> vector_int{1, 4};
  s21::vector<std::string> vector_string{"Hello", ","};

  vector_int.insert_many_back(2, 3);
  vector_string.insert_many_back("world", "!");

  EXPECT_EQ(vector_int[2], 2);
  EXPECT_EQ(vector_int[3], 3);

  EXPECT_EQ(vector_string[2], "world");
  EXPECT_EQ(vector_string[3], "!");
}

TEST(vectorTest, insert_many_exception) {
  s21::vector<int> vector_int{1, 4};

  try {
    vector_int.insert_many(vector_int.data() - 1, 3);
    vector_int.insert_many(vector_int.data() + 5, 3);
  } catch (std::exception &ex) {
    EXPECT_STREQ("Invalid position for insert.", ex.what());
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif  // S21_VECTOR_TEST_CPP
