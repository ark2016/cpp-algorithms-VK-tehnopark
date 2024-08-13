/*//==============================================================================================================
Нужно проверить, является ли путь в неориентированном графе гамильтоновым.

Формат ввода
Первая строка содержит число N – количество вершин.
Вторая строка содержит число M - количество ребер.
Третья строка содержит число K - количество вершин в пути.
Далее идут M строк с ребрами (откуда, куда).
Далее идут K вершин, принадлежащих пути.

Формат вывода
1 - если путь гамильтонов
0 - если путь не гамильтонов
*/ //==============================================================================================================
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    int n, m, k, u, v, previousVertex,currentVertex;
    bool isPathValid;

    cin >> n >> m >> k;

    vector<unordered_set<int>> graph(n);
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        graph[u].insert(v);
        graph[v].insert(u);
    }

    unordered_set<int> visitedVertices;
    cin >> previousVertex;
    visitedVertices.insert(previousVertex);
    isPathValid = true;

    for (int i = 1; i < k; ++i) {
        cin >> currentVertex;
        if (graph[previousVertex].find(currentVertex) == graph[previousVertex].end()) {
            isPathValid = false;
        }
        previousVertex = currentVertex;
        visitedVertices.insert(currentVertex);
    }

    if (isPathValid && n == k && visitedVertices.size() == static_cast<size_t>(n)) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }

    return 0;
}