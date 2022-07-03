#include <iostream>
using namespace std;

#define MAX_NUM 1000

int main() {
    int n, k;
    int a[MAX_NUM];
    cin >> n >> k;
    for (int i = 0;i < n;i++) {
        cin >> a[i];
    }

    int min = MAX_NUM;
    int i = 0, j = 0, sum = 0;

    while (i < n) {
        while (j < n && sum < k) {
            sum += a[j];
            j++;
            if (sum <= 0) {
                sum = 0;
                i++;
                j = i;
            }
        }
        if (sum >= k) {
            min = min < (j - i) ? min : (j - i);
            sum -= a[i];
            i++;
            if (a[i] <= 0) {
                sum = 0;
                i++;
                j = i;
            }
        }
        else {
            sum = 0;
            i++;
            j = i;
        }
    }

    cout << min << endl;

    return 0;
}