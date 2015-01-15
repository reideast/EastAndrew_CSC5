/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 14, 2015, 5:54 PM
    Purpose: sum of positive and negative integers
 */

//System Libraries
#include <iostream>
#include <cstdlib> //random number
#include <ctime> //seed random /w time()
using namespace std;

//User Libraries
//Global Constants
//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv)
{
  //set up variables to hold all 10 numbers
  int num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 0, num6 = 0, num7 = 0, num8 = 0, num9 = 0, num10 = 0;
  
  //get user input
  //addition to the book's project: give the option to generate 10 random numbers
  char userChoice = '/0';
  cout << "Do you want to enter your own numbers (Y/y), or use 10 random numbers between -100 and 100 (N/n)? ";
  cin >> userChoice;
  if (userChoice == 'Y' || userChoice == 'y')
  {
    cout << "Please enter 10 whole numbers, which can include positive and negative numbers: " << endl;
    cin >> num1 >> num2 >> num3 >> num4 >> num5 >> num6 >> num7 >> num8 >> num9 >> num10;
  }
  else
  {
    srand(time(0));
    num1 = rand() % 201 - 100;
    num2 = rand() % 201 - 100;
    num3 = rand() % 201 - 100;
    num4 = rand() % 201 - 100;
    num5 = rand() % 201 - 100;
    num6 = rand() % 201 - 100;
    num7 = rand() % 201 - 100;
    num8 = rand() % 201 - 100;
    num9 = rand() % 201 - 100;
    num10 = rand() % 201 - 100;
  }
  
  //perform calculations
  int sumNeg = 0, sumPos = 0, sum = 0;
  
  //sum all positive numbers and negative numbers separately
  if (num1 > 0)
    sumPos += num1;
  else // (num1 < 0) ---> Or! if (num1 == 0), but 0 will not change the result any, so that's ok.
    sumNeg += num1;
  if (num2 > 0)
    sumPos += num2;
  else
    sumNeg += num2;
  if (num3 > 0)
    sumPos += num3;
  else
    sumNeg += num3;
  if (num4 > 0)
    sumPos += num4;
  else
    sumNeg += num4;
  if (num5 > 0)
    sumPos += num5;
  else
    sumNeg += num5;
  if (num6 > 0)
    sumPos += num6;
  else
    sumNeg += num6;
  if (num7 > 0)
    sumPos += num7;
  else
    sumNeg += num7;
  if (num8 > 0)
    sumPos += num8;
  else
    sumNeg += num8;
  if (num9 > 0)
    sumPos += num9;
  else
    sumNeg += num9;
  if (num10 > 0)
    sumPos += num10;
  else
    sumNeg += num10;
  
  //sum all
  sum = num1 + num2 + num3 + num4 + num5 + num6 + num7 + num8 + num9 + num10;
  
  cout << "The sum of all the numbers, " << num1 << ", " << num2 << ", " << num3 << ", " << num4 << ", " << num5 << ", " << num6 << ", " << num7 << ", " << num8 << ", " << num9 << ", and " << num10 << " is: " << sum << endl;
  cout << "The sum of all the positive numbers is : " << sumPos << endl;
  cout << "The sum of all the negative numbers is : " << sumNeg << endl;
  
  return 0;
}
