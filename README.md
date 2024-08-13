# cpp-algorithms-VK-tehnopark
# Semestr 1
# Общие требования для всех задач

- Ввод/вывод отделены от решения.
- Не должно быть утечек памяти.

# Задача 1. «Представление графа» (5 баллов)

*Обязательная задача*

Дан базовый интерфейс для представления ориентированного графа:

```cpp
struct IGraph {
    virtual ~IGraph() {}
    
    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};
```

Необходимо написать несколько реализаций интерфейса:

1. `ListGraph`, хранящий граф в виде массива списков смежности,
2. `MatrixGraph`, хранящий граф в виде матрицы смежности,
3. `SetGraph`, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев поиска,
4. `ArcGraph`, хранящий граф в виде одного массива пар `{from, to}`.

Также необходимо реализовать конструктор, принимающий `const IGraph&`. Такой конструктор должен скопировать переданный граф в создаваемый объект.

Для каждого класса создавайте отдельные `.h` и `.cpp` файлы.

Число вершин графа задается в конструкторе каждой реализации.

# Задача 2. Количество различных путей (3 балла)

*Обязательная задача*

Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами. Найдите количество различных кратчайших путей между заданными вершинами. 

**Требования:** сложность O(V+E). 

## Формат ввода

- v: кол-во вершин (макс. 50000)
- n: кол-во ребер (макс. 200000)
- n пар реберных вершин
- пара вершин u, w для запроса

## Формат вывода

Количество кратчайших путей от u к w.

## Пример

### Вход

```
4
5
0 1
0 2
1 2
1 3
2 3
0 3
```

### Выход

```
2
```

# Задача 3. «Города» (4 балла)

*Обязательная задача*

Требуется отыскать самый выгодный маршрут между городами. 

**Требования:** время работы O((N+M)logN), где N - количество городов, M - известных дорог между ними.

## Формат входных данных

- Первая строка содержит число N – количество городов.
- Вторая строка содержит число M - количество дорог.
- Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).
- Последняя строка содержит маршрут (откуда и куда нужно доехать).

## Формат выходных данных

Вывести длину самого выгодного маршрута.

## Пример

### Вход

```
6
9
0 3 1
0 4 2
1 2 7
1 3 2
1 4 3
1 5 3
2 5 3
3 4 4
3 5 6
0 2
```

### Выход

```
9
```

# Задача 4. «Пятнашки» (8 баллов)

Написать алгоритм для решения игры в "пятнашки". Решением задачи является приведение к виду:

```
[ 1  2  3  4 ]
[ 5  6  7  8 ]
[ 9  10 11 12] 
[ 13 14 15 0 ]
```

где 0 задает пустую ячейку.

Достаточно найти хотя бы какое-то решение. Число перемещений костяшек не обязано быть минимальным.

## Формат входных данных

Начальная расстановка.

## Формат выходных данных

Если решение существует, то в первой строке выходного файла выведите минимальное число перемещений костяшек, которое нужно сделать, чтобы достичь выигрышной конфигурации, а во второй строке выведите соответствующую последовательность ходов: 
- L означает, что костяшка сдвинулась влево
- R – вправо
- U – вверх
- D – вниз

Если таких последовательностей несколько, то выведите любую из них. Если же выигрышная конфигурация недостижима, то выведите в выходной файл одно число −1.

## Пример

### Вход

```
1 2 3 4
5 6 7 8
9 10 11 0
13 14 15 12
```

### Выход

```
1
U
```

# Задача 5. Приближенное решение метрической неориентированной задачи коммивояжера (6 баллов)

Найдите приближенное решение метрической неориентированной задачи коммивояжера в полном графе (на плоскости) с помощью минимального остовного дерева.

## Требования к реализации:

1. Оцените качество приближения на случайном наборе точек, нормально распределенном на плоскости с дисперсией 1. 
2. Нормально распределенный набор точек получайте с помощью преобразования Бокса-Мюллера.
3. При фиксированном N (количестве вершин графа) несколько раз запустите оценку качества приближения. 
4. Вычислите среднее значение и среднеквадратичное отклонение качества приближения для данного N.
5. Запустите данный эксперимент для всех N в некотором диапазоне, например, [2, 10].
6. Автоматизируйте запуск экспериментов.
7. В решении требуется разумно разделить код на файлы. Каждому классу - свой заголовочный файл и файл с реализацией.

## Варианты реализации:

**Вариант 1.** Для построения минимального остовного дерева используйте алгоритм Крускала.

**Вариант 2.** Для построения минимального остовного дерева используйте алгоритм Прима.

## Тестирование:

В контесте протестируйте работу алгоритма построения минимального остовного дерева. 

**Примечание:** Варианты в контесте - не те, который описаны здесь. Правильные варианты - здесь.

