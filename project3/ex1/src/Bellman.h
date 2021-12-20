#include <fstream>
#include <string>
#include <stack>

#define MAX_NUM 750
#define MAX_LEN 100000
#define INPUT_BASE_PATH "../input/input"
#define OUTPUT_BASE_PATH "../output/result"

typedef struct Node {
    int d;
    int pi;
}Node;

class Bellman {
private:
    int num;
    int w[MAX_NUM][MAX_NUM];
    Node node[MAX_NUM];
    void relax(int u, int v);
    std::string id;
public:
    Bellman(int num, std::string id);
    ~Bellman();
    void run();
    void write();
};

Bellman::Bellman(int num, std::string id) {
    std::ifstream ioread;
    this->num = num;
    this->id = id;
    for (int i = 1;i < num;i++) {
        node[i].d = MAX_LEN;
        node[i].pi = -1;
    }
    node[0].d = 0;

    ioread.open(INPUT_BASE_PATH + id + ".txt");
    for (int i = 0;i < num;i++) {
        for (int j = 0;j < num;j++) {
            char c;
            ioread >> w[i][j] >> c;
        }
    }
    ioread.close();
}

Bellman::~Bellman() {
}

void Bellman::relax(int u, int v) {
    if (node[v].d > node[u].d + w[u][v]) {
        node[v].d = node[u].d + w[u][v];
        node[v].pi = u;
    }
}

void Bellman::run() {
    for (int i = 0;i < num;i++) {
        for (int u = 0;u < num;u++) {
            for (int v = 0;v < num;v++) {
                if (w[u][v] != 0) {
                    relax(u, v);
                }
            }
        }
    }
}

void Bellman::write() {
    std::ofstream iowrite;
    iowrite.open(OUTPUT_BASE_PATH + id + ".txt");
    for (int i = 1;i < num;i++) {
        if (node[i].d != MAX_LEN) {
            int v = i;
            std::stack<int> S;
            bool can_reach = true;
            while (v != 0) {
                S.push(v);
                v = node[v].pi;
                if (v < 0) {
                    can_reach = false;
                    break;
                }
            }
            if (!can_reach) {
                continue;
            }
            iowrite << "0," << i << ',' << node[i].d << ";0";
            while (!S.empty()) {
                iowrite << ',' << S.top();
                S.pop();
            }
            iowrite << std::endl;
        }
    }
}