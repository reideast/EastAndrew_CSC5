/* 
   File:   main.cpp
   Author: Andrew Reid East
	 Class: CSC-5 40718
   Created on January 8, 2015, 1:48 PM
   Purpose: To calculate how much change is worth.
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
    //define variables for input, initialize to zero
		int quarters = 0, dimes = 0, nickels = 0;
    float value = 0.0f; //"f" added to explicitly make into float, not double
    
		//get user input
    cout << "How much change is in your pocket?" << endl;
    cout << "Enter the numbers of quarters: ";
    cin >> quarters;
    cout << "Enter the number of dimes: ";
    cin >> dimes;
    cout << "Enter the number of nickels: ";
    cin >> nickels;
    
		//perform calculations
    value = 0.25f * quarters + 0.1f * dimes + 0.05f * nickels;
    
		//output results
    cout << "The values of your coins is $" << value << "." << endl;
    
    return 0;
}
