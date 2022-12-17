#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "list.h"
#include "ArgumentManager.h"
using namespace std;

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);

    string infilename = am.get("input");
    string outfilename = am.get("output");

    ifstream fin(infilename);
    ofstream fout(outfilename);

    // ifstream fin("input3.txt");
    // ofstream fout("output.txt");

    list in;
    list com;
    string line, travMethod;

    while (getline(fin, line)) // successfuly reads in input :)
    {
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        if(line == "")
        {
            continue;
        }
        if (line == "Inorder" || line == "Preorder" || line == "Postorder")
        {
            travMethod = line; // find which way we're gonna traverse it
        }

        else
        {
            int parPos = line.rfind(')');
            int priority = stoi(line.substr(parPos - 1, 1));
            int openParPos = line.rfind('(');

            string data = line.substr(0, openParPos);
            com.priorityQueue(data, priority); // any other command will go into command queue, CHECK FOR CASE LATER
        }
    }

    list toSort;
    node *root = NULL;
    while (!com.isempty())
    {
        string temp;
        string command = com.getFront(); // grab first node from priority queue
        com.dequeue();                   // takes it out the queue since we wont need it again
        string code = in.getFront();
        int pos = command.find(':');
        string result = command.substr(0, pos); // grabs name of command
        if (code == "" && result != "DECODE")
        {
            continue;
        }
        if (result == "REPLACE")
        {
            int pos = command.find('[') + 1;
            string first = command.substr(pos, 1);
            string second = command.substr(pos + 2, 1);
            temp = in.replace(code, first, second); // maybe enqueue from within the function??
        }
        else if (result == "DECODE")
        {
            int openBrPos = command.find('[');
            int closeBrPos = command.find(']');
            string data = command.substr(openBrPos + 1, closeBrPos - openBrPos - 1); // check later to see if it grabs it correctly
            in.enqueue(data);
            continue;
        }
        else if (result == "ADD")
        {
            int pos = command.find('[') + 1;
            string first = command.substr(pos, 1);
            string second = command.substr(pos + 2, 1);
            temp = in.add(code, first, second);
        }
        else if (result == "REMOVE")
        {
            int pos = command.find('[') + 1;
            string first = command.substr(pos, 1);
            temp = in.removeChar(code, first);
        }
        else if (result == "SWAP")
        {
            int pos = command.find('[') + 1;
            string first = command.substr(pos, 1);
            string second = command.substr(pos + 2, 1);
            temp = in.swap(code, first, second);
        }
        else if (result == "BST")
        {
            root = toSort.insert(root, code);
            in.dequeue();
            continue;
        }
        in.dequeue();
        in.enqueue(temp);
        code = "";
    }
    if (travMethod == "Postorder")
    {
        toSort.PostOrder(root, fout);
    }
    else if (travMethod == "Preorder")
    {
        toSort.PreOrder(root, fout);
    }
    else if (travMethod == "Inorder")
    {
        toSort.InOrder(root, fout);
    }
    return 0;
}