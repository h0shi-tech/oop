# Задача № 8
# Структуры данных и полиморфные итераторы

## Срок сдачи

- До 28 апреля включительно.



## Задание

Разработать **полиморфные** контейнеры `Vector` (аналог `std::vector`) и `Set`
(аналог `std::unordered_set`, см. предыдущую задачу).

Вся работа выполняется в одном единственном файле `main.cpp`.
В архиве прислать файл исходного кода (`main.cpp`) и сценарий сборки (`CMakeLists.txt`).

В качестве основы взять следующую заготовку:
```cpp
#include <memory>

template<typename T>
class IEnumerator {
public:
  IEnumerator(const IEnumerator<T>&) = delete;
  IEnumerator<T>& operator=(const IEnumerator<T>&) = delete;

  virtual bool next() = 0;
  virtual T& current() = 0;

  virtual ~IEnumerator() = default;

protected:
  IEnumerator() = default;
};

template<typename T>
class IEnumerable {
public:
  virtual std::unique_ptr<IEnumerator<T>> enumerator() = 0;

  virtual ~IEnumerable() = default;

protected:
  IEnumerable() = default;
  IEnumerable(const IEnumerable<T>&) = default;
  IEnumerable<T>& operator=(const IEnumerable<T>&) = default;
};

template<typename T>
class Vector : public IEnumerable<T> {
  // ...
};

template<
  typename Key,
  typename Hash = std::hash<Key>,
  typename KeyEqual = std::equal_tp<Key>
>
class Set : public IEnumerable<Key> {
  // ...
};
```

Требования:
1. `Set` должен удовлетворять **всем требованиям**, которые предъявляются к `Set` в предыдущей задаче.
   `Vector` тоже должен удовлетворять всем требованиям, которые применимы к нему
   (в том числе наличие методов `begin` и `end` для получения STL-итераторов).
   Реализация `Vector` будет иметь следующие особенности:
   - метод `find` не нужен;
   - метод `insert` будет иметь следующий профиль:
     ```
     Iterator insert(iterator pos, const T& value);
     ```
   - метод `erase` будет иметь следующий профиль:
     ```
     Iterator erase(iterator pos);
     ```
   - разрешается не имплементировать `capacity`.
   
   Поведение всех методов должно быть эквивалентно поведению методов соответствующего STL-контейнера.
2. `IEnumerator<T>::current()` должен генерировать исключение `std::logic_error`,
   если метод `IEnumerator<T>::next()` не вызывался вообще или если последний вызов вернул `false`.
3. Обратите внимание, что `IEnumerable` не запрещает копирование, а лишь скрывает его на своём уровне.
   Таким образом, конкретные наследники (`Vector` и `Set`) могут (и должны) быть копируемыми.
4. Если всё сделано верно, помимо всего прочего, должен работать и код следующего вида:
   ```cpp
   // В данном примере допускается сделать print шаблонной функцией.
   // Но шаблонным аргументом должен быть исключительно
   // тип элемента контейнера (!), но не сам контейнер:
   // template<typename T>
   // void print(IEnumerable<T>& container);

   void print(IEnumerable<std::string>& container) {
     auto e = v.enumerator();
     while (e->next()) {
       std::cout << e->current() << std::endl;
     }
     std::cout << std::endl;
   }

   int main() {
     Vector<std::string> v;
     // ... (заполнение v)

     Set<std::string> s;
     // ... (заполнение s)
     
     print(v);
     print(s);
   }
   ```

Подсказка № 1. Реализацию полиморфных итераторов можно свести к использованию STL-итераторов.

Подсказка № 2.
Особо смекалистые могут сообразить,
что можно обойтись реализацией всего одного шаблонного наследника от `IEnumerator<T>`.
В качестве шаблонного аргумента должен выступать *тип итератора*.
Затем данный класс можно инстанцировать с аргументами `Set<T>::iterator` и `Vector<T>::iterator`.
