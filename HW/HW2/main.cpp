#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"
#include "List.h" //may have to change to cpp
using namespace std;


int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);

    string infilename = am.get("input");
    string outfilename = am.get("output");
    string commfilename = am.get("command");

    ifstream fin(infilename);
    ofstream fout(outfilename);
    ifstream fread(commfilename);

    //ifstream fin("input5.txt");
    //ofstream fout("output.txt");
    //ifstream fread("command5.txt");

    List list;
    string line, user, com;
    int id, score;
    char grade;

    while (getline(fin, line)) //possibly may have to make them into vectors and do for loop outside??
    {
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        int iPos = line.find("id");
        int uPos = line.find("username");
        int sPos = line.find("score");
        int gPos = line.find("grade");
        if (iPos < uPos && uPos < sPos && sPos < gPos && iPos != -1) // checks to see if they have all attributes and in order
        {
            for (int i = 0; i < line.length(); i++)
            {
                if (line.at(i) == ':' && line.find("id", i - 2) != string::npos)
                {                                             // THE ARGUMENTS OF SUBSTR IS NOT (START, FINISH)!! ITS (START, LENGTH)
                    size_t found = line.find(';', i);         // returns the pos of ;
                    int pos = found - i;                      // finds out the length of the value
                    string num = line.substr(i + 1, pos - 1); // checking to see if it is grabbed correctly
                    id = stoi(num);                           // allows me to grab from : all the way till ;
                }
                else if (line.at(i) == ':' && line.find("username", i - 8) != string::npos)
                {
                    size_t found = line.find(';', i);
                    int pos = found - i;
                    user = line.substr(i + 1, pos - 1);
                }
                else if (line.at(i) == ':' && line.find("score", i - 5) != string::npos)
                {
                    size_t found = line.find(';', i);
                    int pos = found - i;
                    score = stoi(line.substr(i + 1, pos - 1));
                }
                else if (line.at(i) == ':' && line.find("grade", i - 5) != string::npos)
                {
                    size_t found = line.find(';', i);
                    int pos = found - i + 1;
                    grade = line[i + 1];
                    break;
                }
            }
            if(list.isDuplicateUser(id,user,score,grade))
            {
                continue;
            }
            if (list.isDuplicateID(id, user, score, grade))
            {
                continue;
            }
            else
            {
                list.addAtEnd(id, user, score, grade);
            }
        }
        else
        {
            continue;
        }
    }

    while(getline(fread, com))
    {
        com.erase(remove(com.begin(), com.end(), '\n'), com.end());
        com.erase(remove(com.begin(), com.end(), '\r'), com.end());
        if(com.find("Add") != string::npos) //may have to possibly dissect the input here as well, if so then make it a function
        {
            int pos = com.find('(') + 1;
            string word = com.substr(8);
            int numPos = stoi(com.substr(pos));
            for (int i = 0; i < word.length(); i++)
            {
                if (word.at(i) == ':' && word.find("id", i - 2) != string::npos)
                {                                             // THE ARGUMENTS OF SUBSTR IS NOT (START, FINISH)!! ITS (START, LENGTH)
                    size_t found = word.find(';', i);         // returns the pos of ;
                    int pos = found - i;                      // finds out the length of the value
                    string num = word.substr(i + 1, pos - 1); // checking to see if it is grabbed correctly
                    id = stoi(num);                           // allows me to grab from : all the way till ;
                }
                else if (word.at(i) == ':' && word.find("username", i - 8) != string::npos)
                {
                    size_t found = word.find(';', i);
                    int pos = found - i;
                    user = word.substr(i + 1, pos - 1);
                }
                else if (word.at(i) == ':' && word.find("score", i - 5) != string::npos)
                {
                    size_t found = word.find(';', i);
                    int pos = found - i;
                    score = stoi(word.substr(i + 1, pos - 1));
                }
                else if (word.at(i) == ':' && word.find("grade", i - 5) != string::npos)
                {
                    size_t found = word.find(';', i);
                    int pos = found - i + 1;
                    grade = word[i + 1];
                    break;
                }
            }
            if(list.isDuplicateUser(id,user,score,grade))
            {
                continue;
            }
            if(list.getSize() < numPos)
            {
                continue;
            }
            if (list.isDuplicateID(id, user, score, grade))
            {
                continue;
            }
            else
            {
                list.Add(numPos,id,user,score,grade);
            }
            
        }
        else if (com.find("Remove") != string::npos)
        {
            int end = com.find(')');
            int mid = com.find(':') + 1;
            int start = com.find('(') + 1;
            string attribute = com.substr(8, (mid-1) - start);
            string word = com.substr(mid, end - mid);
            list.Remove(word, attribute);
        }
        //could add a function where it takes it in and if the id matches, update the cu node
        else if(com.find("Sort") != string::npos)
        {
            if(list.getSize() == 0)
            {
                continue;
            }
            int start = com.find('(');
            int end = com.find(')');
            string word = com.substr(start + 1, end-start-1);
            list.Sort(word);
        }
    }
        list.print(fout);
}
