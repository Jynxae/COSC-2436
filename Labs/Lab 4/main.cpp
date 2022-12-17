#include <iostream>
#include <fstream>
#include "ArgumentManager.h"
#include <queue>
#include <algorithm>
#include "queueLL.h"

using namespace std;

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);

    string infilename = am.get("input");
    string outfilename = am.get("output");

    ifstream fin(infilename);
    ofstream fout(outfilename);

    // ifstream fin("input4.txt");
    // ofstream fout("output.txt");

    string line;
    queueLL q;
    priority_queue <int, vector<int>, greater<int> > p;

    while(getline(fin, line))
    {
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        if(line != ""){
        int pos = line.rfind(" ");
        double num = stod(line.substr(pos + 1));

        q.enqueue(line, num);
        }
    }

    q.print(fout);


    
    return 0;
}