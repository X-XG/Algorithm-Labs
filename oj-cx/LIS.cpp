#include <stdio.h>

int main() {
    int n;
    int a[1200005];
    int arr[1200005];
    int i, j;
    int len = 0;
    int left, right, mid;
    scanf("%d", &n);
    for (i = 0;i < n;i++) {
        scanf("%d", a + i);
    }

    for (i = 0;i < n;i++) {
        left = 0;
        right = len;
        while (left < right) {
            mid = (left + right) / 2;
            if (arr[mid] > a[i]) {
                right = mid;
            }
            else if (arr[mid] < a[i]) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        if (left == len) {
            len++;
        }
        arr[left] = a[i];
    }

    printf("%d", len);
    return 0;
}
