# ★ Задача № 6
# Моделирование интерфейса на чистом Си

## Срок сдачи

- До 14 апреля включительно (★ при участии в конкурсе на автомат).
- До 28 апреля включительно.



## Задание

Разработать иерархию классов с лекции (`Animal`, `Cow`, `Duck`) на чистом Си.

## Требования

**1. Структура проекта**

- `animal.h` - должен выглядеть строго следующим образом и никак иначе:
  ```c
  #pragma once

  /* Часть 1. Механизм vmt (virtual method table) */

  typedef void (*animal_say_fp)(void* context);
  typedef void (*animal_move_fp)(void* context, const char* dst);
  typedef void (*animal_dtor_fp)(void* context);

  struct animal_vmt {
    animal_say_fp say;
    animal_move_fp move;
    animal_dtor_fp dtor;
  };

  /* Часть 2. Клиентская часть (кроме конструктора - он для наследников) */

  struct animal;

  struct animal* animal_create (struct animal_vmt* vmt, void* context);
  void           animal_say    (struct animal* animal);
  void           animal_move   (struct animal* animal, const char* dst);
  void           animal_destroy(struct animal* animal);
  ```
- `animal.c` - реализовать самостоятельно;
- `cow.h` - должен выглядеть строго следующим образом и никак иначе:
  ```c
  #pragma once

  #include "animal.h"

  struct animal* animal_create_cow(const char* name);
  ```
- `cow.c` - реализовать самостоятельно;
- `duck.h` - должен выглядеть строго следующим образом и никак иначе:
  ```c
  #pragma once

  #include "animal.h"

  struct animal* animal_create_duck();
  ```
- `duck.c` - реализовать самостоятельно;
- `main.c` - должен выглядеть строго следующим образом и никак иначе:
  ```c
  #include <stdio.h>

  #include "cow.h"
  #include "duck.h"

  int main(void) {
    printf("Enter 0 for cow, 1 for duck: ");
    int n = 0;
    scanf("%d", &n);

    struct animal* = NULL;

    switch (n) {
    case 0:
      /* Факультативно: также запросить имя коровы у пользователя. */
      animal = animal_create_cow("Murka");
      break;
    case 1:
      animal = animal_create_duck();
      break;
    }
      
    // Если создана корова, должно быть выведено "Moo!"
    // Если создана утка, должно быть выведено "Quack!"
    animal_say(animal);

    // 1. Если создана корова, должно быть выведено сообщение в формате "A walks to B."
    // Вместо A должно выводиться имя коровы (Murka).
    // Вместо B должно выводиться значение параметра dst функции animal_move (Moscow).
    // С учётом конкретных параметров, должно быть выведено "Murka walks to Moscow."
    // 2. Если создана утка, должно быть выведено "Duck flies to B."
    // Вместо B должно выводиться значение параметра dst функции animal_move (Moscow).
    // С учётом конкретных параметров, должно быть выведено "Duck flies to Moscow."
    animal_move(animal, "Moscow");

    animal_destroy(animal);

    return 0;
  }
  ```
- `CMakeLists.txt` - должен выглядеть строго следующим образом и никак иначе:
  ```cmake
  cmake_minimum_required(VERSION 3.5)

  project("task6-animal" C)

  set(CMAKE_C_STANDARD 99)

  add_executable("task6-animal"
    "animal.c"
    "animal.h"
    "cow.c"
    "cow.h"
    "duck.c"
    "duck.h"
    "main.c"
  )

  if(MSVC)
    target_compile_definitions("task6-animal" PUBLIC _CRT_SECURE_NO_WARNINGS)
  endif()
  ```

**2. Про файлы, которые должны *выглядеть строго следующим образом и никак иначе*.**

- Единственное, что факультативно разрешается сделать, это объявить `typedef`
  для всех структур данных по следующему принципу:
  ```c
  typedef struct some_name some_name_t;
  ```
  И далее везде по коду заменить `struct some_name` на `some_name_t`.

**3. Должен быть реализован именно механизм позднего связывания.**

- Критерий проверки прост.
  Добавление нового типа данных не должно приводить ни к каким изменениям
  (а значит, и необходимости перекомпиляции) в файлах `animal.h`, `animal.c`.
  Например, добавление поддержки нового типа `dog` должно сводиться **исключительно** к следующим двум шагам:
  - добавление файлов `dog.h` и `dog.c` с соответствующим кодом;
  - в `main.c`:
    - добавление включения заголовочного файла `dog.h`;
    - добавление соответствующей ветки `case` в `switch` в функции `main` для поддержки создания нового типа.

**4. Корректное управление ресурсами.**

- Конструктор `create_animal_cow` должен создавать глубокую копию строки в динамике.
- При уничтожении объекта с помощью `animal_destroy(animal)` память должна быть корректно освобождена.
