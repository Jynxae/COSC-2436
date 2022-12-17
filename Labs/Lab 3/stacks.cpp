#include <iostream>
#include <string>
#include "stacks.h"
#include <stack>
using namespace std;

string stacks::makePostFix(string line)
{
  stack<char> st;
  string result = "";

  for (int i = 0; i < line.length(); i++)
  {
    if (line[i] >= '0' && line[i] <= '9')
      result += line[i];

    else if (line[i] == '(')
      st.push('(');

    else if (line[i] == ')')
    {
      while (st.top() != '(')
      {
        result += st.top();
        st.pop();
      }
      st.pop();
    }

    else
    {
      while (!st.empty() && precedent(line[i]) <= precedent(st.top()))
      {
        result += st.top();
        st.pop();
      }
      st.push(line[i]);
    }
  }

  while (!st.empty())
  {
    result += st.top();
    st.pop();
  }
  return result;
}

int stacks::precedent(char x)
{
  if (x == '/' || x == '*')
    return 2;
  else if (x == '+' || x == '-')
    return 1;
  else
    return 0;
}

double stacks::evaluate(string s, string expression) {
  stack<double> st;

  for (int i=0; i<s.length(); i++) {
    if (s[i] >= '0' && s[i] <= '9')
      st.push(s[i] - '0');
    else {
      double val1 = st.top(); 
      st.pop();
      if(st.empty())
      {
        int xpos = s.find('x');
        int eqpos = s.find('=');
        double res = stod(s.substr(xpos+1, eqpos-1));
        if(s[i] == '*'){
            st.push(res / val1);
        }
        else if(s[i] == '/'){
          if(expression[expression.length()-3] == 'x' || expression[expression.length()-4] == 'x')
          {
            st.push(val1 / res);
          }
          else{
          st.push(res * val1);
          }

        }
        else if(s[i] == '+')
        {
          st.push(res - val1);
        }
        else if(s[i] == '-')
        {
          if(expression[expression.length()-3] == 'x' || expression[expression.length()-4] == 'x' )
          {
            st.push((res - val1)/-1);
          }
          else{
          st.push(res + val1);
          }
        }
        return st.top();
      }
      double val2 = st.top(); 
      st.pop();
      switch (s[i]) {
        case '+': st.push(val2 + val1); break;
        case '-': st.push(val2 - val1); break;
        case '*': st.push(val2 * val1); break;
        case '/': st.push(val2 / val1); break;
      }
    }
  }
  return st.top();
}