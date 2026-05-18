
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

vector<vector<int>> buildAdList(int N, const vector<pair<int, int>>& edges, bool directed) {
    vector<vector<int>> Gr(N);  // список смежности
    for (const auto& edge : edges) {
        int x = edge.first;
        int y = edge.second;
        // Проверка корректности вершин (предполагается нумерация с 0)
        if (x < 0 || x >= N || y < 0 || y >= N) {
            continue;  // пропускаем некорректное ребро
        }
        Gr[x].push_back(y);
        if (!directed) {
            Gr[y].push_back(x);
        }
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

struct queue {
    int inf;
    queue* next;
};

void push(queue*& h, queue*& t, int x) { //вставка элемента в очередь
    queue* r = new queue; //создаем новый элемент
    r->inf = x;
    r->next = NULL; //всегда последний
    if (!h && !t) { //если очередь пуста
        h = t = r; //это и голова и хвост
    }
    else {
        t->next = r; //r - следующий для хвоста
        t = r; //теперь r - хвост
    }
}

int pop(queue*& h, queue*& t) { //удаление элемента из очереди
    queue* r = h; //создаем указатель на голову
    int i = h->inf; //сохраняем значение головы
    h = h->next; //сдвигаем указатель на следующий элемент
    if (!h) //если удаляем последний элемент из очереди
        t = NULL;
    delete r; //удаляем первый элемент
    return i;
}

void obhod_v_shirinu(vector<vector<int>>& graph) {
    queue* h = NULL, * t = NULL;
    vector<bool> visited(graph.size(), false);
    push(h, t, 0);
    visited[0] = true;
    while (h) {
        int q = pop(h, t);
        cout << q << endl;
        for (vector<int>::iterator j = graph[q].begin(); j != graph[q].end(); j++) {
            if (!visited[*j]) {
                visited[*j] = true;
                push(h, t, *j);
            }
        }
    }

}

void obhod_v_glubinu(vector<vector<int>>& graph) {
    stack* h = NULL;
    vector<bool> visited(graph.size(), false);
    push(h, 0);
    visited[0] = true;
    while (h) {
        int q = pop(h);
        cout << q << endl;
        for (int i = ((int)graph[q].size()) - 1; i >= 0; --i) {
            if (!visited[graph[q][i]]) {
                visited[graph[q][i]] = true;
                push(h, graph[q][i]);
            }
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
    bool directed;
    cout << "Граф ориентированный? (1 - да, 0 - нет): ";
    cin >> directed;

    vector<vector<int>> adj = buildAdList(N, edges, directed);
    // Вывод списка смежности
    cout << "Список смежности:\n";
    for (int i = 0; i < N; ++i) {
        cout << i << ": ";
        for (int v : adj[i]) {
            cout << v << " ";
        }
        cout << "\n";
    }
}