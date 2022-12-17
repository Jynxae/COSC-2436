#include <iostream>
#include "List.h"
#include <fstream>
using namespace std;

List::List(){
    head = nullptr;
    size = 0;
}

List::~List(){
    node* cu = head;
    while(cu != nullptr)
    {
        node* temp = cu;
        cu = cu->next;
        delete temp;
    }
}

bool List::isEmpty()
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

void List::addAtEnd(int isID, string isUser, int isScore, char isGrade) //fixed
{
    if (isEmpty())
    {
        head = new node;
        head->id = isID;
        head->user = isUser;
        head->score = isScore;
        head->grade = isGrade;
        head->next = nullptr;
        size++; //would probably need to take out again lol
    }


    else
    {
        node *temp = new node;
        node *prev = new node;
        temp->id = isID;
        temp->user = isUser;
        temp->score = isScore;
        temp->grade = isGrade;
        temp->next = nullptr;
        node *cu = head;

        while (cu->next != nullptr)
        {
            if(cu->user == temp->user && cu->id != temp->id) //checks for same user but diff id
            {
                return;
            }
            else if(cu->user != temp->user && cu->id == temp->id) //FIGURE OUT HERE HOW TO UPDATE THE DUPLICATE
            {
                cu->user = temp->user;
                cu->grade = temp->grade;
                cu->id = temp->id;
                prev = cu->next;
                cu ->next = cu->next->next;
                free(prev);
            }
            cu = cu->next;
        }

        cu->next = temp;//delete temp;  this caused an infinite loop somehow??? lmao
        size++;
    }
}

void List::Add(int pos, int isID, string isUser, int isScore, char isGrade) //adding from a certain position, change the parameteres to the same thing as addatend
{
    node *temp = new node;
    node *dup = new node;
    temp->id = isID;
    temp->user = isUser;
    temp->score = isScore;
    temp->grade = isGrade;
    temp->next = nullptr;

    node *cu = head;
    while(cu != nullptr)
    {
        if(cu->user == temp->user && cu->id != temp->id)
        {
            return;
        }
        //can add else if here to change if id matches too
        cu=cu->next;
    }
    cu = head;
    node *prev = nullptr;
    if (pos > getSize()) //if position is higher than the size, dont add anything
        return;
    else if (pos == 0) //if position equals zero, make it the new head
    {
        head = temp;
        temp->next = cu;
    }
    else if (pos == size) //if position and size are equal, add it to the end
    {
        while (cu->next != nullptr)
        {
            cu = cu->next;
        }

        cu->next = temp;
        //delete temp; //could possibly delete??
    }
    else // add it into whatever position it was marked as
    {
        for (int i = 0; i < pos; i++)
        {
            prev = cu;
            cu = cu->next;
        }
        node *holder = cu;
        prev->next = temp; // org
        temp->next = cu;
        //add a delete here??
    }
    size++;
}

bool List::isDuplicateID(int isID, string isUser, int isScore, char isGrade) //MATCHING ID SHOULD BE UPDATED WITH NEW INFO
{                                                                           //MATCHING USERNAME WITH NO ID MATCH SHOULD BE IGNORED
    node* temp = new node;
    node* cu = head;
    temp->id = isID;
    temp->user = isUser;
    temp->score = isScore;
    temp->grade = isGrade;
    temp->next = nullptr;

    if(cu == nullptr)
    {
        return false;
    }

    while(cu != nullptr)
    {
        if(cu->id == temp->id)
        {
            cu->user = temp->user;
            cu->score = temp->score;
            cu->grade = temp->grade;    
            return true;
        }
        cu = cu->next;
    }
    return false;
}

bool List::isDuplicateUser(int isID, string isUser, int isScore, char isGrade) //MATCHING ID SHOULD BE UPDATED WITH NEW INFO
{                                                                           //MATCHING USERNAME WITH NO ID MATCH SHOULD BE IGNORED
    node* temp = new node;
    node* cu = head;
    temp->id = isID;
    temp->user = isUser;
    temp->score = isScore;
    temp->grade = isGrade;
    temp->next = nullptr;

    if(cu == nullptr)
    {
        return false;
    }
    if(cu->next == nullptr)
    {
        return false;
    }

    while(cu != nullptr)
    {
        if(cu->user == temp->user && cu->id != temp->id)
        {
            return true;
        }
        cu = cu->next;
    }
    return false;
}

