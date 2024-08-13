/*//==============================================================================================================
Рик и Морти снова бороздят просторы вселенных, но решили ограничиться только теми, номера которых меньше M. Они могут
 телепортироваться из вселенной с номером z во вселенную (z+1) mod M за a бутылок лимонада или во вселенную
 (z2+1) mod M за b бутылок лимонада. Рик и Морти хотят добраться из вселенной с номером x во вселенную с номером y.
 Сколько бутылок лимонада отдаст Рик за такое путешествие, если он хочет потратить их как можно меньше?

Формат ввода
В строке подряд даны количество бутылок a за первый тип телепортации, количество бутылок b за второй тип телепортации,
 количество вселенных M, номер стартовой вселенной x, номер конечной вселенной y
 (0 ≤ a, b ≤ 100, 1 ≤ M ≤ 106, 0 ≤ x, y < M).

Формат вывода
Выведите одно число — количество бутылок лимонада, которые отдаст Рик за такое путешествие.
*/ //==============================================================================================================
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

#pragma gcc optimize("Ofast")

using namespace std;

int main() {
    long long a, b, M, x, y, nextUniverse, nextNextUniverse;
    cin >> a >> b >> M >> x >> y;
    queue<pair<long long, long long>> q;
    q.push({x, 0});
    vector<long long> cost(M, LLONG_MAX);
    cost[x] = 0;

    while (!q.empty()) {
        auto [current, currentCost] = q.front();
        q.pop();
        nextUniverse = (current + 1) % M;
        if (currentCost + a < cost[nextUniverse]) {
            cost[nextUniverse] = currentCost + a;
            q.push({nextUniverse, cost[nextUniverse]});
        }
        nextNextUniverse = (current * current) % M;
        nextNextUniverse = (nextNextUniverse + 1) % M;
        if (currentCost + b < cost[nextNextUniverse]) {
            cost[nextNextUniverse] = currentCost + b;
            q.push({nextNextUniverse, cost[nextNextUniverse]});
        }
    }

    cout << cost[y] << endl;

    return 0;
}