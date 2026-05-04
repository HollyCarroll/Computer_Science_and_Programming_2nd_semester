#include <iostream>
#include <string>
using namespace std;

struct stack {
    char inf;
    stack* next;
};

// Добавление элемента в стек (в начало списка)
void push(stack*& h, char x) {
    stack* r = new stack;  // создаём новый узел
    r->inf = x;            // записываем значение
    r->next = h;           // связываем с текущей вершиной
    h = r;                 // новая вершина — r
}

// Извлечение элемента из стека (с удалением)
char pop(stack*& h) {
    char i = h->inf;        // сохраняем значение из вершины
    stack* r = h;          // запоминаем удаляемый узел
    h = h->next;           // сдвигаем вершину на следующий
    delete r;              // освобождаем память
    return i;              // возвращаем значение
}

int prior(char x) {
    if (x == '(') {
        return 1;
    }
    else if (x == '-' || x == '+') {
        return 2;
    }
    else if (x == '*' || x == '/') {
        return 3;
    }
}

bool oper(char x) {
    string sravn = "+-*/()";
    for (char c : sravn) {
        if (x == c) {
            return false;
        }
    }
    return true;
}

int main() //a*(b+c*d)+e
{
    setlocale(LC_ALL, "Russian_Russia.65001");
    string s, res = "";
    cout << "Введите математическое выражение в корректной форме: ";
    getline(cin, s);
    stack* h = NULL;
    for (char c : s) {
        if (c == ' ') {
            continue;
        }
        if (oper(c)) {
            res += c;
        }
        else if ((c == '(' || !h) && (c != ')')) {
            push(h, c);
        }
        else if (c == ')') {
            while (h) {
                char verh = pop(h);
                if (verh == '(') {
                    break;
                }
                else {
                    res += verh;
                }
            }
        }
        else if (prior(c) > prior(h->inf)) {
            push(h, c);
        }
        else {
            while (h && prior(c) <= prior(h->inf)) {
                res += pop(h);
            }
            push(h, c);
        }
    }
    while (h) {
        res += pop(h);
    }
    cout << res;
}
