#include<cstdlib>
#include<time.h>

class LCS {
private:
    int num;
    char *x;
    char *y;
    void GetLCS();

public:
    LCS(int num, char *x, char *y);
    ~LCS();
    
    int result;
    int time;
    void GetResult();
};

LCS::LCS(int num, char *x, char *y){
    this->num = num;
    this->x = new char[num];
    this->y = new char[num];
    for(int i=0; i<num; i++){
        this->x[i] = x[i];
        this->y[i] = y[i];
    }
}

LCS::~LCS(){
    delete [] x;
    delete [] y;
}

void LCS::GetLCS(){

}

void LCS::GetResult(){
    int start = clock();
    GetLCS();
    int end = clock();
    time = start - end;
}