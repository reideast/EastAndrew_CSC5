/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 15, 2015, 9:26 PM
    Purpose: Convert Arabic numerals to Roman numerals
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
  bool isUserFinished = false; //controls main loop
  char quit = 0;
  bool isInputValid = false; //controls individual input loops (ie, loop until input is right)
  
  int arabic = 0;
  
  //main program, loops until user asks to quit (copied from my Savitch_9thEd_Chap3_ProgProj1)
  while (!isUserFinished)
  {
    //input loop; until input is verified as valid (copied from my Savitch_9thEd_Chap3_ProgProj1)
    isInputValid = false;
    while (!isInputValid)
    {
      cout << "Input the year in Arabic numerals: ";
      cin >> arabic;
      if (arabic < 0) //don't accept negative numbers
      {
        cout << "The number cannot be negative. Please input again." << endl;
        isInputValid = false;
      }
      else
      {
        isInputValid = true;
      }
    }
    
    //NOTE: FIRST DRAFT DOES NOT ACCOUNT FOR less-than-one ie. 4 == IV
    
    int i;
    
    cout << "num 1000's: " << arabic / 1000 << endl;
    for (i = 0; i < arabic / 1000; ++i) //uses integer division to quickly determine # of 1000's digits
      cout << 'M';
    cout << endl << "leftovers: " << (arabic % 1000) << endl;
    arabic %= 1000;
    
    cout << "num 500's: " << arabic / 500 << endl;
    for (i = 0; i < arabic / 500; ++i) //uses integer division 
      cout << 'L';
    cout << endl << "leftovers: " << (arabic % 500) << endl;
    arabic %= 500;
    
    cout << "num 100's: " << arabic / 100 << endl;
    for (i = 0; i < arabic / 100; ++i) //uses integer division 
      cout << 'C';
    cout << endl << "leftovers: " << (arabic % 100) << endl;
    arabic %= 100;
    
    cout << "num 50's: " << arabic / 50 << endl;
    for (i = 0; i < arabic / 50; ++i) //uses integer division 
      cout << 'L';
    cout << endl << "leftovers: " << (arabic % 50) << endl;
    arabic %= 50;
    
    cout << "num 10's: " << arabic / 10 << endl;
    for (i = 0; i < arabic / 10; ++i) //uses integer division 
      cout << 'X';
    cout << endl << "leftovers: " << (arabic % 10) << endl;
    arabic %= 10;
    
    cout << "num 5's: " << arabic / 5 << endl;
    for (i = 0; i < arabic / 5; ++i) //uses integer division 
      cout << 'V';
    cout << endl << "leftovers: " << (arabic % 5) << endl;
    arabic %= 5;
    
    cout << "num 1's: " << arabic / 1 << endl;
    for (i = 0; i < arabic / 1; ++i) //uses integer division 
      cout << 'I';
    
    //determine if the user would like to repeat the calculation (copied from my Savitch_9thEd_Chap3_ProgProj1)
    cout << endl;
    cout << "Would you like to do more calculations? (N to quit) ";
    cin >> quit;
    if (quit == 'N' || quit == 'n')
      isUserFinished = true;
  }
  return 0;
}
