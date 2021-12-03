typedef struct Node {
    int key;
    int degree;
    bool mark;
    struct Node* p;
    struct Node* child;
    struct Node* left;
    struct Node* right;
} Node;


class FBHeap {
private:
    Node* min;
    int num;
    void rootLInsert(Node* x);
public:
    FBHeap();
    ~FBHeap();
    void insert(int key);
    // void Union(FBHeap* H1, FBHeap* H2);
    Node* extractMin();
};

FBHeap::FBHeap() {
    min = nullptr;
    num = 0;
}

FBHeap::~FBHeap() {
}

void FBHeap::rootLInsert(Node* x) {
    x->left = min->left;
    x->right = min;
    min->left->right = x;
    min->left = x;
}

void FBHeap::insert(int key) {
    auto x = new Node;
    x->key = key;
    x->degree = 0;
    x->p = nullptr;
    x->child = nullptr;
    x->mark = false;
    if (min == nullptr) {
        x->left = x;
        x->right = x;
        min = x;
    }
    else {
        rootLInsert(x);
        if (x->key < min->key) {
            min = x;
        }
    }
    num++;
}

Node* FBHeap::extractMin() {
    auto z = min;
    if (z != nullptr) {
        auto x = z->child;
        auto sentry = x->left;
        while (x != sentry) {
            auto next = x->right;
            rootLInsert(x);
            x = next;
        }
        rootLInsert(x);

    }
}