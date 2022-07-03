#include<stdio.h>
#include<cmath>
#include<complex>
#include<vector>
using namespace std;

// #define MAX_NUM 40005
#define COMPLEX complex<double>
#define VECTOR COMPLEX*

VECTOR FFT(VECTOR a, int n, int reverse) {
    if (n == 1)return a;
    COMPLEX wn = exp(COMPLEX(0, reverse * 2.0 * M_PI / n));
    COMPLEX w = 1;
    VECTOR a0 = (VECTOR)malloc(n * sizeof(COMPLEX));;
    VECTOR a1 = (VECTOR)malloc(n * sizeof(COMPLEX));;
    for (int i = 0;i < n;i++) {
        if (i % 2 == 0)
            a0[i / 2] = a[i];
        else
            a1[i / 2] = a[i];
    }
    VECTOR y0 = FFT(a0, n / 2, reverse);
    VECTOR y1 = FFT(a1, n / 2, reverse);
    VECTOR y = (VECTOR)malloc(n * sizeof(COMPLEX));

    for (int k = 0;k <= n / 2 - 1;k++) {
        y[k] = y0[k] + w * y1[k];
        y[k + n / 2] = y0[k] - w * y1[k];
        w *= wn;
    }
    free(a0);
    free(a1);
    return y;
}

int main() {
    int n;
    int nplus = 1;
    int tmp = n;

    scanf("%d", &n);
    tmp = n + 1;
    while (tmp > 0) {
        nplus++;
        tmp >>= 1;
    }
    nplus = 1 << nplus;

    VECTOR a = (VECTOR)malloc(nplus * sizeof(COMPLEX));
    VECTOR b = (VECTOR)malloc(nplus * sizeof(COMPLEX));

    for (int i = 0;i <= n;i++) {
        scanf("%d", &tmp);
        a[i] = COMPLEX(double(tmp), 0.0);
        // a.push_back(COMPLEX(double(tmp), 0.0));
    }
    for (int i = n + 1;i < nplus;i++) {
        a[i] = COMPLEX(0.0, 0.0);
        // a.push_back(COMPLEX(0.0, 0.0));
    }
    for (int i = 0;i <= n;i++) {
        scanf("%d", &tmp);
        b[i] = COMPLEX(double(tmp), 0.0);
        // b.push_back(COMPLEX(double(tmp), 0.0));
    }
    for (int i = n + 1;i < nplus;i++) {
        b[i] = COMPLEX(0.0, 0.0);
        // b.push_back(COMPLEX(0.0, 0.0));
    }

    VECTOR a1 = FFT(a, nplus, 1);
    VECTOR b1 = FFT(b, nplus, 1);
    VECTOR y = (VECTOR)malloc(nplus * sizeof(COMPLEX));

    for (int i = 0;i < nplus;i++) {
        y[i] = a1[i] * b1[i];
    }
    VECTOR res = FFT(y, nplus, -1);

    for (int i = 0; i <= 2 * n;i++) {
        printf("%d ", int(round(res[i].real() / nplus)));
    }
    return 0;
}
