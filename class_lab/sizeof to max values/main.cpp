/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 6, 2015, 6:05 PM
    Purpose: template
 */

//System Libraries
#include <iostream>
#include <limits>
using namespace std;

//User Libraries
//Global Constants
//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv)
{
  cout << "sizeof(int):" << sizeof(int) << " bytes" << endl;
  //from: http://stackoverflow.com/questions/357629/how-do-you-find-the-range-of-values-that-integer-types-can-represent-in-c
  //as I understand it, it puts a 1 in the two's complement spot of an int (the highest bit position) sort of like: 1000 0000 (for a 1-byte int), and then binary NOT the whole thing, giving 0111 1111 for a 1-byte int
  cout << "upper (int):" << ~(1 << (sizeof(int) * 8) - 1) << endl;
  cout << "lower (int):" << (1 << (sizeof(int) * 8) - 1) << endl;
  cout << "upper (int) limits library:" << numeric_limits<int>::max() << endl;
  cout << "lower (int) limits library:" << numeric_limits<int>::min() << endl;
  cout << "upper (unsigned int) limits library:" << numeric_limits<unsigned int>::max() << endl;
  cout << "lower (unsigned int) limits library:" << numeric_limits<unsigned int>::min() << endl;
  cout << "upper (float) limits library:" << numeric_limits<float>::max() << endl;
  cout << "lower (float) limits library:" << numeric_limits<float>::min() << endl;
  return 0;
}
