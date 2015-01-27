/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 25, 2015, 11:40 PM
    Purpose: Estimate the best solution to a puzzle involving probability by example random outputs
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes

//shoot: enact one test scenario, using a random outcome to decide if the shooter was accurite
void shoot(bool& targetAlive, double accuracy);
//Preconditions:
//  targetAlive is an initilaized variable
//  accuracy is a fraction between 0 and 1 that is the chance the shooter will hit the target
//Postconditions
//  targetAlive will be set to false if rand() was >= accuracy


//Execution Begins Here
int main(int argc, char** argv)
{
  srand(time(0));
  
  //main program, loops until user asks to quit (copied from my Savitch_9thEd_Chap3_ProgProj1)
  bool isUserFinished = false; //controls main loop
  char quit = 0;
  while (!isUserFinished)
  {
    bool aaronAlive = true, bobAlive = true, charlieAlive = true;
    shoot(aaronAlive, 0.5);
    cout << "aaron shot at with 0.5 acc: " << aaronAlive;
    
    
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

void shoot(bool& targetAlive, double accuracy)
{
  float temp = (rand() / static_cast<float>(RAND_MAX));
  cout << "random=" << temp << endl;
  // if ((rand() / static_cast<float>(RAND_MAX)) >= accuracy)
  if (temp >= accuracy)
    targetAlive = false;
}