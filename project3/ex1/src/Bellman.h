#include <fstream>
#include <string>
#include <stack>

#define MAX_NUM 750
#define MAX_LEN 1005
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
            \
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
    for (int i = 0;i < num;i++) {
        if (node[i].d != MAX_LEN) {
            iowrite << "0," << i << ',' << node[i].d << ";0,";
            int v = i;
            std::stack<int> S;
            while (v != 0) {
                S.push(v);
                v = node[v].pi;
            }
            while (!S.empty()) {
                iowrite << S.top() << ',';
                S.pop();
            }
            iowrite << '0' << std::endl;
        }
    }
}