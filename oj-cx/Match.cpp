#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAX_NUM 105
#define P pair<int,int>

vector<P>edge[MAX_NUM];

bool visit[MAX_NUM] = { false };
int match[MAX_NUM] = { 0 };

struct cmp {
    bool operator()(const P& a, const P& b) {
        return a.second < b.second;
    }
};

bool dfs1(int u) {
    for (auto e : edge[u]) {
        int v = e.first;
        if (!visit[v]) {
            visit[v] = true;
            if (!match[v] || dfs1(match[v])) {
                match[v] = u;
                match[u] = v;
                return true;
            }
        }
    }
    return false;
}


int main() {
    int s, t, m;
    int u, v, c;
    cin >> s >> t >> m;
    for (int i = 0;i < m;i++) {
        cin >> u >> v >> c;
        edge[u].push_back(P(v, c));
        edge[v].push_back(P(u, c));
    }
    int num = s + t;

    for (int i = 0;i < m;i++) {
        sort(edge[i].begin(), edge[i].end(), cmp());
    }

    int sum = 0;
    for (int i = 1;i <= num;i++) {
        if (!match[i]) {
            memset(visit, false, sizeof(visit));
            if (dfs1(i))
                sum++;
        }
    }

    int cost = 0;
    for (int i = 1;i <= num;i++) {
        for (auto e : edge[i]) {
            int v = e.first;
            int c = e.second;
            if (match[v] == i) {
                cost += c;
            }
        }
    }
    cost /= 2;

    cout << sum << ' ' << cost << endl;
}