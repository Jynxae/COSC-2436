#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "list.h"
using namespace std;

list::list()
{
  front = rear = nullptr;
}

void list::enqueue(string in)
{
  node *temp = new node;
  temp->data = in;
  temp->next = nullptr;
  if (isempty())
  {
    front = rear = temp;
    return;
  }
  rear->next = temp;
  rear = temp;
}

void list::dequeue()
{
  if (!isempty())
  {
    node *temp = front;
    front = front->next;
    delete temp;
  }
}

void list::priorityQueue(string in, int pri)
{
  node *temp = new node();
  temp->data = in;
  temp->priority = pri;
  temp->next = nullptr;

  if (isempty())
  {
    front = temp;
    rear = temp;
  }
  else
  {
    node *cu = front;
    node *prev = nullptr;
    if (temp->priority < cu->priority)
    {
      temp->next = front;
      front = temp;
    }
    else
    {
      while (cu != nullptr && temp->priority >= cu->priority)
      {
        prev = cu;
        cu = cu->next;
      }
      prev->next = temp;
      temp->next = cu;
      if (temp->next == nullptr)
        rear = temp;
    }
  }
}

string list::replace(string code, string find, string rep)
{
  for (int i = 0; i < code.length(); i++)
  {
    if (code[i] == find[0])
    {
      code[i] = rep[0];
    }
  }
  return code;
}

string list::add(string code, string find, string ad)
{
  for (int i = 0; i < code.length(); i++)
  {
    if (code[i] == find[0])
    {
      code.insert(i + 1, ad); // double check position???
    }
  }
  return code;
}

string list::removeChar(string code, string rem)
{
  char letter = rem[0];
  code.erase(remove(code.begin(), code.end(), letter), code.end());
  return code;
}

string list::swap(string code, string find, string sw)
{
  for (int i = 0; i < code.length(); i++)
  {
    if (code[i] == find[0])
    {
      code[i] = sw[0];
    }
    else if (code[i] == sw[0])
    {
      code[i] = find[0];
    }
  }
  return code;
}

void list::InOrder(node *root, ofstream& fout)
{
  if (!root)
  {
    return;
  }
  InOrder(root->left, fout);
  fout << root->data << endl;
  InOrder(root->right, fout);
}

void list::PreOrder(node *root, ofstream& fout)
{
  if (!root)
  {
    return;
  }
  fout << root->data << endl;
  PreOrder(root->left, fout);
  PreOrder(root->right, fout);
}

void list::PostOrder(node *root, ofstream& fout)
{
  if (!root)
  {
    return;
  }
  PostOrder(root->left, fout);
  PostOrder(root->right, fout);
  fout << root->data << endl;
}

node *list::getNewNode(string data)
{
  node *newNode = new node();
  newNode->data = data;
  newNode->left = newNode->right = NULL;
  return newNode;
}

node *list::insert(node *root, string in)
{
  if (root == NULL) // if the tree is empty
  {
    root = getNewNode(in);
  }

  if (in.length() > root->data.length()) // does .length() work here???
  {
    root->right = insert(root->right, in);
  }

  else if (in.length() < root->data.length())
  {
    root->left = insert(root->left, in);
  }

  else if (in.length() == root->data.length() && in != root->data)
  {
    root->data = in;
  }

  return root;
}

bool list::isempty()
{
  return front == nullptr;
}

string list::getFront()
{
  if (!isempty())
    return front->data;
  return "";
}

void list::print()
{
  while (front != nullptr)
  {
    cout << front->data << endl;
    front = front->next;
  }
}