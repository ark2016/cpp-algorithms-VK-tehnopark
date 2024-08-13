/*//==============================================================================================================
Решение должно поддерживать передачу функции сравнения снаружи.
Дано число N и N строк. Каждая строка содержит команду добавления или удаления натуральных чисел, а также запрос
 на получение k-ой порядковой статистики. Команда добавления числа A задается положительным числом A, команда удаления
 числа A задается отрицательным числом “-A”. Запрос на получение k-ой порядковой статистики задается числом k.
Требования: скорость выполнения запроса - O(log n).
*/ //==============================================================================================================
#include <iostream>
#include <cmath>
#include <functional>

using namespace std;

struct node {
    int key;  // значение
    int height; // высота
    int num; // количество элементов
    node *left;
    node *right;

    explicit node(int k);
};

int getHeight(node *root);

int rightLeftDifference(node *root);

void reHeight(node *root);

node *rotateRight(node *root);

node *rotateLeft(node *root);

node *NewBalance(node *root);

node *insertAVL(node *root, int k, const function<bool(int, int)> &compare);

node *findMinAVL(node *root);

node *removeMinAVL(node *root);

node *removeAVL(node *root, int k, const function<bool(int, int)> &compare);

int getNumAVL(const node *root);

int getKTH(const node *root, int find, const function<bool(int, int)> &greater, const function<bool(int, int)> &eq,
           const function<bool(int, int)> &less);

void deleteAVL(node *root);

void printKTH(int N, node *root, const function<bool(int, int)> &greater, const function<bool(int, int)> &eq,
              const function<bool(int, int)> &less);

int main() {
    int N;
    cin >> N;

    struct node *root = nullptr;
    function<bool(int, int)> greater = [](int a, int b) { // лямбда функция сравнения значений
        return a > b;
    };
    function<bool(int, int)> eq = [](int a, int b) { // лямбда функция сравнения значений
        return a == b;
    };
    function<bool(int, int)> less = [](int a, int b) { // лямбда функция сравнения значений
        return a < b;
    };

    printKTH(N, root, greater, eq, less);

    return 0;
}

node::node(int k) {
    key = k;
    left = nullptr;
    right = nullptr;
    num = 1;
    height = 1;
}

void printKTH(int N, node *root, const function<bool(int, int)> &greater, const function<bool(int, int)> &eq,
              const function<bool(int, int)> &less) {
    int x;

    for (int i = 0; i < N; ++i) {
        cin >> x;

        if (greater(x, 0)) {//x > 0
            root = insertAVL(root, x, greater);
        } else {
            root = removeAVL(root, abs(x), greater);
        }

        cin >> x;
        cout << getKTH(root, x + 1, greater, eq, less) << " ";
    }

    deleteAVL(root);
}

int getHeight(node *root) {
    return root ? root->height : 0;
}

int rightLeftDifference(node *root) {
    return getHeight(root->right) - getHeight(root->left);
}

void reHeight(node *root) {
    int left = getHeight(root->left);
    int right = getHeight(root->right);

    root->height = ((left > right) ? left : right) + 1;
    root->num = getNumAVL(root);
}

node *rotateRight(node *root) {
    node *in = root->left;

    root->left = in->right;
    in->right = root;
    reHeight(root);
    reHeight(in);

    return in;
}

node *rotateLeft(node *root) {
    node *in = root->right;

    root->right = in->left;
    in->left = root;
    reHeight(root);
    reHeight(in);

    return in;
}

node *NewBalance(node *root) {
    reHeight(root);
    if (2 == rightLeftDifference(root)) {
        if (0 > rightLeftDifference(root->right)) {
            root->right = rotateRight(root->right);
        }
        return rotateLeft(root);
    }
    if (-2 == rightLeftDifference(root)) {
        if (0 < rightLeftDifference(root->left)) {
            root->left = rotateLeft(root->left);
        }
        return rotateRight(root);
    }

    return root;
}

node *insertAVL(node *root, int k, const function<bool(int, int)> &compare) {
    if (nullptr == root) {
        return new node(k);
    }

    if (compare(root->key, k)) {//root->key > k
        root->left = insertAVL(root->left, k, compare);
    } else {
        root->right = insertAVL(root->right, k, compare);
    }

    return NewBalance(root);
}

node *findMinAVL(node *root) {
    return root->left ? findMinAVL(root->left) : root;
}

node *removeMinAVL(node *root) {
    if (nullptr == root->left) {
        return root->right;
    }

    root->left = removeMinAVL(root->left);

    return NewBalance(root);
}

node *removeAVL(node *root, int k, const function<bool(int, int)> &compare) {
    if (nullptr == root) {
        return nullptr;
    }

    if (compare(root->key, k)) {//root->key > k
        root->left = removeAVL(root->left, k, compare);
    } else if (compare(k, root->key)) {//k > root->key
        root->right = removeAVL(root->right, k, compare);
    } else {
        if (!root->left && !root->right) {
            delete root;
            root = nullptr;
            return nullptr;
        }

        if (!root->right) {
            node *left = root->left;
            delete root;
            root = nullptr;
            return left;
        }

        if (!root->left) {
            node *right = root->right;
            delete root;
            root = nullptr;
            return right;
        }

        node *left = root->left;
        node *right = root->right;
        delete root;
        root = nullptr;

        node *min = findMinAVL(right);
        min->right = removeMinAVL(right);
        min->left = left;
        return NewBalance(min);
    }

    return NewBalance(root);
}

int getNumAVL(const node *root) {
    int hLeft, hRight;

    if (nullptr == root) {
        return 0;
    }

    hLeft = 0;
    hRight = 0;

    if (root->left) {
        hLeft = getNumAVL(root->left);
    }
    if (root->right) {
        hRight = getNumAVL(root->right);
    }

    return hLeft + hRight + 1;
}

int getKTH(const node *root, int find, const function<bool(int, int)> &greater, const function<bool(int, int)> &eq,
           const function<bool(int, int)> &less) {
    int num;

    if (!root->right) {
        num = root->num;
    } else {
        num = root->num - root->right->num;
    }
    if (eq(num, find)) { // num == find
        return root->key;
    }
    if (greater(num, find)) {//num > find
        return getKTH(root->left, find, greater, eq, less);
    }
    if (less(num, find)) {//num < find
        find -= num;
        return getKTH(root->right, find, greater, eq, less);
    }

    return -1;
}

void deleteAVL(node *root) {
    if (root != nullptr) {
        return;
    }

    deleteAVL(root->left);
    deleteAVL(root->right);
    delete root;
    root = nullptr;
}
