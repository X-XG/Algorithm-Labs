#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 1000005

typedef struct Node {
    int x1, x2, x3;
    bool operator<=(const Node& a)const {
        return (this->x1 < a.x1)
            || (this->x1 == a.x1 && this->x2 < a.x2)
            || (this->x1 == a.x1 && this->x2 == a.x2 && this->x3 <= a.x3);
    }
}Node;

struct Node A[MAX_NUM];

int Partition(int p, int r) {
    Node x = A[r];
    int i = p - 1;
    for (int j = p;j < r;j++) {
        if (A[j] <= x) {
            i++;
            Node tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
        }
    }
    Node tmp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = tmp;
    return i + 1;
}

int RandomPartition(int p, int r) {
    int i = p + (rand() % (r - p));
    Node tmp = A[i];
    A[i] = A[r];
    A[r] = tmp;
    return Partition(p, r);
}

void RandomQuickSort(int p, int r) {
    if (p < r) {
        int q = RandomPartition(p, r);
        RandomQuickSort(p, q - 1);
        RandomQuickSort(q + 1, r);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1;i <= n;i++) {
        scanf("%d %d %d", &(A[i].x1), &(A[i].x2), &(A[i].x3));
    }
    RandomQuickSort(1, n);
    for (int i = 1;i <= n;i++) {
        printf("%d %d %d\n", A[i].x1, A[i].x2, A[i].x3);
    }
    return 0;
}