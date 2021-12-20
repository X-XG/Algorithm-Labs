#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>

#include "Bellman.h"

using namespace std;
using namespace chrono;

ofstream ftime;

void test(int num, string id){
    Bellman BF(num,id);
    auto start = system_clock::now();
    BF.run();
    auto end = system_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    int time = int(duration.count()) * nanoseconds::period::num;
    ftime << time << endl;
    BF.write();
};

int main() {
    ftime.open("../output/time.txt");

    test(27,"11");
    test(27,"12");
    test(81,"21");
    test(81,"22");
    test(243,"31");
    test(243,"32");
    test(729,"41");
    test(729,"42");

    return 0;
}