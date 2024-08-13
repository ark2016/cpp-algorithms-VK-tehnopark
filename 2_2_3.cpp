/*//==============================================================================================================
Дано число N < 10^6 и последовательность целых чисел из [-2^31..2^31] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое
 поддерево root; иначе в левое поддерево root.
Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
Выведите элементы в порядке post-order (снизу вверх).
*/ //==============================================================================================================
#include <iostream>
#include <stack>
#include <functional>

using namespace std;

struct Node {
    int key; // значение
    Node* left; // левый ребенок
    Node* right; // правый ребенок

    explicit Node(int value);
    ~Node();
};

Node *insert(int N, Node *root);
void insertNode(Node*& root, int key, const function<bool(int, int)>& compare);
void postorderTraversal(Node* root);
void freeMemory(Node* root);

int main() {
    int N; // число элементов в дереве
    cin >> N;

    Node* root = nullptr;
    root = insert(N, root);

    postorderTraversal(root);
    freeMemory(root);

    return 0;
}

Node *insert(int N, Node *root) {
    function<bool(int, int)> compare = [](int a, int b) { // лямбда функция сравнения значений Node::key
        return a <= b;
    };
    int key;

    for (int i = 0; i < N; ++i) {
        cin >> key;
        insertNode(root, key, compare);
    }
    return root;
}

void insertNode(Node *&root, int key, const function<bool(int, int)>& compare) {
    Node* newNode = new Node(key);

    if (nullptr == root) {
        root = newNode;
        return;
    }

    Node* current = root;

    for (;;) {
        if (compare(current->key, key)) {
            if (nullptr == current->right) {
                current->right = newNode;
                break;
            }
            current = current->right;
        } else {
            if (nullptr == current->left) {
                current->left = newNode;
                break;
            }
            current = current->left;
        }
    }
}

void postorderTraversal(Node *root) {
    if (nullptr == root) {
        return;
    }

    stack<Node*> st; // Стек для хранения вершин
    Node* current = root;
    Node* lastVisited = nullptr; // для избежания повторений

    while (nullptr != current || !st.empty()) { // обход бинарного дерева снизу вверх (в порядке пост-последовательности)
        if (nullptr != current) {
            st.push(current);
            current = current->left;
        } else {
            Node* top = st.top();
            if (nullptr != top->right && lastVisited != top->right) {
                current = top->right;
            } else {
                cout << top->key << " ";
                lastVisited = top;
                st.pop();
            }
        }
    }
}

Node::Node(int value) : key(value), left(nullptr), right(nullptr) {}
Node::~Node() {
    delete left;
    delete right;
    left = nullptr; // для безопасности
    right = nullptr;

}

void freeMemory(Node* root) {
    stack<Node*> st;
    st.push(root);

    for(int i = 0;!st.empty() && i < st.size()-1;++i) {
        Node* current = st.top();
        st.pop();

        if (current->left) {
            st.push(current->left);
        }
        if (current->right) {
            st.push(current->right);
        }

        delete current;
    }
}
