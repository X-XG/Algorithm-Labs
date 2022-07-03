#include <iostream>
using namespace std;

typedef struct node {
    int key;
    int size = 1;
    int max;
    node* left;
    node* right;
    node* p;
    char color;
}node;

node* root;
node* nil;

int max3(int a, int b, int c) {
    if (a >= b && a >= c)return a;
    else if (b >= a && b >= c) return b;
    else return c;
}
int max2(int a, int b) {
    if (a > b)return a;
    else return b;
}

void left_rotate(node* x) {
    node* y = x->right;
    x->right = y->left;
    if (y->left != nil) {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == nil) {
        root = y;
    }
    else if (x == x->p->left) {
        x->p->left = y;
    }
    else {
        x->p->right = y;
    }
    y->left = x;
    x->p = y;

    y->size = x->size;
    x->size = 1;
    if (x->left != nil)x->size += x->left->size;
    if (x->right != nil)x->size += x->right->size;

    x->max = max3(x->left->max, x->key, x->right->max);
    y->max = max3(y->left->max, y->key, y->right->max);
}
void right_rotate(node* x) {
    node* y = x->left;
    x->left = y->right;
    if (y->right != nil) {
        y->right->p = x;
    }
    y->p = x->p;
    if (x->p == nil) {
        root = y;
    }
    else if (x == x->p->right) {
        x->p->right = y;
    }
    else {
        x->p->left = y;
    }
    y->right = x;
    x->p = y;

    y->size = x->size;
    x->size = 1;
    if (x->left != nil)x->size += x->left->size;
    if (x->right != nil)x->size += x->right->size;

    x->max = max3(x->left->max, x->key, x->right->max);
    y->max = max3(y->left->max, y->key, y->right->max);
}

void insert_fixup(node* z) {
    while (z->p != nil && z->p->p != nil && z->p->color == 'R') {
        if (z->p == z->p->p->left) {
            node* y = z->p->p->right;
            if (y != nil && y->color == 'R') {
                z->p->color = 'B';
                y->color = 'B';
                z->p->p->color = 'R';
                z = z->p->p;
            }
            else if (z == z->p->right) {
                z = z->p;
                left_rotate(z);
            }
            else {
                z->p->color = 'B';
                z->p->p->color = 'R';
                right_rotate(z->p->p);
            }
        }
        else {
            node* y = z->p->p->left;
            if (y != nil && y->color == 'R') {
                z->p->color = 'B';
                y->color = 'B';
                z->p->p->color = 'R';
                z = z->p->p;
            }
            else if (z == z->p->left) {
                z = z->p;
                right_rotate(z);
            }
            else {
                z->p->color = 'B';
                z->p->p->color = 'R';
                left_rotate(z->p->p);
            }
        }
    }
    root->color = 'B';
}

void insert(node* z) {
    node* x = root;
    node* y = nil;
    while (x != nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
        y->size++;
        if (z->key > y->max) {
            y->max = z->key;
        }
    }
    z->p = y;
    if (y == nil) {
        root = z;
    }
    else if (z->key < y->key) {
        y->left = z;
    }
    else {
        y->right = z;
    }
    z->left = nil;
    z->right = nil;
    z->color = 'R';
    insert_fixup(z);
}

void transplant(node* u, node* v) {
    if (u->p == nil) {
        root = v;
    }
    else if (u == u->p->left) {
        u->p->left = v;
    }
    else {
        u->p->right = v;

    }
    v->p = u->p;
}

node* minimum(node* x) {
    while (x->left != nil) {
        x = x->left;
    }
    return x;
}

