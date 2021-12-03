#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

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

    // for(int i=0;i<25;i++){
        // H1.extractMin();
    // }
    // return 0;

    {   //H1
        vector<int> resTemp;
        auto start = system_clock::now();
        resTemp.push_back(H1.insert(249));
        resTemp.push_back(H1.insert(830));
        resTemp.push_back(H1.minimum());
        resTemp.push_back(H1.delet(127));
        resTemp.push_back(H1.delet(141));
        resTemp.push_back(H1.minimum());
        resTemp.push_back(H1.decrease(75, 61));
        resTemp.push_back(H1.decrease(198, 169));
        resTemp.push_back(H1.extractMin());
        resTemp.push_back(H1.extractMin());
        auto end = system_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        int time = int(duration.count()) * nanoseconds::period::num;
        ftime << time << endl;

        fresult << "H1" << endl;
        bool first = true;
        for (auto res : resTemp) {
            if (first) {
                fresult << res;
                first = false;
            }
            else {
                fresult << "," << res;
            }
        }
        fresult << endl;
    }

    {   //H2
        vector<int> resTemp;
        auto start = system_clock::now();
        resTemp.push_back(H2.insert(816));
        resTemp.push_back(H2.minimum());
        resTemp.push_back(H2.insert(345));
        resTemp.push_back(H2.extractMin());
        resTemp.push_back(H2.delet(504));
        resTemp.push_back(H2.delet(203));
        resTemp.push_back(H2.decrease(296,87));
        resTemp.push_back(H2.decrease(278,258));
        resTemp.push_back(H2.minimum());
        resTemp.push_back(H2.extractMin());
        auto end = system_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        int time = int(duration.count()) * nanoseconds::period::num;
        ftime << time << endl;

        fresult << "H2" << endl;
        bool first = true;
        for (auto res : resTemp) {
            if (first) {
                fresult << res;
                first = false;
            }
            else {
                fresult << "," << res;
            }
        }
        fresult << endl;
    }

    {   //H3
        vector<int> resTemp;
        auto start = system_clock::now();
        resTemp.push_back(H3.extractMin());
        resTemp.push_back(H3.minimum());
        resTemp.push_back(H3.insert(262));
        resTemp.push_back(H3.extractMin());
        resTemp.push_back(H3.insert(830));
        resTemp.push_back(H3.minimum());
        resTemp.push_back(H3.delet(134));
        resTemp.push_back(H3.delet(177));
        resTemp.push_back(H3.decrease(617,360));
        resTemp.push_back(H3.decrease(899,353));
        auto end = system_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        int time = int(duration.count()) * nanoseconds::period::num;
        ftime << time << endl;

        fresult << "H3" << endl;
        bool first = true;
        for (auto res : resTemp) {
            if (first) {
                fresult << res;
                first = false;
            }
            else {
                fresult << "," << res;
            }
        }
        fresult << endl;
    }

    {   //H4
        vector<int> resTemp;
        auto start = system_clock::now();
        resTemp.push_back(H4.minimum());
        resTemp.push_back(H4.delet(708));
        resTemp.push_back(H4.insert(281));
        resTemp.push_back(H4.insert(347));
        resTemp.push_back(H4.minimum());
        resTemp.push_back(H4.delet(415));
        resTemp.push_back(H4.extractMin());
        resTemp.push_back(H4.decrease(620,354));
        resTemp.push_back(H4.decrease(617,360));
        resTemp.push_back(H4.decrease(899,353));
        auto end = system_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        int time = int(duration.count()) * nanoseconds::period::num;
        ftime << time << endl;

        fresult << "H4" << endl;
        bool first = true;
        for (auto res : resTemp) {
            if (first) {
                fresult << res;
                first = false;
            }
            else {
                fresult << "," << res;
            }
        }
        fresult << endl;
    }

    return 0;
}