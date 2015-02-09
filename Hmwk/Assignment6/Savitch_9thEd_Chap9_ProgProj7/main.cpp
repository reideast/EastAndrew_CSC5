/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on February 8, 2015, 5:32 PM
    Purpose: Demonstrate 2-dimensional array mechanics using 1-dimensional dynamic array
 */

//System Libraries
#include <iostream>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes
int* create2DArray(int rows, int columns);
void set(int *arr, int rows, int columns, int desired_row, int desired_column, int val);
int get(int *arr, int rows, int columns, int desired_row, int desired_column);

void fill2DArray(int *arr, int rows, int columns);

void print2DArray(int *arr, int rows, int columns);


//Execution Begins Here
int main(int argc, char** argv)
{
  int rows = 3, cols = 4;
  int *arr = create2DArray(rows, cols);
  
  print2DArray(arr, rows, cols);
  cout << endl;
  
  fill2DArray(arr, rows, cols);
  print2DArray(arr, rows, cols);
  cout << endl;
  
  set(arr, rows, cols, 1, 1, 42);
  print2DArray(arr, rows, cols);
  cout << endl;
  
  cout << "The item at index (1, 1) is: " << get(arr, rows, cols, 1, 1) << endl;
  
  return 0;
}

int* create2DArray(int rows, int columns)
{
  return new int[rows * columns];
}

void set(int *arr, int rows, int columns, int desired_row, int desired_column, int val)
{
  if (desired_row >= rows || desired_row < 0)
  {
    cout << "Invalid row index requested." << endl;
    return;
  }
  if (desired_column >= columns || desired_column < 0)
  {
    cout << "Invalid column index requested." << endl;
    return;
  }

  *(arr + (desired_row * columns + desired_column)) = val;
}

int get(int *arr, int rows, int columns, int desired_row, int desired_column)
{
  if (desired_row >= rows || desired_row < 0)
  {
    cout << "Invalid row index requested." << endl;
    return -1;
  }
  if (desired_column >= columns || desired_column < 0)
  {
    cout << "Invalid column index requested." << endl;
    return -1;
  }
  
  return *(arr + (desired_row * columns + desired_column));
}

void fill2DArray(int *arr, int rows, int columns)
{
  int count = 1;
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < columns; ++j)
      set(arr, rows, columns, i, j, count++);
}


void print2DArray(int *arr, int rows, int columns)
{
  for (int i = 0; i < rows; ++i)
  {
    cout << '{';
    for (int j = 0; j < columns; ++j)
    {
      cout << get(arr, rows, columns, i, j) << ((j == columns - 1) ? "" : ", ");
    }
    cout << '}' << endl;
  }
}
