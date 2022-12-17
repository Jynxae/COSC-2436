#include <iostream>
#include "LinkedLists.h"
#include "LinkedLists.cpp"
#include "ArgumentManager.h"
#include <fstream>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

int main(int argc, char *argv[]){

    ArgumentManager am(argc, argv);

    string infilename = am.get("input");
    string outfilename = am.get("output");

    ifstream fin(infilename);
    ofstream fout(outfilename);

   // ifstream fin("input2.txt");
    //ofstream fout("output2.txt");

    LinkedLists<int> intList;   
    LinkedLists<string> strList;
    LinkedLists<char> charList;
    string line;
    string type;
    string start;

    getline(fin,type);
    getline(fin,start);

    type.erase(remove(type.begin(), type.end(), '\n'), type.end());
    type.erase(remove(type.begin(), type.end(), '\r'), type.end());
    start.erase(remove(start.begin(), start.end(), '\n'), start.end());
    start.erase(remove(start.begin(), start.end(), '\r'), start.end()); //was like line.erase and so on gotcha

    //cout << type << "t" << endl;
    //cout << start << "t" << endl;

    if (start == "head")        //if it wants to start adding from the head
    {
        while (getline(fin, line))
        {   
          line.erase(remove(line.begin(), line.end(), '\n'), line.end());
          line.erase(remove(line.begin(), line.end(), '\r'), line.end());
          //start.erase(remove(start.begin(), start.end(), '\n'), start.end());
          //start.erase(remove(start.begin(), start.end(), '\r'), start.end());
            if (type == "string")
            {
                if (line == "remove head" || line == "remove tail")
                {
                    if (line.find("head") != string::npos)
                    {
                        strList.removeHead();
                    }
                    else if(line.find("tail") != string::npos)
                    {
                        strList.removeTail();
                    }
                }
                else
                {
                    strList.addAtBeg(line);
                }
            }

            else if (type == "char")
            {
                if (line == "remove head" || line == "remove tail")
                {
                    if (line.find("head") != string::npos)
                    {
                        charList.removeHead();
                    }
                    else
                    {
                        charList.removeTail();
                    }
                }
                else
                {
                    charList.addAtBeg(line[0]);
                }
            }

            else if (type == "int")
            {
                if (line == "remove head" || line == "remove tail")
                {
                    if (line.find("head") != string::npos)
                    {
                        intList.removeHead();
                    }
                    else
                    {
                        intList.removeTail();
                    }
                }
                else
                {
                    intList.addAtBeg(stoi(line));
                }
            }

            else
            {
                return 0;
            }
        }

        strList.print(fout);
        charList.print(fout);
        intList.print(fout);
    }

    else if(start == "tail")        //if it wants to start adding from the tail
    {
        while (getline(fin, line))
        {
          line.erase(remove(line.begin(), line.end(), '\n'), line.end());
          line.erase(remove(line.begin(), line.end(), '\r'), line.end());
            if (type == "string")
            {
                if (line == "remove head" || line == "remove tail")
                {
                    if (line.find("head") != string::npos)
                    {
                        strList.removeHead(); // how can i get it to know exactly which list im talkiing about??
                    }
                    else
                    {
                        strList.removeTail();
                    }
                }
                else
                {
                    strList.addAtEnd(line);
                }
            }

            else if (type == "char")
            {
                if (line == "remove head" || line == "remove tail")
                {
                    if (line.find("head") != string::npos)
                    {
                        charList.removeHead(); // how can i get it to know exactly which list im talkiing about??
                    }
                    else
                    {
                        charList.removeTail();
                    }
                }
                else
                {
                    charList.addAtEnd(line[0]);
                }
            }

            else if (type == "int")
            {
                if (line == "remove head" || line == "remove tail")
                {
                    if (line.find("head") != string::npos)
                    {
                        intList.removeHead(); // how can i get it to know exactly which list im talkiing about??
                    }
                    else
                    {
                        intList.removeTail();
                    }
                }
                else
                {
                    intList.addAtEnd(stoi(line));
                }
            }

            else
            {
                return 0;
            }
        }
        strList.print(fout);
        charList.print(fout);
        intList.print(fout);
    }

    fin.close();
    fout.close();

    return 0;
    
}