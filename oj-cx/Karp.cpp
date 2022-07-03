#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

#define MAX_NUM 1505
#define P pair<int,int>

int dp[MAX_NUM][MAX_NUM] = { 0 };
vector<P>edge[MAX_NUM];

int main() {
    int n, m, q;
    int u, v, w;
    cin >> n >> m;

    for (int i = 0;i < m;i++) {
        cin >> u >> v >> w;
        edge[u].push_back(P(v, w));
    }

    for (int v = 1;v <= n;v++) {
        edge[0].push_back(P(v, 0));
    }

    for (int v = 0; v <= n;v++) {
        for (int k = 0;k <= n + 1;k++) {
            dp[k][v] = INT32_MAX / 2;
        }
    }
    dp[0][0] = 0;

    for (int k = 1;k <= n + 1;k++) {
        for (int u = 0;u <= n;u++) {
            for (auto e : edge[u]) {
                int v = e.first;
                int w = e.second;
                dp[k][v] = dp[k][v] < dp[k - 1][u] + w ? dp[k][v] : dp[k - 1][u] + w;
            }
        }
    }

    double min = 5000;
    for (int v = 1;v <= n;v++) {
        double max = -5000;
        for (int k = 0;k < n + 1;k++) {
            double tmp = (double)(dp[n + 1][v] - dp[k][v]) / (double)(n + 1 - k);
            max = max > tmp ? max : tmp;
        }
        min = min < max ? min : max;
    }

    printf("%.3f", min);

    return 0;
}