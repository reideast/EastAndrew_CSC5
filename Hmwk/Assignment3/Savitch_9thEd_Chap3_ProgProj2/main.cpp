/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 15, 2015, 8:36 PM
    Purpose: Calculate the roots of a quadratic equation
 */

//System Libraries
#include <iostream>
#include <cmath>
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
  
  //quadratic equation variables:
  float a = 0.0f, b = 0.0f, c = 0.0f;
  float discriminant = 0.0f;
  
  //main program, loops until user asks to quit (copied from my Savitch_9thEd_Chap3_ProgProj1)
  while (!isUserFinished)
  {
    cout << "For the quadratic equation: ax^2 + bx + c = 0" << endl;
    
    //input loop; until input is verified as valid (copied from my Savitch_9thEd_Chap3_ProgProj1)
    isInputValid = false;
    while (!isInputValid)
    {
      cout << "a = ";
      cin >> a;
      if (abs(a - 0) < 1e-6) //float point comparison for: a == 0
      {
        cout << "a cannot be zero. Please input again." << endl;
        isInputValid = false;
      }
      else
      {
        isInputValid = true;
      }
    }
    
    //not checking for valid input of b or c, because the problem did not express any restrictions
    cout << "b = ";
    cin >> b;
    cout << "c = ";
    cin >> c;
    
    discriminant = b * b - 4.0f * a * c;
    
    //output results
    cout << "For the equation " << a << "x^2 " << (b > 0 ? '+' : '-') << " " << abs(b) << "x " << (c > 0 ? '+' : '-') << " " << abs(c) << " = 0" << endl;
    
    //choose which root formula to use based on sign of the discriminant
    //used http://en.wikipedia.org/wiki/Quadratic_equation to brush up on quadratic roots
    if (abs(discriminant - 0) < 1e-6) //float comparison for: (discriminant == 0)
    {
      //one real root
      cout << "The single root is " << (-b / (2 * a)) << endl;
    }
    else if (discriminant > 0)
    {
      //two real roots
      discriminant = sqrt(discriminant);
      cout << "The 1st root is " << ((-b + discriminant) / (2 * a)) << endl;
      cout << "The 2nd root is " << ((-b - discriminant) / (2 * a)) << endl;
    }
    else // discriminant < 0
    {
      //two complex roots
      discriminant = sqrt(abs(discriminant));
      cout << "The 1st complex root is " << (-b / (2 * a)) << " + i * " << (discriminant / (2 * a)) << endl;
      cout << "The 2nd complex root is " << (-b / (2 * a)) << " - i * " << (discriminant / (2 * a)) << endl;
    }
    
    //determine if the user would like to repeat the calculation (copied from my Savitch_9thEd_Chap3_ProgProj1)
    cout << endl;
    cout << "Would you like to do more calculations? (N to quit) ";
    cin >> quit;
    if (quit == 'N' || quit == 'n')
      isUserFinished = true;
  }
  return 0;
}