void List::Remove(string value, string attribute)   //fixed
{
    node* cu = head;
    node* prev = new node;

    if(cu->next == nullptr) //if there is only one line, it will go through this instead;
    {
        if(attribute == "username" || attribute == "score" || attribute == "id" || attribute == "grade")
        {
            free(head);
        }
        head = nullptr;
        size--;
        return; //no need to go through the while loop if the size is only one

    }

    if(attribute == "username")     //ONLY FOR THE HEAD!!isnt there a better way to check???
        {
            if(cu->user == value) //connects before and after together.
            {
                prev = head;
                head = head->next;
                delete prev;
                size--;
                Remove(value, attribute);
                return;
            }
        }
    else if(attribute == "id")
        {
            if(cu->id == stoi(value)) //AFTER REGRADE, ORG cu->next->id
            {
                prev = head;
                head = head->next;
                delete prev;
                size--;
                Remove(value, attribute);
                return;
            }
        }
    else if(attribute == "score")
        {
            if(cu->score == stoi(value))
            {
                prev = head;
                head = head->next;
                delete prev;
                size--;
                Remove(value, attribute);
                return;
            }
        }
    else if(attribute == "grade")
        {
            if(cu->grade == value[0])
            {
                prev = head;
                head = head->next;
                delete prev;
                size--;
                Remove(value, attribute);
                return;
            }
        }

    while(cu->next != nullptr)  //FOR REGRADE, I TOOK OUT ->NEXT?? HOPEFULLY WORK??
    {
        if(attribute == "username")
        {
            if(cu->next->user == value) //connects before and after together.
            {
                prev = cu->next;
                cu ->next = cu->next->next;
                free(prev);
                Remove(value, attribute); //AFTER REGRADE, this caused no input to come out cause i already freed the variable, why am i removing it again???
                size--;
                break;
            }
        }
        else if(attribute == "id")
        {
            if(cu->next->id == stoi(value)) //AFTER REGRADE, ORG cu->next->id
            {
                prev = cu->next;
                cu ->next = cu->next->next;
                free(prev);
                Remove(value, attribute); //if it causes problems, delete this
                size--;
                break;
            }
        }
        else if(attribute == "score")
        {
            if(cu->next->score == stoi(value))
            {
                prev = cu->next;
                cu ->next = cu->next->next;
                free(prev);
                Remove(value, attribute);
                size--;
                break;
            }
        }
        else if(attribute == "grade")
        {
            if(cu->next->grade == value[0])
            {
                prev = cu->next;
                cu ->next = cu->next->next;
                free(prev);
                Remove(value, attribute);
                size--;
                break;
            }
        }
        cu = cu->next;
    }
}

void List::Sort(string attribute)
{
    node *cu = head;
    node *index = nullptr;
    node *temp = new node;
    bool sorthis = false;

    if (head == nullptr)
    {
        return;
    }
    else if(attribute == "id")
    {
        while (!sorthis)
        {
            cu = head;
            sorthis = true;
            while (cu->next != nullptr) // index!=nullptr
            {
                // If current node's data is greater than index's node data, swap the data between them
                if (cu->id > cu->next->id) // org >
                {
                    temp->id = cu->id;
                    temp->user = cu->user;
                    temp->score = cu->score;
                    temp->grade = cu->grade;

                    cu->id = cu->next->id;
                    cu->grade = cu->next->grade;
                    cu->user = cu->next->user;
                    cu->score = cu->next->score;

                    cu->next->id = temp->id;
                    cu->next->user = temp->user;
                    cu->next->grade = temp->grade;
                    cu->next->score = temp->score;

                    sorthis = false;
                }
                cu = cu->next;
            }
        }
    }

    else if(attribute == "username")
    {
        while (!sorthis)
        {
            cu = head;
            sorthis = true;
            while (cu->next != nullptr) // index!=nullptr
            {
                // If current node's data is greater than index's node data, swap the data between them
                if (cu->user > cu->next->user) // org >
                {
                    temp->id = cu->id;
                    temp->user = cu->user;
                    temp->score = cu->score;
                    temp->grade = cu->grade;

                    cu->id = cu->next->id;
                    cu->grade = cu->next->grade;
                    cu->user = cu->next->user;
                    cu->score = cu->next->score;

                    cu->next->id = temp->id;
                    cu->next->user = temp->user;
                    cu->next->grade = temp->grade;
                    cu->next->score = temp->score;

                    sorthis = false;
                }
                cu = cu->next;
            }
        }
    }

    else if(attribute == "grade")
    {
        // Node index will point to node next to current
        while (!sorthis)
        {
            cu = head;
            sorthis = true;
            while (cu->next != nullptr) // index!=nullptr
            {
                // If current node's data is greater than index's node data, swap the data between them
                if (cu->grade > cu->next->grade) // org >
                {
                    temp->id = cu->id;
                    temp->user = cu->user;
                    temp->score = cu->score;
                    temp->grade = cu->grade;

                    cu->id = cu->next->id;
                    cu->grade = cu->next->grade;
                    cu->user = cu->next->user;
                    cu->score = cu->next->score;

                    cu->next->id = temp->id;
                    cu->next->user = temp->user;
                    cu->next->grade = temp->grade;
                    cu->next->score = temp->score;

                    sorthis = false;
                }
                cu = cu->next;
            }
        }
    }

    else if (attribute == "score")
    {
        // Node index will point to node next to current
        while (!sorthis)
        {
            cu = head;
            sorthis = true;
            while (cu->next != nullptr) // index!=nullptr
            {
                // If current node's data is greater than index's node data, swap the data between them
                if (cu->score < cu->next->score) // org >
                {
                    temp->id = cu->id;
                    temp->user = cu->user;
                    temp->score = cu->score;
                    temp->grade = cu->grade;

                    cu->id = cu->next->id;
                    cu->grade = cu->next->grade;
                    cu->user = cu->next->user;
                    cu->score = cu->next->score;

                    cu->next->id = temp->id;
                    cu->next->user = temp->user;
                    cu->next->grade = temp->grade;
                    cu->next->score = temp->score;

                    sorthis = false;
                }
                cu = cu->next;
            }
        }
    }
}

void List::print(ofstream &fout)
{
    node *cu = head;
    while (cu != nullptr)
    {
        if(cu->next == nullptr)
        {
            fout << "[id:" << cu->id << ";" << "username:" << cu->user << ";" << "score:" << cu->score << ";" << "grade:" << cu->grade << "]";
            break;
        }
        fout << "[id:" << cu->id << ";" << "username:" << cu->user << ";" << "score:" << cu->score << ";" << "grade:" << cu->grade << "]" << endl;
        cu = cu->next;   
    }
}