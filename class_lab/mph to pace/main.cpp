/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 13, 2015, 8:20 PM
    Purpose: converted a miles per hour to "pace" - how long it takes to go 1 mile in (integer) minutes and (float) seconds
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
  //test case: 6.5 mph = 9 min, 13.8 seconds
  
  float mph = 0.0f;
  cout << "Please enter miles per hour (float): ";
  cin >> mph;
  
  int minutes; //mintues per mile
  //(hours / mile) * (60 min / 1 hour)
  minutes = static_cast<int>(60 / mph); //static cast truncates fraction AFTER floating-point division was performed
  
  float seconds; //seconds per mile
  //(hours / mile) * (60 min / 1 hour) * (60 sec / 1 min)
  seconds = (60 * 60 / mph); //total pace in seconds
  seconds -= minutes * 60; //remove minutes 
  
  cout << mph << " mph means you can travel one mile in " << minutes << " minutes and " << seconds << " seconds." << endl;
  return 0;
}
