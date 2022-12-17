#include "ArgumentManager.h"
#include "Queue.h"
#include "Stack.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool isSolved(vector<vector<char>> matrix, size_t row, size_t col)
{
  for(size_t i = 0; i < row; i++)
  {
    for(size_t j = 0; j < col; j++)
    {
      if(matrix[i][j] == 'B')
      {
        return false;
      }
    }
  }
  return true;
}

void moveUp(vector<vector<char>> &matrix, size_t row, size_t col)
{
  Stack s;
  int counter = 0;
  char temp;
  for (int j = 0; j < col; j++)
  {
    for (int i = 0; i < row; i++)
    {
      if (matrix[i][j] != 'O' && matrix[i][j] != 'X')
      {
        if (!s.isEmpty() && s.peek() == 'B')
        {
          temp = s.pop();
          s.push('X');
        }

        else
        {
          s.push(matrix[i][j]);
        }
      }
      else if(matrix[i][j] == 'X')
      {
        while(s.getSize() < counter)
        {
          s.push('O');
        }
        s.push('X');
      }
      counter++;
    }
    while (s.getSize() < counter)
    {
      s.push('O');
    }

    for(int i = row-1; i >= 0; i--)
    {
      matrix[i][j] = s.pop();
    }
    counter = 0;
  }
}

void moveDown(vector<vector<char>> &matrix, size_t row, size_t col)
{
  Stack s;
  int counter = 0;
  char temp;
  for (int j = col-1; j >= 0; j--)  //for left and right, figure what need to change for this ***
  {
    for (int i = row-1; i >= 0; i--)  //*******
    {
      if (matrix[i][j] != 'O' && matrix[i][j] != 'X')
      {
        if (!s.isEmpty() && s.peek() == 'B')
        {
          temp = s.pop();
          s.push('X');
        }

        else
        {
          s.push(matrix[i][j]);
        }
      }
      else if(matrix[i][j] == 'X')
      {
        while(s.getSize() < counter)
        {
          s.push('O');
        }
        s.push('X');
      }
      counter++;
    }
    while (s.getSize() < counter)
    {
      s.push('O');
    }

    for(int i = 0; i < row; i++)  //******
    {
      matrix[i][j] = s.pop();
    }
    counter = 0;
  }
}

void moveLeft(vector<vector<char>> &matrix, size_t row, size_t col)
{
  Stack s;
  int counter = 0;
  char temp;
  for (int j = 0; j < row; j++) //switched col for row
  {
    for (int i = 0; i < col; i++) //switched row for col
    {
      if (matrix[j][i] != 'O' && matrix[j][i] != 'X') //switch the spots so it goes [0,0] [0,1] [0,2] instead
      {
        if (!s.isEmpty() && s.peek() == 'B')
        {
          temp = s.pop();
          s.push('X');
        }

        else
        {
          s.push(matrix[j][i]);
        }
      }
      else if(matrix[j][i] == 'X')
      {
        while(s.getSize() < counter)
        {
          s.push('O');
        }
        s.push('X');
      }
      counter++;
    }
    while (s.getSize() < counter)
    {
      s.push('O');
    }

    for(int i = col-1; i >= 0; i--) //was org row-1
    {
      matrix[j][i] = s.pop();
    }
    counter = 0;
  }
}

void moveRight(vector<vector<char>> &matrix, size_t row, size_t col)
{
  Stack s;
  int counter = 0;
  char temp;
  for (int j = row-1; j >= 0; j--)  //swtiched col for row
  {
    for (int i = col-1; i >= 0; i--)  //switched row for col
    {
      if (matrix[j][i] != 'O' && matrix[j][i] != 'X') //PROBABLY NEED TO SWITCH UP THE SPOTS
      {
        if (!s.isEmpty() && s.peek() == 'B')
        {
          temp = s.pop();
          s.push('X');
        }

        else
        {
          s.push(matrix[j][i]);
        }
      }
      else if(matrix[j][i] == 'X')
      {
        while(s.getSize() < counter)
        {
          s.push('O');
        }
        s.push('X');
      }
      counter++;
    }
    while (s.getSize() < counter)
    {
      s.push('O');
    }

    for(int i = 0; i < col; i++)  //was org row
    {
      matrix[j][i] = s.pop();
    }
    counter = 0;
  }
}

void addPath(Queue &q, Pair p, int move, size_t row, size_t col)
{
  Pair temp;
  temp.matrix = p.matrix;
  temp.moves = p.moves;
  switch (move){
    case 1:
      moveUp(temp.matrix, row, col);
      if(temp.matrix != p.matrix)
      {
        temp.moves += "1";
        q.enqueue(temp);
      }
    break;
    case 2:
      moveRight(temp.matrix, row, col);
      if(temp.matrix != p.matrix)
      {
        temp.moves += "2";
        q.enqueue(temp);
      }
    break;
    case 3:
      moveDown(temp.matrix, row, col);
      if(temp.matrix != p.matrix)
      {
        temp.moves += "3";
        q.enqueue(temp);
      }
    break;
    case 4:
      moveLeft(temp.matrix, row, col);
      if(temp.matrix != p.matrix)
      {
        temp.moves += "4";
        q.enqueue(temp);
      }
    break;
  }
}

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream output(am.get("output"));

  //ifstream input("input1.txt");
  //ofstream output("output1.txt");

  size_t row;
  size_t col;
  input >> row; // input row
  input >> col; // input column

  vector<vector<char>> matrix; // input matrix

  // reading the matrix from the input
  for (int i = 0; i < row; i++) {
    vector<char> temp;
    for (int j = 0; j < col; j++) {
      char c;
      input >> c;
      temp.push_back(c);
    }
    matrix.push_back(temp);
  }

  Pair temp;
  temp.matrix = matrix;
  temp.moves = "";

  Queue q;
  q.enqueue(temp);

  while(!q.isEmpty())
  {
    temp = q.dequeue();
    if(isSolved(temp.matrix, row, col))
    {
      if(temp.moves == "")
      {
        cout << "0";
      }
      else{
        cout << temp.moves;
        break;
      }
    }
    else
    {
      addPath(q, temp, 1, row, col);
      addPath(q, temp, 2, row, col);
      addPath(q, temp, 3, row, col);
      addPath(q, temp, 4, row, col);

    }
  }
  return 0;
}
