
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
    }

    // Сортировка и удаление дубликатов в каждом списке
    for (int i = 0; i < N; ++i) {
        sort(Gr[i].begin(), Gr[i].end());
        Gr[i].erase(unique(Gr[i].begin(), Gr[i].end()), Gr[i].end());
    }

    return Gr;
}

struct stack {
    int inf;
    stack* next;
};

void push(stack*& h, int x) {
    stack* r = new stack;  // создаём новый узел
    r->inf = x;            // записываем значение
    r->next = h;           // связываем с текущей вершиной
    h = r;                 // новая вершина — r
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
    cout << "Введите вершины A и B и направление ребра от 0 до" << adj.size() - 1 << "\n";
    int A, B, dir;
    cout << "A = ";
    cin >> A;
    cout << "B = ";
    cin >> B;
    cout << "Направление, 0 - от A к B, 1 - от B к A, 2 - двусторонний: ";
    cin >> dir;
    if (!dir) {
        adj[A].push_back(B);
        sort(adj[A].begin(), adj[A].end());
        adj[A].erase(unique(adj[A].begin(), adj[A].end()), adj[A].end());
    }
    else if (dir == 1) {
        adj[B].push_back(A);
        sort(adj[B].begin(), adj[B].end());
        adj[B].erase(unique(adj[B].begin(), adj[B].end()), adj[B].end());
    }
    else if (dir == 2) {
        adj[A].push_back(B);
        sort(adj[A].begin(), adj[A].end());
        adj[A].erase(unique(adj[A].begin(), adj[A].end()), adj[A].end());
        adj[B].push_back(A);
        sort(adj[B].begin(), adj[B].end());
        adj[B].erase(unique(adj[B].begin(), adj[B].end()), adj[B].end());
    }
    cout << "Новый список смежности:\n";
    for (int i = 0; i < N; ++i) {
        cout << i << ": ";
        for (int v : adj[i]) {
            cout << v << " ";
        }
        cout << "\n";
    }
}