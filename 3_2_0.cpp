/*//==============================================================================================================
Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами.
Найдите количество различных кратчайших путей между заданными вершинами.
Требования: сложность O(V+E).
Формат ввода.
v: кол-во вершин (макс. 50000),
n: кол-во ребер (макс. 200000),
n пар реберных вершин,
пара вершин u, w для запроса.
Формат вывода.
Количество кратчайших путей от u к w.
*/ //==============================================================================================================
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int countShortestPaths(int v,  vector<pair<int, int>> &edges, int u, int w);

int main() {
    int v, n;
    cin >> v >> n;
    vector<pair<int, int>> edges(n);
    for (int i = 0; i < n; ++i) {
        int vertex1, vertex2;
        cin >> vertex1 >> vertex2;
        edges[i] = {vertex1, vertex2};
    }
    int u, w;
    cin >> u >> w;

    cout << countShortestPaths(v, edges, u, w) << endl;

    return 0;
}

int countShortestPaths(int v, vector<pair<int, int>> &edges, int u, int w) {
    vector<vector<int>> adj(v + 1); // Список смежности для графа
    for (const auto &edge: edges) {
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
    }

    vector<int> distance(v + 1, -1);// Массив расстояний для хранения кратчайшего пути
    vector<int> paths(v + 1, 0); // Массив для хранения количества кратчайших путей к каждой вершине.

    // BFS, алгоритм имеет алгоритмическую сложность O(|V|+|E|)
    queue<int> q;
    q.push(u);
    distance[u] = 0;
    paths[u] = 1;

    // BFS для подсчёта кратчайших путей
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        for (int neighbor: adj[current]) {
            if (distance[neighbor] == -1) {  // не посещён
                distance[neighbor] = distance[current] + 1;
                paths[neighbor] = paths[current];
                q.push(neighbor);
            } else if (distance[neighbor] == distance[current] + 1) {  // наёден путь короче
                paths[neighbor] += paths[current];
            }
        }
    }

    return paths[w];
}
