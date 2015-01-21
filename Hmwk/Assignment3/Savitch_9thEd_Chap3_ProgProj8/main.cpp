/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 20, 2015, 5:46 PM
    Purpose: Approximate Pi
 */

//System Libraries
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//User Libraries
//Global Constants
//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv)
{
  cout << setprecision(16);
  
  //main program, loops until user asks to quit (copied from my Savitch_9thEd_Chap3_ProgProj1)
  bool isUserFinished = false; //controls main loop
  char quit = 0;
  bool isInputValid = false; //controls individual input loops (ie, loop until input is right)
  while (!isUserFinished)
  {
    int n = 0;
    double approx = 0.0;
    //input loop; until input is verified as valid (copied from my Savitch_9thEd_Chap3_ProgProj1)
    isInputValid = false;
    while (!isInputValid)
    {
      cout << "To how many terms do you want to approximate Pi? ";
      cin >> n;
      if (n < 0) //terms cannot be negative
        cout << "The number of terms cannot be zero. Please input again." << endl;
      else
        isInputValid = true;
    }
    
    cout << "The standard value of Pi is  " << M_PI << endl; //M_PI from <cmath>

    float sum = 0.0;
    for (int i = 0; i <= n; ++i)
    {
      //cout << "DEBUG: Term#" << i << "=" << (((i % 2) ? -1.0 : 1.0) / (2 * i + 1)) << endl;
      sum += ((i % 2) ? -1.0 : 1.0) / (2 * i + 1);
    }
    sum *= 4;
    
    cout << "The estimated value of Pi is " << sum << endl;
    
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
