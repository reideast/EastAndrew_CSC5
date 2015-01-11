/* 
   File:   main.cpp
   Author: Andrew Reid East
   Class: CSC-5 40718
   Created on January 10, 2015, 6:08 PM
   Purpose: Calculate the average of five values
 */
 
//System Libraries
#include <iostream>
using namespace std;

//User Libraries
//Global Constants
//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv)
{
    //create variables
    int value1 = 28, value2 = 32, value3 = 37, value4 = 24, value5 = 33;
    int sum = 0;
    float avg = 0.0f;
    
    //do calculations
    sum = value1 + value2 + value3 + value4 + value5;
    avg = sum / 5.0f;
    
    //show formatted output
    cout << "The average of " << value1 << ", " << value2 << ", "
         << value3 << ", " << value4 << ", and " << value5
         << " is " << avg << endl;
    
    return 0;
}

