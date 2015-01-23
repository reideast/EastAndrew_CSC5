/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 22, 2015, 6:43 PM
    Purpose: Calculate after-tax cost of new house for the first year
 */

//System Libraries
#include <iostream>
#include <string>
using namespace std;
// #define DEBUG

//User Libraries

//Global Constants

//Function Prototypes

//calcAnnualMortgage: estimates how much the homeowner will pay in one year
float calcAnnualMortgage(float initialBalance);
//Preconditions:
//  initialBalance will be the balance before the year starts
//Postconditions:
//  returns the estimate of 3% of the initialBalance paid off the principle, and 6% of initialBalance paid as interest

//calcAnnualInterest: estimates how much interest will be in one year
float calcAnnualInterest(float initialBalance);
//Preconditions:
//  initialBalance will be the balance before the year starts
//Postconditions:
//  returns the estimate as 6% of initialBalance in interest

//calcAnnualSavings: estimates the tax deduction the homeowner will be eligible for
float calcAnnualSavings(float deductableInterest);
//Preconditions:
//  deductableInterest will be the interest paid over the course of the year
//Postconditions:
//  returns the estimate as 35% tax rate from the interest




//GetInput: Get input from <iostream> between a minimum and maximum value
void getInput(string prompt, int& input, int min = 0, int max = ~(1 << (sizeof(int) * 8) - 1));
void getInput(string prompt, float& input, float min = 0, float max = 1.0e38f);
//Preconditions:
//  prompt contains something to display through cout.
//  input is an initialized variable.
//  min/max contains the range desired (inclusive)
//    if not include, min/max will be zero to the largest integer on this sytem (calculated a bit shift based on the number of bytes in an int, then inversion (only works on two's complement based systems!))
//    for a float, a hard-coded value of 1.0e38f is chosen (based on windows 7 x64 g++ machine)
//Postconditions:
//  input will contain a valid value within the range

//Execution Begins Here
int main(int argc, char** argv)
{
  //main program, loops until user asks to quit (copied from my Savitch_9thEd_Chap3_ProgProj1)
  bool isUserFinished = false; //controls main loop
  char quit = 0;
  while (!isUserFinished)
  {
    float priceHouse = 0.0f, downPayment = 0.0f;
    getInput("What is the price of the house? ", priceHouse);
    getInput("What is the down payment? ", downPayment);
    #ifdef DEBUG
    cout << "DEBUG: Price $" << priceHouse << ", Down payment $" << downPayment << endl;
    #endif
    
    float initialBalance = priceHouse - downPayment;
    cout << "The initial balance of the loan is $" << initialBalance << endl;
    
    float firstYearCost = calcAnnualMortgage(initialBalance);
    cout << "You will pay $" << firstYearCost << " in the first year" << endl;
    
    float firstYearTaxSavings = calcAnnualSavings(calcAnnualInterest(initialBalance));
    cout << "Your tax savings are $" << firstYearTaxSavings << endl;
    
    float afterTaxCost = firstYearCost - firstYearTaxSavings;
    cout << "The after-tax cost of the house for the first year of ownership is $" << afterTaxCost << endl;
    
    //determine if the user would like to repeat the calculation (copied from my Savitch_9thEd_Chap3_ProgProj1)
    cout << endl;
    cout << "Would you like to do more calculations? (N to quit) ";
    cin >> quit;
    if (quit == 'N' || quit == 'n')
      isUserFinished = true;
    else
      cout << endl; //a blank line for readability
  }
  return 0;
}


//calcAnnualMortgage: estimates how much the homeowner will pay in one year
float calcAnnualMortgage(float initialBalance)
{
  float percentMortgage = 3.0 / 100;
  return initialBalance * percentMortgage + calcAnnualInterest(initialBalance);
}

//calcAnnualInterest: estimates how much interest will be in one year
float calcAnnualInterest(float initialBalance)
{
  float percentInterest = 6.0 / 100;
  return initialBalance * percentInterest;
}

//calcAnnualSavings: estimates the tax deduction the homeowner will be eligible for
float calcAnnualSavings(float deductableInterest)
{
  float marginalTaxRate = 35.0 / 100;
  return deductableInterest * marginalTaxRate;
}





void getInput(string prompt, int& input, int min, int max)
{
  bool isInputValid = false; //controls input loop (ie, loop until input is right)
  while (!isInputValid)
  {
    cout << prompt;
    cin >> input;
    if (input < min)
      cout << "The input cannot be less than " << min << ". Please input again." << endl;
    else if (input > max)
      cout << "The input cannot be greater than " << max << ". Please input again." << endl;
    else
      isInputValid = true;
  }
}

void getInput(string prompt, float& input, float min, float max)
{
  bool isInputValid = false; //controls input loop (ie, loop until input is right)
  while (!isInputValid)
  {
    cout << prompt;
    cin >> input;
    if (input < min)
      cout << "The input cannot be less than " << min << ". Please input again." << endl;
    else if (input > max)
      cout << "The input cannot be greater than " << max << ". Please input again." << endl;
    else
      isInputValid = true;
  }
}
