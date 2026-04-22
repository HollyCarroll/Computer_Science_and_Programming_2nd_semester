
#include <iostream>
#include <string>
#include <utility>
#include <clocale> 

using namespace std;

struct stack {
    pair<int, int> inf;
    stack* next;
};

// Добавление элемента в стек (в начало списка)
void push(stack*& h, pair<int, int> x) {
    stack* r = new stack;  // создаём новый узел
    r->inf = x;            // записываем значение
    r->next = h;           // связываем с текущей вершиной
    h = r;                 // новая вершина — r
}

// Извлечение элемента из стека (с удалением)
pair<int, int> pop(stack*& h) {
    pair<int, int> i = h->inf;        // сохраняем значение из вершины
    stack* r = h;          // запоминаем удаляемый узел
    h = h->next;           // сдвигаем вершину на следующий
    delete r;              // освобождаем память
    return i;              // возвращаем значение
}

// Обращение стека (переворачивание порядка элементов)
void reverse(stack*& h) {
    stack* head1 = nullptr; // вспомогательный (буферный) стек
    while (h) {             // пока исходный стек не пуст
        push(head1, pop(h)); // перекладываем элементы
    }
    h = head1;              // результат в исходном указателе
}

struct history {
    pair<int, int> inf;
    history* prev;
};

struct queue {
    pair<int, int> inf;
    queue* next;
    history* his;
};

history* newhis(history* past, pair<int, int> x) { //возвращает указатель на новый элемент
    history* r = new history;
    r->prev = past;
    r->inf = x;
    return r;
};

void push(queue*& h, queue*& t, pair<int, int> x, history* pos) { //вставка элемента в очередь
    queue* r = new queue; //создаем новый элемент
    r->inf = x;
    r->next = NULL; //всегда последний
    r->his = pos;
    if (!h && !t) { //если очередь пуста
        h = t = r; //это и голова и хвост
    }
    else {
        t->next = r; //r - следующий для хвоста
        t = r; //теперь r - хвост
    }
}

pair<int, int> pop(queue*& h, queue*& t) { //удаление элемента из очереди
    queue* r = h; //создаем указатель на голову
    pair<int, int> i = h->inf; //сохраняем значение головы
    h = h->next; //сдвигаем указатель на следующий элемент
    if (!h) //если удаляем последний элемент из очереди
        t = NULL;
    delete r; //удаляем первый элемент
    return i;
}

int main()
{
    setlocale(LC_ALL, "RU");
    cout << "Введите две шахматные клетки по очереди подобным образом:D3" << endl;
    string start, finish;
    cin >> start >> finish;
    pair<int, int> st, fn;
    st.first = (int)start[0] - 64;
    st.second = start[1] - '0';
    fn.first = (int)finish[0] - 64;
    fn.second = finish[1] - '0';
    pair<int, int> hod[8] = { {1, 2 }, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2} };
    history first;
    first.inf = st;
    first.prev = NULL;
    queue* h = NULL, * t = NULL;
    push(h, t, st, &first);
    stack* hs = NULL;
    while (h) {
        history* oldhis = h->his;
        pair<int, int> pos = pop(h, t);
        if (pos == fn) {
            push(hs, pos);
            while (oldhis) {
                push(hs, oldhis->inf);
                oldhis = oldhis->prev;
            }
            while (hs) {
                pair<int, int> pechat = pop(hs);
                char bukv = (char)(pechat.first + 64);
                cout << bukv << pechat.second << " ";
            }
            break;
        }
        else {
            pair<int, int> newpos;
            for (int i = 0; i < 8; i++) {
                newpos.first = pos.first + hod[i].first;
                newpos.second = pos.second + hod[i].second;
                if (0 < newpos.first && newpos.first < 9 && 0 < newpos.second && newpos.second < 9) {
                    history* newposhis = newhis(oldhis, newpos);
                    push(h, t, newpos, newposhis);
                }
            }
        }
    }
    return 0;
}