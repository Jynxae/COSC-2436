#include <iostream>
#include "ArgumentManager.h"
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

// CODE PROVIDED BY LAB TAs FOR HW5

struct node
{
    int *keys;
    node **childptr;
    bool leaf;
    int size;

    node(int degree)
    {
        keys = new int[degree];
        childptr = new node *[degree + 1];
        leaf = true;
        size = 0;

        for (int i = 0; i < degree; i++)
        {
            keys[i] = -1;
        }

        for (int i = 0; i < degree + 1; i++)
        {
            childptr[i] = nullptr;
        }
    }
    void splitChild(node *parent, int degree);
    void print(node* node, int level, ofstream& fout, int height);
    node* addAtLeaf(node *n, int data,int degree, node* root);
    int height(node* n);//, int h, int& result);
     void height(node*temp,int height,int& result);

    friend class btree;
};

class bTree
{
private:
    node *root;
    int degree;
    bool isDup = false;
    vector<int> dup;

public:
    bTree(int _degree)
    {
        root = nullptr;
        degree = _degree;
    }

    void insert(int data)
    {
        if (root == nullptr)
        {
            dup.push_back(data);
            root = new node(degree);
            root->leaf= true;
            root->keys[0] = data;
            root->size = 1;
        }

        else
        {
            for (int i = 0; i < dup.size(); i++)
            {
                if (data == dup.at(i))
                {
                    isDup = true;
                }
            }

            if (!isDup)
            {
                root = root->addAtLeaf(root, data, degree, root); // org did = root
                dup.push_back(data);
            }
            isDup = false;
        }
           //org no return
    }

    void printLevel(int level, ofstream& fout,int height){
        root->print(root,level, fout,height);
    }

    int height(){
        int result;
        root->height(root,1,result);
        return result;
    }

