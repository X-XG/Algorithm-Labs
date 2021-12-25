#include <string>
#include <vector>
#include <chrono>

using namespace std::chrono;

class RabinKarp {
private:
    std::string P, T;
    int n, m;
    int d, q;
public:
    RabinKarp();
    void init(std::string P, std::string T, int d, int n);
    ~RabinKarp();
    int hit;
    int fake_hit;
    std::vector<int> shift;
    void run();

    int time;
};

RabinKarp::RabinKarp() {
}

void RabinKarp::init(std::string P, std::string T, int d, int q) {
    this->P = P;
    this->T = T;
    this->d = d;
    this->q = q;
    m = P.length();
    n = T.length();
    hit = 0;
    fake_hit = 0;
}

RabinKarp::~RabinKarp() {
}

void RabinKarp::run() {
    auto start = system_clock::now();
    int h = 1;
    for (int i = 0;i < m - 1;i++)
        h = (h * d) % q;
    int p = 0;
    int t = 0;
    for (int i = 1;i <= m;i++) {
        p = (d * p + P[i - 1]) % q;
        t = (d * t + T[i - 1]) % q;
    }
    for (int s = 0;s <= n - m;s++) {
        if (p == t) {
            if (P == T.substr(s, m)) {
                shift.push_back(s);
                hit++;
            }
            else {
                fake_hit++;
            }
        }
        if (s < n - m) {
            t = (d * (t - T[s + 1 - 1] * h) + T[s + m + 1 - 1]) % q;
            if (t < 0)t += q;
        }
    }

    auto end = system_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    time = int(duration.count()) * nanoseconds::period::num;
}
