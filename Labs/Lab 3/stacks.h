#include <iostream>
using namespace std;

class stacks{
    public:
        int precedent(char x);
        string makePostFix(string);
        double evaluate(string, string);
        void print();
};