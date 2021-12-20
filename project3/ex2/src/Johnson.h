#include <fstream>
#include <string>
#include <stack>
#include <queue>

#define MAX_NUM 750
#define MAX_LEN 100000
#define MIN_LEN -10000
#define INPUT_BASE_PATH "../input/input"
#define OUTPUT_BASE_PATH "../output/result"

class Johnson {
private:
    int num;
    int w[MAX_NUM][MAX_NUM];
    std::string id;
    void bellman();
    void dijkstra(int s);
public:
    Johnson(int num, std::string id);
    ~Johnson();
    int delta[MAX_NUM][MAX_NUM];
    void run();
};

Johnson::Johnson(int num, std::string id) {
    std::ifstream ioread;
    this->num = num;
    this->id = id;
    for (int i = 0;i <= num;i++) {
        for (int j = 0;j <= num;j++) {
            delta[i][j] = MAX_LEN;
        }
        delta[i][i] = 0;
    }

    ioread.open(INPUT_BASE_PATH + id + ".txt");
    for (int i = 1;i <= num;i++) {
        for (int j = 1;j <= num;j++) {
            char c;
            ioread >> w[i][j] >> c;
            if (w[i][j] == 0) {
                w[i][j] = MIN_LEN;
            }
        }
    }
    ioread.close();
    for (int i = 0;i <= num;i++) {
        w[0][i] = 0;
        w[i][0] = 0;
    }
}

Johnson::~Johnson() {
}

void Johnson::bellman() {
    for (int i = 0;i <= num;i++) {
        for (int u = 0;u <= num;u++) {
            for (int v = 0;v <= num;v++) {
                if (u == 0 || w[u][v] != MIN_LEN) {
                    if (delta[0][v] > delta[0][u] + w[u][v]) {
                        delta[0][v] = delta[0][u] + w[u][v];
                    }
                }
            }
        }
    }
    for (int u = 1;u <= num;u++) {
        for (int v = 1;v <= num;v++) {
            if (w[u][v] != MIN_LEN) {
                w[u][v] = w[u][v] + delta[0][u] - delta[0][v];
            }
        }
    }

}

typedef std::pair<int, int> P;

void Johnson::dijkstra(int s) {
    std::priority_queue<P, std::vector<P>, std::greater<P> > Q;
    Q.push(P(0, s));
    while (!Q.empty()) {
        P node = Q.top();
        Q.pop();
        int u = node.second;
        if (delta[s][u] < node.first) {
            continue;
        }
        for (int v = 1;v <= num;v++) {
            if (w[u][v] != MIN_LEN && (delta[s][v] > delta[s][u] + w[u][v])) {
                delta[s][v] = delta[s][u] + w[u][v];
                Q.push(P(delta[s][v], v));
            }
        }
    }
}

void Johnson::run() {
    bellman();
    for (int u = 1;u <= num;u++) {
        dijkstra(u);
        for (int v = 1;v <= num;v++) {
            if (w[u][v] != MIN_LEN)
                delta[u][v] = delta[u][v] - delta[0][u] + delta[0][v];
        }
    }
}
