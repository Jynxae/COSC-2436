#include<iostream>
using namespace std;

struct node{
    string data;
    int priority;
    node* left;
    node* right;
    node* next;
};

class list{
private:
    node *front;
    node *rear;

public:
    list();
    void enqueue(string);  
    void dequeue();
    void priorityQueue(string, int);
    string replace(string, string, string);
    string add(string, string, string);
    string removeChar(string, string);
    string swap(string, string, string);
    void InOrder(node*, ofstream&);
    void PostOrder(node*, ofstream&);
    void PreOrder(node*, ofstream&);
    bool isempty();
    string getFront();
    void print();
    node* insert(node*, string);
    node* getNewNode(string);
};