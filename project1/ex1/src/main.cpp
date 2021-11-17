#include<iostream>
#include<fstream>
#include<string>
#include<chrono>

#include "MatrixMul.h"

#define NUM_GROUP 5

using namespace std;
using namespace  chrono;

int main() {
    string input_path = "../input/1_1_input.txt";
    string result_path = "../output/result.txt";
    string time_path = "../output/time.txt";

    ifstream infile;
    ofstream fresult;
    ofstream ftime;
    infile.open(input_path);
    fresult.open(result_path);
    ftime.open(time_path);

    for (int i = 0; i < NUM_GROUP; i++) {
        int n;
        infile >> n;
        long long* p = new long long[n + 1];
        for (int j = 0; j <= n; j++) {
            infile >> p[j];
        }

        MatrixMul muler(n, p);
        delete[] p;

        auto start = system_clock::now();
        muler.ChainMul();
        auto end = system_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        double time = double(duration.count()) * nanoseconds::period::num;
        fresult << muler.result << endl;

        muler.PrintParens(1, n);
        fresult << muler.parens << endl;
        ftime << time << "ns" << endl;
    }

    infile.close();
    fresult.close();
    ftime.close();
    return 0;
}