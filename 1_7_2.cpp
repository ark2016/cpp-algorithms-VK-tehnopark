/*//==============================================================================================================
Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 106. Отсортировать массив методом
 поразрядной сортировки LSD по байтам.
*///==============================================================================================================
#pragma GCC optimize ("Ofast")

#include <iostream>
#include <cassert>

#define RADIX 8
#define BASE 256

using namespace std;

int getKey(size_t number, size_t radix) {
    return number >> (RADIX * radix) & (BASE - 1);
}

void countingSort(size_t *arr_of_numbers, size_t number_of_numbers, const size_t radix) {
    assert( arr_of_numbers != nullptr );
    assert( number_of_numbers > 0 );
    size_t count[BASE];

    for (size_t i = 0; i < BASE; ++i) {
        count[i] = 0;
    }

    for (size_t i = 0; i < number_of_numbers; ++i) {
        ++count[getKey(arr_of_numbers[i], radix)];
    }

    for (size_t i = 1; i < BASE; ++i) {
        count[i] += count[i - 1];
    }

    auto auxiliary_array = new size_t[number_of_numbers];
    int k;
    for (size_t j = number_of_numbers - 1;; --j) {
        k = getKey(arr_of_numbers[j], radix);
        auxiliary_array[--count[k]] = arr_of_numbers[j];
        if (0 == j)
            break;
    }

    for (size_t i = 0; i < number_of_numbers; ++i) {
        arr_of_numbers[i] = auxiliary_array[i];
    }

    delete[] auxiliary_array;
}

void LSDSort(size_t *data, size_t size) {
    for (size_t i = 0; i < RADIX; ++i) {
        countingSort(data, size, i);
    }
}

int main() {
    size_t n = 0;
    cin >> n;

    auto data = new size_t[n];

    for (size_t i = 0; i < n; ++i) {
        cin >> data[i];
    }

    LSDSort(data, n);

    for (size_t i = 0; i < n; ++i) {
        cout << data[i] << " ";
    }

    delete[] data;

    return 0;
}
