/* 
   File:   main.cpp
   Author: Andrew Reid East
	 Class: CSC-5 40718
   Created on January 8, 2015, 1:22 PM
   Purpose: To add and multiply two integers
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
		int a = 0, b = 0, sum, product;
    
		//Get user input
    cout << "Please enter two whole numbers, and the press enter: ";
    cin >> a >> b;
    
		//Perform calculations
    sum = a + b;
    product = a * b;
    
		//Show formatted output of results
    cout << "The sum of "  << a << " and " << b << " is " << sum << endl;
    cout << "The product of " << a << " and " << b << " is " << product << endl;
    
    return 0;
}
