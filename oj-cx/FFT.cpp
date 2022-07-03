#include<stdio.h>
#include<cmath>
#include<complex>
#include<vector>
using namespace std;

#define MAX_NUM 40005
#define COMPLEX complex<double>
#define VECTOR vector<COMPLEX>

VECTOR FFT(VECTOR a, int reverse) {
    int n = a.size();
    if (n == 1)return a;
    COMPLEX wn = exp(COMPLEX(0, reverse * 2.0 * M_PI / n));
    COMPLEX w = 1;
    VECTOR a0, a1;
    int i = 0;
    for (auto item : a) {
        if (i % 2 == 0)a0.push_back(item);
        else a1.push_back(item);
        i++;
    }
    VECTOR y0 = FFT(a0, reverse);
    VECTOR y1 = FFT(a1, reverse);
    VECTOR y(n);
    for (int k = 0;k <= n / 2 - 1;k++) {
        y[k] = y0[k] + w * y1[k];
        y[k + n / 2] = y0[k] - w * y1[k];
        w *= wn;
    }
    return y;
}

int main() {
    int n;
    int nplus = 1;
    int tmp = n;

    scanf("%d", &n);
    tmp = n;
    while (tmp > 0) {
        nplus++;
        tmp >>= 1;
    }
    nplus = 1 << nplus;

    VECTOR a(nplus);
    VECTOR b(nplus);

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

    VECTOR a1 = FFT(a, 1);
    VECTOR b1 = FFT(b, 1);
    VECTOR y(nplus);

    for (int i = 0;i < nplus;i++) {
        y[i] = a1[i] * b1[i];
    }
    VECTOR res = FFT(y, -1);

    for (int i = 0; i <= 2 * n;i++) {
        printf("%d ", int(round(res[i].real() / nplus)));
    }
    return 0;
}
