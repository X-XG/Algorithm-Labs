#include<iostream>
#include<fstream>
#include<string>
#include<chrono>

#include "LCS.h"

#define NUM_GROUP 5

using namespace std;
using namespace  chrono;

int main() {
    string input_path = "../input/1_2_input.txt";
    string result_path_base = "../output/result_";
    string time_path = "../output/time.txt";

    ifstream infile;
    ofstream fresult;
    ofstream ftime;
    infile.open(input_path);
    ftime.open(time_path);

    for (int i = 0; i < NUM_GROUP; i++) {
        int len;
        infile >> len;
        char* x = new char[len];
        char* y = new char[len];
        for (int j = 0; j < len; j++) {
            infile >> x[j];
        }
        for (int j = 0; j < len; j++) {
            infile >> y[j];
        }

        LCS lcser(len, x, y);
        delete x;
        delete y;

        string result_path = result_path_base + to_string(len) + ".txt";
        fresult.open(result_path);

        auto start = system_clock::now();
        lcser.GetLCS();
        lcser.PrintLCS(len, len, "");
        auto end = system_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        int time = int(duration.count()) * nanoseconds::period::num;

        fresult << lcser.result << endl;
        for (auto str_lcs : lcser.lcss) {
            fresult << str_lcs << endl;
        }
        fresult.close();

        ftime << time << endl;
    }

    infile.close();
    ftime.close();
    return 0;
}