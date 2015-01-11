/* 
   File:   main.cpp
   Author: Andrew Reid East
	 Class: CSC-5 40718
   Created on January 8, 2015, 4:20 PM
   Purpose: To display a large block letter "C" in a character of your choice
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
    //initialize variable for input to null character
    char c = '\0';
    
    //ask user what character to use for the big "C"
    cout << "What character would you like to use? ";
    cin >> c;
    
    //output formatted "C" using spaces and the variable user inputted
    cout << "   " << c << " " << c << " " << c << endl;
    cout << "  " << c << "    " << c << endl;
    cout << " " << c << endl;
    cout << " " << c << endl;
    cout << " " << c << endl;
    cout << " " << c << endl;
    cout << " " << c << endl;
    cout << "  " << c << "    " << c << endl;
    cout << "   " << c << " " << c << " " << c << endl;
    
    return 0;
}
