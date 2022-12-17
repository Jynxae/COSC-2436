#include <iostream>
#include "LinkedLists.h"
#include <fstream>
using namespace std;

template<typename T>
LinkedLists<T>::LinkedLists(){
    head = nullptr;
    tail = 0;
}


template<typename T>
LinkedLists<T>::~LinkedLists()
{
    node<T>* cu = head;
    while(cu != nullptr)
    {
        node<T>* temp = cu;
        cu = cu->next;
        delete temp;
    }
}

template<typename T>
void LinkedLists<T>::removeHead()
{
    if(isEmpty())
    {
        return;
    }
    else{
    node<T> *temp = head;
    head = head->next;
    delete temp;
    }
}

template<typename T>
void LinkedLists<T>::removeTail()
{

    node<T>* cu = head;
    node<T>* prev = nullptr;
    if(cu == nullptr)
    {
        return;
    }
    else if(cu->next == nullptr)
    {
        head = nullptr;
    }
    else{
        while(cu->next != nullptr)
        {
            prev = cu;
            cu = cu->next;
        }
        prev->next = nullptr;   
        delete cu;              //why delete when in previous line, it was set to null??
    }
}

template<typename T>
void LinkedLists<T>::addAtBeg(T input)
{
  if(isEmpty())
  {
    head = new node<T>;
    head->word = input;
    head->next = 0;
  }

  else{
  
    node<T>* temp = new node<T>;
    temp->word = input;
    temp->next = 0;
  
    temp->next = head;
    head = temp; 
  }
  
}

template<typename T>
void LinkedLists<T>::addAtEnd(T input)
{
  if(isEmpty())
  {
    head = new node<T>;
    head->word = input;
    head->next = 0;
  }

  else{
    node<T>* temp = new node<T>;
    temp->word = input;
    temp->next = nullptr;

    node<T> *cu = head;

    while( cu -> next != nullptr)
      {
        cu = cu -> next;
      }

    cu -> next = temp;
    
    //FIX ME: UNCOMMENT AFTER, JUST TESTING
    //if(cu == 0)
    //{
        //head = temp;
    //}
    //else{
        //while(cu->next != nullptr) //was just cu
        //{
        //cu = cu->next;
        //}
        //cu->next = temp;    //this means the value after the current value is currently null, so we will add temp to the next value of curr
    
    }
}


template<typename T>
bool LinkedLists<T>::isEmpty()
{
    if (head == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T>
void LinkedLists<T>::print(ofstream& foute )
{
    node<T> *cu = head;
    while(cu != nullptr)
    {
        if(cu == nullptr)
        {
            foute << cu->word;
        }

        else{
        foute << cu->word << " ";
        cu = cu->next;
        }
    }
}