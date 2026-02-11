#include <gtest/gtest.h>

#include <stdexcept>

#include "../s21_queue.h"

using namespace s21;

TEST(QueueTest, DefaultConstructor) {
  Queue<int> q;
  EXPECT_EQ(q.empty(), true);
}

TEST(QueueTest, ListConstructor) {
  Queue<int> q = {1, 2, 3, 4, 5};

  EXPECT_EQ(q.empty(), false);
  EXPECT_EQ(q.size(), 5);

  int ans[] = {1, 2, 3, 4, 5};
  int ans_ind = 0;

  for (Node<int> *ptr = q.head; ptr != nullptr; ptr = ptr->next) {
    EXPECT_EQ(ptr->data, ans[ans_ind++]);
  }
}

TEST(QueueTest, CopyConstructor) {
  Queue<int> q = {1, 2, 3, 4, 5};

  int ans[] = {1, 2, 3, 4, 5};
  int ans_ind = 0;

  Queue<int> q2 = q;

  EXPECT_EQ(q2.empty(), false);
  EXPECT_EQ(q2.size(), 5);

  for (Node<int> *ptr = q2.head; ptr != nullptr; ptr = ptr->next) {
    EXPECT_EQ(ptr->data, ans[ans_ind++]);
  }
}

TEST(QueueTest, MoveConstructor) {
  Queue<int> q = {1, 2, 3, 4, 5};

  int ans[] = {1, 2, 3, 4, 5};
  int ans_ind = 0;

  Queue<int> q2 = std::move(q);

  EXPECT_EQ(q.empty(), true);
  EXPECT_EQ(q.size(), 0);

  EXPECT_EQ(q2.empty(), false);
  EXPECT_EQ(q2.size(), 5);

  for (Node<int> *ptr = q2.head; ptr != nullptr; ptr = ptr->next) {
    EXPECT_EQ(ptr->data, ans[ans_ind++]);
  }
}

TEST(QueueTest, MoveOperator) {
  Queue<int> q = {1, 2, 3, 4, 5};

  int ans[] = {1, 2, 3, 4, 5};
  int ans_ind = 0;

  Queue<int> q2;
  q2 = std::move(q);

  EXPECT_EQ(q.empty(), true);
  EXPECT_EQ(q.size(), 0);

  EXPECT_EQ(q2.empty(), false);
  EXPECT_EQ(q2.size(), 5);

  for (Node<int> *ptr = q2.head; ptr != nullptr; ptr = ptr->next) {
    EXPECT_EQ(ptr->data, ans[ans_ind++]);
  }
}

TEST(QueueTest, Front) {
  Queue<int> q = {1, 2, 3, 4, 5};
  EXPECT_EQ(q.front(), 1);
}

TEST(QueueTest, FrontException) {
  Queue<int> q;
  try {
    q.front();
  } catch (std::exception &ex) {
    EXPECT_STREQ("Empty queue", ex.what());
  }
}

TEST(QueueTest, Back) {
  Queue<int> q = {1, 2, 3, 4, 5};
  EXPECT_EQ(q.back(), 5);
}

TEST(QueueTest, Pop) {
  Queue<int> q = {1, 2, 3, 4, 5};
  q.pop();
  q.pop();
  q.pop();
  q.pop();
  q.pop();
  q.pop();
}

TEST(QueueTest, BackException) {
  Queue<int> q;
  try {
    q.back();
  } catch (std::exception &ex) {
    EXPECT_STREQ("Empty queue", ex.what());
  }
}

TEST(QueueTest, Swap) {
  Queue<int> q = {1, 2, 3, 4, 5};
  Queue<int> q2 = {5, 4, 3, 2, 1};

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

TEST(QueueTest, InsertManyBack) {
  Queue<int> q = {1, 2, 3, 4, 5};
  Queue<int> q2 = {6, 7, 8, 9, 10};

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
