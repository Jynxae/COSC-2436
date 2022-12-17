#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "avlTree.h"
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
    int size;
    int num;
    node* root;
    avlTree list;
    fin >> size;

    while(fin >> num)
    {
        root = list.add(num);
    }
    list.printLevelOrder(root, fout, size);
return 0;
}