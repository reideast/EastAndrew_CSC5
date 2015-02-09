/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on February 8, 2015, 3:26 PM
    Purpose: Implement a function to reverse a C-string
 */

//System Libraries
#include <iostream>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes
void test(char a[]);
void reverse(char a[]);
void swap(char *a, char *b);
void printArrayInt(const char a[]);


//Execution Begins Here
int main(int argc, char** argv)
{
  const short MAX = 100;
  char a[MAX] = "abcde"; //odd
  test(a);
  
  char b[MAX] = "abcdef"; //even
  test(b);
  
  char c[MAX] = "A man, a plan, a canal: Panama."; //odd
  test(c);
  char d[MAX] = "amanaplanacanalpanama"; //odd
  test(d);
  
  char e[MAX] = "I prefer Pi!"; //even
  test(e);
  char f[MAX] = "ipreferpi"; //odd
  test(f);

  
  return 0;
}

void test(char a[])
{
  cout << "Original string \"" << a << "\" = ";
  printArrayInt(a);
  cout << endl;
  reverse(a);
  cout << "Reversed string \"" << a << "\" = ";
  printArrayInt(a);
  cout << endl;
}

//This code was going to be based upon my Savitch_9thEd_Chap7_ProgProj2, but that code doesn't apply at all, since it uses a loop counter.
//so, the whole thing is redone using purely pointers
void reverse(char* a)
{
  //took this method of counting the length out in favor of a pointer loop through a[] to find rear
  // short length = 0;
  // while (a[length]) //loops until '\0' (which equals 0)
    // length++;
  // cout << "DEBUG: length=" << length << endl;
  
  char *front = a, *rear = a;// = &a[length-1];
  while (*rear) rear++; //while *rear is not '\0', increment rear
  --rear; //go back one from '\0'
  // cout << "DEBUG: front and rear start at: " << *front << "/" << *rear << endl;
  while (front != rear && ((front - 1) != rear)) //odd length && even length (they do not overlap cases)
    swap(front++, rear--);
  // cout << "DEBUG reverseString: reversed=\"" << a << "\"" << endl;
}

void swap(char *a, char *b)
{
  char temp = *a;
  *a = *b;
  *b = temp;
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
