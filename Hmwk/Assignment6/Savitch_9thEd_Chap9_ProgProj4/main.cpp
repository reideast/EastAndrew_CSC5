/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on February 8, 2015, 3:26 PM
    Purpose: Implement a function to reverse a C-string
 */

//System Libraries
#include <iostream>
#include <string>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes
void test(char a[]);
void reverse(char a[]);
void swap(char &a, char &b);
void printArrayInt(const char a[]);


//Execution Begins Here
int main(int argc, char** argv)
{
  const short MAX = 100;
  char a[MAX] = "abcde"; //odd
  test(a);
  
  char b[MAX] = "abcdef"; //even
  test(b);

  
  return 0;
}

void test(char a[])
{
  printArrayInt(a);
  cout << a << endl;
  reverse(a);
  printArrayInt(a);
  cout << a << endl;
}

//code based on my Savitch_9thEd_Chap7_ProgProj2
void reverse(char a[])
{
  short length = 0;
  while (a[length]) //loops until '\0' (which equals 0)
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


void swap(char &a, char &b)
{
  char temp = a;
  a = b;
  b = temp;
}

void printArrayInt(const char orig[])
{
  cout << '{';
  int i = 0;
  while (orig[i])
  {
    cout << static_cast<int>(orig[i++]) << ',';
  }
  cout << static_cast<int>(orig[i]); // \0
  cout << '}';
}
