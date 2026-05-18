#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

vector<vector<int>> buildAdList(int N, const vector<pair<int, int>>& edges) {
    vector<vector<int>> Gr(N);  // список смежности
    for (const auto& edge : edges) {
        int x = edge.first;
        int y = edge.second;
        // Проверка корректности вершин (предполагается нумерация с 0)
        if (x < 0 || x >= N || y < 0 || y >= N) {
            continue;  // пропускаем некорректное ребро
        }
        Gr[x].push_back(y);
        Gr[y].push_back(x);
    }

    // Сортировка и удаление дубликатов в каждом списке
    for (int i = 0; i < N; ++i) {
        sort(Gr[i].begin(), Gr[i].end());
        Gr[i].erase(unique(Gr[i].begin(), Gr[i].end()), Gr[i].end());
    }

    return Gr;
}

int main()
{
    setlocale(LC_ALL, "RU");
    int N, M;
    cout << "Введите количество вершин и рёбер: ";
    cin >> N >> M;

    vector<pair<int, int>> edges(M);
    cout << "Введите пары вершин (нумерация с 0):\n";
    for (int i = 0; i < M; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }

    vector<vector<int>> adj = buildAdList(N, edges);
    cout << "Список смежности:\n";
    for (int i = 0; i < N; ++i) {
        cout << i << ": ";
        for (int v : adj[i]) {
            cout << v << " ";
        }
        cout << "\n";
    }
    for (int i = 0; i < adj.size(); i++) {
        cout << i << ": " << adj[i].size() << endl;
    }
}