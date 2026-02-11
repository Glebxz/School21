#include <gtest/gtest.h>

#include <stdexcept>

#include "../s21_stack.h"

using namespace s21;

TEST(StackTest, DefaultConstructor) {
  Stack<int> q;
  EXPECT_EQ(q.empty(), true);
}

TEST(StackTest, ListConstructor) {
  Stack<int> q = {1, 2, 3, 4, 5};

  EXPECT_EQ(q.empty(), false);
  EXPECT_EQ(q.size(), 5);

  int ans[] = {1, 2, 3, 4, 5};
  int ans_ind = 0;

  for (Node<int> *ptr = q.head; ptr != nullptr; ptr = ptr->next) {
    EXPECT_EQ(ptr->data, ans[ans_ind++]);
  }
}

TEST(StackTest, CopyConstructor) {
  Stack<int> q = {1, 2, 3, 4, 5};

  int ans[] = {1, 2, 3, 4, 5};
  int ans_ind = 0;

  Stack<int> q2 = q;

  EXPECT_EQ(q2.empty(), false);
  EXPECT_EQ(q2.size(), 5);

  for (Node<int> *ptr = q2.head; ptr != nullptr; ptr = ptr->next) {
    EXPECT_EQ(ptr->data, ans[ans_ind++]);
  }
}

TEST(StackTest, MoveConstructor) {
  Stack<int> q = {1, 2, 3, 4, 5};

  int ans[] = {1, 2, 3, 4, 5};
  int ans_ind = 0;

  Stack<int> q2 = std::move(q);

  EXPECT_EQ(q.empty(), true);
  EXPECT_EQ(q.size(), 0);

  EXPECT_EQ(q2.empty(), false);
  EXPECT_EQ(q2.size(), 5);

  for (Node<int> *ptr = q2.head; ptr != nullptr; ptr = ptr->next) {
    EXPECT_EQ(ptr->data, ans[ans_ind++]);
  }
}

TEST(StackTest, MoveOperator) {
  Stack<int> q = {1, 2, 3, 4, 5};

  int ans[] = {1, 2, 3, 4, 5};
  int ans_ind = 0;

  Stack<int> q2;
  q2 = std::move(q);

  EXPECT_EQ(q.empty(), true);
  EXPECT_EQ(q.size(), 0);

  EXPECT_EQ(q2.empty(), false);
  EXPECT_EQ(q2.size(), 5);

  for (Node<int> *ptr = q2.head; ptr != nullptr; ptr = ptr->next) {
    EXPECT_EQ(ptr->data, ans[ans_ind++]);
  }
}

TEST(StackTest, Top) {
  Stack<int> q = {1, 2, 3, 4, 5};
  EXPECT_EQ(q.top(), 5);
}

TEST(StackTest, Pop) {
  Stack<int> q = {1, 2, 3, 4, 5};

  q.pop();
  q.pop();
  q.pop();
  q.pop();
  q.pop();
  q.pop();
}

TEST(StackTest, TopException) {
  Stack<int> q;
  try {
    q.top();
  } catch (std::exception &ex) {
    EXPECT_STREQ("Empty stack", ex.what());
  }
}

TEST(StackTest, Swap) {
  Stack<int> q = {1, 2, 3, 4, 5};
  Stack<int> q2 = {5, 4, 3, 2, 1};

  int ans[] = {1, 2, 3, 4, 5};
  int ans2[] = {5, 4, 3, 2, 1};

  int ans_ind = 0;
  for (Node<int> *ptr = q.head; ptr != nullptr; ptr = ptr->next) {
    EXPECT_EQ(ptr->data, ans[ans_ind++]);
  }

  ans_ind = 0;
  for (Node<int> *ptr = q2.head; ptr != nullptr; ptr = ptr->next) {
    EXPECT_EQ(ptr->data, ans2[ans_ind++]);
  }

  q.swap(q2);

  ans_ind = 0;
  for (Node<int> *ptr = q.head; ptr != nullptr; ptr = ptr->next) {
    EXPECT_EQ(ptr->data, ans2[ans_ind++]);
  }

  ans_ind = 0;
  for (Node<int> *ptr = q2.head; ptr != nullptr; ptr = ptr->next) {
    EXPECT_EQ(ptr->data, ans[ans_ind++]);
  }
}

TEST(StackTest, InsertManyBack) {
  Stack<int> q = {1, 2, 3, 4, 5};
  Stack<int> q2 = {6, 7, 8, 9, 10};

  q.insert_many_back(6, 7, 8, 9, 10);
  int ans[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int ans_ind = 0;

  for (Node<int> *ptr = q.head; ptr != nullptr; ptr = ptr->next) {
    EXPECT_EQ(ptr->data, ans[ans_ind++]);
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
