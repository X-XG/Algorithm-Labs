#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_NUM 605

struct edge {
    int u;
    int v;
    int capacity;
    int flow;
    edge(int u, int v, int capacity) : u(u), v(v), capacity(capacity), flow(0) {}
};

edge* e_mat[MAX_NUM][MAX_NUM] = { NULL };
vector<edge*> out[MAX_NUM];
vector<edge*> in[MAX_NUM];

bool cmp(pair<edge*, int>a, pair<edge*, int>b) {
    return a.second > b.second;
}

int main() {
    int n, m;
    int u, v, w;
    cin >> n >> m;

    for (int i = 0;i < m;i++) {
        cin >> u >> v >> w;
        edge* e = new edge(u, v, w);
        e_mat[u][v] = e;
        out[u].push_back(e);
        in[v].push_back(e);
    }

    int s, t;
    cin >> s >> t;

    bool find = true;

    while (find) {
        queue<int>Q;
        find = false;
        bool visited[MAX_NUM] = { false };
        int step[MAX_NUM];
        visited[s] = true;
        Q.push(s);

        while (!Q.empty()) {
            u = Q.front();
            Q.pop();
            if (u == t) {
                find = true;
                break;
            }
            for (auto e : out[u]) {
                v = e->v;
                if (!visited[v] && e->flow < e->capacity) {
                    visited[v] = true;
                    Q.push(v);
                    step[v] = u;
                }
            }
            for (auto e : in[u]) {
                v = e->u;
                if (!visited[v] && e->flow > 0) {
                    visited[v] = true;
                    Q.push(v);
                    step[v] = u;
                }
            }
        }

        if (find) {
            int min = INT32_MAX;
            for (v = t;v != s;v = step[v]) {
                u = step[v];
                int residual;
                if (e_mat[u][v] != NULL) {
                    residual = e_mat[u][v]->capacity - e_mat[u][v]->flow;
                }
                else {
                    residual = e_mat[v][u]->flow;
                }
                min = min < residual ? min : residual;
            }

            for (v = t;v != s;v = step[v]) {
                u = step[v];
                if (e_mat[u][v] != NULL) {
                    e_mat[u][v]->flow += min;
                }
                else {
                    e_mat[v][u]->flow -= min;
                }
            }
        }
    }

    int max = 0;
    for (auto e : out[s]) {
        max += e->flow;
    }
    for (auto e : in[s]) {
        max -= e->flow;
    }
    cout << max << endl;

    return 0;
}