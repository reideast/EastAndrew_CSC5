/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 14, 2015, 6:52 PM
    Purpose: modify previous program to sum AND average ten numbers
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
  int sumNeg = 0, sumPos = 0, sumAll = 0;
  int countNeg = 0, countPos = 0, countAll = 10;
  float avgNeg = 0.0f, avgPos = 0.0f, avgAll = 0.0f;
  
  //sum all positive numbers and negative numbers separately
  if (num1 > 0)
  {
    sumPos += num1;
    ++countPos;
  }
  else if (num1 < 0) // this time we have to make sure it is a negative number to make sure we don't count any 0's for average
  {
    sumNeg += num1;
    ++countNeg;
  }
  if (num2 > 0)
  {
    sumPos += num2;
    ++countPos;
  }
  else if (num2 < 0)
  {
    sumNeg += num2;
    ++countNeg;
  }
  if (num3 > 0)
  {
    sumPos += num3;
    ++countPos;
  }
  else if (num3 < 0)
  {
    sumNeg += num3;
    ++countNeg;
  }
  if (num4 > 0)
  {
    sumPos += num4;
    ++countPos;
  }
  else if (num4 < 0)
  {
    sumNeg += num4;
    ++countNeg;
  }
  if (num5 > 0)
  {
    sumPos += num5;
    ++countPos;
  }
  else if (num5 < 0)
  {
    sumNeg += num5;
    ++countNeg;
  }
  if (num6 > 0)
  {
    sumPos += num6;
    ++countPos;
  }
  else if (num6 < 0)
  {
    sumNeg += num6;
    ++countNeg;
  }
  if (num7 > 0)
  {
    sumPos += num7;
    ++countPos;
  }
  else if (num7 < 0)
  {
    sumNeg += num7;
    ++countNeg;
  }
  if (num8 > 0)
  {
    sumPos += num8;
    ++countPos;
  }
  else if (num8 < 0)
  {
    sumNeg += num8;
    ++countNeg;
  }
  if (num9 > 0)
  {
    sumPos += num9;
    ++countPos;
  }
  else if (num9 < 0)
  {
    sumNeg += num9;
    ++countNeg;
  }
  if (num10 > 0)
  {
    sumPos += num10;
    ++countPos;
  }
  else if (num10 < 0)
  {
    sumNeg += num10;
    ++countNeg;
  }
  
  //calculate all
  sumAll = num1 + num2 + num3 + num4 + num5 + num6 + num7 + num8 + num9 + num10;
  
  //calculate averages
  avgPos = static_cast<float>(sumPos) / countPos;
  avgNeg = static_cast<float>(sumNeg) / countNeg;
  avgAll = static_cast<float>(sumAll) / countAll;
  
  cout << "The sum of all " << countAll << " numbers, " << num1 << ", " << num2 << ", " << num3 << ", " << num4 << ", " << num5 << ", " << num6 << ", " << num7 << ", " << num8 << ", " << num9 << ", and " << num10 << " is: " << sumAll << endl;
  cout << "The average of all " << countAll << " numbers is : " << avgAll << endl;
  cout << endl;
  cout << "The sum of the " << countPos << " positive numbers is : " << sumPos << endl;
  cout << "The average of the " << countPos << " positive numbers is : " << avgPos << endl;
  cout << endl;
  cout << "The sum of the " << countNeg << " negative numbers is : " << sumNeg << endl;
  cout << "The average of the " << countNeg << " negative numbers is : " << avgNeg << endl;
  
  return 0;
}
