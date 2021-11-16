#include<iostream>
#include<fstream>
#include<string>

#include "MatrixMul.h"

#define NUM_GROUP 5

using namespace std;

int main(){
    string input_path = "../input/1_1_input.txt";
    string result_path = "../output/result.txt";
    string time_path = "..output/time.txt";

    ifstream infile;
    ofstream fresult;
    ofstream ftime;
    infile.open(input_path);
    fresult.open(result_path);
    ftime.open(time_path);

    for(int i=0; i<NUM_GROUP; i++){
        int n;
        infile >> n;
        int *p = new int[n];
        for(int j=0; j<n; j++){
            infile >> p[j];
        } 

        MatrixMul muler(n, p);
        delete p;

        fresult << muler.result << endl;
        // fresult << muler.
        ftime << muler.time << endl;
    }

    return 0;
}