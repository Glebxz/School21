#include <iostream>

#include "s21_list.h"

int main() {
  // list<int> first;
  // first.push_back(7);
  // first.push_back(10);
  // first.push_back(5);
  // first.push_back(1);
  // first.push_front(44);

  // std::cout << "list size: " << first.size() << std::endl;
  // std::cout << "Front: " << first.front() << std::endl;

  // for (std::size_t i = 0; i < first.size(); i++) {
  //     std::cout << first[i] << std::endl;
  // }

  // first.pop_back();
  // std::cout << "\n" << std::endl;

  // for (std::size_t i = 0; i < first.size(); i++) {
  //     std::cout << first[i] << std::endl;
  // }

  // first.pop_front();
  // std::cout << "\n" << std::endl;

  // for (std::size_t i = 0; i < first.size(); i++) {
  //     std::cout << first[i] << std::endl;
  // }

  // first.clear();
  // std::cout << "Clear\n" << std::endl;

  // for (std::size_t i = 0; i < first.size(); i++) {
  //     std::cout << first[i] << std::endl;
  // }

  // list<int> list1;

  // list1.push_back(2);
  // list1.push_back(2);
  // list1.push_back(3);
  // list1.push_back(6);
  // list1.push_back(3);
  // list1.push_back(6);

  // list1.unique();

  // std::cout << "Clear\n" << std::endl;

  // for (std::size_t i = 0; i < list1.size(); i++) {
  //     std::cout << list1[i] << std::endl;
  // }

  // return 0;

  list<int> list1;

  // Добавляем элементы в список
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  // Используем итераторы для вывода элементов
  std::cout << "List elements using iterators:\n";
  for (auto it = list1.begin(); it != list1.end(); ++it) {
    std::cout << *it << std::endl;  // Выводит 1, 2, 3
  }

  return 0;
}
