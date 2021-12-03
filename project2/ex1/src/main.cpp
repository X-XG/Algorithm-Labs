#include <iostream>
#include <fstream>
#include<chrono>

#include "FBHeap.h"

#define INIT_NUM 3
#define INIT_H1_NUM 50
#define INIT_H2_NUM 100
#define INIT_H3_NUM 150
#define INIT_H4_NUM 200

using namespace std;
using namespace  chrono;

int main() {
    string input_path = "../input/2_1_input.txt";
    string result_path = "../output/result.txt";
    string time_path = "../output/time.txt";

    ifstream infile;
    ofstream fresult;
    ofstream ftime;
    infile.open(input_path);
    fresult.open(result_path);
    ftime.open(time_path);

    FBHeap H1;
    FBHeap H2;
    FBHeap H3;
    FBHeap H4;
    FBHeap H5;
    int key;
    for (int i = 0;i < INIT_H1_NUM; i++) {
        infile >> key;
        H1.insert(key);
    }
    for (int i = 0;i < INIT_H2_NUM; i++) {
        infile >> key;
        H2.insert(key);
    }
    for (int i = 0;i < INIT_H3_NUM; i++) {
        infile >> key;
        H3.insert(key);
    }
    for (int i = 0;i < INIT_H4_NUM; i++) {
        infile >> key;
        H4.insert(key);
    }

    {   //H1
        auto start = system_clock::now();
        H1.insert(249);
        H1.insert(830);
        H1.minimum();
        H1.delet(127);
        H1.delet(141);
        H1.minimum();
        H1.decrease(75, 61);
        H1.decrease(198, 169);
        H1.extractMin();
        H1.extractMin();
        auto end = system_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        int time = int(duration.count()) * nanoseconds::period::num;
        ftime << time << endl;
    }
    // H1.extractMin();
    // H1.decrease(198, 169);
    // H1.decrease()
    return 0;
}