#include <iostream>
using namespace std;

#define MAX_NUM 1000

int main() {
    int n;
    int mat[MAX_NUM][MAX_NUM];
    int sub[MAX_NUM][MAX_NUM] = { 0 };
    cin >> n;
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            cin >> mat[i][j];
            if (mat[i][j]) {
                sub[i][j] = 1;
            }
        }
    }

    for (int i = 1;i < n;i++) {
        for (int j = 1;j < n;j++) {
            if (mat[i][j]) {
                int min = sub[i][j - 1] < sub[i - 1][j] ? sub[i][j - 1] : sub[i - 1][j];

                if (min == 0) {
                    continue;
                }

                if (sub[i][j - 1] == sub[i - 1][j] && mat[i - min][j - min] == 0) {
                    sub[i][j] = min;
                }
                else {
                    sub[i][j] = min + 1;
                }
            }
        }
    }

    int max = 0;
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            if (max < sub[i][j]) {
                max = sub[i][j];
            }
        }
    }

    cout << max << endl;

    return 0;
}