#ifndef LINKEDLISTS_H
#define LINKEDLISTS_H

#include <iostream>
#include <string>
using namespace std;

template <typename T>
struct node {
    T word;
    node<T>* next;  //was this declared correctly??
};

template <typename T>
class LinkedLists{
    private:    
        node<T>* head; //find out how to get it to match with list
        node<T>* tail;
    public:
        LinkedLists();
        void removeHead();    //if it detects head, will either remove or add here
        void removeTail();    //if it detects tail, will either remove or add here
        void addAtEnd(T);
        void addAtBeg(T);
        bool isEmpty();
        void print(ofstream&);
        ~LinkedLists();
};

#endif