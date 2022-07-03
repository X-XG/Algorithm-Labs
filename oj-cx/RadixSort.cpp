#include<iostream>
using namespace std;

#define MAX_NUM 185

int main() {
    int n, a[MAX_NUM], b[MAX_NUM];
    cin >> n;
    int i, j;
    for (i = 1;i <= n;i++)cin >> a[i];

    int max = 0;
    for (i = 1;i <= n;i++) {
        if (max < a[i])max = a[i];
    }

    int m = n, r = 0;
    while (m > 0) {
        m >>= 1;
        r++;
    }

    int d = 0, k = 1 << r;
    while (max > 0) {
        max >>= r;
        d++;
    }

    int c[2*MAX_NUM];
    int tmp[MAX_NUM];
    for (i = 0;i < d;i++) {
        for (j = 1;j <= n;j++)
            tmp[j] = (a[j] >> i * r) % k;
        for (j = 0;j < k;j++)
            c[j] = 0;
        for (j = 1;j <= n;j++)
            c[tmp[j]] += 1;
        for (j = 1;j < k;j++)
            c[j] += c[j - 1];
        for (j = n;j >= 1;j--) {
            b[c[tmp[j]]] = a[j];
            c[tmp[j]] -= 1;
        }
        for (j = 1;j <= n;j++)
            a[j] = b[j];
    }

    for (i = 1;i <= n;i++)cout << a[i] << ' ';
}