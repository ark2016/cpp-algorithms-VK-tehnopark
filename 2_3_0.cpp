/*//==============================================================================================================
Постройте B-дерево минимального порядка t и выведите его по слоям.
В качестве ключа используются числа, лежащие в диапазоне 0..2^32 -1

Требования:
B-дерево должно быть реализовано в виде шаблонного класса.
Решение должно поддерживать передачу функции сравнения снаружи.

Формат входных данных
Сначала вводится минимальный порядок дерева t.
Затем вводятся элементы дерева.

Формат выходных данных
Программа должна вывести B-дерево по слоям. Каждый слой на новой строке, элементы должны выводится в том порядке, в
котором они лежат в узлах.

*/ //==============================================================================================================
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template<typename T, typename Compare = less<T>>
class BTree {
public:
    explicit BTree(int minOrder, Compare comp = Compare());

    void insert(const T &key);

    vector<vector<T>> layerByLayer(); // Возвращает 2D-вектор, представляющий B-дерево в поуровневом порядке

private:
    struct Node {
        vector<T> keys; // Ключи
        vector<Node *> children; // дочерние node
        bool isLeaf; // есть конечный узел

        explicit Node(bool isLeaf);
    };

    void insertNonFull(Node *node, const T &key);

    void splitChild(Node *parent, int index, Node *child);

    Node *root;
    int minOrder;
    Compare compare;
};

int main() {
    int minOrder;
    cin >> minOrder;
    BTree<int> bTree(minOrder);

    int key;
    while (cin >> key) {
        bTree.insert(key);
    }

    vector<vector<int>> layers = bTree.layerByLayer();
    for (const auto &layer: layers) {
        for (int k: layer) {
            cout << k << " ";
        }
        cout << endl;
    }

    return 0;
}

template<typename T, typename Compare>
BTree<T, Compare>::BTree(int minOrder, Compare comp) : root(nullptr), minOrder(minOrder), compare(comp) {}

template<typename T, typename Compare>
BTree<T, Compare>::Node::Node(bool isLeaf) : isLeaf(isLeaf) {}

template<typename T, typename Compare>
void BTree<T, Compare>::insert(const T &key) {
    if (nullptr == root) {
        root = new Node(true);
        root->keys.push_back(key);
        return;
    }

    if (root->keys.size() == (minOrder << 1) - 1) {
        Node *newRoot = new Node(false);
        newRoot->children.push_back(root);
        root = newRoot;
        splitChild(newRoot, 0, newRoot->children[0]);
    }

    insertNonFull(root, key);
}

template<typename T, typename Compare>
void BTree<T, Compare>::insertNonFull(Node *node, const T &key) {
    int i = node->keys.size() - 1;

    if (node->isLeaf) {
        while (0 <= i && compare(key, node->keys[i])) {
            --i;
        }
        node->keys.insert(node->keys.begin() + i + 1, key);
    } else {
        while (0 <= i && compare(key, node->keys[i])) {
            --i;
        }
        ++i;

        if (node->children[i]->keys.size() == (minOrder << 1) - 1) {
            splitChild(node, i, node->children[i]);
            if (compare(node->keys[i], key)) {
                ++i;
            }
        }

        insertNonFull(node->children[i], key);
    }
}

template<typename T, typename Compare>
void BTree<T, Compare>::splitChild(Node *parent, int index, Node *child) {
    Node *newNode = new Node(child->isLeaf);
    newNode->keys.assign(child->keys.begin() + minOrder, child->keys.end());

    if (!child->isLeaf) {
        newNode->children.assign(child->children.begin() + minOrder, child->children.end());
    }

    parent->keys.insert(parent->keys.begin() + index, child->keys[minOrder - 1]);
    parent->children.insert(parent->children.begin() + index + 1, newNode);

    child->keys.erase(child->keys.begin() + minOrder - 1, child->keys.end());
    if (!child->isLeaf) {
        child->children.erase(child->children.begin() + minOrder, child->children.end());
    }
}

template<typename T, typename Compare>
vector<vector<T>> BTree<T, Compare>::layerByLayer() {
    vector<vector<T>> result;

    if (nullptr == root) {
        return result;
    }

    queue<Node *> queue; // очередь для обхода
    queue.push(root);

    while (!queue.empty()) {
        int size = queue.size();
        vector<T> currentLayer;
        for (int i = 0; i < size; ++i) {
            Node *node = queue.front();
            queue.pop();
            currentLayer.insert(currentLayer.end(), node->keys.begin(), node->keys.end());
            if (!node->isLeaf) {
                for (Node *child: node->children) {
                    queue.push(child);
                }
            }
        }
        result.push_back(currentLayer);
    }
    return result;
}

