/*//==============================================================================================================
Требуется отыскать самый выгодный маршрут между городами.
Требования: время работы O((N+M)logN), где N-количество городов, M-известных дорог между ними.
Формат входных данных.
Первая строка содержит число N – количество городов.
Вторая строка содержит число M - количество дорог.
Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).
Последняя строка содержит маршрут (откуда и куда нужно доехать).
Формат выходных данных.
Вывести длину самого выгодного маршрута.
*/ //==============================================================================================================
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

vector<int> dijkstra(int N, const vector<vector<pair<int, int>>> &adj, int start);

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<pair<int, int>>> vertexes(N);

    for (int i = 0; i < M; ++i) {
        int vertexFrom, vertexTo, time;
        cin >> vertexFrom >> vertexTo >> time;
        vertexes[vertexFrom].emplace_back(vertexTo, time);
        vertexes[vertexTo].emplace_back(vertexFrom, time); // учитываем непрямой маршрут
    }

    int start, end;
    cin >> start >> end;

    vector<int> dist = dijkstra(N, vertexes, start);

    cout << dist[end] << endl;

    return 0;
}

vector<int> dijkstra(int N, const vector<vector<pair<int, int>>> &adj, int start) {
    vector<int> dist(N, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (currentDist > dist[u]) continue;

        for (const auto &neighbor: adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
            }
        }
    }
    return dist;
}
