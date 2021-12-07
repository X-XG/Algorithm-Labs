#include <iostream>
#include <fstream>
#include <chrono>

#define NUM_MAX 30

using namespace std;
using namespace  chrono;

typedef struct Node {
    int rank;
    Node* parent;
}Node;

void makeSet(Node* x) {
    x->parent = x;
    x->rank = 0;
}

void link(Node* x, Node* y) {
    if (x->rank > y->rank) {
        y->parent = x;
    }
    else {
        x->parent = y;
        if (x->rank == y->rank) {
            y->rank++;
        }
    }
}

Node* findSet(Node* x) {
    if (x != x->parent) {
        x->parent = findSet(x->parent);
    }
    return x->parent;
}

void Union(Node* x, Node* y) {
    link(findSet(x), findSet(y));
}

int main() {
    string input_path = "../input/2_2_input.txt";
    string result_path = "../output/result.txt";
    string time_path = "../output/time.txt";

    ifstream infile;
    ofstream fresult;
    ofstream ftime;
    infile.open(input_path);
    fresult.open(result_path);
    ftime.open(time_path);

    int M[NUM_MAX][NUM_MAX];
    Node* set[NUM_MAX] = { nullptr };
    for (int num = 10; num <= NUM_MAX; num += 5) {
        for (int i = 0;i < num;i++) {
            for (int j = 0;j < num;j++) {
                infile >> M[i][j];
            }
            set[i] = new Node;
        }

        int count = 0;
        int op_num = 0;
        auto start = system_clock::now();
        for (int i = 0;i < num;i++) {
            makeSet(set[i]);
            op_num++;
        }
        for (int i = 0;i < num;i++) {
            for (int j = i + 1;j < num;j++) {
                if (M[i][j] == 1) {
                    Union(set[i], set[j]);
                    op_num++;
                }
            }
        }
        for (int i = 0;i < num;i++) {
            op_num++;
            if (findSet(set[i]) == set[i]) {
                count++;
            }
        }
        auto end = system_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        int time = int(duration.count()) * nanoseconds::period::num;
        ftime << time << endl;
        fresult << "n=" << num << ' ' << count << endl;
        cout << "n=" << num << ' ' << op_num << endl;
    }

    return 0;
}