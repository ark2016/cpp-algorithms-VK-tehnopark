/*//==============================================================================================================
Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием в виде шаблонной функции.
Решение должно поддерживать передачу функции сравнения снаружи.
Общее время работы алгоритма O(n log n).
На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого отрезка (Li и Ri).
 Найти длину окрашенной части числовой прямой.
*///==============================================================================================================
#pragma GCC optimize ("Ofast")

#include <iostream>

using namespace std;

struct Segment { // Segment of a line: left, right
    int left, right;
};

struct SegmentComparator { // сравнение левых концов
    bool operator()(const Segment &s1, const Segment &s2) {
        return s1.left < s2.left;
    }
};

template<typename T, typename Comparator>
void merge(T *arr, int left, int mid, int right, Comparator comp);

template<typename T, typename Comparator>
void mergeSort(T *arr, int left, int right, Comparator comp);

int getPaintedLen(int n, const Segment *segments);

int main() {
    int n;
    cin >> n;

    Segment *segments = new Segment[n];
    for (int i = 0; i < n; ++i) {
        cin >> segments[i].left >> segments[i].right;
    }

    mergeSort(segments, 0, n - 1, SegmentComparator());

    cout << getPaintedLen(n, segments) << endl;

    delete[] segments; // очищаем память

    return 0;
}

template<typename T, typename Comparator>
void merge(T *arr, int left, int mid, int right, Comparator comp) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    T *L = new T[n1];
    T *R = new T[n2];

    for (i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (comp(L[i], R[j])) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }

    delete[] L; // очищаем память
    delete[] R;// очищаем память
}

template<typename T, typename Comparator>
void mergeSort(T *arr, int left, int right, Comparator comp) {
    if (left < right) {
        int mid = left + ((right - left) >> 1);
        mergeSort(arr, left, mid, comp);
        mergeSort(arr, mid + 1, right, comp);
        merge(arr, left, mid, right, comp);
    }
}

int getPaintedLen(int n, const Segment *segments) {
    int totalLength = 0; // длина
    int nextRight = segments[0].right; // старый правый конец
    int currentLeft = segments[0].left; // старый левый конец

    for (int i = 0; i < n; ++i) {
        if (segments[i].left > nextRight) { // левый конец больше правого конца
            totalLength += nextRight - currentLeft;
            currentLeft = segments[i].left;
            nextRight = segments[i].right;

        } else if (segments[i].right > nextRight) { // правый конец больше старого правого конца
            nextRight = segments[i].right;
        }
    }

    totalLength += nextRight - currentLeft; // добавляем последний элемент
    return totalLength;
}
