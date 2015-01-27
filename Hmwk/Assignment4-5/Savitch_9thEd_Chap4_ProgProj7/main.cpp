/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 25, 2015, 9:34 PM
    Purpose: Compute the different between a start time and a time up to 24 hours in the future
             Also, converts a time into Unix time...for fun.
            (but this is transparent to the main function)
 */

//System Libraries
#include <iostream>
using namespace std;

//User Libraries

//Global Constants
const int EPOCH_YEAR = 1970;
const int EPOCH_MONTH = 1;
const int EPOCH_DAY = 1;
const int EPOCH_HOUR = 0;
const int EPOCH_MIN = 0;
const int EPOCH_SEC = 0;

//Function Prototypes

//computeDifference: Calc how many minutes are between two times <24 hours
int computeDifference(int startHour, int startMin, bool startIsAM, int futureHour, int futureMin, bool futureIsAM);
//Preconditions:
//  hours must be between 1-12, minutes must be between 0 and 59
//  isAM variables are true if AM, false if PM
//Postconditions:
//  returns how many minutes are between the times


//absoluteTime: Given a time and date, computes how many seconds have passed since the Unix epoch
int absoluteTime(int year, int month, int day, int hour, int min, int sec);
//Precondition:
//  year between 1901 and 2038, I think, or it will overflow signed int
//  month 1-12, day 1-31, hour 0-23, min 0-59, sec 0-59
//Postconditions:
//  returns the number of seconds since the Epoch
//  as defined for Unix time, accounts for leap years but not for precise leap seconds

//dayOfYear: a helper function to absoluteTime that returns between 1 and 366 for the month/day/year combo
int dayOfYear(int year, int month, int day);

//calculates leap days that happened in all the years to EPOCH_YEAR
// does not not count the current year
int leapDaysSinceEpoc(int year);

//a helper function to return true if year is a leap year, false if not
bool isLeapYear(int year);

// basic driver program tests for absoluteTime()
void testUnixTime();

//NOTE: My original function that does not use a date, or Unix time
//absoluteTime: Given a time, compute how many minutes have passed since midnight of that day
//int absoluteTime(int hour, int minute, bool isAM);
//Preconditions:
//  hours must be between 1-12, minutes must be between 0 and 59
//  isAM variable are true if AM, false if PM
//Postconditions:
//  returns how many minutes hour:minutes is since midnight

//getTime: inputs a time from <iostream>
void getTime(int& hour, int& minute, bool& isAM);
//Preconditions:
//  hour, minute, and isAM are initialized variables
//Postconditions:
//  hour, minute, and isAM are set to time inputted (isAM is true for AM, false for PM)


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
    int startHour = 0, startMin = 0, futureHour = 0, futureMin = 0, minInFuture = 0;
    bool startIsAM = false, futureIsAM = false;
    
    cout << "What is the start time?" << endl;
    getTime(startHour, startMin, startIsAM);
    cout << "The start time is " << startHour << ":" << startMin << " " << (startIsAM ? 'A' : 'P') << 'M' << '.' << endl;
    cout << endl;
    
    cout << "What is the future time?" << endl;
    getTime(futureHour, futureMin, futureIsAM);
    cout << "The future time is " << futureHour << ":" << futureMin << " " << (futureIsAM ? 'A' : 'P') << 'M' << '.' << endl;
    cout << endl;
    
    //Note: did not change this function call when I switched to Unix time
    minInFuture = computeDifference(startHour, startMin, startIsAM, futureHour, futureMin, futureIsAM);
    cout << "The time machine must travel " << minInFuture << " minutes into the future." << endl;
    
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

//Note: uses fake dates to be able to utilize Unix time
int computeDifference(int startHour, int startMin, bool startIsAM, int futureHour, int futureMin, bool futureIsAM)
{

  
  //set up fake date (and seconds)
  const int YR = EPOCH_YEAR, MTH = EPOCH_MONTH, DY = EPOCH_DAY, SEC = EPOCH_SEC;
  
  //converts hours to military time: (startIsAM ? (startHour % 12) : (startHour + 12))
  //  12 --> 0 by using modulo 12
  //  1-11 --> 1-11
  //  pm + 12 hours
  int startTime = absoluteTime(YR, MTH, DY, (startHour % 12) + (startIsAM ? 0 : 12), startMin, SEC);
  int futureTime = absoluteTime(YR, MTH, DY, (futureHour % 12) + (futureIsAM ? 0 : 12), futureMin, SEC);
  
  //If futureTime has now been determined to be before startTime, advance it by one full day
  //Note: I judged that problem was ambiguous if "up to 24 hours" was inclusive of 24 hours,
  //  so I decided if the start time == future time, they did in fact deign to go a full 24 hours
  if (futureTime <= startTime)
    futureTime = absoluteTime(YR, MTH, (DY + 1), (futureIsAM ? (futureHour % 12) : (futureHour + 12)), futureMin, SEC);
  
  //return the difference in the times, ie. how many seconds have passed
  //converts seconds back to minutes
  return (futureTime - startTime) / 60;
}

