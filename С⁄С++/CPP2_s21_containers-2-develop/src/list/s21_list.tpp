#include "s21_list.h"

template <typename T>
void list<T>::clear() {
  while (!empty()) {
    pop_front();
  }
}

template <typename T>
list<T>::Node::Node(value_type data, Node *pNext, Node *pPrev)
    : pNext(pNext), pPrev(pPrev), data(data) {}

template <typename T>
list<T>::list() : Size(0), head(nullptr), tail(nullptr) {}

template <typename T>
list<T>::list(size_type n) : Size(0), head(nullptr), tail(nullptr) {
  for (size_type i = 0; i < n; ++i) {
    push_back(T());  // Создание элемента по умолчанию
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items)
    : Size(0), head(nullptr), tail(nullptr) {
  for (const auto &item : items) {
    push_back(item);
  }
}

// Конструктор копирования
template <typename T>
list<T>::list(const list &l) : Size(0), head(nullptr), tail(nullptr) {
  Node *current = l.head;
  while (current) {
    push_back(current->data);
    current = current->pNext;
  }
}

// Конструктор перемещения
template <typename T>
list<T>::list(list &&l) : Size(l.Size), head(l.head), tail(l.tail) {
  l.Size = 0;
  l.head = nullptr;
  l.tail = nullptr;
}

// Перегрузка оператора присваивания для перемещения
template <typename T>
list<T> &list<T>::operator=(list &&l) {
  if (this != &l) {  // Проверка самоприсваивания
    clear();         // Очистка текущего списка

    // Перемещаем данные
    Size = l.Size;
    head = l.head;
    tail = l.tail;

    // Обнуляем исходный объект
    l.Size = 0;
    l.head = nullptr;
    l.tail = nullptr;
  }
  return *this;
}

template <typename T>
list<T>::~list() {
  clear();
}

template <typename T>
typename list<T>::reference list<T>::operator[](size_type index) {
  if (index >= Size) {
    throw std::out_of_range("Index out of range");
  }
  size_type count = 0;
  Node *current = head;
  while (current != nullptr) {
    if (count == index) {
      return current->data;
    }
    current = current->pNext;
    count++;
  }
  throw std::out_of_range("Index out of range");
}

template <typename T>
typename list<T>::const_reference list<T>::operator[](size_type index) const {
  if (index >= Size) {
    throw std::out_of_range("Index out of range");
  }
  size_type count = 0;
  Node *current = head;
  while (current != nullptr) {
    if (count == index) {
      return current->data;
    }
    current = current->pNext;
    count++;
  }
  throw std::out_of_range("Index out of range");
}

template <typename T>
void list<T>::push_back(const_reference value) {
  if (empty()) {
    head = tail = new Node(value);
  } else {
    tail->pNext = new Node(value, nullptr, tail);
    tail = tail->pNext;
  }
  Size++;
}

template <typename T>
void list<T>::push_front(const_reference value) {
  if (empty()) {
    head = tail = new Node(value);
  } else {
    head->pPrev = new Node(value, head, nullptr);
    head = head->pPrev;
  }
  Size++;
}

template <typename T>
void list<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("Empty list");
  }

  if (head == tail) {
    delete tail;
    head = tail = nullptr;
  } else {
    Node *temp = tail;  // Запоминаем текущий tail
    tail = tail->pPrev;  // Перемещаем tail на предыдущий узел
    tail->pNext =
        nullptr;  // У нового tail обнуляем указатель на следующий узел
    delete temp;  // Удаляем старый tail
  }

  Size--;
}

template <typename T>
void list<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("Empty list");
  }

  if (head == tail) {
    delete head;
    head = tail = nullptr;
  } else {
    Node *temp = head;
    head = head->pNext;
    head->pPrev = nullptr;
    delete temp;
  }

  Size--;
}

template <typename T>
void list<T>::swap(list &other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(Size, other.Size);
}

template <typename T>
void list<T>::merge(list<T> &other) {
  if (this == &other) {
    return;
  }

  if (other.head == nullptr) {
    return;
  }

  if (this->head ==
      nullptr) {  // Если текущий список пуст, просто копируем второй
    this->head = other.head;
    this->tail = other.tail;
  } else {
    this->tail->pNext = other.head;  // конец текущего списка = начало другого
    other.head->pPrev =
        this->tail;  // Устанавливаем обратную ссылку на текущий список
    this->tail = other.tail;  // Обновляем tail
  }

  this->Size += other.Size;
  other.head = other.tail = nullptr;  // Обнуляем второй список
  other.Size = 0;  // Обнуляем размер второго списка
}

template <typename T>
void list<T>::reverse() {
  if (Size <= 1) {
    return;  // Если список пуст или состоит из одного элемента, ничего не
             // делаем
  }

  Node *current = head;
  Node *temp = nullptr;

  // Меняем местами pNext и pPrev для каждого узла
  while (current != nullptr) {
    temp = current->pPrev;
    current->pPrev = current->pNext;
    current->pNext = temp;
    current = current->pPrev;  // Переходим к следующему узлу (теперь это pPrev)
  }

  // После завершения цикла temp указывает на старый head
  temp = head;
  head = tail;
  tail = temp;
}

template <typename T>
void list<T>::unique() {
  if (Size <= 1) {
    return;
  }

  Node *current = head;

  while (current != nullptr && current->pNext != nullptr) {
    if (current->data == current->pNext->data) {
      // Найден дубликат: удаляем следующий узел
      Node *duplicate = current->pNext;
      current->pNext = duplicate->pNext;

      if (duplicate->pNext != nullptr) {
        duplicate->pNext->pPrev = current;
      } else {
        // Если дубликат был последним элементом, обновляем tail
        tail = current;
      }

      delete duplicate;
      --Size;
    } else {
      // Переходим к следующему узлу, если нет дубликатов
      current = current->pNext;
    }
  }
}

