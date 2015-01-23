/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 22, 2015, 9:12 PM
    Purpose: Create a function to convert integers 0..99 to their English equivalent. Test it with "ninety-nine bottles of beer on the wall".
 */

//System Libraries
#include <iostream>
#include <string>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes

//intToEnglish: returns a value from 0 to 99 in English, eg. 68 -> "Sixty-eight"
string intToEnglish(int value);
//Preconditions: value is 0-99, inclusive
//Postconditions: returns the value in English, or an error message for values out-of-range

//Execution Begins Here
int main(int argc, char** argv)
{
  //cout << "ninety-nine bottles of beer on the wall";
  cout << intToEnglish(99) << endl;
  cout << intToEnglish(98) << endl;
  cout << intToEnglish(68) << endl;
  cout << intToEnglish(60) << endl;
  cout << intToEnglish(20) << endl;
  cout << intToEnglish(19) << endl;
  cout << intToEnglish(18) << endl;
  cout << intToEnglish(11) << endl;
  cout << intToEnglish(10) << endl;
  cout << intToEnglish(19) << endl;
  cout << intToEnglish(1) << endl;
  return 0;
}

string intToEnglish(int value)
{
  if (value < 0 || value > 99)
  {
    return "Error: The value must be between 0 and 99 to be converted to English.";
  }
  else
  {
    string english = "";
    switch (value / 10)
    {
      case 9: string += "Ninety"; break;
      case 8: string += "Ninety"; break;
      case 7: string += "Ninety"; break;
      case 6: string += "Ninety"; break;
      case 5: string += "Ninety"; break;
      case 4: string += "Ninety"; break;
      case 3: string += "Ninety"; break;
      case 2: string += "Ninety"; break;
      case 1:
      string += "Ninety"; break;
      case 0:
        //do we handle the dash here??
      default:
        //this could happen only if the value is greater than 99
    }
    
    english += "Ninety";
    english += "-";
    english += "nine";
    
    return english;
  }
}