#include <string>
#include <vector>

#define MAX_LEN_P 150

class KMP {
private:
    std::string P, T;
    void prefix();
public:
    KMP(std::string P, std::string T);
    ~KMP();
    int n, m;
    int pi[MAX_LEN_P];
    int hit;
    std::vector<int> shift;
    void run();
};

KMP::KMP(std::string P, std::string T) {
    this->P = P;
    this->T = T;
    m = P.length();
    n = T.length();
    hit = 0;
}

KMP::~KMP() {
}

void KMP::prefix() {
    pi[1] = 0;
    int k = 0;
    for (int q = 2;q <= m;q++) {
        while (k > 0 && P[k + 1 - 1] != P[q - 1])
            k = pi[k];
        if (P[k + 1 - 1] == P[q - 1])
            k++;
        pi[q] = k;
    }
}

void KMP::run() {
    prefix();
    int q = 0;
    for (int i = 1;i <= n;i++) {
        while (q > 0 && P[q + 1 - 1] != T[i - 1])
            q = pi[q];
        if (P[q + 1 - 1] == T[i - 1])
            q++;
        if (q == m) {
            shift.push_back(i - m);
            q = pi[q];
            hit++;
        }
    }
}