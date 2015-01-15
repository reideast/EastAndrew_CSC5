/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 13, 2015, 6:35 PM
    Purpose: demonstrate a truth table of two boolean values.
    Also, do a swap using XOR.
    Also, do functions by reference.
    Also, I convert an integer into a string of bits...for some reason.
 */

//System Libraries
#include <iostream>
#include <string>
using namespace std;

//User Libraries
//Global Constants

//Function Prototypes
void printRow(bool x, bool y); //prints a row of the truth table
void printTF(bool expr); //prints 'T' or 'F' with exactly 7 spaces after

void swapTemp(int* a, int* b); //swaps two integers by reference (uses temporary variable)
void swapBitwise(int* a, int* b); //swaps two integers by reference (uses bitwise XOR)
void swapBitwise(char* a, char* b); //testing function overloading??

void printBits(int value, unsigned int precision); //put bits of value to cout, show precision binary digits
string getBits(int value, unsigned int precision); //return a String of binary digits representing value

//Execution Begins Here
int main(int argc, char** argv)
{  
  //header (each column is 8 char, 13 columns)
  cout << "Print a Boolean truth table:" << endl;
  cout << "x       y       !x      !y      x&&y    x||y    x^y     x^y^y   x^y^x   !(x||y) !x&&!y  !(x&&y) !x||!y  " << endl;
  printRow(true, true);
  printRow(true, false);
  printRow(false, true);
  printRow(false, false);
  cout << endl;
  
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
  
  printBits(2, 8);
  cout << endl;
  printBits(2, 4);
  cout << endl;
  printBits(2, 32);
  cout << endl;
  printBits(3, 8);
  cout << endl;
  printBits(19, 8);
  cout << endl;
  printBits(19, 4);
  cout << endl;
  cout << endl;
  
  int test = 2;
  cout << "In binary, " << test << " = " << getBits(test, 8) << endl;
  cout << "In binary, " << test << " = " << getBits(test, 4) << endl;
  cout << "In binary, " << test << " = " << getBits(test, 32) << endl;
  test = 3;
  cout << "In binary, " << test << " = " << getBits(test, 8) << endl;
  test = 19;
  cout << "In binary, " << test << " = " << getBits(test, 8) << endl;
  cout << "In binary, " << test << " = " << getBits(test, 4) << endl;
  cout << endl;
  
  return 0;
}

string getBits(int value, unsigned int precision)
{
  string output;
  
  int mask = 1 << (precision - 1); // 00000001 shifted left to the largest bit requested by precision, ex for 8 = 10000000
  for (int i = 0; i < precision; ++i) //loop once for each bit requested by precision
  {
    //add a space every nibble
    if (!(i % 4) && i) output += ' ';//every four lines: (i % 4) == 0 equiv to !(i % 4), not the first bit: i != 0 equiv to i
    
    output += ((value & mask) ? '1' : '0'); //if bitwise AND with the mask has a value (ie. True), then there is a bit in that position, so output 1
    mask = mask >> 1; //shift right 1. ex: 10000000 -> 01000000, and then 00100000 -> 0001000
  }
  
  return output;
}

//referenced: http://stackoverflow.com/questions/2686542/converting-integer-to-a-bit-representation
void printBits(int value, unsigned int precision)
{
  int mask = 1 << (precision - 1); // 00000001 shifted left to the largest bit requested by precision, ex for 8 = 10000000
  for (int i = 0; i < precision; ++i) //loop once for each bit requested by precision
  {
    //add a space every nibble
    if (!(i % 4) && i) cout << ' ';//every four lines: (i % 4) == 0 equiv to !(i % 4), not the first bit: i != 0 equiv to i
    
    cout << ((value & mask) ? '1' : '0'); //if bitwise AND with the mask has a value (ie. True), then there is a bit in that position, so output 1
    mask = mask >> 1; //shift right 1. ex: 10000000 -> 01000000, and then 00100000 -> 0001000
  }
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
