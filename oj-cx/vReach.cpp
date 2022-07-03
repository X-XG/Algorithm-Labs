#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 16005
#define MAX_SCC 1005

typedef struct Node {
    int scc;
    bool visited = false;
    vector<Node*> out;
    vector<Node*> in;
}Node;

Node* graph[MAX_N];
vector<Node*> r_graph;

bool vis_scc[MAX_SCC] = { false };
bool edge_scc[MAX_SCC][MAX_SCC] = { false };
bool reach[MAX_SCC][MAX_SCC] = { false };

void dfs1(Node* u) {
    u->visited = true;
    for (auto v : u->out) {
        if (!v->visited) {
            dfs1(v);
        }
    }
    r_graph.push_back(u);
}

void dfs2(Node* u, int scc) {
    u->visited = true;
    u->scc = scc;
    for (auto v : u->in) {
        if (!v->visited) {
            dfs2(v, scc);
        }
    }
}

void dfs3(int source, int scc, int count) {
    vis_scc[scc] = true;
    reach[source][scc] = true;
    for (int i = 0;i < count;i++) {
        if (edge_scc[scc][i] && !vis_scc[i]) {
            dfs3(source, i, count);
        }
    }
}

int main() {
    int n, m, q;
    int u, v;
    cin >> n >> m;

    for (int i = 1;i <= n;i++) {
        graph[i] = new Node;
    }

    for (int i = 0;i < m;i++) {
        cin >> u >> v;
        graph[u]->out.push_back(graph[v]);
        graph[v]->in.push_back(graph[u]);
    }

    for (int i = 1;i <= n;i++) {
        if (!graph[i]->visited) {
            dfs1(graph[i]);
        }
    }
    for (int i = 1;i <= n;i++) {
        graph[i]->visited = false;
    }
    int scc = 0;
    for (auto it = r_graph.rbegin();it != r_graph.rend();it++) {
        if (!(*it)->visited) {
            dfs2((*it), scc);
            scc++;
        }
    }

    for (int i = 1;i <= n;i++) {
        for (auto v : graph[i]->out) {
            edge_scc[graph[i]->scc][v->scc] = true;
        }
    }
    for (int i = 0;i < scc;i++) {
        for (int j = 0;j < scc;j++) {
            vis_scc[j] = false;
        }
        dfs3(i, i, scc);
    }

    cin >> q;
    for (int i = 0;i < q;i++) {
        cin >> u >> v;
        if (graph[u]->scc == graph[v]->scc | reach[graph[u]->scc][graph[v]->scc])
            cout << '1' << endl;
        else
            cout << '0' << endl;
    }
    return 0;
}