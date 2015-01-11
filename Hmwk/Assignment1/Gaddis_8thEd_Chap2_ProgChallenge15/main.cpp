/* 
   File:   main.cpp
   Author: Andrew Reid East
   Class: CSC-5 40718
   Created on January 10, 2015, 6:16 PM
   Purpose: Display a triangle pattern
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
    int maxSize = 7; //the number of '*' in the largest row
    int i = 0, j = 0; //loop counters
    
    if (maxSize % 2) //only allow odd numbers
        for (i = 1; i <= maxSize; i += 2) //loop through all odd numbers from 1..maxSize
        {
            //make a number of spaces to center the row
            for (j = (maxSize - i) / 2; j > 0; --j) //max characters minus the number of characters in this row, half (integer divide) will give number of spaces to center
                cout << ' ';
            for (j = 0; j < i; ++j) //loop i times
                cout << '*';

            cout << endl; //new line
        }
    else
        cout << "maxSize should be odd." << endl; //well, now that I think about...my loop condition i <= maxSize when i += 2 still work fine with even numbers.
    
    return 0;
}

//
//1 -> 4
//3 -> 2
//5 -> 1
//7 -> 0
