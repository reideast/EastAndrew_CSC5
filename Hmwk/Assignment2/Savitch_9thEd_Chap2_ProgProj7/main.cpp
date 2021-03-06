/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 12, 2015, 9:22 PM
    Purpose: Calculate cost due to inflation
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
  
  float currentCost = 0.0f, inflation = 0.0f;
  int targetTime = 0;
  
  cout << "What is the current cost? $";
  cin >> currentCost;
  cout << "How many years from now would you like to be calculated? ";
  cin >> targetTime;
  cout << "What is the estimated inflation rate as a percentage? ";
  cin >> inflation;
  cout << endl;
  
  inflation /= 100.0f; //convert whole number percentage to a fraction
  //cout << "DEBUG: inflation: " << inflation << endl;
  
  int countTime = 0;
  float inflatedCost = currentCost;
  //cout << "DEBUG: inflatedCost: " << inflatedCost << endl;
  while (countTime < targetTime) //loop once for each year
  {
    inflatedCost += inflatedCost * inflation; //add the percentage increased
    ++countTime;
    //cout << "DEBUG: " << countTime<< "/inflatedCost: " << inflatedCost << endl;
  }
  
  cout << "The cost after " << countTime << " years at " << inflation * 100.0f << "% inflation  will be $" << inflatedCost << endl;
  
  return 0;
}
