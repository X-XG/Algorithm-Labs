#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#define MAX_NUM 700005

typedef struct node {
    string name;
    int score;
}node;
node stu[MAX_NUM];
list<int> hash_map[MAX_NUM];
int heap_size = 0;

int hash_func(string name) {
    unsigned int hash = 0;
    for (auto c : name) {
        hash = (hash << 5) + c;
    }
    return hash % MAX_NUM;
}

int hash_value(string name) {
    int key = hash_func(name);
    for (auto it = hash_map[key].begin(); it != hash_map[key].end();it++) {
        if (stu[*it].name == name) {
            return *it;
        }
    }
    return 0;
}

void hash_modify(string name, int value) {
    int key = hash_func(name);
    for (auto it = hash_map[key].begin(); it != hash_map[key].end();it++) {
        if (stu[*it].name == name) {
            *it = value;
            break;
        }
    }
    return;
}

void hash_insert(string name, int value) {
    int key = hash_func(name);
    hash_map[key].push_back(value);
    return;
}

void hash_delet(string name) {
    int key = hash_func(name);
    for (auto it = hash_map[key].begin(); it != hash_map[key].end();it++) {
        if (stu[*it].name == name) {
            hash_map[key].erase(it);
            break;
        }
    }
}

void max_heapify(int i) {
    int l = 2 * i;
    int r = 2 * i + 1;
    int largest;
    if (l <= heap_size && stu[l].score > stu[i].score) {
        largest = l;
    }
    else {
        largest = i;
    }
    if (largest != i) {
        hash_modify(stu[i].name, largest);
        hash_modify(stu[largest].name, i);
        node tmp = stu[i];
        stu[i] = stu[largest];
        stu[largest] = tmp;
        max_heapify(largest);
    }
}
void max_heapify_up(int i) {
    if (i == 1) return;
    int p = i / 2;
    if (stu[i].score > stu[p].score) {
        hash_modify(stu[i].name, p);
        hash_modify(stu[p].name, i);
        node tmp = stu[i];
        stu[i] = stu[p];
        stu[p] = tmp;
        max_heapify_up(p);
    }
    return;
}

void insert(string name, int score) {
    heap_size++;
    stu[heap_size].name = name;
    stu[heap_size].score = score;
    hash_insert(name, heap_size);
    int i = heap_size;
    while (i > 1 && stu[i / 2].score < stu[i].score) {
        hash_modify(stu[i].name, i / 2);
        hash_modify(stu[i / 2].name, i);
        node tmp = stu[i];
        stu[i] = stu[i / 2];
        stu[i / 2] = tmp;
        i = i / 2;
    }
    return;
}
void delet(string name) {
    int i = hash_value(name);
    hash_modify(stu[heap_size].name, i);
    hash_delet(name);
    stu[i] = stu[heap_size];
    heap_size--;
    if (heap_size == 0) return;
    max_heapify_up(i);
    max_heapify(i);
    return;
}
void search_score(string name) {
    int i = hash_value(name);
    int score = stu[i].score;
    cout << score << endl;
    return;
}
vector<string> highest;
void get_same_score(int score, int i) {
    if (i > heap_size) return;
    if (stu[i].score == score) {
        highest.push_back(stu[i].name);
        get_same_score(score, 2 * i);
        get_same_score(score, 2 * i + 1);
    }
    return;
}
void highest_score() {
    highest.clear();
    int best = stu[1].score;
    get_same_score(best, 1);
    sort(highest.begin(), highest.end());
    for (auto name : highest) {
        cout << name << endl;
    }
    return;
}

int main() {
    int m;
    char c;
    int score;
    string name;
    cin >> m;
    for (int i = 0;i < m;i++) {

        cin >> c;
        if (c == 'F') {
            highest_score();
            continue;
        }
        else if (c == 'S') {
            cin >> name;
            search_score(name);
        }
        else if (c == 'D') {
            cin >> name;
            delet(name);
        }
        else if (c == 'I') {
            cin >> name;
            cin >> score;
            insert(name, score);
        }
    }
}