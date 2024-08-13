/*//==============================================================================================================
Посчитать кол-во компонент связности в неориентированном графе.

Формат ввода
Первая строка содержит число N – количество вершин.
Вторая строка содержит число M - количество ребер.
Каждая следующая строка содержит ребро (откуда, куда).

Формат вывода
Целое число - кол-во компонент связности в графе.
*/ //==============================================================================================================
#include <iostream>
#include <vector>
#include <queue>

#pragma  gcc optimize("Ofast")

using namespace std;

size_t numberOfConnectedComponents(const vector<vector<int>> &graph) {
    vector<bool> visited(graph.size(), false);
    size_t componentCount;
    int current;

    componentCount = 0;
    auto bfs = [&](int start) {
        queue<int> q;
        q.push(start);
        visited[start] = true;
        while (!q.empty()) {
            current = q.front();
            q.pop();
            for (int neighbor: graph[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    };

    for (size_t i = 0; i < graph.size(); ++i) {
        if (!visited[i]) {
            ++componentCount;
            bfs(static_cast<int>(i));
        }
    }

    return componentCount;
}

int main() {
    size_t n, m;
    int u, v;

    cin >> n >> m;
    vector<vector<int>> graph(n);
    for (size_t i = 0; i < m; ++i) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cout << numberOfConnectedComponents(graph) << endl;

    return 0;
}