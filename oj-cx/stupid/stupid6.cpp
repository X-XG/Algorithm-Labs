#include <iostream>
#include <cstring>
using namespace std;

#define MAX_NUM 100000

int ind[MAX_NUM] = { 0 };
int sum = 0;

int greater_left[MAX_NUM] = { 0 };
int greater_right[MAX_NUM] = { 0 };
int less_right[MAX_NUM] = { 0 };
int less_left[MAX_NUM] = { 0 };

void merge(int* a, int p, int q, int r) {
    int L[MAX_NUM], R[MAX_NUM];
    int n1 = q - p + 1;
    int n2 = r - q;
    int i, j;
    for (int i = 1;i <= n1;i++) {
        L[i] = ind[p + i - 1];
    }
    for (int i = 1;i <= n2;i++) {
        R[i] = ind[q + i];
    }

    i = 1;
    j = 1;
    for (int k = p;k <= r;k++) {
        if (j == (n2 + 1) || (i <= n1 && a[L[i]] <= a[R[j]])) {
            sum += (j - 1) * less_right[L[i]];
            i++;
        }
        else {
            sum += (i - 1) * greater_right[R[j]];
            sum -= (i - 1) * less_left[R[j]];
            j++;
        }
    }

    i = 1;
    j = 1;
    for (int k = p;k <= r;k++) {
        if (j == (n2 + 1) || (i <= n1 && a[L[i]] <= a[R[j]])) {
            ind[k] = L[i];
            greater_right[ind[k]] += j - 1;
            less_right[ind[k]] += n2 - j + 1;
            i++;
        }
        else {
            ind[k] = R[j];
            greater_left[ind[k]] += i - 1;
            less_left[ind[k]] += n1 - i + 1;
            j++;
        }
    }
    return;
}

void merge_sort(int* a, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        merge_sort(a, p, q);
        merge_sort(a, q + 1, r);
        merge(a, p, q, r);
    }
    return;
}

int main() {
    int n;
    int a[MAX_NUM];
    cin >> n;
    for (int i = 1;i <= n;i++) {
        cin >> a[i];
    }
    for (int i = 1;i <= n;i++) {
        ind[i] = i;
    }

    merge_sort(a, 1, n);

    cout << sum << endl;

    return 0;
}