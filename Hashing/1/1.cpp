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

// вставка элемента в начало
void push(list **& hash, int key, vector<string> vec) {
    list* r = new list;
    r->inf = vec;
    r->next = NULL;
    r->prev = NULL;
    int m = stoi(vec[4]) % key;
    if (!hash[m]) {
        hash[m] = r;
    }
    else {
        r->next = hash[m];
        hash[m]->prev = r;
        hash[m] = r;

    }
}

void print(list** hash, int key) {
    for (int i = 0; i < key; ++i) {
        cout << i << ": ";
        list* cur = hash[i];
        if (!cur) {
            cout << "\n";
            continue;
        }
        while (cur) {
            for (const string& s : cur->inf) {
                cout << s << " ";
            }
            cout << "\n" << "   ";
            cur = cur->next;
        }
        cout << "\n";
    }
}

void print_elem(list* x) {
    for (int i = 0; i < x->inf.size(); i++) {
        cout << x->inf[i] << " ";
    }
    cout << "\n";
}

//возвращает вектор элементов с нужной зарплатой
vector<list*> find_all(list** hash, int key, int z) {
    int m = z % key;
    list* cur = hash[m];
    vector<list*> finded;
    while (cur) {
        if (stoi(cur->inf[4]) == z) {
            finded.push_back(cur);
        }
        cur = cur->next;
    }
    return finded;
}

//удаляет элемент переданный
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
    return hash;
}

//вводит элемент из строки в хэш-таблицу
void vvod_elem(list**& hash, int key, string x) {
    vector<string> vec;
    string slovo = "";
    for (int i = 0; i < x.length(); i++) {
        if (x[i] == ';') {
            vec.push_back(slovo);
            slovo = "";
        }
        else {
            slovo += x[i];
        }
    }
    vec.push_back(slovo);
    int m = stoi(vec[4]) % key;
    push(hash,key, vec);
}

//вводит данные из файла f.txt в хэш-таблицу
void vvod(list**& hash, int key) { 
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
            int m = stoi(x[4]) % key;
            push(hash,key, x);
            slovo = "";
            n += 1;
        }
    }
    in.close();
    //return n;
}

int main() {

    // кодировка вывода (на экран
    /*
    setlocale(LC_ALL, "ru_RU.UTF-8");
    SetConsoleCP(CP_UTF8); // Установка кодировки для ввода
    SetConsoleOutputCP(CP_UTF8);// для функций C и C++
    */
    SetConsoleCP(1251);          // ввод с клавиатуры
    SetConsoleOutputCP(1251);    // вывод на экран
    setlocale(LC_ALL, "Russian"); // для C-функций
    int key = 17;
    list** hash = new list*[key]();
    //int n = vvod(hash, key);
    vvod(hash, key);
    print(hash, key);
    cout << "Введите элемент для вставки" << endl;
    string x;
    getline(cin, x);
    vvod_elem(hash, key, x);
    print(hash, key);
    cout << "Введите зарплату для поиска и удаления сотрудников с ней" << endl;
    int z;
    cin >> z;
    vector<list*> finded = find_all(hash, key, z);
    for (auto elem : finded) {
        print_elem(elem);
        hash = del(hash, key, elem);
    }
    cout << "Новая хэш-таблица" << endl;
    print(hash, key);
    return 0;
    
}