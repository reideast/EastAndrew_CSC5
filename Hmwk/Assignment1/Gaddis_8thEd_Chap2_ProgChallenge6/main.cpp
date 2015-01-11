/* 
   File:   main.cpp
   Author: Andrew Reid East
   Class: CSC-5 40718
   Created on January 10, 2015, 5:49 PM
   Purpose: Show an employee's paycheck
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
    float payAmount = 2200.0f;
    int payPeriods = 26;
    float annualPay = 0.0f;
    
    //do calculations
    annualPay = payAmount * payPeriods;
    
    //show formatted output
    cout << "An employee paid $" << payAmount << " over " << payPeriods << " pay periods will make $" << annualPay << " that year." << endl;
    cout << "(Pre-tax amount.)" << endl;
    
    return 0;
}
