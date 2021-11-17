#include<cstdlib>
#include<string>
#include<time.h>
#define MAX_NUM 32

class MatrixMul {
private:
    int num;
    long long* scale;
    int s[MAX_NUM][MAX_NUM];

public:
    MatrixMul(int num, long long* scale);
    ~MatrixMul();

    long long result;
    std::string parens;
    void ChainMul();
    void PrintParens(int i, int j);
};

MatrixMul::MatrixMul(int n, long long* p) {
    this->num = n;
    this->scale = new long long[n];
    for (int i = 0; i <= n; i++) {
        this->scale[i] = p[i];
    }
}

MatrixMul::~MatrixMul() {
    delete[] scale;
}

void MatrixMul::ChainMul() {
    int n = this->num;
    long long m[MAX_NUM][MAX_NUM] = { 0 };
    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = __INT64_MAX__;
            for (int k = i; k <= j - 1; k++) {
                long long q = m[i][k] + m[k + 1][j] + this->scale[i - 1] * this->scale[k] * this->scale[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    this->result = m[1][n];
}

void MatrixMul::PrintParens(int i, int j) {
    if (i == j) {
        parens = parens + 'A' + std::to_string(i);
    }
    else {
        parens += '(';
        PrintParens(i, s[i][j]);
        PrintParens(s[i][j] + 1, j);
        parens += ')';
    }
}

// void MatrixMul::GetResult() {
//     clock_t start = clock();
//     ChainMul();
//     clock_t end = clock();
//     time = double(start - end)/CLOCKS_PER_SEC;
// }