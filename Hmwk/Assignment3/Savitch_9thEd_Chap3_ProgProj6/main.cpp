/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 19, 2015, 9:14 PM
    Purpose: Fibonacci sequence for population of "green crud"
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
  //main program, loops until user asks to quit (copied from my Savitch_9thEd_Chap3_ProgProj1)
  bool isUserFinished = false; //controls main loop
  char quit = 0;
  bool isInputValid = false; //controls individual input loops (ie, loop until input is right)
  while (!isUserFinished)
  {
    int poundsOfCrud = 0, daysOfCrud = 0, t = 0, numTimePeriods = 0;
    
    //input loop; until input is verified as valid (copied from my Savitch_9thEd_Chap3_ProgProj1)
    isInputValid = false;
    while (!isInputValid)
    {
      cout << "Input the starting population of green crud (in whole lbs.): ";
      cin >> poundsOfCrud;
      if (poundsOfCrud < 1)
      {
        cout << "The number of pounds cannot be negative or zero. Please input again." << endl;
      }
      else
      {
        isInputValid = true;
      }
    }
    isInputValid = false;
    while (!isInputValid)
    {
      cout << "Input the number of days that pass (whole number): ";
      cin >> daysOfCrud;
      if (daysOfCrud < 1)
      {
        cout << "The number of days cannot be negative or zero. Please input again." << endl;
      }
      else
      {
        isInputValid = true;
      }
    }

    cout << "Progression of crud: ";
    numTimePeriods = daysOfCrud / 5; //use integer division to find time periods from days
    int prevPoundsOfCrud = poundsOfCrud; //define initial Fibonacci conditions
    for (t = 1; t <= numTimePeriods; ++t)
    {
      // cout << "DEBUG: prev=" << prevPoundsOfCrud << " curr=" << poundsOfCrud << " next=";
      
      if (t != 1 && t != 2)
      {
        poundsOfCrud = poundsOfCrud + prevPoundsOfCrud; // calculate pounds of crud using prev from last time (ie, two times ago) and curr from last time (ie. prev)
        prevPoundsOfCrud = poundsOfCrud - prevPoundsOfCrud; // set prev to curr
      }
      cout << poundsOfCrud << " ";
    }
    cout << endl;
    
    cout << "The total amount of crud after " << daysOfCrud << " days is " << poundsOfCrud << " lbs." << endl;
    
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
