#include <iostream>
#include "ArgumentManager.h"
#include <string>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <vector>


using namespace std;

string isID(string ID)
{
    string idNum;
    for(int i = 0; i < ID.length(); i++)
    {
        if(ID.at(i) == 'i' && ID.at(i+1) == 'd')
        {
            idNum += ID.substr(i+3, ID.length()-1);
            return idNum;
        }
    }
    return "";
}

std::array<string,10> separateChar(string section) //increase the space
{
    std::array<string,10> code; 
    int x = 0;
    for(int i = 0; i < section.length(); i++){
        if(section.at(i) == 'i' && section.at(i+1) == 'd')
        {
            return code; //reuse this code to make another function to save charset??
        }
        if(section.at(i) == ':')
        {                               //THE ARGUMENTS OF SUBSTR IS NOT (START, FINISH)!! ITS (START, LENGTH)
            size_t found= section.find(';', i);
            int pos = found - i+1;
            code[x] = section.substr(i-1, pos+1);// when going througgh the id list, when a letter has been found, if it is greater than other letter values
            x++;                                //just assign it the array value
        }
    }
    return code;
}

string delHash(string ID)
{

    for(int i = ID.length()-1; i >= 0; i--) //starts from the last index so that it doesn't mess up the previous indexes
    {
        if(ID.at(i) == '#')
        {
            ID.replace(i, 1, to_string(i));
        }
    }
        return ID;
    
}

string decode(string ID, std::array<string, 10> charLet)
{
    string decodedString = "";
    int size = charLet.size();
    for(int i = 0; i < ID.length(); i++)        //will go through the ID string
    {
        if(isalpha(ID.at(i)))           //if its  a letter, it will jump into the for loop of code array
        {
            for(int x = 0; x < size; x++)       //it will go through the array to see which letter matches
            {  
                if(ID.at(i) == charLet[x][0]) //or charLet.at(x).at(0) ///if the letter matches, it will go into the for loop
                {
                    string place = "";
                    for(int a = 2; a < charLet[x].length()-1; a++) //this takes out the number and places it into the string
                    {
                        int letter = x;
                        place += charLet[letter][a];
                        //cout << place << endl;
                        //5#83912931##5897377
                    }
                    ID.replace(i, 1, place);
                    decodedString += ID.at(i);
                    break;
                }     
            }
        }
        else{
        decodedString += ID.at(i);
        }
    }
    return decodedString;
}


int main(int argc, char *argv[]){

ArgumentManager am(argc, argv);

string infilename = am.get("input");
string outfilename = am.get("output");
string commandFile = am.get("command");

ifstream fin(infilename);
ofstream fout(outfilename);
ifstream fread(commandFile);

/*ifstream fin("input6.txt");
ifstream fread("command6.txt");
ofstream fout("output.txt");*/

string line = "";
string id;
string charLet;
string filter;
std::array<string, 10> isChar;
vector <string> first;
vector <string> last;
vector <string> output;
vector <string> theFinal;



while(getline(fread, filter))
    {
        filter.erase(remove(filter.begin(), filter.end(), '\n'), filter.end());
        filter.erase(remove(filter.begin(), filter.end(), '\r'), filter.end());
        filter.erase(remove(filter.begin(), filter.end(), ' '), filter.end());

        if (filter.size() == 0)
        {
            continue;
        }

        if (filter.find("first4:") != string::npos){
            first.push_back(filter.substr(7));
        }
        else
        {
            last.push_back(filter.substr(6));
        }
    }

int i = 0;
while(getline(fin, line)) {
    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    if(line.size() == 0){
      continue;
    }
    id = isID(line);
    isChar = separateChar(line);
    string decoded = "";
    string final = "";
    decoded = decode(id, isChar);
    final = delHash(decoded);
    if(id != "" && isChar.at(0) != "") //will reject invaild entry
    {
    theFinal.push_back(final);
    }
}


for (int i = 0; i < theFinal.size(); i++)
{
    if (first.size() > 0 && last.size() > 0)
    {
        if (count(first.begin(), first.end(), theFinal[i].substr(0, 4)) && count(last.begin(), last.end(), theFinal[i].substr(theFinal[i].length() - 4)))
        {
            output.push_back(theFinal[i]);
        }
    }
    else if (first.size() > 0 && last.size() == 0)
    {
        if (count(first.begin(), first.end(), theFinal[i].substr(0, 4)) == 1)
        {
            output.push_back(theFinal[i]);
        }
    }
    else if (first.size() == 0 && last.size() > 0)
    {
        if (count(last.begin(), last.end(), theFinal[i].substr(theFinal[i].length() - 4)) == 1) //org ==1
        {
            output.push_back(theFinal[i]);
        }
    }
    else
    {
        output.push_back(theFinal[i]);
    }
}

for (int i = 0; i < output.size(); i++)
{
    fout << output[i] << endl;
}

fin.close();
fout.close();
}
