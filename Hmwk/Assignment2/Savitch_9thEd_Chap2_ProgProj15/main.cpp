/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 14, 2015, 11:14 PM
    Purpose: Calculate thermal expansion
 */

//System Libraries
#include <iostream>
using namespace std;

//User Libraries
//Global Constants
const float ALPHA_AL = 2.31e-5f;
const float ALPHA_CU = 1.7e-5f;
const float ALPHA_GLASS = 8.5e-6f;
const float ALPHA_STEEL = 1.2e-5f;
//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv)
{
  float displacement = 0.0f, length = 0.0f, tempDelta = 0.0f, alpha = 0.0f;
  
  //added to problem: a menu to choose one of the provided coefficients of expansion, or option to enter your own
  int choice = 5;
  cout << "Please choose the number of a material, or the final option to input your own coefficient for linear expansion:" << endl;
  cout << "(1) Aluminum: 2.31 x 10^-5" << endl;
  cout << "(2) Copper:   1.70 x 10^-5" << endl;
  cout << "(3) Glass:    8.50 x 10^-6" << endl;
  cout << "(4) Steel:    1.20 x 10^-5" << endl;
  cout << "(5) Input you own" << endl;
  cout << "> ";
  cin >> choice;
  switch (choice)
  {
    case 1:
      alpha = ALPHA_AL;
      break;
    case 2:
      alpha = ALPHA_CU;
      break;
    case 3:
      alpha = ALPHA_GLASS;
      break;
    case 4:
      alpha = ALPHA_STEEL;
      break;
    case 5:
      cout << endl << "Enter the coefficient for linear expansion (can use scientific notation, ex: 1.23e-4): ";
      cin >> alpha;
      break;
    default:
      cout << "default";
  }
  cout << endl;
  
  //get the rest of the user input
  cout << "Enter the initial length of the material (in meters): ";
  cin >> length;
  cout << "Enter the change in temperature (in degrees Celsius): ";
  cin >> tempDelta;
  
  //calculate linear displacement
  displacement = alpha * length * tempDelta;
  
  //output results
  cout << "The material will " << ((displacement >= 0) ? "expand" : "contract") << " by " << ((displacement >= 0) ? displacement : -displacement) << " meters." << endl;
  
  return 0;
}
