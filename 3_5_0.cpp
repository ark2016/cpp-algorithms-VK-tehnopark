/*//==============================================================================================================
Дан неориентированный связный граф. Требуется найти вес минимального остовного дерева в этом графе
С помощью алгоритма Прима.
Формат ввода
Первая строка содержит два натуральных числа n и m — количество вершин и ребер графа соответственно
 (1 ≤ n ≤ 20000, 0 ≤ m ≤ 100000).
Следующие m строк содержат описание ребер по одному на строке.
Ребро номер i описывается тремя натуральными числами bi, ei и wi — номера концов ребра и его вес соответственно
 (1 ≤ bi, ei ≤ n, 0 ≤ wi ≤ 100000).
Формат вывода
Выведите единственное целое число - вес минимального остовного дерева.
*/ //==============================================================================================================
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <limits>
#include <climits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<bool> visited(n + 1, false);
    vector<int> min_edge(n + 1, INT_MAX);

    min_edge[1] = 0;
    pq.emplace(0, 1);
    long long total_weight = 0;

    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;
        total_weight += w;

        for (auto &[v, weight] : graph[u]) {
            if (!visited[v] && weight < min_edge[v]) {
                min_edge[v] = weight;
                pq.emplace(weight, v);
            }
        }
    }

    cout << total_weight << endl;

    return 0;
}
