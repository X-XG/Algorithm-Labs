#include<cstdlib>
#include<vector>
#include<string>

#define MAX_NUM 32

class LCS {
private:
    int len;
    char* x;
    char* y;
    int c[MAX_NUM][MAX_NUM] = { 0 };

public:
    LCS(int len, char* x, char* y);
    ~LCS();

    int result = 0;
    std::vector<std::string> lcss;
    void GetLCS();
    void PrintLCS(int i, int j, std::string str_lcs);
};

LCS::LCS(int len, char* x, char* y) {
    this->len = len;
    this->x = new char[len];
    this->y = new char[len];
    for (int i = 0; i < len; i++) {
        this->x[i] = x[i];
        this->y[i] = y[i];
    }
}

LCS::~LCS() {
    delete[] x;
    delete[] y;
}

void LCS::GetLCS() {
    for (int i = 1;i <= len;i++) {
        for (int j = 1; j <= len; j++) {
            if (x[i - 1] == y[j - 1])c[i][j] = c[i - 1][j - 1] + 1;
            else c[i][j] = c[i - 1][j] >= c[i][j - 1] ? c[i - 1][j] : c[i][j - 1];
        }
    }
}

void LCS::PrintLCS(int i, int j, std::string str_lcs) {
    while (i > 0 && j > 0) {
        if (x[i - 1] == y[j - 1]) {
            str_lcs = x[i - 1] + str_lcs;
            i--;
            j--;
        }
        else if (c[i - 1][j] < c[i][j - 1]) j--;
        else if (c[i - 1][j] > c[i][j - 1]) i--;
        else {
            PrintLCS(i, j - 1, str_lcs);
            PrintLCS(i - 1, j, str_lcs);
            return;
        }
    }
    result++;
    lcss.push_back(str_lcs);
}
