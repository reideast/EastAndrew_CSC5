/* 
 * File:   main.cpp
 * Author: rcc
 *
 * Created on January 13, 2015, 6:35 PM
 */

 //sytem lib
#include <iostream>
using namespace std;

//global constants

//user function definitions
void printRow(bool x, bool y); //prints a row of the truth table
void printTF(bool expr); //prints 'T' or 'F' with exactly 7 spaces after

void swapTemp(int* a, int* b);
void swapBitwise(int* a, int* b);
void swapBitwise(char* a, char* b);

int main(int argc, char** argv)
{  
  //header (each column is 8 char, 13 columns)
  cout << "Print a Boolean truth table:" << endl;
  cout << "x       y       !x      !y      x&&y    x||y    x^y     x^y^y   x^y^x   !(x||y) !x&&!y  !(x&&y) !x||!y  " << endl;
  printRow(true, true);
  printRow(true, false);
  printRow(false, true);
  printRow(false, false);
  
  cout << "Test temp variable swap:" << endl;
  int a = 2, b = 3;
  cout << "a = " << a << ", b = " << b << endl;
  swapTemp(&a, &b);
  cout << "a = " << a << ", b = " << b << endl;
  cout << endl;
  
  cout << "Test bitwise swap:" << endl;
  a = 2, b = 3;
  cout << "a = " << a << ", b = " << b << endl;
  swapBitwise(&a, &b);
  cout << "a = " << a << ", b = " << b << endl;
  cout << endl;
  
  cout << "Test bitwise swap using char:" << endl;
  char c = 2, d = 3;
  cout << "c = " << (int) c << ", d = " << (int) d << endl;
  swapBitwise(&c, &d);
  cout << "c = " << static_cast<int>(c) << ", d = " << static_cast<int>(d) << endl;
  cout << endl;
  
  return 0;
}

void swapTemp(int* a, int* b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void swapBitwise(int* a, int* b)
{
  *a = *a ^ *b;
  *b = *a ^ *b;
  *a = *a ^ *b;
}

void swapBitwise(char* a, char* b)
{
  *a = *a ^ *b;
  *b = *a ^ *b;
  *a = *a ^ *b;
}

void printRow(bool x, bool y)
{
  printTF(x);
  printTF(y);
  printTF(!x);
  printTF(!y);
  printTF(x && y);
  printTF(x || y);
  printTF(x ^ y);
  printTF(x ^ y ^ y);
  printTF(x ^ y ^ x);
  printTF(!(x || y));
  printTF(!x && !y);
  printTF(!(x && y));
  printTF(!x || !y);
  cout << endl;
}

void printTF(bool expr)
{
  cout << (expr ? 'T' : 'F') << "       ";
}