void delet_fixup(node* x) {
    while (x != root && x->color == 'B') {
        if (x == x->p->left) {
            node* w = x->p->right;
            if (w->color == 'R') {
                w->color = 'B';
                x->p->color = 'R';
                left_rotate(x->p);
                w = x->p->right;
            }
            if (w->left->color == 'B' && w->right->color == 'B') {
                w->color = 'R';
                x = x->p;
            }
            else if (w->right->color == 'B') {
                w->left->color = 'B';
                w->color = 'R';
                right_rotate(w);
                w = x->p->right;
            }
            else {
                w->color = x->p->color;
                x->p->color = 'B';
                w->right->color = 'B';
                left_rotate(x->p);
                x = root;
            }
        }
        else {
            node* w = x->p->left;
            if (w->color == 'R') {
                w->color = 'B';
                x->p->color = 'R';
                right_rotate(x->p);
                w = x->p->left;
            }
            if (w->right->color == 'B' && w->left->color == 'B') {
                w->color = 'R';
                x = x->p;
            }
            else if (w->left->color == 'B') {
                w->right->color = 'B';
                w->color = 'R';
                left_rotate(w);
                w = x->p->left;
            }
            else {
                w->color = x->p->color;
                x->p->color = 'B';
                w->left->color = 'B';
                right_rotate(x->p);
                x = root;
            }
        }
    }
    x->color = 'B';
}

void delet_size(node* x) {
    root->p = nil;
    while (x != nil) {
        x->size--;
        x = x->p;
    }
}

void delet(node* z) {
    node* y = z;
    node* x;
    char y_original_color = y->color;
    if (z->left == nil) {
        x = z->right;
        delet_size(y);
        transplant(z, z->right);
    }
    else if (z->right == nil) {
        x = z->left;
        delet_size(y);
        if (y->p != nil) {
            y->p->max = max2(y->p->key, z->left->max);
        }
        transplant(z, z->left);
    }
    else {
        y = minimum(z->right);
        delet_size(y);
        y_original_color = y->color;
        x = y->right;
        if (y->p == z) {
            x->p = y;
        }
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
        y->size = z->size;
    }


    if (y_original_color == 'B') {
        delet_fixup(x);
        nil->p = nil;
    }
}

node* search(node* x, int k) {
    if (x == nil || k == x->key) {
        return x;
    }
    if (k < x->key) {
        return search(x->left, k);
    }
    else {
        return search(x->right, k);
    }
}

node* select(node* x, int i) {
    int r = x->right->size + 1;
    if (i == r) {
        return x;
    }
    else if (i < r) {
        return select(x->right, i);
    }
    else {
        return select(x->left, i - r);
    }
}

node* select_min(node* x, int a) {
    if (x->key < a) {
        return select_min(x->right, a);
    }
    else if (x->left->max < a) {
        return x;
    }
    else {
        return select_min(x->left, a);
    }
}

int select_num(node* x, int l, int r) {
    if (x == nil) {
        return 0;
    }
    else if (x->key > r) {
        return select_num(x->left, l, r);
    }
    else if (x->key < l) {
        return select_num(x->right, l, r);
    }
    else {
        if (x->p == nil) {
            return 1 + select_num(x->left, l, r) + select_num(x->right, l, r);
        }
        else {
            if (x == x->p->left) {
                if (x->p->key <= r) {
                    return 1 + x->right->size + select_num(x->left, l, r);
                }
                else {
                    return 1 + select_num(x->left, l, r) + select_num(x->right, l, r);
                }
            }
            else {
                if (x->p->key >= l) {
                    return 1 + x->left->size + select_num(x->right, l, r);
                }
                else {
                    return 1 + select_num(x->left, l, r) + select_num(x->right, l, r);
                }
            }
        }
    }
}


int main() {
    nil = new node;
    nil->key = INT32_MIN;
    nil->max = INT32_MIN;
    nil->size = 0;
    nil->color = 'B';
    nil->left = nil;
    nil->right = nil;
    nil->p = nil;
    root = nil;
    int m;
    char c;
    int key;
    cin >> m;
    for (int i = 0;i < m;i++) {
        cin >> c;
        if (c == 'I') {
            cin >> key;
            node* x = new node;
            x->key = key;
            x->max = key;
            insert(x);
        }
        else if (c == 'D') {
            cin >> key;
            node* x = search(root, key);
            delet(x);
            delete x;
        }
        else if (c == 'S') {
            int j;
            cin >> j;
            cout << select(root, j)->key << endl;
        }
        else if (c == 'L') {
            int a;
            cin >> a;
            cout << select_min(root, a)->key << endl;
        }
        else if (c == 'T') {
            int l, r;
            cin >> l >> r;
            cout << select_num(root, l, r) << endl;
        }
    }
    return 0;
}