/*//==============================================================================================================
Написать алгоритм для решения игры в “пятнашки”. Решением задачи является приведение к виду:
[ 1  2  3  4 ]
[ 5  6  7  8 ]
[ 9  10 11 12]
[ 13 14 15 0 ]
где 0 задает пустую ячейку.
Достаточно найти хотя бы какое-то решение. Число перемещений костяшек не обязано быть минимальным.
Формат входных данных
Начальная расстановка.
Формат выходных данных
Если решение существует, то в первой строке выходного файла выведите минимальное число перемещений костяшек, которое
 нужно сделать, чтобы достичь выигрышной конфигурации, а во второй строке выведите соответствующую последовательность
 ходов: L означает, что костяшка сдвинулась влево, R – вправо, U – вверх, D – вниз. Если таких последовательностей
 несколько, то выведите любую из них. Если же выигрышная конфигурация недостижима, то выведите в выходной файл одно
 число −1.
*/ //==============================================================================================================
#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cstdint>

using namespace std;

static const size_t LINE = 4;
static const size_t FIELD = LINE * LINE;
static const int COEFFICIENT = 3;
static const array<unsigned char, FIELD> START = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
};
static const array<unsigned char, FIELD> RESULT = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 0
};

class FieldState {
public:
    FieldState(const FieldState &st);

    explicit FieldState(const array<unsigned char, FIELD> &arr, int distance = 0);

    ~FieldState() = default;

    [[nodiscard]] vector<FieldState> getNextVertices() const;

    bool operator==(const FieldState &fieldState) const;

    bool operator!=(const FieldState &fieldState) const;

    bool operator<(const FieldState &fieldState) const;

    [[nodiscard]] bool hasSolution() const;

    void setDist(int distance);

    [[nodiscard]] int getDist() const;

    [[nodiscard]] int getMetric() const;

private:
    void up();

    void down();

    void left();

    void right();

    static int x(unsigned char value);

    static int y(unsigned char value);

    static int manhattanDistance(unsigned char val, int nowX, int nowY);

    array<unsigned char, FIELD> cell{};
    int pos;
    int dist;
};

void aStar(const FieldState &start);

int main() {
    array<unsigned char, FIELD> tag{};
    int num;

    for (int i = 0; i < FIELD; ++i) {
        cin >> num;
        tag[i] = num;
    }
    FieldState fieldState(tag);
    aStar(fieldState);

    return 0;
}

FieldState::FieldState(const FieldState &st) : cell(st.cell), pos(st.pos), dist(st.getDist()) {}

FieldState::FieldState(const array<unsigned char, FIELD> &arr, int distance) : dist(distance) {
    for (int i = 0; i < arr.size(); ++i) {
        if (0 == arr[i])
            pos = i;
        cell[i] = arr[i];
    }
}

vector<FieldState> FieldState::getNextVertices() const {
    FieldState empty(START);
    vector<FieldState> res;

    if (LINE > pos) {
        res.push_back(empty);
    } else {
        FieldState st(*this);
        st.up();
        res.push_back(st);
    }
    if (FIELD - LINE <= pos) {
        res.push_back(empty);
    } else {
        FieldState st(*this);
        st.down();
        res.push_back(st);
    }
    if (!(pos % LINE)) {
        res.push_back(empty);
    } else {
        FieldState st(*this);
        st.left();
        res.push_back(st);
    }
    if (!((pos + 1) % LINE)) {
        res.push_back(empty);
    } else {
        FieldState st(*this);
        st.right();
        res.push_back(st);
    }

    return res;
}

bool FieldState::operator==(const FieldState &fieldState) const {
    return cell == fieldState.cell;
}

bool FieldState::operator!=(const FieldState &fieldState) const {
    return !(cell == fieldState.cell);
}

bool FieldState::operator<(const FieldState &fieldState) const {
    return cell < fieldState.cell;
}

bool FieldState::hasSolution() const {
    int k, l;

    k = pos / LINE + 1;
    l = 0;

    for (int i = 0; i < cell.size(); ++i) {
        if (0 == cell[i]) {
            continue;
        }
        for (int j = 0; j < i; ++j) {
            if (0 != cell[j] && cell[j] > cell[i]) {
                l++;
            }
        }
    }

    return 0 == (l + k) % 2;
}

void FieldState::setDist(int distance) {
    dist = distance;
}

int FieldState::getDist() const {
    return dist;
}

int FieldState::getMetric() const {
    int metric;
    metric = 0;

    if (START == cell) {
        return LINE * LINE * FIELD + dist;
    }
    for (int i = 0; i < FIELD; ++i) {
        if (0 == cell[i]) {
            continue;
        }
        metric += (int) manhattanDistance(cell[i], i % LINE, i / LINE);
    }

    return COEFFICIENT * metric + dist;
}

void FieldState::up() {
    int newPos;

    newPos = pos - LINE;
    swap(cell[newPos], cell[pos]);
    pos = newPos;
}

void FieldState::down() {
    int newPos;

    newPos = pos + LINE;
    swap(cell[newPos], cell[pos]);
    pos = newPos;
}

void FieldState::left() {
    int newPos;

    newPos = pos - 1;
    swap(cell[newPos], cell[pos]);
    pos = newPos;
}

void FieldState::right() {
    int newPos;

    newPos = pos + 1;
    swap(cell[newPos], cell[pos]);
    pos = newPos;
}

int FieldState::x(unsigned char value) {
    return 0 == value ? LINE - 1 : ((int) value - 1) % LINE;
}

int FieldState::y(unsigned char value) {
    return 0 == value ? LINE - 1 : ((int) value - 1) / LINE;
}

int FieldState::manhattanDistance(unsigned char val, int nowX, int nowY) {
    int right_x, right_y;

    right_x = x(val);
    right_y = y(val);

    return abs(nowX - right_x) + abs(nowY - right_y);
}

void aStar(const FieldState &start) {
    if (!start.hasSolution()) {
        cout << -1 << endl;

        return;
    }

    int stepCount;
    string way;
    FieldState fieldState(START);
    FieldState result(RESULT);
    map<FieldState, FieldState> visited;

    visited.insert({start, fieldState});
    auto cmp = [](const FieldState &left, const FieldState &right) {
        return left.getMetric() < right.getMetric();
    };

    multiset<FieldState, decltype(cmp)> stateStorage(cmp);
    FieldState now(START);

    stateStorage.insert(start);

    while (!stateStorage.empty()) {
        now = *stateStorage.begin();
        stateStorage.erase(stateStorage.begin());
        if (now == result) {
            break;
        }
        vector<FieldState> nextVertices = now.getNextVertices();
        for (auto vertice: nextVertices) {
            vertice.setDist(now.getDist() + 1);
            if (visited.find(vertice) == visited.end()) {
                visited.insert({vertice, now});
                stateStorage.insert(vertice);
            }
        }
    }

    stepCount = 0;

    while (now != fieldState) {
        FieldState last = visited.find(now)->second;
        if (last == fieldState) {
            break;
        }
        vector<FieldState> nextVertices = last.getNextVertices();
        if (now == nextVertices[0]) {
            way += "D";
        } else if (now == nextVertices[1]) {
            way += "U";
        } else if (now == nextVertices[2]) {
            way += "R";
        } else if (now == nextVertices[3]) {
            way += "L";
        }
        now = visited.find(now)->second;
        stepCount++;
    }
    
    cout << stepCount << endl;
    reverse(way.begin(), way.end());
    cout << way << endl;
}
