/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 26, 2015, 9:49 PM
    Purpose: Convert 24-hour time to 12-hour time
 */

//System Libraries
#include <iostream>
#include <iomanip>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes

//getTime24Hour: read a 24-hour time from <iostream>
void getTime24Hour(int& hour, int& min);
//Postconditions:
//  hour will be set to 0-23
//  minute will be set to 0-59

//outputTime12Hour: puts a 12 hour time to <iostream>
void outputTime12Hour(int hour, int min, char am);
//Preconditions:
// hour is 1-12, min is 0-59, am is 'A' or 'P'

//convertTime24to12Hour: change a 24-hour time to 12 hour time with AM/PM
void convertTime(int hour24, int min24, int& hour12, int& min12, char& am);
//Preconditions
//  hour24 is 0-23
//  min24 is 0-59
//Postconditions:
//  hour12 will be set to 0-23
//  min12 will be set to 0-59
//  am will be set to 'A' or 'P'

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
    int hour24 = 0, min24 = 0, hour12 = 0, min12 = 0;
    char am = 0;
    
    getTime24Hour(hour24, min24);
    convertTime(hour24, min24, hour12, min12, am);
    outputTime12Hour(hour12, min12, am);
    
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


void getTime24Hour(int& hour, int& min)
{
  cout << "Please input time in 24-hour notation:" << endl;
  getInput("Input hour as a number from 0-23: ", hour, 0, 23);
  getInput("Input minutes as a number from 0-59: ", min, 0, 59);
}

void outputTime12Hour(int hour, int min, char am)
{
  cout << "The time in 12-hour notation is: ";
  cout << hour << ":";
  cout << setfill('0') << setw(2) << min << " ";
  if (am == 'A')
    cout << "AM";
  else if (am == 'P')
    cout << "PM";
  else
    cout << "AM/PM variable was not either 'A' or 'P'";
  cout << endl;
}

//convertTime24to12Hour: change a 24-hour time to 12 hour time with AM/PM
void convertTime(int hour24, int min24, int& hour12, int& min12, char& am)
{
  hour12 = hour24 % 12; // gives 0-11
  if (hour12 == 0)
    hour12 += 12;
  
  min12 = min24;
  
  if (hour24 < 12)
    am = 'A';
  else
    am = 'P';
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
