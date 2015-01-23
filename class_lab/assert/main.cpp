/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 6, 2015, 6:05 PM
    Purpose: template
 */

//Define NDEBUG to disable all assertions.
#define NDEBUG
#include <cassert>

//System Libraries
#include <iostream>
using namespace std;

//User Libraries
//Global Constants
//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv)
{
  assert(1 > 0);
  cout << "1 was greater than 0! tautology." << endl;
  
  assert(0 > 1);
  cout << "What, zero is not greater than one! Assertions must be turned off by #define NDEBUG!" << endl;
	
  return 0;
}
