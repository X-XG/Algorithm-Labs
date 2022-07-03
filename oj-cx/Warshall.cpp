#include <iostream>
using namespace std;

#define MAX_NUM 1005
#define MAX_LEN 268435455

int delta[MAX_NUM][MAX_NUM];
int next[MAX_NUM][MAX_NUM];

int main() {
    int num, m, q;
    int u, v;
    cin >> num >> m;

    for (int i = 1;i <= num;i++) {
        for (int j = 1;j <= num;j++) {
            delta[i][j] = MAX_LEN;
        }
    }

    for (int i = 0;i < m;i++) {
        cin >> u >> v;
        cin >> delta[u][v];
    }

    for (int k = 1;k <= num;k++) {
        for (int i = 1;i <= num;i++) {
            for (int j = 1;j <= num;j++) {
                if (delta[i][j] > delta[i][k] + delta[k][j]) {
                    delta[i][j] = delta[i][k] + delta[k][j];
                }
            }
        }
    }

    for (int i = 1;i <= num;i++) {
        if (delta[i][i] < 0) {
            cout << "negative-weight cycle" << endl;
            exit(0);
        }
    }

    cin >> q;
    for (int i = 0;i < q;i++) {
        cin >> u >> v;
        cout << delta[u][v] << endl;
    }
    return 0;
}