#define D_MAX 20
#define LITERAL_MAX 1005

typedef struct Node {
    int key;
    int degree;
    bool mark;
    struct Node* p;
    struct Node* child;
    struct Node* left;
    struct Node* right;
} Node;

Node* HashTable[LITERAL_MAX];

class FBHeap {
private:
    Node* min;
    int num;
    void ListInsert(Node* x, Node* y);
    void ListRemove(Node* x);
    void consolidate();
    void Cut(Node* x, Node* y);
    void CascadingCut(Node* y);
public:
    FBHeap();
    ~FBHeap();
    void insert(int key);
    // void Union(FBHeap* H1, FBHeap* H2);
    int minimum();
    int extractMin();
    int decrease(int xkey, int k);
    int delet(int xkey);
    static FBHeap Union(FBHeap H1, FBHeap H2);
};

FBHeap::FBHeap() {
    min = nullptr;
    num = 0;
}

FBHeap::~FBHeap() {
}

int FBHeap::minimum() {
    return min->key;
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

void FBHeap::ListRemove(Node* x) {
    if (x == nullptr)return;
    else if (x->right->right == x) {
        x->right->left = x->right;
        x->right->right = x->right;
    }
    else {
        x->left->right = x->right;
        x->right->left = x->left;
    }
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
    HashTable[x->key] = x;
}

int FBHeap::extractMin() {
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
            ListRemove(z);
            consolidate();
        }
        num -= 1;
    }
    int res = z->key;
    delete z;
    return res;
}

void FBHeap::consolidate() {
    Node* A[D_MAX] = { nullptr };
    auto sentry = min->left;
    auto next = min;
    bool getout = false;
    while(true){
        auto x = next;
        int d = x->degree;
        // if(A[d] == x){
        //     printf("111111111111111111111");
        //     exit(2);
        // }
        if(x==sentry){
            getout = true;
        }
        while (A[d] != nullptr) {
            auto y = A[d];
            if (x->key > y->key) {
                auto tmp = y;
                y = x;
                x = tmp;
            }
            // if(x==x->right){
            //     printf("fefsfwfwagwgg");
            //     exit(-1);
            // }
            ListRemove(y);
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
        if(getout){
            break;
        }
        next = x->right;
    }

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

int FBHeap::decrease(int xkey, int k) {
    Node* x = HashTable[xkey];
    if (k > x->key) {
        return -1;
    }
    x->key = k;
    auto y = x->p;
    if (y != nullptr && x->key < y->key) {
        Cut(x, y);
        CascadingCut(y);
    }
    if (x->key < min->key) {
        min = x;
    }
    return min->key;
}

void FBHeap::Cut(Node* x, Node* y) {
    if (x->right == x) {
        y->child = nullptr;
    }
    else {
        ListRemove(x);
    }
    x->p = nullptr;
    y->degree--;
    x->mark = false;
    ListInsert(x, min);
}

void FBHeap::CascadingCut(Node* y) {
    Node* z = y->p;
    if (z != nullptr) {
        if (y->mark == false) {
            y->mark = true;
        }
        else {
            Cut(y, z);
            CascadingCut(z);
        }
    }
}

int FBHeap::delet(int xkey) {
    decrease(xkey, -1);
    extractMin();
    return num;
}

FBHeap FBHeap::Union(FBHeap H1, FBHeap H2) {
    if (H1.min == nullptr) {
        H1.~FBHeap();
        return H2;
    }
    if (H2.min == nullptr) {
        H2.~FBHeap();
        return H1;
    }
    FBHeap H;
    H.min = H1.min;
    H2.min->right->left = H1.min->left;
    H1.min->left->right = H2.min->right;
    H2.min->right = H1.min;
    H1.min->left = H2.min;

    if (H1.min < H2.min) {
        H.min = H1.min;
    }
    else {
        H.min = H2.min;
    }
    H.num = H1.num + H2.num;
    H1.~FBHeap();
    H2.~FBHeap();
    return H;
}