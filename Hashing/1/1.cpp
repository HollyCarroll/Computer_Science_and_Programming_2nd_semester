#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>   // в начале файла

using namespace std;

// Структура узла двусвязного списка
struct list {
    vector<string> inf;
    list* next;
    list* prev;
};

// 1. Вставка элемента в конец списка
void push(list*& a, vector<string> x) {
    list* r = new list;
    r->inf = x;
    r->next = NULL;
    r->prev = NULL;
    if (!a) {
        a = r;
    }
    else {
        list* cur = a;
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = r;
        r -> prev = cur;
        
    }
}

void print(list** hash, int key) {
    for (int i = 0; i < key; ++i) {
        cout << i << ": ";
        list* cur = hash[i];
        if (!cur) {
            continue;
        }
        while (cur) {
            for (const string& s : cur->inf) {
                cout << s << " ";
            }
            cout << "\n" << "   ";
            cur = cur->next;
        }
        cout << endl;
    }
}

void print_elem(list* x) {
    for (int i = 0; i < x->inf.size(); i++) {
        cout << x->inf[i] << " ";
    }
    cout << "\n";
}

list* find(list** hash, int key, vector<string> x) {
    int m = stoi(x[4]) % key;
    list* cur = hash[m];
    while (cur) {
        if (cur->inf == x) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

list** del(list** hash, int key, list * x) {
    if (x) {
        int m = stoi(x->inf[4]) % key;
        if (x == hash[m]) {
            if (x->next) {
                x->next->prev = NULL;
                hash[m] = x->next;
            }
            else {
                hash[m] = NULL;
            }
        }
        else if (x->next) {
            x->next->prev = x->prev;
            x->prev->next = x->next;
        }
        else {
            x->prev->next = NULL;
        }
        delete x;
        return hash;
    }
}

void vvod_elem(list**& hash,int key, vector<string> x) {
    int m = stoi(x[4]) % key;
    push(hash[m], x);
}

void vvod(list**& hash, int key) { //вводит данные в хэш-таблицу и возвращает размер строк
    int n = 0;
    string line, slovo;
    ifstream in("f.txt");
    if (in.is_open())
    {
        while (getline(in, line))
        {
            vector<string> x;
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ';') {
                    x.push_back(slovo);
                    slovo = "";
                }
                else {
                    slovo += line[i];
                }
            }
            x.push_back(slovo);
            vvod_elem(hash, key, x);
            slovo = "";
            n += 1;
        }
    }
    in.close();
    //return n;
}




int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int key = 11;
    list** hash = new list*[key]();
    //int n = vvod(hash, key);
    vvod(hash, key);
    print(hash, key);
    setlocale(LC_ALL, "rus");
    cout << "Введите элемент для поиска и удаления" << endl;
    vector<string> x;
    for (int i = 0; i < 5; i++) {
        string str;
        cin >> str;
        x.push_back(str);
    }
    vvod_elem(hash, key, x);
    print(hash, key);
    del(hash, key, find(hash, key, x));
    print(hash, key);
    return 0;
}