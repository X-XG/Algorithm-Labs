#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

#define MAX_K 2003
#define MAX_LEN 2500


struct big {
    char d[MAX_LEN];
    int len;
    big() {
        memset(d, 0, sizeof(d));
        len = 0;
    }
    big(int x) {
        while (x > 0) {
            d[len++] = x % 10;
            x /= 10;
        }
    }
    big operator+(const big b) {
        big c = *this;
        int carry = 0;
        for (int i = 0;i < this->len || i < b.len;i++) {
            int temp = this->d[i] + b.d[i] + carry;
            c.d[c.len++] = temp % 10;
            carry = temp / 10;
        }
        if (carry) {
            c.d[c.len++] = carry;
        }
        return c;
    }
    big operator-(const big b) {
        big c = *this;
        for (int i = 0;i < b.len;i++) {
            c.d[i] -= b.d[i];
        }
        for (int i = 0; i < c.len;i++) {
            if (c.d[i] < 0) {
                c.d[i] += 10;
                c.d[i + 1]--;
            }
        }
        for (;c.d[c.len - 1] == 0;c.len--);
        return c;
    }
    bool operator>=(const big b) {
        if (this->len > b.len)return true;
        else if (this->len < b.len)return false;
        else {
            for (int i = this->len - 1;i >= 0;i--) {
                if (this->d[i] > b.d[i])return true;
                else if (this->d[i] < b.d[i])return false;
            }
            return true;
        }
    }
    big operator*(const long long b) {
        big c = *this;
        long long carry = 0;
        for (int i = 0;i < c.len | carry;i++) {
            long long temp = c.d[i] * b + carry;
            c.d[c.len++] = temp % 10;
            carry = temp / 10;
        }
        return c;
    }
    big operator/(const int b) {
        big c = *this;
        int r = 0;
        for (int i = this->len - 1;i >= 0;i--) {
            r = r * 10 + this->d[i];
            c.d[i] = r / b;
            r %= b;
        }
        for (;c.d[c.len - 1] == 0;c.len--);
        return c;
    }
    int operator%(const int b) {
        int r = 0;
        for (int i = this->len - 1;i >= 0;i--) {
            r = r * 10 + this->d[i];
            r = r % b;
        }
        return r;
    }
    big operator%(const big b) {
        big c = *this;
        while (c >= b) {
            big t1 = b;
            big t2 = t1 * 10;
            while (c >= t2) {
                t1 = t2;
                t2 = t2 * 10;
            }
            while (c >= t1) {
                c = c - t1;
            }
        }
        return c;
    }

};



int main() {
    int k, r[MAX_K], p[MAX_K];
    int c[MAX_K], inv[MAX_K];
    big N, all(1), b[MAX_K];
    cin >> k;
    for (int i = 0;i < k;i++) {
        cin >> r[i] >> p[i];
        all = all * p[i];
    }
    for (int i = 0;i < k;i++) {
        b[i] = all / p[i];
        c[i] = b[i] % p[i];
    }

    for (int i = 0;i < k;i++) {
        int t = 0;
        for (int j = 1;j < p[i];j++) {
            t += c[i];
            t %= p[i];
            if (t == 1) {
                inv[i] = j;
                break;
            }
        }
    }

    for (int i = 0;i < k;i++) {
        N = N + b[i] * (r[i] * inv[i]);
    }

    N = N % all;

    for (int i = N.len - 1; i >= 0;i--) {
        cout << char((N.d[i] + '0'));
    }

    return 0;
}