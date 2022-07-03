#include <iostream>
using namespace std;
#define MAX_NUM 10
#define MAX_VALUE 100
int main() {
    int n, m;
    int a[MAX_NUM];
    int s[MAX_VALUE] = { 0 };
    cin >> n >> m;
    s[0] = 1;
    for (int i = 1;i <= n;i++) {
        cin >> a[i];
    }
    for (int i = 1;i <= n;i++) {
        for (int j = 0;j + a[i] <= m;j++) {
            s[j + a[i]] = (s[j + a[i]] + s[j]) % 1000000007;
        }
    }
    cout << s[m] << endl;
    return 0;
}