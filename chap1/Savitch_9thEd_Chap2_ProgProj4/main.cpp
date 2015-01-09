/* 
   File:   main.cpp
   Author: Andrew Reid East
	 Class: CSC-5 40718
   Created on January 8, 2015, 3:59 PM
   Purpose: To calculate how far an objects falls in freefall
 */
 
//System Libraries
#include <iostream>
using namespace std;

//User Libraries
//Global Constants
const float GRAVITY = 32.174; //ft per second ^ 2
//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv)
{
    //declare variables for input and storing results
    float time = 0.0f, distance = 0.0f;
    
    //get user input
    cout << "How many seconds has the object dropped? ";
    cin >> time;
    
    //calculate based on formula for freefall from stationary position
    distance = (GRAVITY * time * time) / 2;
    
    //output results
    cout << "The object has fallen " << distance << " feet." << endl;
    
    return 0;
}

