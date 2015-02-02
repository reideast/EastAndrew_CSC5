/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 13, 2015, 6:04 PM
    Purpose: test writing to a screen and animate it
 */

//System Libraries
#include <iostream>
#include <iomanip>
#include <string>

//for sleeping. referece: http://stackoverflow.com/questions/4184468/sleep-for-milliseconds
//chrono needs C++11. In NetBeans, right click on Project. Set Configuration -> Customize. Build -> C++ Compiler. C++ Standard == C++11.
#include <chrono>
#include <thread>

using namespace std;

//User Libraries

//Global Constants
//should these be global, or passed to function??
const int ANIMATION_RATE = 50; //miliseconds
const int WINDOW_COLUMNS = 80;
const int WINDOW_ROWS = 25;

//Function Prototypes
bool writeScreen(int x, int y); //write a screen with a '*' at (x, y)
void testWriteScreen();

void cls(); //clear the screen by writing 100 new lines
void testCls();

//Execution Begins Here
int main(int argc, char** argv)
{
  testWriteScreen();
  
  return 0;
}
void testWriteScreen()
{
  int x = WINDOW_COLUMNS / 2;
  for (int y = 0; y < WINDOW_ROWS; ++y)
  {
    cls();
    writeScreen(x, y);
    this_thread::sleep_for(chrono::milliseconds(ANIMATION_RATE)); //reference: http://stackoverflow.com/questions/4184468/sleep-for-milliseconds
  }
}

bool writeScreen(int x, int y)
{
  if (x < 1 || x > WINDOW_COLUMNS)
  {
    cout << "Error in writeScreen: horizontal (" << x << ") is out of bounds.";
    return 1;
  }
  else if (y < 1 || y > WINDOW_ROWS)
  {
    cout << "Error in writeScreen: vertical (" << y << ") is out of bounds.";
    return 1;
  }
  else 
  {
    cout << WINDOW_ROWS << string(WINDOW_COLUMNS - 3, '-') << endl;; //line WINDOW_ROWS
    
    int row, col;
    for (row = (WINDOW_ROWS - 1); row > 0; --row)
    {
      cout << setw(2) << row;
      if (row == y)
      {
        //for (col = 0; col < x; ++col)
        //  cout << ' ';
        //cout << '*';
        cout << string(x, ' ') << '*';
      }
      cout << endl;
    }
    
    cout << " 0" << string(WINDOW_COLUMNS - 3, '-') << endl; //line 0
  }
}

void testCls()
{
  cls();
  int nothing;
  cout << "enter a number to cls(): ";
  cin >> nothing;
  cls();
  cout << "did the screen clear??" << endl;
  cout << "enter a number to cls(): ";
  cin >> nothing;
  cls();
  cout << "ok, we're done." << endl;
}

void cls()
{
  for (int i = 0; i < 100; ++i)
    cout << endl;
  return;
}
