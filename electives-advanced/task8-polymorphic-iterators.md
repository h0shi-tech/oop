# Задача № 8
# Структуры данных и полиморфные итераторы

## Срок сдачи

- До 28 апреля включительно.



## Задание

Разработать полимфорфные контейнеры `Vector` (аналог `std::vector`) и `Set`
(аналог `std::unordered_set`, см. предыдущую задачу).

В качестве основы взять следующую заготовку:
```cpp
#include <memory>

template<typename T>
class IEnumerator {
  virtual bool next() = 0;
  virtual T& get_current() = 0;
};

template<typename T>
class IEnumerable {
  virtual std::unique_ptr<Iterator<T>> get_enumerator() = 0;
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
   `Vector` должен удовлетворять всем тем же требованиям, которые применимы к `Vector`
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
2. Если всё сделано верно, помимо всего прочего, должен работать и код следующего вида:
   ```cpp
   // В данном примере допускается сделать print шаблонной функцией.
   // Но шаблонным аргументом должен быть исключительно
   // тип элемента контейнера (!), но не сам контейнер:
   // template<typename T>
   // void print(IEnumerable<T>& container);

   void print(IEnumerable<std::string>& container) {
     auto e = v.get_enumerator();
     while (e->next()) {
       std::cout << e->get_current() << std::endl;
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

Подсказка. Реализацию полиморфных итераторов можно свести к использованию STL-итераторов.
