/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 14, 2015, 8:22 PM
    Purpose: calculate the amount of water a well can hold
 */

//System Libraries
#include <iostream>
using namespace std;

//User Libraries
//Global Constants
const float PI = 3.14159f;
const float CUBIC_FEET_TO_GAL = 7.48f; // 1 cubic foot = 7.48 gallons
const int FEET_TO_INCHES = 12; // 12 inches = 1 foot
//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv)
{
  float radius = 0.0f, height = 0.0f, volume = 0.0f;

  cout << "What is the radius of the well's casing (in inches)? ";
  cin >> radius;
  cout << "What is the height of the well (in feet)? ";
  cin >> height;
  
  radius = radius / FEET_TO_INCHES; //convert inches to feet
  
  volume = PI * radius * radius * height; //volume of a cylinder = PI * r^2 * h
  
  volume = volume * CUBIC_FEET_TO_GAL; //convert volume in cubic feet to gallons
  
  cout << "The capacity of the well is " << volume << " gallons.";
  
  return 0;
}
