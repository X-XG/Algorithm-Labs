#include<iostream>
#include<fstream>
#include<string>

#include "LCS.h"

#define NUM_GROUP 5

using namespace std;

int main(){
    string input_path = "../input/1_2_input.txt";
    string result_path_base = "../output/result_";
    string time_path = "..output/time.txt";

    ifstream infile;
    ofstream fresult;
    ofstream ftime;
    infile.open(input_path);
    ftime.open(time_path);

    for(int i=0; i<NUM_GROUP; i++){
        int num;
        infile >> num;
        char *x = new char[num];
        char *y = new char[num];
        for(int j=0; j<num; j++){
            infile >> x[j];
        }
        for(int j=0; j<num; j++){
            infile >> y[j];
        }  

        LCS lcser(num, x, y);
        delete x;
        delete y;

        string result_path = result_path_base + to_string(num) + ".txt";
        fresult.open(result_path);

        fresult << lcser.result << endl;
        fresult.close();
        
        ftime << lcser.time << endl;
    }

    infile.close();
    ftime.close();
    return 0;
}