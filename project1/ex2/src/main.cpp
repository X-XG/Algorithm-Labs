#include<iostream>
#include<fstream>
#include<string>

#include "LCS.h"

#define NUM_GROUP 5

using namespace std;

int main(){
    string input_path = "../input/1_2_input.txt";
    string result_path = "../output/result.txt";
    string time_path = "..output/time.txt";

    ifstream infile;
    ofstream fresult;
    ofstream ftime;
    infile.open(input_path);
    fresult.open(result_path);
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

        fresult << lcser.result << endl;
        // fresult << lcser.
        ftime << lcser.time << endl;
    }

    return 0;
}