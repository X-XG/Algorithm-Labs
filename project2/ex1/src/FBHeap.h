#define D_MAX 20

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
    void ListInsert(Node* x, Node* y);
    void rootLRemove(Node* x);
    void consolidate();
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

void FBHeap::ListInsert(Node* x, Node* y) {
    // if (y == nullptr) {
    //     y = x;
    //     y->left = y;
    //     y->right = y;
    // }
    // else {
    //     // x->p = nullptr;
    x->left = y->left;
    x->right = y;
    y->left->right = x;
    y->left = x;
    // }
}

void FBHeap::rootLRemove(Node* x) {
    if (x == nullptr)return;
    x->left->right = x->right;
    x->right->left = x->left;
    // delete x;
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
        ListInsert(x, min);
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
        if (x != nullptr) {
            auto sentry = x;
            do {
                auto next = x->right;
                x->p = nullptr;
                ListInsert(x, min);
                x = next;
            } while (x != sentry);
        }

        // while (x != sentry) {
        //     auto next = x->right;
        //     x->p = nullptr;
        //     rootLInsert(x);
        //     x = next;
        // }
        // rootLInsert(x);

        if (z == z->right) {
            min = nullptr;
        }
        else {
            min = z->right;
            rootLRemove(z);
            consolidate();
        }
        num -= 1;
    }
    return z;
}

void FBHeap::consolidate() {
    Node* A[D_MAX] = { nullptr };
    auto x = min;
    auto sentry = min;
    do {
        auto next = x->right;
        int d = x->degree;
        while (A[d] != nullptr) {
            auto y = A[d];
            if (x->key > y->key) {
                auto tmp = y;
                y = x;
                x = tmp;
            }
            rootLRemove(y);
            if (x->child == nullptr) {
                y->left = y;
                y->right = y;
                y->p = x;
                x->child = y;
            }
            else {
                y->p = x;
                ListInsert(y, x->child);
            }
            x->degree++;
            y->mark = false;
            A[d] = nullptr;
            d++;
        }
        A[d] = x;
        x = next;
    } while (x != sentry);

    min = nullptr;
    for (int i = 0; i < D_MAX;i++) {
        if (A[i] != nullptr) {
            if (min == nullptr) {
                min = A[i];
                min->p = nullptr;
                min->left = min;
                min->right = min;
            }
            else {
                ListInsert(A[i], min);
                if (A[i]->key < min->key) {
                    min = A[i];
                }
            }
        }
    }
}