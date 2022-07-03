#include <queue>
#include <stack>
#include <vector>
#include <cstring>
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

bool find_path = true;
int s, t;
bool visited[MAX_NUM] = { false };
int step2[MAX_NUM];
int step[MAX_NUM];

bool cmp(pair<edge*, int>a, pair<edge*, int>b) {
    return a.second > b.second;
}

void dfs(int u) {
    if (find_path)return;
    visited[u] = true;
    if (u == t) {
        memcpy(step,step2,sizeof(step));
        find_path = true;
        return;
    }
    
    vector<pair<edge*, int> >dump;
    for (auto e : out[u]) {
        int v = e->v;
        if (!visited[v] && e->flow < e->capacity) {
            dump.push_back(pair<edge*, int>(e, e->capacity - e->flow));
        }
    }
    for (auto e : in[u]) {
        int v = e->u;
        if (!visited[v] && e->flow > 0) {
            dump.push_back(pair<edge*, int>(e, e->flow));
        }
    }
    sort(dump.begin(), dump.end(), cmp);
    for (auto ei : dump) {
        auto e = ei.first;
        int v = e->u == u ? e->v : e->u;
        if (!visited[v]) {
            step2[v]=u;
            dfs(v);
        }
    }
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

    cin >> s >> t;

    while (find_path) {
        find_path = false;
        memset(visited,false,sizeof(visited));
        dfs(s);

        if (find_path) {
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