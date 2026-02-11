#include <gtest/gtest.h>

#include <stdexcept>

#include "../s21_array.h"

using namespace s21;

TEST(ArrayTest, DefaultConstructor) {
  Array<int, 5> q;
  EXPECT_EQ(q.empty(), true);
}

TEST(ArrayTest, ListConstructor) {
  Array<int, 5> a{1, 2, 3, 4, 5};

  EXPECT_EQ(a.empty(), false);
  EXPECT_EQ(a.size(), 5);

  int ans[] = {1, 2, 3, 4, 5};

  for (size_t i = 0; i < a.size(); ++i) {
    EXPECT_EQ(a[i], ans[i]);
  }
}

TEST(ArrayTest, CopyConstructor) {
  Array<int, 5> b{1, 2, 3, 4, 5};
  Array<int, 5> a(b);

  int ans[] = {1, 2, 3, 4, 5};

  for (size_t i = 0; i < a.size(); ++i) {
    EXPECT_EQ(a[i], ans[i]);
  }
}

TEST(ArrayTest, CopyConstructorException) {
  try {
    Array<int, 6> b{1, 2, 3, 4, 5, 6, 7, 8, 9};
  } catch (std::exception &ex) {
    EXPECT_STREQ("Too many items", ex.what());
  }
}

TEST(ArrayTest, MoveConstructor) {
  Array<int, 5> arr1{1, 2, 3, 4, 5};
  Array<int, 5> arr2(std::move(arr1));

  for (size_t i = 0; i < arr2.size(); ++i) {
    EXPECT_EQ(arr2[i], i + 1);
  }
}

TEST(ArrayTest, MoveOperator) {
  Array<int, 5> a{1, 2, 3, 4, 5};

  int ans[] = {1, 2, 3, 4, 5};

  Array<int, 5> a2;
  a2 = std::move(a);

  for (size_t i = 0; i < a.size(); ++i) {
    EXPECT_EQ(a2[i], ans[i]);
  }
}

TEST(ArrayTest, Front) {
  Array<int, 5> a{1, 2, 3, 4, 5};
  EXPECT_EQ(a.front(), 1);
}

TEST(ArrayTest, At) {
  Array<int, 5> a{1, 2, 3, 4, 5};
  EXPECT_EQ(a.at(1), 2);
}

TEST(ArrayTest, AtException) {
  try {
    Array<int, 5> a{1, 2, 3, 4, 5};
    a.at(5);
  } catch (std::exception &ex) {
    EXPECT_STREQ("Wrong index", ex.what());
  }
}

TEST(ArrayTest, Back) {
  Array<int, 5> a{1, 2, 3, 4, 5};
  EXPECT_EQ(a.back(), 5);
}

TEST(ArrayTest, Data) {
  Array<int, 5> a{1, 2, 3, 4, 5};
  EXPECT_EQ(*a.data(), 1);
}

TEST(ArrayTest, Begin) {
  Array<int, 5> a{1, 2, 3, 4, 5};
  EXPECT_EQ(*a.begin(), 1);
}

TEST(ArrayTest, End) {
  Array<int, 5> a{1, 2, 3, 4, 5};
  EXPECT_EQ(*(a.end() - 1), 5);
}

TEST(ArrayTest, Empty) {
  Array<int, 5> a;
  EXPECT_EQ(a.empty(), true);
}

TEST(ArrayTest, Size) {
  Array<int, 5> a;
  EXPECT_EQ(a.max_size(), 5);
}

TEST(ArrayTest, Maxsize) {
  Array<int, 5> a;
  EXPECT_EQ(a.max_size(), 5);
}

TEST(ArrayTest, Swap) {
  Array<int, 5> a{3, 4, 3, 4, 5};
  Array<int, 5> b{1, 2, 3, 4, 5};

  int ans[] = {1, 2, 3, 4, 5};
  int ans2[] = {3, 4, 3, 4, 5};

  for (size_t i = 0; i < a.size(); ++i) {
    EXPECT_EQ(a[i], ans2[i]);
  }

  for (size_t i = 0; i < b.size(); ++i) {
    EXPECT_EQ(b[i], ans[i]);
  }

  a.swap(b);

  for (size_t i = 0; i < a.size(); ++i) {
    EXPECT_EQ(a[i], ans[i]);
  }

  for (size_t i = 0; i < b.size(); ++i) {
    EXPECT_EQ(b[i], ans2[i]);
  }
}

TEST(ArrayTest, Fill) {
  Array<int, 5> a;
  a.fill(5);

  int ans[] = {5, 5, 5, 5, 5};

  for (size_t i = 0; i < a.size(); ++i) {
    EXPECT_EQ(a[i], ans[i]);
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
