/*//==============================================================================================================
Напишите две функции для создания архива из одного файла и извлечения файла из архива.
Требования: коэффициент сжатия < 1.

// Метод архивирует данные из потока original
void Encode(IInputStream& original, IOutputStream& compressed);
// Метод восстанавливает оригинальные данные
void Decode(IInputStream& compressed, IOutputStream& original);

 где:

typedef unsigned char byte;
#define interface struct

interface IInputStream {
	// Возвращает false, если поток закончился
	virtual bool Read(byte& value) = 0;
};

interface IOutputStream {
	virtual void Write(byte value) = 0;
};
В архиве сохраняйте дерево Хаффмана и код Хаффмана от исходных данных.
Дерево Хаффмана требуется хранить эффективно - не более 10 бит на каждый 8-битный символ.
В контест необходимо отправить .cpp файл содержащий функции Encode, Decode, а также включающий файл Huffman.h.
 Тестирующая программа выводит размер сжатого файла в процентах от исходного.
*/ //==============================================================================================================
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <cmath>
#include "Huffman.h"

struct Node {
    char c{};
    int fr{};
    Node *l{};
    Node *r{};

    Node() = default;

    explicit Node(char c);

    Node(Node *left, Node *right) : c(0), l(left), r(right) {}

    Node(char c, int freq, Node *left = nullptr, Node *right = nullptr)
            : r(right), c(c), l(left), fr(freq) {
    }

    ~Node() {
        delete l;
        delete r;
    }
};

Node::Node(char c) : c(c), l(nullptr), r(nullptr) {}

struct nodeComp {
    bool operator()(const Node *left, const Node *right) const {
        return left->fr < right->fr;
    }
};


void table(Node *root, std::vector<bool> &bitVector, std::map<char, std::vector<bool> > &text);

void parseT(Node *root, IOutputStream &compressed);

Node *reverseParseT(IInputStream &compressed);

void Encode(IInputStream &original, IOutputStream &compressed) {
    std::map<char, int> frequent;
    std::string f;
    size_t sp = 0;
    byte val;

    while (original.Read(val)) {
        ++frequent[val];
        f += val;
    }

    std::list<Node *> list;

    for (auto &pair: frequent) {
        Node *node = new Node(pair.first, pair.second, nullptr, nullptr);
        list.push_back(node);
    }

    if (list.empty()) {
        return;
    }

    while (1 != list.size()) {
        list.sort(nodeComp());
        Node *left = list.front();
        list.pop_front();
        Node *right = list.front();
        list.pop_front();
        Node *parent = new Node(0, left->fr + right->fr, left, right);
        list.push_back(parent);
    }

    Node *root = list.front();
    std::vector<bool> bitVector;
    std::map<char, std::vector<bool> > text;
    table(root, bitVector, text);

    int c = 0;
    char buffer = 0;

    size_t fileSize = f.size();
    char cbyte;
    for (int i = 0; i < 8; ++i) {
        cbyte = (fileSize >> (i << 3));
        compressed.Write(cbyte);
    }

    int size;
    size = text.size();
    compressed.Write(size);
    compressed.Write(size >> 8);

    parseT(root, compressed);


    while (f.size() > sp) {
        val = f[sp];
        ++sp;
        std::vector<bool> x = text[val];
        for (auto &&bitReference: x) {
            buffer = buffer | (bitReference << (7 - c));
            ++c;
            if (8 == c) {
                c = 0;
                compressed.Write(buffer);
                buffer = 0;
            }
        }
    }

    compressed.Write(buffer);

    delete root;
}


void Decode(IInputStream &compressed, IOutputStream &original) {
    size_t size = 0;
    size_t pos = 0;
    for (int k = 0; k < 8; ++k) {
        byte ch;
        compressed.Read(ch);
        if (ch <= 0) {
            if (ch < 0) {
                size += pow(256, k) * (256 + ch);
            }
        } else {
            size += pow(256, k) * ch;
        }
    }

    Node *root = reverseParseT(compressed);
    Node *node = root;
    if (!root) {
        return;
    }

    std::vector<bool> bitVector;
    std::map<char, std::vector<bool> > text;
    table(root, bitVector, text);


    int c = 0;
    byte value;
    compressed.Read(value);

    while (pos < size) {
        bool b = value & (1 << (7 - c++));
        if (!b) {
            node = node->l;
        } else {
            node = node->r;
        }
        if (!node) {
            return;
        }
        if (!node->r && !node->l) {
            original.Write(node->c);
            ++pos;
            node = root;
        }
        if (8 == c) {
            c = 0;
            compressed.Read(value);
        }
    }

    delete root;
}


void table(Node *root, std::vector<bool> &bitVector, std::map<char, std::vector<bool> > &text) {
    if (!root) {
        return;
    }

    if (!root->r && !root->l) {
        text[root->c] = bitVector;
    }

    if (root->l) {
        bitVector.push_back(0);
        table(root->l, bitVector, text);
    }

    if (root->r) {
        bitVector.push_back(1);
        table(root->r, bitVector, text);
    }
    bitVector.pop_back();
}

void parseT(Node *root, IOutputStream &compressed) {
    if (!root) {
        return;
    }
    parseT(root->l, compressed);
    parseT(root->r, compressed);
    if (root->l || root->r) {
        compressed.Write('0');
    } else {
        compressed.Write('1');
        compressed.Write(root->c);
    }
}


Node *reverseParseT(IInputStream &compressed) {
    byte bSize;
    int iSize;
    compressed.Read(bSize);
    iSize = (unsigned char) bSize;
    compressed.Read(bSize);
    iSize += (int) ((unsigned char) bSize) << 8;
    std::stack<Node *> st;
    int size = 0;
    byte b;

    while (!(size >= iSize && st.size() <= 1)) {
        compressed.Read(b);
        if ('1' == b) {
            compressed.Read(b);
            ++size;
            Node *newNode = new Node(b);
            st.push(newNode);
        } else if ('0' == b) {
            Node *node1 = st.top();
            st.pop();
            Node *node2 = st.top();
            st.pop();
            Node *newNode = new Node(node2, node1);
            st.push(newNode);
        }
    }
    Node *root = nullptr;
    if (!st.empty()) {
        root = st.top();
    }
    st.pop();
    return root;
}
