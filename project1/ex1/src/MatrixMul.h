#include<cstdlib>
#include<time.h>

class MatrixMul {
private:
    int num;
    int *scale;
    void ChainMul();

public:
    MatrixMul(int num, int *scale);
    ~MatrixMul();
    
    long long result;
    int time;
    void GetResult();
};

MatrixMul::MatrixMul(int n, int *p){
    num = n;
    scale = new int[n];
    for(int i=0; i<n; i++){
        scale[i] = p[i];
    }
}

MatrixMul::~MatrixMul(){
    delete [] scale;
}

void MatrixMul::ChainMul(){

}

void MatrixMul::GetResult(){
    int start = clock();
    ChainMul();
    int end = clock();
    time = start - end;
}