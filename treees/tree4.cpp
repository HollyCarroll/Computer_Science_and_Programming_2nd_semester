#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct tree {
    int inf;
    tree* left;
    tree* right;
    tree* parent;
};

tree* node(int x) { // начальный узел
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = NULL;
    n->parent = NULL;
    return n;
}

void insert(tree*& tr, int x) { // вставка
    tree* n = node(x);
    if (!tr)
        tr = n; // если дерево пустое - корень
    else {
        tree* y = tr;
        while (y) { // ищем куда вставлять
            if (n->inf > y->inf) { // правая ветка
                if (y->right)
                    y = y->right;
                else {
                    n->parent = y; // узел становится правым ребенком
                    y->right = n;
                    break;
                }
            }
            else if (n->inf < y->inf) { // левая ветка
                if (y->left)
                    y = y->left;
                else {
                    n->parent = y; // узел становится левым ребенком
                    y->left = n;
                    break;
                }
            }
            else {                         // равны → не вставлять (или увеличить счётчик)
                delete n;                  // избегаем утечки памяти
                break;                     // выходим из цикла
            }
        }
    }
}

void inorder(tree* tr) { // симметричный обход
    if (tr) {
        inorder(tr->left);
        cout << tr->inf << " ";
        inorder(tr->right);
    }
}

tree* find(tree* tr, int x) { // поиск
    if (!tr || x == tr->inf) // нашли или дошли до конца ветки
        return tr;
    if (x < tr->inf)
        return find(tr->left, x); // ищем по левой ветке
    else
        return find(tr->right, x); // ищем по правой ветке
}

tree* Min(tree* tr) { // поиск min
    if (!tr->left)
        return tr; // нет левого ребенка
    else
        return Min(tr->left); // идем по левой ветке до конца
}

tree* Max(tree* tr) { // поиск max
    if (!tr->right)
        return tr; // нет правого ребенка
    else
        return Max(tr->right); // идем по правой ветке до конца
}

tree* Next(tree* tr, int x) { // поиск следующего
    tree* n = find(tr, x);
    if (n->right) // если есть правый ребенок
        return Min(n->right); // min по правой ветке
    tree* y = n->parent; // родитель
    while (y && n == y->right) { // пока не дошли до корня или узел - правый ребенок
        n = y; // идем вверх по дереву
        y = y->parent;
    }
    return y; // возвращаем родителя
}

tree* Prev(tree* tr, int x) { // поиск предыдущего
    tree* n = find(tr, x);
    if (n->left) // если есть левый ребенок
        return Max(n->left); // max по левой ветке
    tree* y = n->parent; // родитель
    while (y && n == y->left) { // пока не дошли до корня или узел - левый ребенок
        n = y; // идем вверх по дереву
        y = y->parent;
    }
    return y; // возвращаем родителя
}

void Delete(tree*& tr, tree* v) { //новое удаление
    if (!v) return;

    // Случай 1: нет детей
    if (!v->left && !v->right) {
        if (!v->parent) {          // корень-лист
            delete v;
            tr = NULL;
        }
        else {
            if (v->parent->left == v) v->parent->left = NULL;
            else v->parent->right = NULL;
            delete v;
        }
        return;
    }

    // Случай 2: только один ребёнок
    if (!v->left || !v->right) {
        tree* child = v->left ? v->left : v->right;
        if (!v->parent) {          // корень с одним ребёнком
            tr = child;
            child->parent = NULL;
        }
        else {
            if (v->parent->left == v) v->parent->left = child;
            else v->parent->right = child;
            child->parent = v->parent;
        }
        delete v;
        return;
    }

    // Случай 3: два ребёнка
    tree* succ = Next(tr, v->inf); // преемник
    v->inf = succ->inf;
    Delete(tr, succ);              // рекурсивно удаляем преемника
}

void leafs(tree* tr, vector<pair<int, tree*>>& vec) { // симметричный обход и копировние элементов в vec
    if (tr) {
        leafs(tr->left, vec);
        if (!(tr->left) && !(tr->right)) {
            pair<int, tree*> p;
            p.first = tr->inf;
            p.second = tr;
            vec.push_back(p);
        }
        leafs(tr->right, vec);
    }

}

int main() {
    setlocale(LC_ALL, "RU");
    int n, x;
    cout << "n=";
    cin >> n;
    tree* tr = NULL;
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        cin >> x;
        insert(tr, x);
    }
    cout << "Дерево бинарного поиска ";
    inorder(tr);
    cout << endl;
    vector<pair<int, tree*>> vec;
    leafs(tr, vec);
    sort(vec.begin(), vec.end());
    if (vec.empty()) {
        cout << "Нет листьев в дереве" << endl;
        return 0;
    }
    tree* medium = vec[((vec.size()-1)/2)].second;
    if (medium -> parent && medium->parent->parent) {
        Delete(tr, medium->parent->parent);
        cout << "Новое дерево бинарного поиска ";
        inorder(tr);
    }
    else cout << "У нужного листа нет 'деда'" << endl;
    return 0;
}