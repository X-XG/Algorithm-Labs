#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

#include "RabinKarp.h"

using namespace std;

int main() {
    ifstream infile;
    ofstream fresult;
    ofstream ftime;
    infile.open("../input/4_2_input.txt");
    fresult.open("../output/result.txt");
    ftime.open("../output/time.txt");

    RabinKarp matcher[5][4];

    for (int i = 0;i < 5;i++) {
        string P, T;
        infile >> P >> T;
        matcher[i][0].init(P, T, 2, 13);
        matcher[i][1].init(P, T, 2, 1009);
        matcher[i][2].init(P, T, 10, 13);
        matcher[i][3].init(P, T, 10, 1009);
    }
    for (int i = 0;i < 5;i++)
        for (int j = 0;j < 4;j++)
            matcher[i][j].run();
    for (int i = 0;i < 5;i++) {
        fresult << matcher[i][0].hit << endl;
        for (int j = 0;j < 4;j++) {
            fresult << matcher[i][j].fake_hit << ' ';
        }
        fresult << endl;
        for (auto s : matcher[i][0].shift) {
            fresult << s << ' ';
        }
        fresult << endl << endl;
    }

    ftime << "(2,13)" << endl;
    for (int i = 0;i < 4;i++)
        ftime << matcher[i][0].time << ' ';
    ftime << endl;

    ftime << "(2,1009)" << endl;
    for (int i = 0;i < 4;i++)
        ftime << matcher[i][1].time << ' ';
    ftime << endl;

    ftime << "(10,13)" << endl;
    for (int i = 0;i < 4;i++)
        ftime << matcher[i][2].time << ' ';
    ftime << endl;

    ftime << "(10,1009)" << endl;
    for (int i = 0;i < 4;i++)
        ftime << matcher[i][3].time << ' ';
    ftime << endl;

    return 0;
}