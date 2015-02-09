/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on February 8, 2015, 8:12 AM
    Purpose: Inputs hex numbers as char string and adds them
 */

//System Libraries
#include <iostream>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes
bool checkHex(const char digits[], short numDigits);
bool addHexNumbers(const char op1[], const char op2[], char sum[], short numDigits);
void reverseString(const char orig[], char reversed[], short numDigits);
char addHexDigit(const char op1, const char op2, const char carryDigit, char& overflow);
char decToHexDigit(short dec);
short hexToDecDigit(char hex);

//Execution Begins Here
int main(int argc, char** argv)
{
  //main program, loops until user asks to quit (copied from my Savitch_9thEd_Chap3_ProgProj1)
  bool isUserFinished = false; //controls main loop
  char quit = 0;
  while (!isUserFinished)
  {
    const short MAX_DIGITS = 11; // 10 + '\0'
    
    char operand[2][MAX_DIGITS] = {{},{}}, sum[MAX_DIGITS] = {};
    
    for (int i = 0; i < 2; ++i)
    {
      bool isInputDone = false;
      do
      {
        cout << "Please input hex operand #" << (i + 1) << ": ";
        cin >> operand[i];
        if (checkHex(operand[i], MAX_DIGITS))
          isInputDone = true;
        else
          cout << "\"" << operand[i] << "\" is not a valid hexadecimal numeral. Try again." << endl;
      } while (!isInputDone);
    }
    
    if (addHexNumbers(operand[0], operand[1], sum, MAX_DIGITS))
      cout << operand[0] << " + " << operand[1] << " = " << sum << endl;
    else
      cout << "Addition Overflow" << endl;
    
    
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



bool checkHex(const char digits[], short numDigits)
{
  for (int i = 0; i < (numDigits - 1); ++i) //don't check null terminator char
  {
    if (digits[i] == '\0')
      break;
    else
    {
      if (!((digits[i] >= '0' && digits[i] <= '9') ||
           (digits[i] >= 'A' && digits[i] <= 'F') ||
           (digits[i] >= 'a' && digits[i] <= 'f')))
      {
        return false;
      }
    }
  }
  return true;
}

bool addHexNumbers(const char op1[], const char op2[], char sum[], short numDigits)
{
  char *reversed1 = new char[numDigits], *reversed2 = new char[numDigits], *reversedSum = new char[numDigits];
  
  reverseString(op1, reversed1, numDigits);
  reverseString(op2, reversed2, numDigits);
  
  char carryDigit = '0';
  bool endOf1 = false, endOf2 = false;
  for (short i = 0; i < (numDigits - 1); ++i) //don't add the null terminator
  {
    if (reversed1[i] == '\0') endOf1 = true;
    if (reversed2[i] == '\0') endOf2 = true;
    if (!endOf1 && !endOf2)
    {
      reversedSum[i] = addHexDigit((endOf1 ? '0' : reversed1[i]), (endOf2 ? '0' : reversed2[i]), carryDigit, carryDigit);
    }
    else
    {
      reversedSum[i] = '\0';
      break;
    }
  }
  reverseString(reversedSum, sum, numDigits);
  
  if (carryDigit == '0') //the final addition carried anything but a 0
    return true;
  else
    return false;
}

void reverseString(const char orig[], char reversed[], short numDigits)
{
  short length = 0;
  while (length < numDigits && orig[length] != '\0') // less than (not equal to) assumes the last char of array is null term. depending on && short-circuit to not read invalid memory
    length++;
  // cout << "DEBUG: length=" << length << endl;
  short start, end;
  for (start = 0, end = (length - 1); start < length; ++start, --end)
  {
    // cout << "DEBUG: reversed[" << start << "]=" << reversed[start] << " set to orig[" << end << "]=" << orig[end] << endl;
    reversed[start] = orig[end];
  }
  reversed[start] = '\0';
  // cout << "DEBUG reverseString: orig=\"" << orig << "\", reversed=\"" << reversed << "\"" << endl;
}

char addHexDigit(const char op1, const char op2, const char carryDigit, char& overflow)
{
  short sum = hexToDecDigit(op1) + hexToDecDigit(op2) + hexToDecDigit(carryDigit);
  // cout << "DEBUG addHexDigit: " << hexToDecDigit(op1) << " + " << hexToDecDigit(op2) << " + " << hexToDecDigit(carryDigit) << " = " << sum << endl;
  if (sum > 15)
  {
    // cout << "DEBUG addHexDigit: overflow=" << decToHexDigit(sum - 15) << ", sum=" << decToHexDigit(15) << endl;
    overflow = decToHexDigit(sum - 15);
    return decToHexDigit(15);
  }
  else
  {
    // cout << "DEBUG addHexDigit: overflow=" << decToHexDigit(0) << ", sum=" << decToHexDigit(sum) << endl;
    overflow = decToHexDigit(0);
    return decToHexDigit(sum);
  }
}

char decToHexDigit(short dec)
{
  if (dec >= 0 && dec <= 9)
    return dec + '0';
  else if (dec >= 10 && dec <= 15)
    return dec - 10 + 'A';
  else
    return '*';
}

short hexToDecDigit(char hex)
{
  if (hex >= '0' && hex <= '9')
    return hex - '0';
  else if (hex >= 'A' && hex <= 'F')
    return hex - 'A' + 10;
  else if (hex >= 'a' && hex <= 'f')
    return hex - 'a' + 10;
  else
    return 0;
}
