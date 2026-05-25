#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>   // в начале файла

using namespace std;

int key = 41, c1 = 3, c2 = 1, m = 12;
double a = 0.618;

int hash_func_help(int z) {
    return (int)(fmod((double)abs(z) * a, 1) * m);
}

void print_elem(vector<string> x) {
    for (auto elem : x) {
        cout << elem << " ";
    }
}
// Вставка элемента список
void push(vector<string>*& hash, vector<string> x) { //элемент массива требуем подходящий под ключ и вектор сотрудника
    int help = hash_func_help(stoi(x[4]));
    if (!hash[help].size()) {
        hash[help] = x;
        return;
    }
    else {
        int h;
        for (int i = 1; i < key; i++) {
            h = (help + c1 * i + c2 * i * i) % key;
            if (!hash[h].size()) {
                hash[h] = x;
                return;
            }
        }
    }
    cout << "Для элемента ";
    print_elem(x);
    cout << "нет подходящего места в хэш-таблице";
}

void print(vector<string>*& hash) {
    for (int i = 0; i < key; ++i) {
        cout << i << ": ";
        print_elem(hash[i]);
        cout << "\n";
    }
}

vector<vector<string>> find_all(vector<string>*& hash, int z) { //элемент массива требуем подходящий под ключ и вектор сотрудника
    int help = hash_func_help(z);
    int h;
    vector<bool> visited(key, false);
    vector<vector<string>> vec;
    for (int i = 0; i < key; i++){
        h = (help + c1 * i + c2 * i * i) % key;
        if (visited[h]) continue;
        visited[h] = true;
        if (!hash[h].size()) {
            return vec;
        }
        if (stoi(hash[h][4]) == z) {
            vec.push_back(hash[h]);
        }
    }
    return vec;
}

void vvod_elem(vector<string>*& hash, string x) {
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
    push(hash, vec);
}

void vvod(vector<string>*& hash) { //вводит данные в хэш-таблицу и возвращает размер строк
    int n = 0;
    string line, slovo;
    ifstream in("f.txt");
    if (in.is_open())
    {
        while (getline(in, line))
        {
            vector<string> vec;
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ';') {
                    vec.push_back(slovo);
                    slovo = "";
                }
                else {
                    slovo += line[i];
                }
            }
            vec.push_back(slovo);
            push(hash, vec);
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
    vector<string>* hash = new vector<string>[key]();
    vvod(hash);
    print(hash);
    cout << "Введите элемент для вставки" << endl;
    string x;
    getline(cin, x);
    vvod_elem(hash,x);
    print(hash);
    cout << "Введите зарплату для поиска сотрудников с ней" << endl;
    int z;
    cin >> z;
    vector<vector<string>> finded = find_all(hash, z);
    for (auto elem : finded) {
        print_elem(elem);
        cout << endl;
    }
    delete[] hash;
    return 0;
}