#include <iostream>
#include <string>
using namespace std;

struct stack {
    string inf;
    stack* next;
};

// Добавление элемента в стек (в начало списка)
void push(stack*& h, string x) {
    stack* r = new stack;  // создаём новый узел
    r->inf = x;            // записываем значение
    r->next = h;           // связываем с текущей вершиной
    h = r;                 // новая вершина — r
}

// Извлечение элемента из стека (с удалением)
string pop(stack*& h) {
    string i = h->inf;        // сохраняем значение из вершины
    stack* r = h;          // запоминаем удаляемый узел
    h = h->next;           // сдвигаем вершину на следующий
    delete r;              // освобождаем память
    return i;              // возвращаем значение
}

int prior(string x) {
    if (x == "(") {
        return 1;
    }
    else if (x == "*" || x == "+") {
        return 2;
    }
    else {
        return 3;
    }
}

bool oper(string x) {
    string sravn = "+-+/()";
}

int main()
{
    string s, res = "";
    cout << "Введите математическое выражение: ";
    cin >> s;
    stack* h = NULL;
    while (s.length()) {
        string simb = s.substr(0, 1);
        if (simb == "(") {
            push(h, simb);
        }
        else if (!h) {

        }
    }
}
