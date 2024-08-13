/*//==============================================================================================================
Требование для всех вариантов Задачи 4
Решение всех задач данного раздела предполагает использование кучи, реализованной в виде шаблонного класса.
Решение должно поддерживать передачу функции сравнения снаружи.
Куча должна быть динамической.
Топ K пользователей из лога
Имеется лог-файл, в котором хранятся пары для N пользователей (Идентификатор пользователя, посещаемость сайта).
Напишите программу, которая выбирает K пользователей, которые чаще других заходили на сайт, и выводит их в порядке
 возрастания посещаемости. Количество заходов и идентификаторы пользователей не повторяются.
Требования: время работы O(N * logK), где N - кол-во пользователей. Ограничение на размер кучи O(K).
Формат входных данных: Сначала вводятся N и K, затем пары (Идентификатор пользователя, посещаемость сайта).
Формат выходных данных: Идентификаторы пользователей в порядке возрастания посещаемости

 *///==============================================================================================================
#pragma GCC optimize ("Ofast")

#include <iostream>

using namespace std;

struct UserFreq {
    int user;
    int freq;
};

bool operator<(const UserFreq &l, const UserFreq &r) {
    return l.freq < r.freq;
}

bool operator>(const UserFreq &l, const UserFreq &r) {
    return l.freq > r.freq;
}

template<class T>
struct DefaultComparator {
    bool operator()(const T &l, const T &r) {
        return l > r;
    }
};

template<class T, class Comp=DefaultComparator<T> >
class Heap {
public:
    explicit Heap(Comp cmp = Comp()) {
        arr = new T[4095];
        heapSize = 0;
        capacity = 4095;
        comp = cmp;
    }

    explicit Heap(T *arr, size_t size, Comp cmp = Comp()) {
        comp = cmp;
        arr = new T[size];
        for (int i = 0; i < size; ++i) {
            arr[i] = arr[i];
        }
        heapSize = size;
        capacity = size;
        heapify();
    }

    ~Heap() {
        delete[] arr;
        arr = nullptr; // для улучшения безопасности кода
        heapSize = 0;
        capacity = 0;
    }

    Heap(const Heap &) = delete;

    Heap(Heap &&) = delete;

    Heap &operator=(const Heap &) = delete;

    Heap &operator=(Heap &&) = delete;

    const T &getTop() const;

    void extractMin();

    void insert(const T &value);

    bool isEmpty() const;

    bool isFull();

private:
    void siftUp(size_t i);

    void siftDown(int i);

    void heapify();

    void grow();

    T *arr;
    size_t heapSize;
    size_t capacity;

    Comp comp;
};

template<class T, class Comp>
bool Heap<T, Comp>::isFull() {
    return heapSize >= capacity;
}

template<class T, class Comp>
const T &Heap<T, Comp>::getTop() const {
    return arr[0];
}

template<class T, class Comp>
void Heap<T, Comp>::extractMin() {
    if (0 >= heapSize) {
        return;
    }
    --heapSize;
    arr[0] = arr[heapSize];
    heapify();
}

template<class T, class Comp>
void Heap<T, Comp>::insert(const T &value) {
    ++heapSize;
    if (isFull()) {
        grow();
    }
    arr[heapSize - 1] = value;
    siftUp(heapSize - 1);
}

template<class T, class Comp>
bool Heap<T, Comp>::isEmpty() const {
    return 0 == heapSize;
}

template<class T, class Comp>
void Heap<T, Comp>::siftUp(size_t i) {
    while (i > 0) {
        size_t parent = (i - 1) >> 1;
        if (comp(arr[i], arr[parent]))
            return;
        swap(arr[i], arr[parent]);
        i = parent;
    }
}

template<class T, class Comp>
void Heap<T, Comp>::siftDown(int i) {
    int left, largest, right;
    left = 2 * i + 1;
    right = left + 1;
    largest = i;
    if (left < (int) heapSize && comp(arr[largest], arr[left]))
        largest = left;
    if (right < (int) heapSize && comp(arr[largest], arr[right]))
        largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        siftDown(largest);
    }
}

template<class T, class Comp>
void Heap<T, Comp>::heapify() {
    if (!heapSize || 1 == heapSize) {
        return;
    }
    for (int i = (heapSize >> 1) - 1; 0 <= i; --i)
        siftDown(i);
}

template<class T, class Comp>
void Heap<T, Comp>::grow() { // увеличиваем размер массива
    capacity <<= 1;
    T *newArr = new T[capacity];
    for (int i = 0; i < (int) heapSize; ++i) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
}

int main() {
    int N, K;

    cin >> N >> K;
    if (!N || !K) { // один из массивов пуст
        return 0;
    }

    auto heap = new Heap<UserFreq>(); // создаем экземпляр класса Heap
    UserFreq userFreq{}; // создаем объект класса UserFreq, который будет хранить данные пользователя и частоту посещения

    for (int i = 0; i < N; ++i) {
        cin >> userFreq.user >> userFreq.freq; // считываем данные
        if (i >= K) { // удаляем минимальный элемент из массива в слуае превышения K элементов
            heap->insert(userFreq);
            heap->extractMin();
        } else
            heap->insert(userFreq);
    }

    for (int i = 0; i < min(K, N); ++i) {
        cout << heap->getTop().user << " "; // выводим минимальный элемент массива через пробел
        heap->extractMin();
    }
    delete heap; // освобождаем память
    return 0;
}
