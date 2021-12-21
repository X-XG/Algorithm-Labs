#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>

#include "Johnson.h"

using namespace std;
using namespace chrono;

ofstream ftime;
ofstream fresult;

void test(int num, string id) {
    Johnson JH(num, id);
    auto start = system_clock::now();
    JH.run();
    auto end = system_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    int time = int(duration.count()) * nanoseconds::period::num;
    ftime << time << endl;
    fresult.open("../output/result" + id + ".txt");
    for (int i = 1;i <= num;i++) {
        for (int j = 1;j <= num;j++) {
            if (JH.delta[i][j] == MAX_LEN) {
                fresult << 'X' << ' ';
            }
            else {
                fresult << JH.delta[i][j] << ' ';
            }
        }
        fresult << endl;
    }
    fresult.close();
};

int main() {
    ftime.open("../output/time.txt");

    test(27, "11");
    test(27, "12");
    test(81, "21");
    test(81, "22");
    test(243, "31");
    test(243, "32");
    test(729, "41");
    test(729, "42");

    return 0;
}