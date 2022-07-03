#include <queue>
#include <unordered_set>
#include <iostream>
using namespace std;

#define MAX_NUM 1005
#define MAX_LEN 268435455

typedef std::pair<int, int> P;

int num;
int w[MAX_NUM][MAX_NUM];
int delta[MAX_NUM][MAX_NUM];
std::unordered_set<int> edge[MAX_NUM];

void bellman() {
    for (int i = 0;i <= num;i++) {
        for (int u = 0;u <= num;u++) {
            for (int v : edge[u]) {
                if (delta[0][v] > delta[0][u] + w[u][v]) {
                    delta[0][v] = delta[0][u] + w[u][v];
                }
            }
        }
    }

    for (int u = 0;u <= num;u++) {
        for (int v : edge[u]) {
            if (delta[0][v] > delta[0][u] + w[u][v]) {
                cout << "negative-weight cycle" << endl;
                exit(0);
            }
        }
    }

    for (int u = 1;u <= num;u++) {
        for (int v : edge[u]) {
            w[u][v] = w[u][v] + delta[0][u] - delta[0][v];
        }
    }
}


void dijkstra(int s) {
    std::priority_queue<P, std::vector<P>, std::greater<P> > Q;
    Q.push(P(0, s));
    while (!Q.empty()) {
        P node = Q.top();
        Q.pop();
        int u = node.second;
        if (delta[s][u] < node.first) {
            continue;
        }
        for (int v : edge[u]) {
            if (delta[s][v] > delta[s][u] + w[u][v]) {
                delta[s][v] = delta[s][u] + w[u][v];
                Q.push(P(delta[s][v], v));
            }
        }
    }
}

void run() {
    bellman();
    for (int u = 1;u <= num;u++) {
        dijkstra(u);
        for (int v = 1;v <= num;v++) {
            if (delta[u][v] != MAX_LEN)
                delta[u][v] = delta[u][v] - delta[0][u] + delta[0][v];
        }
    }
}

int main() {
    int m, q;
    int u, v;
    cin >> num >> m;

    for (int i = 0;i <= num;i++) {
        for (int j = 0;j <= num;j++) {
            delta[i][j] = MAX_LEN;
        }
        delta[i][i] = 0;
    }

    for (int i = 0;i < m;i++) {
        cin >> u >> v;
        cin >> w[u][v];
        edge[u].insert(v);
    }

    run();

    cin >> q;
    for (int i = 0;i < q;i++) {
        cin >> u >> v;
        cout << delta[u][v] << endl;
    }
    return 0;
}