# Semestr 2

# Задача 1. Хеш-таблица (6 баллов)

*Обязательная задача*

Реализуйте структуру данных типа "множество строк" на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.

## Требования:

1. Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
2. Начальный размер таблицы должен быть равным 8-ми.
3. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
4. Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
5. В таблице запрещено хранение указателей на описатель элемента.

## Варианты разрешения коллизий:

1. Квадратичное пробирование. i-ая проба g(k, i) = g(k, i-1) + i (mod m). m - степень двойки.
2. Двойное хеширование.

## Формат входных данных:

Каждая строка входных данных задает одну операцию над множеством. Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция.

Тип операции – один из трех символов:
- `+` означает добавление данной строки в множество;
- `-` означает удаление строки из множества;
- `?` означает проверку принадлежности данной строки множеству.

**Примечание:** При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве. При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.

## Формат выходных данных:

Программа должна вывести для каждой операции одну из двух строк: `OK` или `FAIL`, в зависимости от того, встречается ли данное слово в нашем множестве.

## Пример:

### Вход:

```
+ hello
+ bye
? bye
+ bye
- bye
? bye
? hello
```

### Выход:

```
OK
OK
OK
FAIL
OK
FAIL
OK
```

# Задача 2. Порядок обхода (4 балла)

*Обязательная задача*

Дано число N < 10^6 и последовательность целых чисел из [-2^31..2^31] длиной N.

Требуется построить бинарное дерево, заданное наивным порядком вставки. Т.е., при добавлении очередного числа K в дерево с корнем root:
- если root→Key ≤ K, то узел K добавляется в правое поддерево root;
- иначе в левое поддерево root.

**Требования:** 
- Рекурсия запрещена. 
- Решение должно поддерживать передачу функции сравнения снаружи.

## 2_1. Выведите элементы в порядке in-order (слева направо).

### Пример 1:
**Вход:**
```
3
2 1 3
```
**Выход:**
```
1 2 3
```

### Пример 2:
**Вход:**
```
3
1 2 3
```
**Выход:**
```
1 2 3
```

### Пример 3:
**Вход:**
```
3
3 1 2
```
**Выход:**
```
1 2 3
```

## 2_2. Выведите элементы в порядке pre-order (сверху вниз).

### Пример 1:
**Вход:**
```
3
2 1 3
```
**Выход:**
```
2 1 3
```

### Пример 2:
**Вход:**
```
3
1 2 3
```
**Выход:**
```
1 2 3
```

### Пример 3:
**Вход:**
```
3
3 1 2
```
**Выход:**
```
3 1 2
```

### Пример 4:
**Вход:**
```
4
3 1 4 2
```
**Выход:**
```
3 1 2 4
```

## 2_3. Выведите элементы в порядке post-order (снизу вверх).

### Пример 1:
**Вход:**
```
3
2 1 3
```
**Выход:**
```
1 3 2
```

### Пример 2:
**Вход:**
```
3
1 2 3
```
**Выход:**
```
3 2 1
```

### Пример 3:
**Вход:**
```
3
3 1 2
```
**Выход:**
```
2 1 3
```

## 2_4. Выведите элементы в порядке level-order (по слоям, "в ширину").

### Пример 1:
**Вход:**
```
3
2 1 3
```
**Выход:**
```
2 1 3
```

### Пример 2:
**Вход:**
```
3
1 2 3
```
**Выход:**
```
1 2 3
```

### Пример 3:
**Вход:**
```
3
3 1 2
```
**Выход:**
```
3 1 2
```

### Пример 4:
**Вход:**
```
4
3 1 4 2
```
**Выход:**
```
3 1 4 2
```

# Задача № 3 (4 балла)

Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.

## Формат входных данных

В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.

- a = 1 - push front
- a = 2 - pop front
- a = 3 - push back
- a = 4 - pop back

Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается "-1". 

## Формат выходных данных

Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

### 3_1. Реализовать очередь с динамическим зацикленным буфером (на основе динамического массива)

Требования: Очередь должна быть реализована в виде класса.

#### Пример 1:
Input:
```
3
3 44
3 50
2 44
```
Output:
```
YES
```

#### Пример 2:
Input:
```
2
2 -1
3 10
```
Output:
```
YES
```

#### Пример 3:
Input:
```
2
3 44
2 66
```
Output:
```
NO
```

### 3_2. Реализовать дек с динамическим зацикленным буфером (на основе динамического массива)

Требования: Дек должен быть реализован в виде класса.

#### Пример 1:
Input:
```
3
1 44
3 50
2 44
```
Output:
```
YES
```

#### Пример 2:
Input:
```
2
2 -1
1 10
```
Output:
```
YES
```

