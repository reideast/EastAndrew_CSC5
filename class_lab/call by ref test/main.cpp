/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 6, 2015, 6:05 PM
    Purpose: template
 */

//System Libraries
#include <iostream>
using namespace std;

//User Libraries
//Global Constants
//Function Prototypes
void swapRef(int& a, int& b); //I didn't realize that you could do by-ref in C++ this way. I wonder why I didn't learn it this way?
void swapPtr(int* a, int* b); //this is how I thought you do by-ref
void output(int, int);

//Execution Begins Here
int main(int argc, char** argv)
{
  int a = 4, b = 5;
  
  output(a, b);
  swapRef(a, b);
  output(a, b);
  swapPtr(&a, &b);
  output(a, b);
  
  return 0;
}

void output(int a, int b)
{
  cout << "a=" << a << ", b=" << b << endl;
}

void swapRef(int& a, int& b)
{
  int temp = a;
  a = b;
  b = temp;
}

void swapPtr(int* a, int* b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}