/* My original function:
 * int computeDifference(int startHour, int startMin, bool startIsAM, int futureHour, int futureMin, bool futureIsAM)
 * {
 *   //get minutes from midnight for each time
 *   int startTime = absoluteTime(startHour, startMin, startIsAM);
 *   int futureTime = absoluteTime(futureHour, futureMin, futureIsAM);
 *   
 *   //if the time in the future is earlier in the day than the time in the past,
 *   //  then adjust it to be in the future by adding 24-hours worth of minutes
 *   //Note: I judged that problem was ambiguous if "up to 24 hours" was inclusive of 24 hours,
 *   //  so I decided if the start time == future time, they did in fact deign to go a full 24 hours
 *   if (futureTime <= startTime)
 *     futureTime += 24 * 60; // += 24-hours
 *   
 *   //return the difference in the times, ie. how many minutes have passed
 *   return futureTime - startTime;
 * }
*/

/* my original function:
 * //absoluteTime: Given a time, compute how many minutes have passed since midnight of that day
 * int absoluteTime(int hour, int minute, bool isAM)
 * {
 *   //hour (12 => 0) * 60 minutes, plus minutes, add 12 hours worth of minutes if afternoon
 *   return ((hour % 12) * 60) + minute + (isAM ? 0 : (12 * 60));
 * }
*/

//absoluteTime: Given a time, compute how many minutes have passed since the Unix Epoch, define in global constants
int absoluteTime(int year, int month, int day, int hour, int min, int sec)
{
  //hour (12 => 0) * 60 minutes, plus minutes, add 12 hours worth of minutes if afternoon
  int total = 0;
  total += (year - EPOCH_YEAR) * 365 * 24 * 60 * 60;
  total += leapDaysSinceEpoc(year) * 24 * 60 * 60;
  total += (dayOfYear(year, month, day) - dayOfYear(EPOCH_YEAR, EPOCH_MONTH, EPOCH_DAY)) * 24 * 60 * 60;
  total += (hour - EPOCH_HOUR) * 60 * 60;
  total += (min - EPOCH_MIN) * 60;
  total += (sec - EPOCH_SEC);
  return total;
}

int dayOfYear(int year, int month, int day)
{
  //initialize total to the day of the current month
  int total = day;
  //starting with the current month, add all previous months into the total days of the year
  switch (month)
  {
    case 12: total += 30; //for December, add in November, then all previous months
    case 11: total += 31;
    case 10: total += 30;
    case 9: total += 31;
    case 8: total += 31;
    case 7: total += 30;
    case 6: total += 31;
    case 5: total += 30;
    case 4: total += 31;
    case 3: total += (isLeapYear(year) ? 29 : 28);
    case 2: total += 31;
    break;
  }
  
  return total;
}

//calculates leap days that happened in all the years to EPOCH_YEAR
// does not not count the current year
int leapDaysSinceEpoc(int year)
{
  int total = 0;
  for (int i = (year - 1) - ((year - 1) % 4); i >= EPOCH_YEAR; i -= 4)
    if (isLeapYear(i))
      ++total;
  return total;
}

bool isLeapYear(int year)
{
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// basic driver program tests for absoluteTime()
void testUnixTime()
{
  cout << "test unix time 00:00:01 Jan 1 1970: " << absoluteTime(1970, 1, 1, 0, 0, 1) << endl;
  cout << "test unix time 00:01:00 Jan 1 1970: " << absoluteTime(1970, 1, 1, 0, 1, 0) << endl;
  cout << "test unix time 01:00:00 Jan 1 1970: " << absoluteTime(1970, 1, 1, 1, 0, 0) << endl;
  cout << "test unix time 00:00:00 Jan 2 1970: " << absoluteTime(1970, 1, 2, 0, 0, 0) << endl;
  cout << "test unix time 00:00:00 Feb 1 1970: " << absoluteTime(1970, 2, 1, 0, 0, 0) << endl;
  cout << "test unix time 00:00:00 Jan 1 1971: " << absoluteTime(1971, 1, 1, 0, 0, 0) << endl;
  // notable events (from wikipedia)
  cout << "test unix time 01:46:40 Sept 9 2001: " << absoluteTime(2001, 9, 9, 1, 46, 40) << endl;
  cout << "test unix time 23:31:30 Feb 13 2009: " << absoluteTime(2009, 2, 13, 23, 31, 30) << endl;
}

//getTime: inputs a time from <iostream>
void getTime(int& hour, int& minute, bool& isAM)
{
  getInput("Hour? ", hour, 1, 12);
  getInput("Minute? ", minute, 0, 59);
  char a = 0, b = 0;
  bool isInputValid = false; //controls input loop (ie, loop until input is right)
  while (!isInputValid)
  {
    cout << "AM or PM? ";
    cin >> a >> b;
    //do not test for M, doesn't change value
    if (a == 'A' || a == 'a')
    {
      isAM = true;
      isInputValid = true;
    }
    else if (a == 'P' || a == 'p')
    {
      isAM = false;
      isInputValid = true;
    }
    else
    {
      cout << "You must input \"AM\" or \"PM\"." << endl;
    }
  }
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
