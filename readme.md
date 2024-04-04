# Объектно-ориентированное программирование

## Лабораторные работы

[Подготовка к выполнению лабораторных работ](base/labs/lab0-preparation.md)
1. [Ввод-вывод](base/labs/lab1-io.md)
2. [Классы](base/labs/lab2-classes.md)
3. [Контейнеры](base/labs/lab3-containers.md)
4. [Полиморфные классы](base/labs/lab4-polymorphism.md)
5. TUI
6. \* GUI (факультативно)



## Примеры с лекций и практик

Лекции:
1. [`Ratio`](base/example1-ratio) (v1)
2. [`Ratio`](base/example2-ratio) (v2: с исключением и перегрузкой операторов)

Практики:
1. [std::iostream](base/practice1-std-iostream)
2. [std::vector](base/practice2a-std-vector),
   [std::random](base/practice2b-std-random)
   и
   [sfml](base/practice2c-sfml)
3. [std::string](base/practice3-std-string)
4. `std::thread`:
   [account](base/practice4a-std-thread-account)
   и
   [matrix-multiplication](base/practice4b-std-thread-matrix-multiplication)
5. `det`: [часть 1](base/practice5-matrix-det-part1) (`IMatrix`, `Matrix`)
6. `det`: ⌛ (+ `SubMatrix`, `det`)



## Факультативные задачи

[Порядок сдачи задач](electives-advanced/procedure.md)
1. *В течение 1 недели после сдачи 2-ой лабы.* [Opaque Structs](electives-advanced/task1-opaque-structs.md)
2. *До 10 марта.* [SFML](electives-advanced/task2-sfml.md)
3. *До 31 марта.* [Small String Optimization](electives-advanced/task3-sso.md)
4. *До 31 марта.* [Параллельное умножение матриц](electives-advanced/task4-parallel-multiplication.md)
5. *До 14 апреля.* [SharedPtr](electives-advanced/task5-shared-ptr.md)
6. ⌛ Моделирование виртуальных методов на чистом Си
7. ⌛ Vector & Set, part 1: stl iterators
8. ⌛ Vector & Set, part 2: polymorphic iterators
9. ⌛ Map
10. ⌛ Paint



## Онлайн-ресурсы и литература

- [en.cppreference.com/w/cpp](https://en.cppreference.com/w/cpp)
- [stackoverflow.com/search](https://stackoverflow.com/search)
- [google.com](https://www.google.com/)

| Автор(ы)             | Название                                                                                 | Комментарий                                              |
| :------------------- | :--------------------------------------------------------------------------------------- | :------------------------------------------------------- |
| Stroustrup, Sutter   | [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines.html) | Нормы кодирования                                        |
| Sutter, Alexandrescu | [C++ Coding Standards](https://www.labirint.ru/books/512945/)                            | Может использоваться как дополнение к нормам кодирования |
| Lippman, Lajoie, Moo | [C++ Primer](https://www.labirint.ru/books/512910/)                                      | Факультативно: основной учебник (замена лекциям)         |
| Meyers               | [Effective C++](https://www.labirint.ru/authors/47004/)                                  | Факультативно: продвинутые особенности языка             |



## Условия для получения оценки автоматом

Для оценки "отлично" до 31 мая необходимо выполнить **все** следующие условия:
- Сдать 5 лабораторных работ.
- Количество посещённых практик - **не менее 6**.
  Практика считается непосещённой, если вы не писали и/или не сдали соответствующую самостоятельную работу
  (то есть когда соответствующая клетка в онлайн-ведомости является пустой и не содержит никакую цифру).
- Количество базовых баллов (столбец J, `∑Б`): **больше или равно 50**.
- Количество факультативных баллов (столбец K, `∑Ф`): **больше или равно 25**.

Выставление автоматом оценок "удовлетворительно" и "хорошо" не предусмотрено.

P. S. Даже если вы не выполните все условия для получения "отлично" автоматом,
выполнение факультативных задач как минимум:
- позволит лучше разобраться в предмете;
- подготовит вас к экзамену;
- обеспечит вам *повышенную карму* на экзамене;
- лучше подготовит вас к освоению на 2-ом курсе дисциплины "Алгоритмы и структуры данных" (C++) и,
  отчасти, дисциплины "Прикладное программирование" (Python).



## Дополнительные занятия для отстающих

[Примеры с занятий](electives-beginner)

Занятия проводятся в 608-18.

| Тема                                                 | Дата |
| :--------------------------------------------------- | :--- |
| 1. Переменные и выражения                            | ✓ 10 февраля (сб), 11:30 |
| 2. Управляющие конструкции                           | ✓ 17 февраля (сб), 11:30 |
| 3. Функции и рекурсия                                | ✓ 21 февраля (ср), 15:15 (перенос с субботы) |
| 4. Указатели и массивы                               | ✓ 2 марта (сб), 11:30 |
| 5.1. Указатели на функции<br/>5.2. Двумерные массивы | ✓ 6 марта (ср), 15:15 (перенос с субботы) |
| 6. Структуры                                         | ✓ 16 марта (сб), 11:30 |
| Консультации                                         | По тем средам, когда есть практика по ООП, в 15:15 |
