#include <iostream>
#include "ArgumentManager.h"
#include <fstream>
#include <algorithm>
#include <cstring>
#include "stacks.h"
#include <iomanip>
using namespace std;

int main(int argc, char *argv[]){
    ArgumentManager am(argc, argv);

    string infilename = am.get("input");
    string outfilename = am.get("output");

    ifstream fin(infilename);
    ofstream fout(outfilename);

    //ifstream fin("input3.txt");
    //ofstream fout("output.txt");

    string line;
    stacks eq;

    while(getline(fin, line)){
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        string postfix = eq.makePostFix(line);
        double result = eq.evaluate(postfix, line);
        fout << setprecision(2) << fixed;
        fout << result;
    }
}