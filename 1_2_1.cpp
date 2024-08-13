/*//==============================================================================================================
Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для каждого элемента массива B[i]
 найдите минимальный индекс k минимального элемента массива A, равного или превосходящего B[i]: A[k] >= B[i].
 Если такого элемента нет, выведите n. Время работы поиска k для каждого элемента B[i]: O(log(k)). n, m ≤ 10000.
 *///==============================================================================================================
#include <iostream>
using namespace std;

int binary_search(int A[], int key, int left, int right, int n){ // бинарный поиск
    int mid; //Определяем переменную для хранения индекса минимального элемента массива,
    // чтобы не переписывать ее в каждом цикле
    int result = n;

    while (left <= right) {
        mid = left + (right - left) / 2;

        if (A[mid] >= key) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return result;
}

int exponential_search(int A[], int n, int key, int m){// экспоненциальный поиск
    if (!n){
        return n;
    }
    int bound = 1;
    while (bound < n  && A[bound] <= key){
        bound <<= 1;
    }
    return binary_search(A, key, bound >> 1, min(bound, n), n);
}

void reverse(int *A, int n){
    int i, j, temp;
    for (i = 0, j = n - 1; i < j; i++, j--) {
        temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    int A[n], B[m];
    for (unsigned int i = 0; i < n; ++i) { // заполняем массив A
        cin >> A[i];
    }
    for (unsigned int i = 0; i < m; ++i) { // заполняем массив B
        cin >> B[i];
    }
    if ((n > 1) && (A[0] > A[n -1])){
        reverse(A, n); // переворачиваем массив A, если первый элемент меньше второго
    };
    for (unsigned int i = 0; i < m; ++i) { // проходим по массиву B
        cout << exponential_search(A, n, B[i], m) << " ";
    }
    return 0;
}
