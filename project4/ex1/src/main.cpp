#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

#include "KMP.h"

using namespace std;
using namespace  chrono;

ifstream infile;
ofstream fresult;
ofstream ftime;

void test() {
    string P, T;
    infile >> P >> T;
    KMP searcher(P, T);

    auto start = system_clock::now();
    searcher.run();
    auto end = system_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    int time = int(duration.count()) * nanoseconds::period::num;
    ftime << time << endl;

    fresult << searcher.hit << endl;
    for (int i = 1;i <= searcher.m;i++)
        fresult << searcher.pi[i] << ' ';
    fresult << endl;
    for (auto s : searcher.shift)
        fresult << s << ' ';
    fresult << endl << endl;
}

int main() {
    infile.open("../input/4_1_input.txt");
    fresult.open("../output/result.txt");
    ftime.open("../output/time.txt");

    for (int i = 0;i < 5;i++)
        test();

    return 0;
}