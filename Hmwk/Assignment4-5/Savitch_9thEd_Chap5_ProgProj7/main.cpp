/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 28, 2015, 9:39 PM
    Purpose: Determine the day of the week (Sun-Mon) from the date (M/D/Y)
 */

//System Libraries
#include <iostream>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes

//numDayToEnglishDay: returns "Sunday" to "Saturday" from 0 to 6
string numDayToEnglishDay(int dayOfWeek);
//preconditions:
//  dayOfWeek is 0..6
//postconditions:
//  returns "Sunday" to "Saturday" or "Invalid day of week" if dayOfWeek is out of range


//getDayOfWeek: returns the day of week based on a date (M/D/Y)
int getDayOfWeek(int month, int day, int year);
//preconditions:
//  month is 1-12, day is 1-31 (and valid for the month), year is a calendar year
//postconditions:
//  returns 0-6 for Sunday-Saturday, or -1 if the input was invalid

//isLeapYear: returns true if a year is a leap year
bool isLeapYear(int year);
//preconditions:
//  year is a calendar year

//getCenturyValue: return a value for the century from the formula: (3 - ((year / 100) % 4)) * 2
int getCenturyValue(int year);
//preconditions:
//  year is a calendar year

//getYearValue: return a value from the year (discard century) based on the formula: (year % 4) + ((year % 100) / 4)
int getYearValue(int year);
//preconditions:
//  year is a calendar year

//getMonthValue: return a value for the month based on a table
int getMonthValue(int month, int year);
//preconditions:
//  month is an integer 1-12
//  year is a calendar year
//postconditions:
//  returns a number small number, or -1 as error

//getInput: As assigned in project, gets m/d/y from <iostream>
void getInput(int& month, int& day, int& year);
//preconditions:
//  uses my getInput function, which will be called properly b/c of overloading

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
    int m = 0, d = 0, y = 0;
    
    // m = 7, d = 4, y = 2008;
    // cout << m << "/" << d << "/" << y << ": " << getDayOfWeek(m, d, y) << " is Fri?"<< endl;
    // m = 1, d = 28, y = 2015;
    // cout << m << "/" << d << "/" << y << ": " << getDayOfWeek(m, d, y) << " is Wed?"<< endl;
    // m = 1, d = 1, y = 2000;
    // cout << m << "/" << d << "/" << y << ": " << getDayOfWeek(m, d, y) << " is Sat?"<< endl;
    // m = 11, d = 18, y = 1492;
    // cout << m << "/" << d << "/" << y << ": " << getDayOfWeek(m, d, y) << " is Fri?"<< endl;
    // m = 6, d = 28, y = 2025;
    // cout << m << "/" << d << "/" << y << ": " << getDayOfWeek(m, d, y) << " is Sat?"<< endl;
    
    getInput(m, d, y);
    
    //int dayOfWeek = getDayOfWeek(m, d, y);
    cout << "The day of the week of " << m << "/" << d << "/" << y << " is " << numDayToEnglishDay(getDayOfWeek(m, d, y)) << endl;
    
    
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


//numDayToEnglishDay: returns "Sunday" to "Saturday" from 0 to 6
string numDayToEnglishDay(int dayOfWeek)
{
  switch (dayOfWeek)
  {
    case 0: return "Sunday"; //break; ??
    case 1: return "Monday";
    case 2: return "Tuesday";
    case 3: return "Wednesday";
    case 4: return "Thursday";
    case 5: return "Friday";
    case 6: return "Saturday";
    default: return "Invalid day of week";
  }
}

//getDayOfWeek: returns the day of week based on a date (M/D/Y)
int getDayOfWeek(int month, int day, int year)
{
  if (month < 1 || month > 12) return -1;
  if (day < 1 || day > 31) return -1;
  //DEBUG: since function is return wrong number. used this to narrow it down to my getMonthValue function, and then fixed that.
  // cout << "day: " << day << endl;
  // cout << "getMonthValue(" << month << ", " << year << "): " << getMonthValue(month, year) << endl;
  // cout << "getYearValue(" << year << "): " << getYearValue(year) << endl;
  // cout << "getCenturyValue(" << year << "): " << getCenturyValue(year) << endl;
  return (day + getMonthValue(month, year) + getYearValue(year) + getCenturyValue(year)) % 7;
}

//isLeapYear: returns true if a year is a leap year
bool isLeapYear(int year)
{
  return ((year % 400) == 0 || ((year % 4 == 0) && (year % 100 != 0)));
}

//getCenturyValue: return a value for the century from the formula: (3 - ((year / 100) % 4)) * 2
int getCenturyValue(int year)
{
  return (3 - ((year / 100) % 4)) * 2;
}

//getYearValue: return a value from the year (discard century) based on the formula: (year % 4) + ((year % 100) / 4)
int getYearValue(int year)
{
  return ((year % 100) + ((year % 100) / 4));
}

//getMonthValue: return a value for the month based on a table
int getMonthValue(int month, int year)
{
  switch (month)
  {
    case 1: return (isLeapYear(year) ? 6 : 0); //break;
    case 2: return (isLeapYear(year) ? 2 : 3);
    case 3: return 3;
    case 4: return 6;
    case 5: return 1;
    case 6: return 4;
    case 7: return 6;
    case 8: return 2;
    case 9: return 5;
    case 10: return 0;
    case 11: return 3;
    case 12: return 5;
    default: return -1;
  }
}

//get date from cin
void getInput(int& month, int& day, int& year)
{
  getInput("Please enter the month as a number (Jan = 1 ... Dec = 12): ", month, 1, 12);
  // 30 + [1:12][1 -2 1 0 1 0 1 1 0 1 0 1]
  int monthMax = 30 + ((month >= 8) ? ((month + 1) % 2) : ((month == 2) ? (-2) : (month % 2)));
  //cout << "DEBUG: monthMax=" << monthMax << endl;
  getInput("Please enter the day of the month (1 to end of current month): ", day, 1, monthMax);
  getInput("Please enter the year: ", year);
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
