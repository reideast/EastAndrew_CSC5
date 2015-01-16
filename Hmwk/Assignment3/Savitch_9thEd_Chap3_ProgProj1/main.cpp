/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 15, 2015, 5:55 PM
    Purpose: Calculate the rate of a long-distance phone call according to a branching rate structure
 */

//System Libraries
#include <iostream>
#include <iomanip>
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
  
  char dayChar1 = 0, dayChar2 = 0; //user input two character date code
  enum Days {MON, TUE, WED, THU, FRI, SAT, SUN};
  int day = MON; //internal storage of day
  
  int hour = 0, minute = 0; //user input of the time of day
  char throwAwayTheColon; //user input of a single character ':' that isn't used
  float time = 0.0f; //internal storage with minutes converted to fractional hours
  
  int rate = 0; //internal storage of rate based on time of day/day of week
  enum RateInCents {DAYTIME = 40, EVENINGS = 25, WEEKENDS = 15};
  
  int lengthOfCall = 0; //user input of length in minutes
  
  float cost = 0.0f; //result of calculation
  
  //main program, loops until user asks to quit
  while (!isUserFinished)
  {
    //input loop; until input is verified as valid
    isInputValid = false;
    while (!isInputValid)
    {
      cout << "What day of the week did the call start? (Mo Tu We Th Fr Sa Su) ";
      cin >> dayChar1 >> dayChar2;
      //cout << "DEBUG: char1=" << dayChar1 << ", char2=" << dayChar2 << endl;
      
      isInputValid = true; //save some code by "assuming" the user inputted correctly first
      switch (dayChar1)
      {
        case 'M': case 'm':
          if (dayChar2 == 'o' || dayChar2 == 'O')
            day = MON;
          else
            isInputValid = false;
          break;
        case 'T': case 't':
          if (dayChar2 == 'u' || dayChar2 == 'U')
            day = TUE;
          else if (dayChar2 == 'h' || dayChar2 == 'H')
            day = THU;
          else
            isInputValid = false;
          break;
        case 'W': case 'w':
          if (dayChar2 == 'e' || dayChar2 == 'E')
            day = WED;
          else
            isInputValid = false;
          break;
        case 'F': case 'f':
          if (dayChar2 == 'r' || dayChar2 == 'R')
            day = FRI;
          else
            isInputValid = false;
          break;
        case 'S': case 's':
          if (dayChar2 == 'a' || dayChar2 == 'A')
            day = SAT;
          else if (dayChar2 == 'u' || dayChar2 == 'U')
            day = SUN;
          else
            isInputValid = false;
          break;
        default:
          isInputValid = false;
      }
      // cout << "DEBUG: day=" << day << endl;
      if (!isInputValid)
        cout << dayChar1 << dayChar2 << " is not a valid day of the week. Please try again." << endl;
    }
    
    isInputValid = false;
    while (!isInputValid)
    {
      cout << "At what time did the call start? (24-hour format with a colon, 00:00) ";
      cin >> hour >> throwAwayTheColon >> minute;
      //cout << "DEBUG: hour=" << hour << ", minute=" << minute << ", char=" << throwAwayTheColon << endl;
      if (hour > 23 || hour < 0)
      {
        cout << hour << " was not a valid hour. Please try again." << endl;
        isInputValid = false;
      }
      else if (minute > 59 || minute < 0)
      {
        cout << minute << " was not a valid minute. Please try again." << endl;
        isInputValid = false;
      }
      else
      {
        time = hour + minute / 60.0f;
        isInputValid = true;
      }
    }
    
    isInputValid = false;
    while (!isInputValid)
    {
      cout << "How many minutes long was the call? (please round to a whole number) ";
      cin >> lengthOfCall;
      if (lengthOfCall < 1)
      {
        cout << "The length of the call must be at least one minute. Please try again." << endl;
        isInputValid = false;
      }
      else
      {
        isInputValid = true;
      }
    }
    
    //determine when call took place and rate to bill at
    if (day == SAT || day == SUN)
      rate = WEEKENDS;
    else
      if (time < 8.0f || time > 18.0f) //before 8am or after 6pm
        rate = EVENINGS;
      else
        rate = DAYTIME;
    
    //calculate total cost
    cost = lengthOfCall * rate / 100.0; //calculate cost in cents, and convert to dollars
    
    //output results of this calculation
    cout << "The cost of the call was $" << fixed << setprecision(2) << cost << endl;
    
    //determine if the user would like to repeat the calculation
    cout << endl;
    cout << "Would you like to do more calculations? (N to quit) ";
    cin >> quit;
    if (quit == 'N' || quit == 'n')
      isUserFinished = true;
  }
  return 0;
}
