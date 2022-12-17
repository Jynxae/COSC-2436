#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>
#include "ArgumentManager.h"
using namespace std;

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);

    string infilename = am.get("input");
    string outfilename = am.get("output");

    ifstream fin(infilename);
    ofstream fout(outfilename);

    // ifstream fin("input1.txt");
    // ofstream fout("output.txt");

    string line;
    map<string, int> myMap;

    while (fin >> line) // getline(fin, line))
    {
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        line.erase(remove_if(line.begin(), line.end(),[]
        (char x)
        {
            return ispunct(x) && x != '\'';
        }),line.end());
        myMap[line]++;
    }

    for (const auto &p : myMap)
    {
        fout << p.first << ": " << p.second << '\n';
    }
    return 0;
}
