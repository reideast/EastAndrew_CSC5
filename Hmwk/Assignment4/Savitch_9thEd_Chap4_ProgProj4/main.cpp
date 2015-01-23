/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 22, 2015, 9:12 PM
    Purpose: Compute clothing sizes according to formulas. Show results for 10 years in the future as well.
 */

//System Libraries
#include <iostream>
#include <string>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes

//hatSize: Guess hat size
float hatSize(int height, float weight);
//Preconditions: height is in inches, weight is in lbs.
//Postconditions: returns hat size

//chestSize: Guess chest size in inches
float chestSize(int height, float weight, int age);
//Preconditions: height in inches, weigth in labs, age in whole years
//Postconditions: returns chest size based on a formula

//waistSize: Guess waist in inches based on weight and adjusted for age
float waistSize(float weight, int age);
//Preconditions: weight in lbs, age in years
//Postconditions: returns waist size

//getHeight: Prompt for height in feet/inches, returns height in inches
int getHeight();
//Preconditions:
//  <iostream>
//  uses my getInput function
//Postconditions:
//  returns height in inches

//GetInput: Get input from <iostream> between a minimum and maximum value
//  (From my Savitch_9thEd_Chap4_ProgProj1)
void getInput(string prompt, int& input, int min = 0, int max = ~(1 << (sizeof(int) * 8) - 1));
void getInput(string prompt, float& input, float min = 0, float max = 1.0e38f);
//Preconditions:
//  prompt contains something to display through cout.
//  input is an initialized variable.
//  min/max contains the range desired (inclusive)
//    if not included, min/max will be zero to the largest integer on this system (calculated a bit shift based on the number of bytes in an int, then inversion (only works on two's complement based systems!))
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
    int height = 0, age = 0;
    float weight = 0.0f;
    height = getHeight();
    getInput("What is your weight in lbs.? ", weight, 0, 1000);
    getInput("What is your age in years? ", age, 0, 122);
    
    cout << "Your estimated hat size is " << hatSize(height, weight) << "." << endl;
    cout << "Your estimated jacket chest size is " << chestSize(height, weight, age) << " inches." << endl;
    cout << "Your estimated waist is " << waistSize(weight, age) << " inches." << endl;
    
    //Code added for Savitch_9thEd_Chap4_ProgProj3
    age += 10;
    cout << "In 10 years, your jacket chest size will be " << chestSize(height, weight, age) << " inches." << endl;
    cout << "In 10 years, your waist will be " << waistSize(weight, age) << " inches." << endl;
    //End code added for Savitch_9thEd_Chap4_ProgProj3
    
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


float hatSize(int height, float weight)
{
  return (weight / height) * 2.9f;
}

float chestSize(int height, float weight, int age)
{
  //cout << "((" << age << " - 30) / 10) " << ((age - 30) / 10) << endl;
  //cout << "((age > 30) ? (1.0/8 * ((age - 30) / 10)) : 0) " << ((age > 30) ? (1.0/8 * ((age - 30) / 10)) : 0) << endl;
  
  //height*weight / 288 plus 1/8th of an inch for every 10 years over 30
  //note: extra parenthesis added for readability
  return ((height * weight) / 288) + 1.0/8 * ((age > 30) ? ((age - 30) / 10) : 0);
}

float waistSize(float weight, int age)
{
  //weight/5.7 plus 1/10th of an inch for every two years over age 28
  return (weight / 5.7) + 0.1 * ((age > 28) ? ((age - 28) / 2) : 0);
}


int getHeight()
{
  int feet = 0, inches = 0;
  getInput("What is your height?\nFirst, input feet: ", feet, 0, 9);
  getInput("Next, input inches: ", inches, 0, 11);
  return feet * 12 + inches;
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
