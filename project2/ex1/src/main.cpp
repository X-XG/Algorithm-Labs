#include "FBHeap.h"
#include <iostream>
#include <fstream>
#define INIT_NUM 3
#define INIT_H1_NUM 50
#define INIT_H2_NUM 100
#define INIT_H3_NUM 150
#define INIT_H4_NUM 200
using namespace std;

int main(){
    ifstream infile;
    infile.open("../input/2_1_input.txt");

    FBHeap H1;
    FBHeap H2;
    FBHeap H3;
    FBHeap H4;
    FBHeap H5;
    int key;
    for(int i=0;i < INIT_H1_NUM; i++){
        infile>>key;
        H1.insert(key);
    }
    for(int i=0;i < INIT_H2_NUM; i++){
        infile>>key;
        H2.insert(key);
    }
    for(int i=0;i < INIT_H3_NUM; i++){
        infile>>key;
        H3.insert(key);
    }
    for(int i=0;i < INIT_H4_NUM; i++){
        infile>>key;
        H4.insert(key);
    }
    H1.extractMin();
    H1.decrease(198,169);
    // H1.decrease()
    return 0;
}