
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

int pop(stack*& h) {
    int i = h->inf;        // сохраняем значение из вершины
    stack* r = h;          // запоминаем удаляемый узел
    h = h->next;           // сдвигаем вершину на следующий
    delete r;              // освобождаем память
    return i;              // возвращаем значение
}

void obhod_v_glubinu(vector<vector<int>>& graph, int x) {
    stack* h = NULL;
    vector<bool> visited(graph.size(), false);
    push(h, x);
    visited[x] = true;
    while (h) {
        int q = pop(h);
        for (int i = ((int)graph[q].size()) - 1; i >= 0; --i) {
            if (!visited[graph[q][i]]) {
                visited[graph[q][i]] = true;
                push(h, graph[q][i]);
            }
        }
    }
    for (int i = 0; i < visited.size(); i++) {
        if (!visited[i]) {
            cout << i << endl;
        }
    }
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
    // Вывод списка смежности
    cout << "Список смежности:\n";
    for (int i = 0; i < N; ++i) {
        cout << i << ": ";
        for (int v : adj[i]) {
            cout << v << " ";
        }
        cout << "\n";
    }

    cout << "Введите вершину: ";
    int x;
    cin >> x;
    obhod_v_glubinu(adj, x);


}