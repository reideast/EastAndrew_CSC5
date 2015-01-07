/* 
   File:   main.cpp
   Author: Andrew Reid East
   Created on January 6, 2015, 6:05 PM
   Purpose: Our first program
   I am up at github now!
 */

//System Libraries
#include <iostream>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes

//Execution Begins Here!
int main(int argc, char** argv)
{
    //Output Hello World
    cout << "Hello world!" << endl << endl;
    
    bool isProgramError = false;
    int userChoice = 0;
    
    cout << "Do you want the program to work? (1 for yes, 0 for no (or any string to mess things up, uhh)) ";
    cin >> userChoice;
    
    if (userChoice == 1)
        isProgramError = false;
    else if (userChoice == 0)
        isProgramError = true;
    else
    {
        cout << "Your input was not valid." << endl << "I'm going to fail the program out of spite." << endl;
        isProgramError = true;
    }
    
    return isProgramError;
}

