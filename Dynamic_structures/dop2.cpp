#include <iostream>
#include <string>
#include <vector>
using namespace std;

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
    vector<vector<int>> graph = { { 1, 2 },
    { 0, 3, 4 },
    { 0, 5 },
    { 1 },
    { 1 },
    { 2 } };
    cout << "Вывод элементов графа в порядке обхода в ширину" << endl;
    obhod_v_shirinu(graph);
    cout << "Вывод элементов графа в порядке обхода в глубину" << endl;
    obhod_v_glubinu(graph);
}