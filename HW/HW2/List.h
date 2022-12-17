#include <iostream>
#include <string>
using namespace std;

struct node{
    int id;
    string user;
    int score;
    char grade; 
    node *next;
};

class List{
private:
    node *head;
    int size;
public:
    List();
    ~List();
    void addAtEnd(int, string, int, char);
    bool isEmpty();
    void Add(int, int, string, int, char);
    void Remove(string, string);
    void Sort(string);
    int getSize(){return size;}
    void print(ofstream&);
    bool isDuplicateID(int, string, int, char);
    bool isDuplicateUser(int, string, int, char);
};