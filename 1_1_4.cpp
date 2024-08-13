/*//==============================================================================================================
Инвертируйте значение бита в числе N по его номеру K.

Необходимо использование битовых операций.
Использование арифметических операций запрещено.
 *///==============================================================================================================
#include <iostream>
using namespace std;

int invert_bit_value_by_its_number(unsigned int N, unsigned int K) {
    return N ^ (1 << K); // инвертируем значение бита по его номеру
}

int main() {
    unsigned int N, K;
    cin >> N >> K;
    cout << invert_bit_value_by_its_number(N, K);
    return 0;
}
