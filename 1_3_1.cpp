/*//==============================================================================================================
Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
Формат входных данных.
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных,
 то ожидается “-1”.
Формат выходных данных.
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось,
 то напечатать NO.
 Реализовать очередь с динамическим зацикленным буфером (на основе динамического массива).
Требования: Очередь должна быть реализована в виде класса.
 *///==============================================================================================================
#pragma GCC optimize ("Ofast")

#include <iostream>

using namespace std;

class Queue {
public:
    Queue();//конструктор
    ~Queue();//деструктор

    Queue(const Queue &other) = delete;

    Queue &operator=(const Queue &other) = delete;

    void Enqueue(int val);//вставка элемента в очередь
    int Dequeue();//удаление элемента из очереди, возвращает -1 если очередь пуста
    bool IsEmpty();//проверка на пустоту
    bool IsFull();//проверка на заполненность

private:
    int *data; //массив для хранения данных
    int dataSize; //количество данных в массиве
    int head;
    int tail;

    void growSize();// динамическое расширение массива

};

Queue::Queue()
        : data(nullptr), dataSize(0), head(0), tail(0) //конструктор
{
    growSize();
}

Queue::~Queue() { //деструктор
    delete[] data;
    data = nullptr;
    dataSize = 0;
    head = 0;
    tail = 0;
}

void Queue::Enqueue(int val) { //вставка элемента в очередь
    if (!IsFull()) {
        data[(tail) % dataSize] = val;
        tail = (tail + 1) % dataSize;
    } else {
        growSize();
        Enqueue(val);
    }
}

int Queue::Dequeue() { //удаление элемента из очереди, возвращает -1 если очередь пуста
    if (IsEmpty()) { // если очередь пуста
        return -1;
    }
    int element = data[head];
    if (head == dataSize - 1) {
        head = 0;
    } else {
        ++head;
    }
    return element;
}

bool Queue::IsEmpty() { // проверка на пустоту
    return head == tail;
}

bool Queue::IsFull() { // проверка на заполненность
    return (tail + 1) % dataSize == head;
}

void Queue::growSize() { // динамическое расширение массива
    int newDataSize = (dataSize > 0) ? (dataSize << 1) : 4096, // размер нового массива
    *newData = new int[newDataSize]; // создаём новый массив размером newDataSize
    if (head != tail) {
        int j = 0;
        for (int i = head; i < dataSize; ++i) {
            if (tail == i) {
                break;
            }
            newData[j++] = data[i]; // копируем данные из старого массива в новый массив
            if (dataSize - 1 == i) {
                i = -1;
            }
        }
        head = 0;
        tail = j;
    }
    delete[] data; // удаляем старый массив
    data = newData;
    dataSize = newDataSize;
}

int main() {
    int n, op, val, elem;
    cin >> n;
    Queue queue;
    for (int i = 0; i < n; ++i) {
        cin >> op >> val;
        switch (op) {
            case 2:
                //pop front
                elem = queue.Dequeue();
                if (elem != val) {
                    cout << "NO" << endl;
                    return 0;
                }
                break;
            case 3:
                //push back
                queue.Enqueue(val);
                break;
        }
    }
    cout << "YES" << endl;
    return 0;
}