    node* getRoot()
    {
        return root;
    }
};
    void node:: height(node*temp, int h,int& result){
             if(this->leaf || temp == nullptr){
                result=h;
                return;
                
            }
            childptr[0]->height(temp,h+1,result);
        }


    node* node::addAtLeaf(node *n, int data, int degree, node* root)    //was org void
    {
        if (leaf)    //if there was no children  doesnt print if it isnt n->leaf, but leaf seems to help get 81 to go through this statement
        {
            
            int i = size;

            while (i != 0 && keys[i - 1] > data) // will find the correct position to add in the array
            {
                keys[i] = keys[i - 1];
                i--;
            }

            keys[i] = data;
            size = size + 1;
        }

        else    //goes here if it has children
        {
            int i = 0;
            while (i < size && data > keys[i])
            {
                i++;
            }

            childptr[i]->addAtLeaf(this, data,degree,root); //only problem left is to get this 81 into the other node
        }

        if (size == degree)
        {
            if (this == root)       //WHEN YOU COME BACK, WE TESTING IT WITH THIS CAUSE IT WAS N SO MAYBE THATS WHY, IT SHOULD HAVE GONE TO ELSE
            {
                node *temp = new node(degree);
                temp->leaf = false;
                temp->childptr[0] = this; //n
                temp->splitChild(this,degree);
                return temp;
            }

            else
            {
                n->splitChild(this ,degree);        //SAME WITH THIS ONE TOO^^^^^^^
            }
        }
        return root;
    }

    void node::splitChild(node *parent, int degree)     
    {
        node *rightNode = new node(degree);
        node *leftNode = new node(degree);
        int mid = (degree - 1) / 2;
        int midValue = parent->keys[mid];
        // copy half of left node to right node
        int indexR = 0;
        int indexC = 0;
        int spot = degree-1, correctSpot = degree-1;
        int childPlace = degree/2;
        int parentSize = parent->size;
        for (int i = mid+1; i < parentSize; i++) //PUT <= BACK       creates right node
        {
            rightNode->keys[indexR] = parent->keys[i];
            parent->size--;
            rightNode->size++;
            indexR++;
        }

        for (int i = 0; i < mid; i++)   //creates left node
        {
            leftNode->keys[i] = parent->keys[i];
            leftNode->size++;
        }

        // // check if the node is a leaf node or not, if it is not a leaf node, copy half of the pointer from left node to right node
        if (parent->leaf == false)
        {
            for (int j = childPlace; j <= degree; j++)  //should it be <??  //shifts children
            {
                rightNode->childptr[indexC] = parent->childptr[j];
                indexC++;
            }
            rightNode->leaf = parent->leaf;
            //leftNode->leaf = parent->leaf; //   NOT ORG HERE
        }
        // rightNode->leaf = parent->leaf;
        // leftNode->leaf = parent->leaf;

        while(childptr[spot] != parent)    //making space for kids
        {
            childptr[spot+1] = childptr[spot];
            spot--;
        }
        //childptr[spot] = leftNode;  //NOT ORG HERE
        childptr[spot+1] = rightNode;

        while(keys[correctSpot-1] == -1 && correctSpot != 0)    //helps to avoid the junk values and finds the right spot to start looking
        {
            correctSpot--;
        }

        while(keys[correctSpot-1] > midValue && correctSpot != 0)  //finds the correct spot between all the other values
        {
            keys[correctSpot] = keys[correctSpot-1];
            correctSpot--;
        }
        //correctSpot = 0;        //TAKE THIS OUT LATER
        keys[correctSpot] = midValue;    //places it in the correct spot
        size = size+1;  //children increase here
        parent->size = parent->size - 1; //parent loses one since midValue went up top
        //find the midvalue spot in childptr with a for loop

        //with the another for loop, copy the old array into a new one with no empty spots
    }

    void node::print(node* node, int level, ofstream& fout, int height)
    {
        if (node == nullptr)
        {
            fout << "Empty" << endl;
            return;
        }

        if(level > height)
        {
            fout << "Empty";
            return;
        }
        
        if(leaf && level > 1)
        {
            fout << "Empty";
            return;
        }
        else if(level == 1)
        {
            for(int i = 0; i < size; i++)
            {
                fout << keys[i] << " ";
            }

        }

        else
        {
            for(int i = 0; i <= size; i++)
            {
                childptr[i]->print(this,level-1, fout,height);
            }
        }
    }


int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);

    string infilename = am.get("input");
    string outfilename = am.get("output");
    string commandFile = am.get("command");

    ifstream fin(infilename);
    ofstream fout(outfilename);
    ifstream fread(commandFile);

    // ifstream fin("input6.txt");
    // ifstream fread("command6.txt");
    // ofstream fout("output.txt");

    string coms;
    int num, degree, level = 0;
    vector<int> levels;
    vector<int> dup;
    bool isDup = false;

    while (getline(fread, coms))
    {
        if (coms.find("Degree") != string::npos)
        {
            int spot = coms.find('=');
            degree = stoi(coms.substr(spot + 1));
        }
        if (coms.find("Level") != string::npos)
        {
            int spot = coms.find(' ');
            levels.push_back(stoi(coms.substr(spot + 1)));
        }
    }

    if(degree == 0)     //checks to see if cmd file is empty
    {
        fout << "works";
        return 0;
    }
    

    bTree tree(degree);
    while (fin >> num)
    {
        tree.insert(num);
    }

    node* temp = tree.getRoot();
    if (temp == nullptr)    //if input is empty but there is a cmd file, it runs this
    {
        fout << "Height=0" << endl;
        for (int i = 0; i < levels.size(); i++)
        {
            fout << "Empty";
            fout << endl;
        }
    }

    else if(temp != nullptr)        //if there was input and it passes the command file check, run it normally
    {
        fout << "Height=" << tree.height() << endl;
        int height = tree.height();
        for (int i = 0; i < levels.size(); i++)
        {

            tree.printLevel(levels.at(i), fout, height);
            fout << endl;
        }
    }

    return 0;
}