#### Пример 3:
Input:
```
2
3 44
4 66
```
Output:
```
NO
```

### 3_3. Реализовать очередь с помощью двух стеков

Требования: Очередь должна быть реализована в виде класса. Стек тоже должен быть реализован в виде класса.

#### Пример 1:
Input:
```
3
3 44
3 50
2 44
```
Output:
```
YES
```

#### Пример 2:
Input:
```
2
2 -1
3 10
```
Output:
```
YES
```

#### Пример 3:
Input:
```
2
3 44
2 66
```
Output:
```
NO
```
# Задача 3. B-дерево (4 балла)

Постройте B-дерево минимального порядка t и выведите его по слоям.
В качестве ключа используются числа, лежащие в диапазоне 0..2^32 -1

## Требования: 
- B-дерево должно быть реализовано в виде шаблонного класса.
- Решение должно поддерживать передачу функции сравнения снаружи.

## Формат входных данных
Сначала вводится минимальный порядок дерева t.
Затем вводятся элементы дерева.

## Формат выходных данных
Программа должна вывести B-дерево по слоям. Каждый слой на новой строке, элементы должны выводится в том порядке, в котором они лежат в узлах.

### Пример 1:

#### Ввод (stdin):
```
2
0 1 2 3 4 5 6 7 8 9
```

#### Вывод (stdout):
```
3
1 5 7
0 2 4 6 8 9
```

### Пример 2:

#### Ввод (stdin):
```
4
0 1 2 3 4 5 6 7 8 9
```

#### Вывод (stdout):
```
3
0 1 2 4 5 6 7 8 9
```
# Задача 4. Использование АВЛ-дерева (5 баллов)

**Обязательная задача**

## Требование для всех вариантов Задачи 4

Решение должно поддерживать передачу функции сравнения снаружи.

## 4_1. Солдаты

В одной военной части решили построить в одну шеренгу по росту. Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в конце – самые низкие. За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного роста. Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится. 

**Требования:** скорость выполнения команды - O(log n).

### Формат входных данных

Первая строка содержит число N – количество команд (1 ≤ N ≤ 30 000). В каждой следующей строке содержится описание команды: число 1 и X если солдат приходит в строй (X – рост солдата, натуральное число до 100 000 включительно) и число 2 и Y если солдата, стоящим в строе на месте Y надо удалить из строя. Солдаты в строе нумеруются с нуля.

### Формат выходных данных

На каждую команду 1 (добавление в строй) вы должны выводить число K – номер позиции, на которую должен встать этот солдат (все стоящие за ним двигаются назад).

#### Пример:

**Ввод:**
```
5
1 100
1 200
1 50
2 1
1 150
```

**Вывод:**
```
0
0
2
1
```

## 4_2. Порядковые статистики

Дано число N и N строк. Каждая строка содержит команду добавления или удаления натуральных чисел, а также запрос на получение k-ой порядковой статистики. Команда добавления числа A задается положительным числом A, команда удаления числа A задается отрицательным числом "-A". Запрос на получение k-ой порядковой статистики задается числом k. 

**Требования:** скорость выполнения запроса - O(log n).

#### Пример:

**Ввод:**
```
5
40 0
10 1
4 1 
-10 0
50 2
```

**Вывод:**
```
40
40
10
4
50
```
# Задача 5. Алгоритм сжатия данных Хаффмана (6 баллов и более)

Напишите две функции для создания архива из одного файла и извлечения файла из архива.

**Требования:** коэффициент сжатия < 1.

```cpp
// Метод архивирует данные из потока original
void Encode(IInputStream& original, IOutputStream& compressed);

// Метод восстанавливает оригинальные данные
void Decode(IInputStream& compressed, IOutputStream& original);
```

где:

```cpp
typedef unsigned char byte;
#define interface struct

interface IInputStream {
    // Возвращает false, если поток закончился
    virtual bool Read(byte& value) = 0;
};

interface IOutputStream {
    virtual void Write(byte value) = 0;
};
```

В архиве сохраняйте дерево Хаффмана и код Хаффмана от исходных данных.
Дерево Хаффмана требуется хранить эффективно - не более 10 бит на каждый 8-битный символ.

В контест необходимо отправить .cpp файл содержащий функции Encode, Decode, а также включающий файл Huffman.h. Тестирующая программа выводит размер сжатого файла в процентах от исходного.

Лучшие 3 решения с коэффициентом сжатия < 1 из каждой группы оцениваются в 10, 7 и 4 баллов соответственно.

## Пример минимального решения:

