#include <iostream>
#include <fstream>

using namespace std;

struct node
{
    string data;
    double priority;
    node *next;
};

class queueLL
{
private:
    node *front;
    node *back;

public:
    queueLL()
    {
        front = back = NULL;
    }

    void enqueue(string input, double pri)
    {
        node *temp = new node;
        temp->data = input;
        temp->priority = pri;
        temp->next = NULL;

        if (isEmpty())  //if empty, first spot
        {
            front = back = temp;
            return;
        }

        if(front->priority > pri)   //checks the head first
        {
            temp->next = front;
            front = temp;
        }

        else{
            node*head = front;
            //node* prev = nullptr;
            while(head->next != NULL && head->next->priority <= pri) //makes sure the spot after is null and checks priority
            {
                //prev = head;
                head = head->next;
            }
            //prev->next = temp;
            //temp->next = head;
            temp->next = head->next;
            head->next = temp;  //if it has lowest priority, it will go here
        }

    }

    void deQueue()
    {
        // If queue is empty, return NULL.
        if (isEmpty())
            return;

        // Store previous front and
        // move front one node ahead
        node *temp = front;
        front = front->next;

        // If front becomes NULL, then
        // change rear also as NULL
        if (front == NULL)
            back = NULL;

        delete (temp);
    }

    void print(ofstream& fout)
    {
        while(front != nullptr )
        {
            int pos = front->data.rfind(" ");
            string line = front->data.substr(0, pos);
            fout << line << endl;
            front = front->next;
        }
    }

    bool isEmpty()
    {
        return front == NULL;
    }
};