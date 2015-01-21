/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 20, 2015, 7:40 PM
    Purpose: Find a secret number based on clues
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
  int guess = 0, digit1 = 0, digit2 = 0, digit3 = 0, digit4 = 0;
  
  //naive solution: use a single loop to test all the four-digits numbers that match the rules
  //Rule 0: four digit number
  //Rule 3: only odd numbers
  for (guess = 1001; guess <= 9999; guess += 2)
  {
    //rule 2: 1000's place is 3 times 10's place
    digit1 = guess / 1000;
    digit3 = (guess % 100) / 10;
    if (digit1 == (3 * digit3))
    {
      //rule 4: sum of digits = 27
      digit2 = (guess % 1000) / 100;
      digit4 = guess % 10;
      if (27 == digit1 + digit2 + digit3 + digit4)
      {
        //rule 1: all four digits are different
        //don't need to compare 1000's and 10's, since 1000's is already known to be 3 * 10's
        if (digit1 != digit2 && digit1 !=digit4 && digit2 != digit3 && digit2 != digit4 && digit3 != digit4)
          cout << "A solution was found: " << guess << endl;
      }
    }
  }
  
  //creative solution: treat each digit differently, and use nested loops
  digit1 = 0, digit2 = 0, digit3 = 0, digit4 = 0;
  //rule 2: digit1 (1000's) is 3 times tens place (digit3), so the only pairs are 9/3, 6/2, 3/1
  for (digit3 = 1; digit3 <= 3; ++digit3) //1..2..3
  {
    cout << "digit3=" << digit3 << endl;
    digit1 = digit3 * 3; //rule 2
    cout << "digit1=" << digit1 << endl;
    //rule 3: number is odd, so the last digit can only be 1..3..5..7..9
    for (digit4 = 1; digit4 <= 9; digit4 += 2)
    {
      cout << "digit4=" << digit4 << endl;
      if (digit4 == digit3 || digit4 == digit1) //skip digits that match 1000's or 10's
        continue; //skip this loop (digit4's odd number loop only)
      for (digit2 = 0; digit2 <= 9; ++digit2) //100's place can be any number 0-9, so it should be the innermost loop
      {
        cout << "digit2=" << digit2 << endl;
        
      }
    }
  }
  
  
  return 0;
}
