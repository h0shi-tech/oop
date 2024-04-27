# Объектно-ориентированное программирование

## Экзамен

**1. Порядок проведения экзамена**

На экзамене будет:
- один теоретический вопрос ([список вопросов](exam.md));
- две практических задачи.

Практические задачи могут быть на любые темы, которые были разобраны на протяжении всего семестра.
Темы практических задач определяются совокупностью тем, входящих в:
- лекции;
- лабораторные работы (исключая Turbo Vision и Qt);
- практики (исключая SFML, `std::thread` и Qt);
- самостоятельные работы на практиках (исключая школьные логические задачи и `std::thread`).

**2. Условия для получения оценки "отлично" автоматом на общих основаниях (вне конкурсных задач и проекта)**
- До конца мая выполнить все следующие условия:
  - сдать 5 лабораторных работ;
  - написать **не менее 6** самостоятельных работ на практиках
    (самостоятельная работа считается написанной,
    если соответствующая клетка не пуста и содержит любую цифру, включая 0);
  - количество нормированных по ФОСу базовых баллов (столбец J) **`∑Б >= 50`**;
  - количество факультативных баллов (столбец K) **`∑Ф >= 25`**.

**3. Условия для получения оценки автоматом за выполнение проекта**
- 15 мая (в 15:15 в 608-18) или 16-17 мая (в любое время в 607-18) согласовать тему проекта **очно**.
- До конца мая:
  - для **отлично** сдать 5 лабораторных (каждую - на 3 базовых балла из 3);
  - для **хорошо** сдать 5 лабораторных (каждую - минимум на 2 базовых балла из 3);
  - для **удовлетворительно** сдать 4 лабораторных (каждую - минимум на 1 базовый балл из 3;
    но в совокупности за первые 4 лабораторные должно быть не менее 6 базовых баллов).
- Защитить проект на соответствующую оценку на практике 5 июня.



## Лабораторные работы

[Подготовка к выполнению лабораторных работ](base/labs/lab0-preparation.md)
1. [Ввод-вывод](base/labs/lab1-io.md)
2. [Классы](base/labs/lab2-classes.md)
3. [Контейнеры](base/labs/lab3-containers.md)
4. [Полиморфные классы](base/labs/lab4-polymorphism.md)
5. [TUI](base/labs/lab5-tui.md)
6. \* [GUI](base/labs/lab6-gui.md) (факультативно)



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
6. `det`: [часть 2](base/practice6-matrix-det-part2) (`IMatrix`, `Matrix`, `SubMatrix`, `det`) и [введение в Qt](base/practice6-qt-intro.pdf)
7. ⌛ (15.05) Пример приложения на Qt
8. ⌛ (29.05) Пример численного интегрирования
9. Показ и защита проектов



## Факультативные задачи

[Порядок сдачи задач](electives-advanced/procedure.md)
1. *В течение 1 недели после сдачи 2-ой лабы.* [Opaque Structs](electives-advanced/task1-opaque-structs.md)
2. *До 10 марта.* [SFML](electives-advanced/task2-sfml.md)
3. *До 31 марта.* [Small String Optimization](electives-advanced/task3-sso.md)
4. *До 31 марта.* [Параллельное умножение матриц](electives-advanced/task4-parallel-multiplication.md)
5. *До 14 апреля.* [SharedPtr](electives-advanced/task5-shared-ptr.md)
6. *До 14 апреля (★)., до 28 апреля.* [Моделирование интерфейса на чистом Си](electives-advanced/task6-c-vmt.md)
7. *До 28 апреля (★).* [Структуры данных и итераторы STL](electives-advanced/task7-stl-iterators.md)
8. *До 28 апреля (★).* [Структуры данных и полиморфные итераторы](electives-advanced/task8-polymorphic-iterators.md)
9. *5 июня.* Проект

Задачи, помеченные ★, предоставляют конкурс на моментальный автомат.
Автомат ставится за полностью корректное решение, присланное раньше всех других в сроки, помеченные ★,
при условии выполнении пяти лабораторных работ до 31 мая включительно.
Приславшим полностью корректное решение не самым первым, но в рамках срока, помеченного ★,
возможность получения автомата определяется исключительно на субъективное усмотрение преподавателя.



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



## Дополнительные занятия

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
