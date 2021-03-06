/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 10, 2015, 10:07 PM
    Purpose: Calculate paycheck
 */

//System Libraries
#include <iostream>
#include <iomanip>
using namespace std;

//User Libraries
//Global Constants
//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv)
{
  //set output formatting
  cout << fixed << setprecision(2) << showpoint;
  
  //define current parameters
  float payRate = 16.78f;
  float taxSocialSecurity = 0.06f;
  float taxFederalIncome = 0.14f;
  float taxStateIncome = 0.05f;
  int unionDues = 10;
  int dependentHealthCost = 35;
  
  //define working variables
  float hoursWorked = 0.0f;
  int dependents = 0;
  
  float payGross = 0.0f;
  float payNet = 0.0f;
  
  char again = 'y';
  while (again == 'y' || again == 'Y')
  {
    //gather input
    cout << "How may hours has the employee worked? ";
    cin >> hoursWorked;
    cout << "How many dependents does the employee have? ";
    cin >> dependents;
    
    //perform paycheck calculations
    payGross = hoursWorked * payRate;
    payNet = payGross - payGross * taxSocialSecurity - payGross * taxFederalIncome - payGross * taxStateIncome - unionDues;
    if (dependents >= 3)
      payNet -= dependentHealthCost;
    
    //show paycheck output
    cout << "Gross pay: $" << payGross << endl;
    cout << "Withheld for:" << endl;
    cout << "  Social Security: $" << payGross * taxSocialSecurity << endl;
    cout << "  Federal Income: $" << payGross * taxFederalIncome << endl;
    cout << "  State Income: $" << payGross * taxStateIncome << endl;
    cout << "  Union Dues: $" << unionDues << endl;
    if (dependents >= 3)
      cout << "  Dependent Health Insurance: $" << dependentHealthCost << endl;
    cout << "Net pay: $" << payNet << endl << endl;

    //ask user to repeat
    cout << "Do you want to calculate another employee? (Y/N) ";
    cin >> again;
    
    cout << endl;
  }
  
  return 0;
}

/*
notes:

40 hr at $16.78
> 40 hr at 1.5 *
equals gross pay
6% taxSocialSecurity
14% taxFederalIncome
5% taxStateIncome
$10 unionDues
if (dependnets >= 3) $35
net pay
*/