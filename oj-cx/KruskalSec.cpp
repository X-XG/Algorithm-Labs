#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#define edge tuple<int, int, int>
#define MAX_N 5005
#define MAX_M 450005

using namespace std;

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


bool cmp(edge a, edge b) {
    return get<0>(a) < get<0>(b);
}

Node* node[MAX_N];
vector<edge> edgeG;
vector<edge> edgeT;

int Kruskal(int Du, int Dv, int n, bool first) {
    int cost = 0;
    int count = 0;

    for (int i = 1;i <= n;i++) {
        makeSet(node[i]);
    }

    for (auto e : edgeT) {
        int u = get<1>(e);
        int v = get<2>(e);
        if (!(Du == u && Dv == v)) {
            Union(node[u], node[v]);
        }
    }

    for (auto e : edgeG) {
        int u = get<1>(e);
        int v = get<2>(e);
        int w = get<0>(e);
        if (!(Du == u && Dv == v) && findSet(node[u]) != findSet(node[v])) {
            cost += w;
            count++;
            Union(node[u], node[v]);
            if (first)
                edgeT.push_back(e);
            else
                break;
        }
    }
    return cost;
}

int main() {
    int n, m;
    int u, v, w;
    cin >> n >> m;

    for (int i = 1;i <= n;i++) {
        node[i] = new Node;
    }

    for (int i = 0;i < m;i++) {
        cin >> u >> v >> w;
        edgeG.push_back(edge(w, u, v));
    }
    sort(edgeG.begin(), edgeG.end(), cmp);

    int min = Kruskal(0, 0, n, true);
    vector<edge>tmp;
    set_difference(edgeG.begin(), edgeG.end(), edgeT.begin(), edgeT.end(), inserter(tmp, tmp.begin()));
    edgeG = tmp;

    int second = INT32_MAX;
    for (auto e : edgeT) {
        int cost = min - get<0>(e) + Kruskal(get<1>(e), get<2>(e), n, false);
        if (second > cost)
            second = cost;
    }

    cout << min << endl << second << endl;

    return 0;
}