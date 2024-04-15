
# Лабораторная работа № 5 <!-- omit in toc -->
# Текстовый интерфейс пользователя <!-- omit in toc -->

## ⚠ Данный документ находится в разработке и не предназначен (пока) для обучающихся <!-- omit in toc -->

- [1 Теоретические сведения](#1-теоретические-сведения)
  - [1.1 Подключение Turbo Vision](#11-подключение-turbo-vision)
  - [1.2 Отличие фреймворка от библиотеки](#12-отличие-фреймворка-от-библиотеки)
  - [1.3 Основной каркас](#13-основной-каркас)
  - [1.4 Окна и события](#14-окна-и-события)
  - [1.5 Пример](#15-пример)
- [2 Обязательное задание](#2-обязательное-задание)
  - [2.1 Общее задание](#21-общее-задание)
  - [2.2 Варианты](#22-варианты)
  - [2.3 Нормы](#23-нормы)
  - [2.4 Пример](#24-пример)
- [3 Факультативное задание](#3-факультативное-задание)

# 1 Теоретические сведения

Фреймворк [Turbo Vision](https://github.com/magiblot/tvision) предназначен для разработки приложений
с текстовым пользовательским интерфейсом (TUI -
[Text-based User Interface](https://en.wikipedia.org/wiki/Text-based_user_interface),
не путать с CLI,
[Command Line Interface](https://en.wikipedia.org/wiki/Command-line_interface)).

**⚠ Данный документ не содержит все сведения, необходимые для выполнения лабораторной работы.<br/>
Отсутствующую информацию см. в следующих книгах:**
- [Turbo Vision For C++ User's Guide](https://archive.org/details/BorlandTurboVisionForCUserSGuide/page/n4/mode/1up)
- [Turbo Vision 2.0 Programming Guide](https://archive.org/details/bitsavers_borlandTurrogrammingGuide1992_25707423)



## 1.1 Подключение Turbo Vision

### Настройка системы сборки <!-- omit in toc -->

В `CMakeLists.txt`:
1. Объявить:
   ```cmake
   include(FetchContent)

   FetchContent_Declare(
     tvision
     GIT_REPOSITORY https://github.com/magiblot/tvision.git
   )

   FetchContent_MakeAvailable(tvision)
   ```
2. Добавить зависимость от `tvision` для своей цели сборки при линковке
   (см. [`target_link_libraries`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html)).

### Использование в коде <!-- omit in toc -->

Включение заголовочного файла `tvision/tv.h` предваряется объявлением определений вида `#define Uses_TClass`,
где `TClass` - класс из фреймворка, объявление которого необходимо импортировать.
Например, если нужны классы `TApplication` и `TDeskTop`:

```cpp
#define Uses_TApplication
#define Uses_TDeskTop
#include <tvision/tv.h>
```



## 1.2 Отличие фреймворка от библиотеки

Для начала напомним, как выглядит разработка с использованием *библиотеки* SFML (см. соответствующую практику).
При использовании библиотеки разработчик полностью контролирует основной поток выполнения,
обращаясь к библиотеке по мере необходимости.
Например, приложение на SFML состоит из цикла, на каждой итерации которого:
- запрашивается и обрабатывается список произошедших событий;
- отрисовывается новый кадр.

При этом цикл, запрос событий, обработку событий и отрисовку (то есть *весь код*) пишет сам разработчик
(используя при необходимости функции и типы, предоставляемые библиотекой).

При использовании *фреймворка* у разработчика отбирается контроль над основным потоком выполнения.
Задача разработчика заключается в том, чтобы предоставить некоторые куски кода, которые будут вызываться фреймворком.

Резюмируя:
- при использовании библиотеки разработчик вызывает библиотечный код;
- при использовании фреймворка фреймворк вызывает код разработчика.

Как правило, при использовании фреймворка в функции `main` выполняется всего два шага:
- инициализация и настройка фреймворка;
- передача управления фреймворку.

Передача управления происходит с помощью вызова специальной функции (метода).
Вызов такой функции не вернёт управление до тех пор, пока работает приложение и фреймворк.
Если такая функция возвращает управление (например, пользователь нажал на кнопку закрытия окна),
то как правило дальше происходит просто выход из функции `main` и завершение работы приложения.

В сравнении с SFML, упрощённо говоря, можно сказать,
что при использовании фреймворка разработчику не требуется самому писать цикл обработки событий и отрисовки.
Реализация такого цикла с получением событий, обработкой событий и отрисовкой кадра спрятана внутри фреймворка.

См. также:
- [Framework vs Library](https://www.interviewbit.com/blog/framework-vs-library/)
- [Зачем нужны фреймворки и библиотеки](https://robotdreams.cc/blog/251-zachem-nuzhny-freymvorki-i-biblioteki)



## 1.3 Основной каркас

Turbo Vision является фреймворком.
Для его использования необходимо предоставить собственный наследник от класса `TApplication`.
Далее в `main` необходимо создать объект этого класса и передать управление путём вызова метода `run`:
```cpp
#include <limits>

// Uses_TKeys for kbCtrlX
// Uses_ViewCommands for cmQuit
#define Uses_TApplication
#define Uses_TDeskTop
#define Uses_TKeys
#define Uses_TProgInit
#define Uses_TStatusLine
#define Uses_TStatusItem
#define Uses_TStatusDef
#define Uses_TView
#define Uses_ViewCommands
#include <tvision/tv.h>

class App : public TApplication {
public:
  App() :
    TProgInit(
      &App::initStatusLine,
      nullptr,
      &App::initDeskTop
    )
  { }

  App(const App&) = delete;

  App& operator=(const App&) = delete;

private:
  static TStatusLine* initStatusLine(TRect r) {
    const auto defs = new TStatusDef(std::numeric_limits<ushort>::min(), std::numeric_limits<ushort>::max());
    *defs + *new TStatusItem("~Ctrl-X~ Exit", kbCtrlX, cmQuit);
    r.a.y = r.b.y - 1;
    return new TStatusLine(r, *defs);
  }

  static TDeskTop* initDeskTop(TRect r) {
    --r.b.y;
    return new TDeskTop(r);
  }
};

int main() {
  App app;

  app.run();

  return 0;
}
```

- ⚠ Работа с Turbo Vision в основном подразумевает использование обычных указателей.
  Однако когда такой указатель передаётся внутрь объекта фреймворка,
  то обычно такой объект становится владельцем указателя и в своём деструкторе корректно его освободит.
  Таким образом, несмотря на использование обычных указателей и явное выделение памяти в приведённом коде утечки нет.
  Более подробную информацию об управлению памятью см. в документации.
  
- **Вызов конструктора базового класса `TProgInit`.**
  
  Конструктор `TProgInit` принимает три указателя на функции:
  - `TStatusLine* (*cStatusLine)(TRect)`;
  - `TMenuBar* (*cMenuBar)(TRect)`;
  - `TDeskTop* (*cDeskTop)(TRect)`.
  
  Как видно из названий, эти функции используются для создания строки статуса, меню и рабочего стола.
  Все три функции являются необязательными (можно указать `nullptr`).
  В данном примере:
  - для создания строки статуса используется статический метод `App::initStatusLine`;
  - меню не создаётся;
  - для создания рабочего стола используется статический метод `App::initDeskTop`.
  
  Все три функции принимают `TRect` - это доступные размеры окна.
  Отметим, что объекты типа `TRect` имеют два открытых поля `a` и `b` типа `TPoint`,
  которые задают верхний левый и нижний правый угол.
  Объекты типа `TPoint`, в свою очередь, имеют два открытых поля `x` и `y`.
  Так это TUI, здесь все размеры целочисленные и измеряются **в символах**.
  
- **Пользовательский метод `initStatusLine`.**
  
  В строке статуса отображаются команды, которые доступны для пользователя прямо сейчас.
  Набор отображаемых команд определяется текущим **контекстом подсказки** (это обычное число, изначально равное 0).

  Для добавления отображаемых команд разработчик создаёт один или несколько объектов типа `TStatusDef`.
  Объект `TStatusDef` является контейнером, который может содержать произвольное количество команд.
  Конструктор `TStatusDef` принимает два числа `min` и `max`.
  В строке подсказки отрисовывается первый контейнер `TStatusDef`,
  в диапазон [`min`, `max`] которого попадает значение текущего контекста подсказки.

  В примере выше объект `defs` типа `TStatusDef` создаётся с максимально возможным диапазоном [`min`, `max`].
  Это означает, что команды из данного контейнера будут отображаться всегда (независимо от текущего контекста подсказки).

  Добавление нового элемента (команды типа `TStatusItem`) в контейнер типа `TStatusDef`  осуществляется с помощью оператора `+`.

  Конструктор `TStatusItem` принимает три параметра:
  - Отображаемый текст. Текст, обрамленный `~`, будет отображён особым цветом.
  - Горячая клавиша для выполнения команды.
    Фреймворк предоставляет предопределённый набор клавиш и комбинаций в виде глобальных констант,
    начинающихся с `kb` (от слова `keyboard`).
    В примере выше константа `kbCtrlX` означает комбинацию клавиш `Ctrl`+`X`.
  - Выполняемая команда.
    В общем случае определяется пользователем.
    Однако фреймворк предоставляет некоторый предопределённый набор повсеместно используемых команд
    в виде глобальных констант, начинающихся с `cm` (от слова `command`).
    В примере выше предопределённая команда `cmQuit` означает выход из приложения.

  Конструктор `TStatusLine` принимает два параметра:
  - Прямоугольник, задающий место расположения строки статуса.
    В примере выше строка статуса располагается в последней строке окна.
  - Контейнер `TStatusDef`, определяющий наборы отображаемых команд.
    
    Если необходимо указать более одного контейнера,
    то дополнительные контейнеры "присоединяются" к первому контейнеру с помощью оператора `+`.
    То есть существует две перегрузки оператора `+`, где в качестве левого операнда выступает `TStatusDef`:
    - у одной перегрузки правым операндом является `TStatusItem` (добавляет новый элемент в контейнер);
    - у другой перегрузки правым операндом является `TStatusDef` ("присоединяет" новый контейнер).

- **Пользовательский метод `initDeskTop`.**

  Конструктор `TDeskTop` принимает прямоугольник, задающий область рабочего стола.
  В примере выше данная область - это всё окно, за исключеним строки статуса.

- **Задача для самостоятельного закрепления материала.**

  Измените вышеприведённый код таким образом, чтобы строка состояния оказалась в верхней части окна, а не в нижней.



## 1.4 Окна и события

Вся основная работа идёт в окнах (`TWindow`) и/или диалогах (`TDialog`).
Разработчик описывает очередное окно/диалог как наследник `TWindow`/`TDialog`.
В конструкторе наследника создаётся макет окна - создаются различные элементы управления и добавляются в окно/диалог с помощью метода `insert`.
Полный список доступных элементов управления и предоставляемые им методы/события см. в книгах.
Приведём некоторые из самых распространённых:
- `TStaticText` - элемент управления для отображения неизменяемого текста ("подписи");
- `TListBox` - элемент управления для отображения списка строк;
- `TInputLine` - элемент управления для ввода строки;
- `TButton` - элемент управления для отображения кнопки, нажатие на которую приведёт к генерированию события

При создании кнопки можно указать номер команды (целое число типа `ushort`).
Этот номер может быть как предопределённым (одно из значений, предоставляемых фреймворком), так и пользовательским.
Пример предопределённой команды на уровне фреймворка - `const ushort cmQuit = 1`,
см. также все константы, начинающиеся с `cm` - от слова `command`.

Для реагирования на различные события (в том числе для выполнения команды при нажатии на кнопку),
в классе-наследнике необходимо переопределить метод `handleEvent`:
```cpp
void handleEvent(TEvent& event) override {
  TApplication::handleEvent(event);

  switch (event.what) {
  case evCommand:
    switch (event.message.command) {
      case ...: {
        ...
      }
    }
  }
```

В первой строке вызывается реализация метода из базового класса - для обработки тех событий,
которые могут быть обработаны на уровне фреймворка без вмешательства разработчика.

У объекта `event` есть поле `what`, которое определяет тип произошедшего события.
Вот некоторые из предопределённых констант, которым может быть равно поле `what`:
- `evMouseDown`;
- `evMouseUp`;
- `evMouseMove`;
- `evMouseAuto`;
- `evMouseWheel`;
- `evKeyDown`;
- `evCommand`.

В зависимости от типа события (связано ли оно с клавиатурой, мышью или командой)
у объекта `event` можно обратиться к одному из трёх вложенных объектов
(все три объекта образуют `union`, так как в зависимости от типа события только одно из трех полей содержит данные):
- `mouse`;
- `keyDown`;
- `message`.

В текущей лабораторной работе в основном понадобится только обрабатывать события типа команды (`event.what == evCommand`),
которые возникают при нажатии кнопки из строки статуса `TStatusItem` или обычной кнопки `TButton`.
В этом случае в обработчике `handleEvent` проверяется значение кода команды (`event.message.command`),
в зависимости от которого выполняется конкретное действие.



## 1.5 Пример

⚠ К сожалению, фреймворк Turbo Vision имеет не очень адекватные стили по умолчанию для окон и для всех модальных окон,
родителем для которых выступает не `TDeskTop`, а другое окно или диалог.
Поэтому при выполнении лабораторной рекомендуется ограничиться использованием только диалоговых окон (`TDialog`),
родителем для любого из которых всегда будет выступать `TDeskTop`.
Тем не менее использование `TWindow` со стандартным стилем не воспрещается (а со своим стилем - даже приветствуется).

Ниже приведён пример, в котором:

1. Описан класс `MessageDialog` для отображения простого диалогового окна с простым сообщением.
2. Описан класс `ListDialog` для отображения сложного диалогового окна со списком строк и
   и возможностью добавления новой строки в конец списка.
3. В примере используются следующие команды:
   - В строке статуса:
     - `cmQuit` - предопределённая команда для выхода из приложения.
       Обратите внимание, что в коде нет обработчика на эту команду.
       Она обрабатывается базовой реализацией `TProgram::handleEvent`.
     - `cmNew` - предопределённая команда для создания нового диалогового окна.
       Несмотря на то, что команда предопределённая,
       фреймворк в базовой реализации `handleEvent` это событие не обрабатывает.
       Поэтому эта команда обрабатывается в переопределённом `handleEvent`.
   - В диалоговом окне `ListDialog`:
     - `cmCustomNew` - команда с этим номером генерируется при нажатии на кнопку "Add".
       Событие, возникающее при выполнении этой команды, обрабатывается в переопределённом `handleEvent`.

```cpp
#include <cstring>
#include <limits>
#include <iostream>
#include <string>
#include <vector>

// Uses_TKeys for kbCtrlN, kbCtrlX
// Uses_ViewCommands for cmNew, cmQuit
#define Uses_TApplication
#define Uses_TButton
#define Uses_TDeskTop
#define Uses_TDialog
#define Uses_TInputLine
#define Uses_TKeys
#define Uses_TListBox
#define Uses_TStaticText
#define Uses_TStatusLine
#define Uses_TStatusItem
#define Uses_TStatusDef
#define Uses_TStringCollection
#define Uses_ViewCommands
#include <tvision/tv.h>

class MessageDialog : public TDialog {
private:
  static TRect center(const TRect& parentBounds, const int messageSize) {
    const TPoint parentSize = {
      parentBounds.b.x - parentBounds.a.x,
      parentBounds.b.y - parentBounds.a.y
    };

    const TPoint size = { messageSize + 5 , 8 };

    // TODO Сделайте так, чтобы диалоговое окно с сообщением показывалось по центру родительского окна
    return TRect(
      parentBounds.a.x + 1,
      parentBounds.a.y + 1,
      parentBounds.a.x + size.x,
      parentBounds.a.y + size.y
    );
  }

public:
  MessageDialog(const TRect& parentBounds, const std::string& title, const std::string& message) :
    TDialog(center(parentBounds, static_cast<int>(message.size())), title.c_str()),
    TWindowInit(TWindow::initFrame)
  {
    const auto staticText = new TStaticText(TRect(2, 2, size.x - 1, 3), message.c_str());
    insert(staticText);

    const auto button = new TButton(TRect(size.x - 8, 4, size.x - 2, 6), "Ok", cmOK, bfNormal);
    insert(button);
  }
};

class ListDialog : public TDialog {
private:
  std::vector<std::string> _items;

  TDeskTop* _desktop;
  TListBox* _listBox;
  TInputLine* _newItemInputLine;

  static TStringCollection* to_string_collection(const std::vector<std::string>& items) {
    const auto stringCollection = new TStringCollection(static_cast<short>(items.size()), 0);
    for (size_t i = 0; i < items.size(); ++i) {
      const auto& item = items[i];
      char* rawString = new char[item.size() + 1];
      strcpy(rawString, item.c_str());
      stringCollection->atInsert(static_cast<ccIndex>(i), rawString);
    }
    return stringCollection;
  }

  void addItem() {
    std::string item(_newItemInputLine->data);
    if (!item.empty()) {
      _items.push_back(item);
      _listBox->newList(to_string_collection(_items));
      _newItemInputLine->setData(const_cast<void*>(static_cast<const void*>("")));
    }
    else {
      const auto dialog = new MessageDialog(this->getBounds(), "Error", "A new element cannot be empty.");
      _desktop->execView(dialog);
      TObject::destroy(dialog);
    }
  }

public:
  static const ushort cmCustomAdd = 100;

  ListDialog(TDeskTop* desktop, const TRect& bounds, TStringView title) :
    TDialog(bounds, title),
    TWindowInit(&TWindow::initFrame),
    _desktop(desktop)
  {
    // _listBox
    {
      const auto listBoxText = new TStaticText(TRect(2, 2, size.x - 2, 3), "List:");
      insert(listBoxText);

      _listBox = new TListBox(TRect(2, 3, size.x - 2, size.y - 4), 1, nullptr);
      insert(_listBox);
    }

    // _newItemInputLine + addButton
    {
      const auto textLinePrompt = new TStaticText(TRect(2, size.y - 3, 12, size.y - 2), "New item:");
      insert(textLinePrompt);

      _newItemInputLine = new TInputLine(TRect(12, size.y - 3, size.x - 13, size.y - 2), 17);
      insert(_newItemInputLine);

      const auto addButton = new TButton(TRect(size.x - 12, size.y - 3, size.x - 2, size.y - 1), "Add", cmCustomAdd, bfNormal);
      insert(addButton);
    }
  }

  ListDialog(const ListDialog&) = delete;

  ListDialog& operator=(const ListDialog&) = delete;

  void handleEvent(TEvent &event) override {
    TWindow::handleEvent(event);

    if (event.what == evCommand && event.message.command == cmCustomAdd) {
      addItem();
    }
  }
};

class App : public TApplication {
public:
  App() :
    TProgInit(
      &App::initStatusLine,
      nullptr,
      &App::initDeskTop
    )
  { }

  App(const App&) = delete;

  App& operator=(const App&) = delete;

  void handleEvent(TEvent &event) override {
    TApplication::handleEvent(event);

    if (event.what == evCommand && event.message.command == cmNew) {
      newWindow();
    }
  }

private:
  void newWindow() {
    const auto window = new ListDialog(deskTop, TRect(0, 0, deskTop->size.x, deskTop->size.y), "List");
    deskTop->insert(window);
  }

  static TStatusLine* initStatusLine(TRect r) {
    const auto defs = new TStatusDef(
      std::numeric_limits<ushort>::min(),
      std::numeric_limits<ushort>::max()
    );

    *defs
      + *new TStatusItem("~Ctrl-X~ Exit", kbCtrlX, cmQuit)
      + *new TStatusItem("~Ctrl+N~ New", kbCtrlN, cmNew);

    r.a.y = r.b.y - 1;

    return new TStatusLine(r, *defs);
  }

  static TDeskTop* initDeskTop(TRect r) {
    --r.b.y;
    return new TDeskTop(r);
  }
};

int main() {
  App app;

  app.run();

  return 0;
}

```

TODO Описать некоторые нюансы в примере



# 2 Обязательное задание

## 2.1 Общее задание

TODO



## 2.2 Варианты

TODO



## 2.3 Нормы

TODO



## 2.4 Пример

TODO



# 3 Факультативное задание

1. Продемонстрировать работоспособность вашего проекта под операционной системой семейства Linux.
1. TODO Меню с сохранением/загрузкой
