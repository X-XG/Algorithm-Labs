#include <iostream>
#include <cstring>
using namespace std;

#define MAX_NUM 25

int ind[MAX_NUM] = { 0 };
int ind_next[MAX_NUM] = { 0 };
int less_num[MAX_NUM] = { 0 };
int less_num_next[MAX_NUM] = { 0 };
int great_num[MAX_NUM] = { 0 };
int great_num_next[MAX_NUM] = { 0 };
int great_right[MAX_NUM] = { 0 };

void merge(int* a, int p, int q, int r) {
    int L[MAX_NUM], R[MAX_NUM];
    int n1 = q - p + 1;
    int n2 = r - q;
    for (int i = 1;i <= n1;i++) {
        L[i] = ind[p + i - 1];
    }
    for (int i = 1;i <= n2;i++) {
        R[i] = ind[q + i];
    }
    // L[n1 + 1] = INT32_MAX;
    // R[n2 + 1] = INT32_MAX;
    int i = 1;
    int j = 1;

    for (int k = p;k <= r;k++) {
        if (j == (n2 + 1) || (i <= n1 && a[L[i]] <= a[R[j]])) {
            ind[k] = L[i];
            // ind[L[i]] = k;
            great_num[ind[k]] += j - 1;
            i++;
        }
        else {
            ind[k] = R[j];
            // ind[R[j]] = k;
            less_num[ind[k]] += i - 1;
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
    int b[MAX_NUM];
    cin >> n;
    for (int i = 1;i <= n;i++) {
        cin >> a[i];
        b[n - i + 1] = a[i];
    }

    int count = 0;

    for (int i = 1;i <= n;i++) {
        ind[i] = i;
    }
    merge_sort(a, 1, n);
    int less[MAX_NUM] = { 0 };
    int greater[MAX_NUM] = { 0 };
    for (int i = 1;i <= n;i++) {
        // less[i] = (ind[i] < i ? ind[i] : i) - 1;
        less[i] = less_num[i];
    }

    for (int i = 1;i <= n;i++) {
        ind[i] = i;
    }
    memset(less_num, 0, sizeof(less_num));
    merge_sort(b, 1, n);
    for (int i = 1;i <= n;i++) {
        // greater[i] = (ind[i] < i ? ind[i] : i) - 1;
        greater[i] = less_num[n + 1 - i];
    }

    for (int i = 1;i <= n;i++) {
        count += (less[i] * greater[i]);
    }

    cout << count << endl;

    return 0;
}