/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 20, 2015, 6:44 PM
    Purpose: Find the nearest number that can be entered if some numbers are broken
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
  //define which digits cannot be used
  int bad1 = 1, bad2 = 4, bad3 = 7;
  cout << "Oh, no! The keypad on the oven is broken, and you cannot use " << bad1 << ", " << bad2 << ", or " << bad3 << "!" << endl;

  int desiredTemp = 0, lowerTemp = 0, higherTemp = 0;
  //input loop; until input is verified as valid (copied from my Savitch_9thEd_Chap3_ProgProj1)
  bool isInputValid = false;
  while (!isInputValid)
  {
    cout << "What temperature would you actually like to set the oven at? ";
    cin >> desiredTemp;
    if (desiredTemp < 0 || desiredTemp > 999)
      cout << "The temperature must be between 0 and 999." << endl;
    else
      isInputValid = true;
  }
  
  int digit1, digit2, digit3;
  for (lowerTemp = desiredTemp; lowerTemp >= 0; --lowerTemp)
  {
    digit1 = lowerTemp / 100; //integer division truncates
    digit2 = (lowerTemp % 100) / 10;
    digit3 = (lowerTemp % 100) % 10;
    //determine if current number is free of the bad digits. (Placed in this order to short circuit the complex boolean operation as quick as possible.)
    if (digit1 != bad1 && digit1 != bad2 && digit1 != bad3 &&
        digit2 != bad1 && digit2 != bad2 && digit2 != bad3 &&
        digit3 != bad1 && digit3 != bad2 && digit3 != bad3)
     break; // lowerTemp is already equal to the first temperature that works
  }
  
  if (lowerTemp != desiredTemp) //skip the second loop if we already know desiredTemp is valid
  {
    for (higherTemp = desiredTemp; higherTemp <= 999; ++higherTemp)
    {
      digit1 = higherTemp / 100; //integer division truncates
      digit2 = (higherTemp % 100) / 10;
      digit3 = (higherTemp % 100) % 10;
      //determine if current number is free of the bad digits. (Placed in this order to short circuit the complex boolean operation as quick as possible.)
      if (digit1 != bad1 && digit1 != bad2 && digit1 != bad3 &&
          digit2 != bad1 && digit2 != bad2 && digit2 != bad3 &&
          digit3 != bad1 && digit3 != bad2 && digit3 != bad3)
       break;
    }
    
    cout << "The two closest temperatures are " << lowerTemp << " and " << higherTemp << endl;
  }
  else //the first loop showed that the temperature was valid
  {
    cout << "The desired temperature " << desiredTemp << " may be used as-is." << endl;
  }
  
  return 0;
}
