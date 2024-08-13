/*//==============================================================================================================
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые
 строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда
 коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки
 принадлежности данной строки множеству.
Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
Требования: В таблице запрещено хранение указателей на описатель элемента.
Формат входных данных
        Каждая строка входных данных задает одну операцию над множеством. Запись операции состоит из типа операции и
        следующей за ним через пробел строки, над которой проводится операция.
Тип операции  – один из трех символов:
+  означает добавление данной строки в множество;
-  означает удаление  строки из множества;
?  означает проверку принадлежности данной строки множеству.
При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве. При удалении элемента из
 множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
Формат выходных данных
Программа должна вывести для каждой операции одну из двух строк OK или FAIL, в зависимости от того, встречается ли
 данное слово в нашем множестве.
*/ //==============================================================================================================
#include <iostream>
#include <vector>

using namespace std;


class HashTable {
public:
    HashTable();
    ~HashTable();
    bool add(string); // добавляет строку в таблицу
    bool has(string key) const;
    bool remove(string);

private:
    struct Node { // элемент хеш-таблицы
        bool deleted;
        string value;
        Node();
        explicit Node(string s);
    };

    void reHash(); // увеличивает размер таблицы в 2 раза
    unsigned int getHash(string key) const;

    unsigned size; // размер таблицы
    int currSize; // реальный размер таблицы
    double alpha; // коэффициент заполнения таблицы
    double const maxAlpha; // максимальный коэффициент заполнения таблицы
    vector<Node *> array;   // хэш-таблица

};

HashTable::Node::Node(string s) : value(s), deleted(false) {}

HashTable::Node::Node() : deleted(false) {}

void readOp(HashTable &hashTable);

int main() {
    HashTable hashTable;
    readOp(hashTable);
    return 0;
}

void readOp(HashTable &hashTable) {
    char operation;
    string key;

    while (cin >> operation >> key) { // пока пользователь вводит данные
        switch (operation) {
            case '+':
                cout << ((hashTable.add(key)) ? "OK" : "FAIL") << endl;
                break;
            case '-':
                cout << ((hashTable.remove(key)) ? "OK" : "FAIL") << endl;
                break;
            case '?':
                cout << ((hashTable.has(key)) ? "OK" : "FAIL") << endl;
                break;
            default:
                cout << "ERROR: Invalid operation" << endl;
        }
    }
}

HashTable::HashTable() : size(8), maxAlpha(3.0 / 4.0), alpha(0), currSize(0) {
    array.assign(size, nullptr);
}


HashTable::~HashTable() {
    for (int i = 0; i < size; ++i) {
        if (array[i]) {
            delete array[i];
            array[i] = nullptr;
        }
    }
}


bool HashTable::add(string key) {
    if (has(key)) {
        return false;
    }

    int index, sample;
    bool success;

    index = (int)getHash(key);
    sample = 0;
    success = false;

    while (sample < size) {
        index = (index + sample) % size;
        if (!array[index]) {
            success = true;
            array[index] = new Node(key);
        } else if (array[index]->deleted) {
            success = true;
            array[index]->value = key;
            array[index]->deleted = false;
        }
        if (success) {
            ++currSize;
            alpha = (double) currSize / size;
            if (alpha >= maxAlpha) {
                reHash();
            }

            return true;
        }
        ++sample;
    }

    return false;
}


bool HashTable::remove(string key) {
    int sample, index;

    sample = 0;
    index = (int)getHash(key);

    if (!has(key)) {
        return false;
    }

    while (sample < array.size()) {
        index = (index + sample) % size;
        if (array[index]->value == key && !array[index]->deleted) {
            array[index]->deleted = true;
            --currSize;
            alpha = (double) currSize / size;
            break;
        }
        ++sample;
    }

    return true;
}


bool HashTable::has(string key) const {
    int sample, index;
    Node *node;

    sample = 0;
    index = (int)getHash(key);
    node = array[index];

    while (node && sample < size) {
        if (!node->deleted && !node->value.compare(key)) {
            return true;
        }
        ++sample;
        index = (index + sample) % size;
        node = array[index];
    }

    return false;
}


void HashTable::reHash() {
    vector<Node *> oldArray;

    oldArray = array;
    size <<= 1;
    array.assign(size, nullptr);
    currSize = 0;

    for (size_t i = 0; i < oldArray.size(); ++i) {
        if (oldArray[i] && !oldArray[i]->deleted) {
            add(oldArray[i]->value);
            delete oldArray[i];
        }
    }
}


unsigned int HashTable::getHash(string key) const {
    unsigned int index;
    int const a = 255;

    index = 0;

    for (size_t i = 0; i < key.length(); ++i) {
        index = (index + a * key[i]) % size;
    }

    return index;
}


