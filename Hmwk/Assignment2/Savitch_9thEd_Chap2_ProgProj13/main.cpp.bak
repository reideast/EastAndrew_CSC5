/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 14, 2015, 8:39 PM
    Purpose: to calculate the Harris-Benedict basal metabolic rate
 */

//System Libraries
#include <iostream>
using namespace std;

//User Libraries
//Global Constants
const int CAL_PER_CHOCOLATE = 230; //230 Calories in one chocolate bar...yes, it is totally a globally true fact of physics, haha
//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv)
{
  //set up variables for input
  float weight = 0.0f, height = 0.0f;
  int age = 0;
  char gender = 0;
  
  //get user input
  cout << "Please enter your: " << endl;
  cout << "Weight (in lbs.): ";
  cin >> weight;
  cout << "Height (in inches): ";
  cin >> height;
  cout << "Age (in whole number years): ";
  cin >> age;
  cout << "Gender (M or F): ";
  cin >> gender;
  
  //set up variables for calculation
  float BMR = 0.0f;
  int baseBMR;
  float weightFactor, heightFactor, ageFactor;
  if (gender == 'F' || gender == 'f')
  {
    baseBMR = 655;
    weightFactor = 4.3f;
    heightFactor = 4.7f;
    ageFactor = 4.7f;
  }
  else if (gender == 'M' || gender == 'm')
  {
    baseBMR = 66;
    weightFactor = 6.3f;
    heightFactor = 12.9f;
    ageFactor = 6.8f;
  }
  else
  {
    cout << "Gender was not M or F. Cannot calculate.";
    return 1;
  }
  
  BMR = baseBMR + weightFactor * weight + heightFactor * height + ageFactor * age;
  
  cout << "DEBUG: BMR in Calories: " << BMR << endl;
  
  cout << "You need to eat " << BMR / CAL_PER_CHOCOLATE << " chocolate bars to maintain your basal metabolic rate." << endl;
  
  return 0;
}