```cpp
#include "Huffman.h"

static void copyStream(IInputStream& input, IOutputStream& output)
{
    byte value;
    while (input.Read(value)) 
    { 
        output.Write(value); 
    }
}

void Encode(IInputStream& original, IOutputStream& compressed) 
{
    copyStream(original, compressed); 
}

void Decode(IInputStream& compressed, IOutputStream& original) 
{ 
    copyStream(compressed, original); 
}
```
# Задача 1. «Представление графа» (5 баллов)

**Обязательная задача**

Дан базовый интерфейс для представления ориентированного графа:

```cpp
struct IGraph {
    virtual ~IGraph() {}
    
    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};
```

Необходимо написать несколько реализаций интерфейса:

1. `ListGraph`, хранящий граф в виде массива списков смежности,
2. `MatrixGraph`, хранящий граф в виде матрицы смежности,
3. `SetGraph`, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев поиска,
4. `ArcGraph`, хранящий граф в виде одного массива пар {from, to}.

Также необходимо реализовать конструктор, принимающий `const IGraph&`. Такой конструктор должен скопировать переданный граф в создаваемый объект.

Для каждого класса создавайте отдельные h и cpp файлы.

Число вершин графа задается в конструкторе каждой реализации.
# Задача 2. Количество различных путей (3 балла)

**Обязательная задача**

Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами. Найдите количество различных кратчайших путей между заданными вершинами. 

**Требования:** сложность O(V+E). 

## Формат ввода

- v: кол-во вершин (макс. 50000),
- n: кол-во ребер (макс. 200000),
- n пар реберных вершин,
- пара вершин u, w для запроса.

## Формат вывода

Количество кратчайших путей от u к w.

### Пример

#### Ввод:
```
4
5
0 1
0 2
1 2
1 3
2 3
0 3
```

#### Вывод:
```
2
```
# Задача 3. «Города» (4 балла)

**Обязательная задача**

Требуется отыскать самый выгодный маршрут между городами. 

**Требования:** время работы O((N+M)logN), где N-количество городов, M-известных дорог между ними.

## Формат входных данных

1. Первая строка содержит число N – количество городов.
2. Вторая строка содержит число M - количество дорог.
3. Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).
4. Последняя строка содержит маршрут (откуда и куда нужно доехать).

## Формат выходных данных

Вывести длину самого выгодного маршрута.

### Пример

#### Ввод:
```
6
9
0 3 1
0 4 2
1 2 7
1 3 2
1 4 3
1 5 3
2 5 3
3 4 4
3 5 6
0 2
```

#### Вывод:
```
9
```
# Задача 4. «Пятнашки» (8 баллов)

Написать алгоритм для решения игры в "пятнашки". Решением задачи является приведение к виду:

```
[ 1  2  3  4 ]
[ 5  6  7  8 ]
[ 9  10 11 12] 
[ 13 14 15 0 ]
```

где 0 задает пустую ячейку.

Достаточно найти хотя бы какое-то решение. Число перемещений костяшек не обязано быть минимальным.

## Формат входных данных

Начальная расстановка.

## Формат выходных данных

Если решение существует, то в первой строке выходного файла выведите минимальное число перемещений костяшек, которое нужно сделать, чтобы достичь выигрышной конфигурации, а во второй строке выведите соответствующую последовательность ходов: 
- L означает, что костяшка сдвинулась влево, 
- R – вправо, 
- U – вверх, 
- D – вниз. 

Если таких последовательностей несколько, то выведите любую из них. Если же выигрышная конфигурация недостижима, то выведите в выходной файл одно число −1.

### Пример

#### Ввод:
```
1 2 3 4
5 6 7 8
9 10 11 0
13 14 15 12
```

#### Вывод:
```
1
U
```
# Задача 5. Приближенное решение метрической неориентированной задачи коммивояжера (6 баллов)

Найдите приближенное решение метрической неориентированной задачи коммивояжера в полном графе (на плоскости) с помощью минимального остовного дерева.

## Требования:

1. Оцените качество приближения на случайном наборе точек, нормально распределенном на плоскости с дисперсией 1. 
2. Нормально распределенный набор точек получайте с помощью преобразования Бокса-Мюллера.
3. При фиксированном N (количестве вершин графа) несколько раз запустите оценку качества приближения. 
4. Вычислите среднее значение и среднеквадратичное отклонение качества приближения для данного N.
5. Запустите данный эксперимент для всех N в некотором диапазоне, например, [2, 10].
6. Автоматизируйте запуск экспериментов.
7. В решении требуется разумно разделить код на файлы. Каждому классу - свой заголовочный файл и файл с реализацией.

## Варианты:

1. Для построения минимального остовного дерева используйте алгоритм Крускала.
2. Для построения минимального остовного дерева используйте алгоритм Прима.

## Примечание:

В контесте протестируйте работу алгоритма построения минимального остовного дерева. (Варианты в контесте - не те, который описаны здесь. Правильные варианты - здесь.)