// ListIterator
template <typename T>
class list<T>::ListIterator {
 protected:
  Node *current;  // Указатель на текущий узел

 public:
  // Конструктор
  explicit ListIterator(Node *node) : current(node) {}

  // Операторы разыменования
  T &operator*() const {
    if (current == nullptr) {
      throw std::out_of_range("Iterator out of range");
    }
    return current->data;
  }

  T *operator->() const {
    if (current == nullptr) {
      throw std::out_of_range("Iterator out of range");
    }
    return &(current->data);
  }

  // Префиксный и постфиксный инкремент (++it, it++)
  ListIterator &operator++() {
    if (current == nullptr) {
      throw std::out_of_range("Iterator out of range");
    }
    current = current->pNext;
    return *this;
  }

  ListIterator operator++(int) {
    ListIterator temp = *this;
    ++(*this);
    return temp;
  }

  // Префиксный и постфиксный декремент (--it, it--)
  ListIterator &operator--() {
    if (current == nullptr) {
      throw std::out_of_range("Iterator out of range");
    }
    current = current->pPrev;
    return *this;
  }

  ListIterator operator--(int) {
    ListIterator temp = *this;
    --(*this);
    return temp;
  }

  // Операторы сравнения
  bool operator==(const ListIterator &other) const {
    return current == other.current;
  }

  bool operator!=(const ListIterator &other) const {
    return current != other.current;
  }

  // Метод доступа к current
  Node *getNode() const { return current; }
};

// ListConstIterator
template <typename T>
class list<T>::ListConstIterator : public ListIterator {
 public:
  // Конструктор
  explicit ListConstIterator(Node *node) : ListIterator(node) {}

  // Операторы разыменования
  const T &operator*() const {
    if (this->current == nullptr) {
      throw std::out_of_range("Iterator out of range");
    }
    return this->current->data;
  }

  const T *operator->() const {
    if (this->current == nullptr) {
      throw std::out_of_range("Iterator out of range");
    }
    return &(this->current->data);
  }
};

// Методы для обычных итераторов
template <typename T>
typename list<T>::ListIterator list<T>::begin() {
  return ListIterator(head);  // Итератор на первый элемент списка
}

template <typename T>
typename list<T>::ListIterator list<T>::end() {
  return ListIterator(nullptr);  // Итератор на nullptr (конец списка)
}

template <typename T>
typename list<T>::ListConstIterator list<T>::cbegin() const {
  return ListConstIterator(head);  // Возвращает константный итератор
}

template <typename T>
typename list<T>::ListConstIterator list<T>::cend() const {
  return ListConstIterator(nullptr);  // Возвращает константный итератор
}

template <typename T>
typename list<T>::ListIterator list<T>::insert(ListIterator pos,
                                               const_reference value) {
  if (pos == end()) {
    push_back(value);
    return ListIterator(tail);
  }

  Node *current = pos.getNode();  // Получаем указатель на текущий узел
  Node *newNode = new Node(value, current, current->pPrev);

  if (current->pPrev != nullptr) {
    current->pPrev->pNext = newNode;
  } else {
    head = newNode;
  }

  current->pPrev = newNode;
  ++Size;

  return ListIterator(newNode);
}

template <typename T>
void list<T>::erase(ListIterator pos) {
  if (pos == end()) {
    throw std::out_of_range("Cannot erase end iterator");
  }

  Node *current = pos.getNode();

  if (current->pPrev != nullptr) {
    current->pPrev->pNext = current->pNext;
  } else {
    head = current->pNext;
  }

  if (current->pNext != nullptr) {
    current->pNext->pPrev = current->pPrev;
  } else {
    tail = current->pPrev;
  }

  delete current;
  --Size;
}

template <typename T>
void list<T>::splice(ListConstIterator pos, list &other) {
  if (other.empty()) {
    return;  // Если другой список пуст, ничего не делаем
  }

  Node *posNode = pos.getNode();  // Узел, на который указывает pos

  if (posNode == nullptr) {
    // Если pos указывает на end(), добавляем элементы в конец текущего списка
    if (tail) {
      tail->pNext =
          other.head;  // Присоединяем начало другого списка к текущему
      other.head->pPrev = tail;  // Устанавливаем обратную ссылку
    } else {
      head = other.head;  // Если текущий список пуст, устанавливаем head
    }
    tail = other.tail;  // Обновляем tail текущего списка
  } else {
    // Вставляем элементы перед posNode
    if (posNode->pPrev) {
      posNode->pPrev->pNext =
          other.head;  // Устанавливаем pNext предыдущего узла
      other.head->pPrev = posNode->pPrev;  // Устанавливаем обратную ссылку
    } else {
      head = other.head;  // Если posNode - это head, обновляем head
    }
    other.tail->pNext = posNode;  // Устанавливаем pNext для нового tail
    posNode->pPrev = other.tail;  // Устанавливаем pPrev для posNode
  }

  Size += other.Size;  // Увеличиваем размер текущего списка
  other.head = other.tail = nullptr;  // Очищаем другой список
  other.Size = 0;  // Обнуляем размер другого списка
}

template <typename T>
void list<T>::sort() {
  if (Size <= 1) {
    return;  // Если список пуст или состоит из одного элемента, ничего не
             // делаем
  }

  bool swapped;
  do {
    swapped = false;
    ListIterator it = begin();

    while (it != end() && ++it != end()) {
      ListIterator next = it;  // Сохраняем итератор на следующий элемент
      --next;  // Возвращаемся к текущему элементу

      if (*next > *it) {
        // Меняем местами данные
        std::swap(*next, *it);
        swapped = true;
      }
    }
  } while (swapped);
}