/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on February 8, 2015, 10:02 AM
    Purpose: Create a function to check for duplicates in an array of [lowercase letters]
 */

//System Libraries
#include <iostream>
#include <string>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes
void test(char a[], short size);
short assign(char a[], string toAssign, short MAX);
bool delete_repeats(char orig[], short &size);
bool extract(char orig[], short position, short &size);
void printArray(const char orig[], short size);


//Execution Begins Here
int main(int argc, char** argv)
{
  const short MAX = 30;
  short size = 4;
  char a[MAX] = {'a', 'b', 'a', 'c'};

  test(a, size);
  
  // a = {'a', 'b', 'c', 'd', 'e'};
  size = assign(a, string("abcde"), MAX); //5 no dupe
  test(a, size);
  size = assign(a, string("abcdefghij"), MAX); //10 no dupe
  test(a, size);
  size = assign(a, string(""), MAX); //empty therefore no dupe
  test(a, size);
  
  //testing not all duplicates being removed:
  size = assign(a, string("aaaaaaaaaa"), MAX); //10 --> returns "aaa"!!
  test(a, size);
  size = assign(a, string("aaaaaaaaa"), MAX); //9 --> also returns "aaa"
  test(a, size);
  size = assign(a, string("aaaaaa"), MAX); //6 --> but this returns "aa"
  test(a, size);
  size = assign(a, string("aabbccddee"), MAX); // --> works
  test(a, size);
  size = assign(a, string("aaaaabcde"), MAX); // "aaaaa" 5 -> "aa" 2
  test(a, size);
  //OK, fixed: I wasn't examining the index that got shifted down after a delete
  
  size = assign(a, string("asdfdsggfd"), MAX); // asdfg
  test(a, size);
  size = assign(a, string("a man a plan a canal panama"), MAX);
  test(a, size);
  size = assign(a, string("i prefer pi"), MAX);
  test(a, size);
  size = assign(a, string("abcdefghijlkmnopqrstuvwxyz"), MAX);
  test(a, size);
  size = assign(a, string("blahblahblah"), MAX);
  test(a, size);
  
  return 0;
}

void test(char a[], short size)
{
  printArray(a, size);
  cout << endl;
  if (!delete_repeats(a, size))
    cout << "Deletion of repeats from array failed." << endl;
  printArray(a, size);
  cout << endl;
}

short assign(char a[], string toAssign, short MAX)
{
  short i;
  for (i = 0; i < toAssign.length() && i < MAX; ++i)
  {
    a[i] = toAssign.at(i); //string.at() see savitch ch 8 pg 483
  }
  return i; //will be (last array index + 1) because of failed test
}

bool delete_repeats(char orig[], short &size)
{
  // cout << "CYBERMAN SAYS? DELETED!" << endl;
  for (short master = 0; master < size; ++master)
  {
    for (short inspecting = (master + 1); inspecting < size; ++inspecting)
      if (orig[master] == orig[inspecting])
        if (!extract(orig, inspecting, size)) //this changes size!! so, both for loops will now end earlier than before
        {
          cout << "Extraction of " << orig[inspecting] << " at position " << inspecting << " from ";
          printArray(orig, size);
          cout << " failed." << endl;
          return false;
        }
        else
        {
          --inspecting; //since we shifted down one, look backwards one as well on the next loop
        }
  }
  return true;
}

bool extract(char orig[], short position, short &size)
{
  if (position >= size)
  {
    return false;
  }
  else
  {
    for (short i = position; i < (size - 1); ++i)
      orig[i] = orig[i + 1];
    --size;
    return true;
  }
}

void printArray(const char orig[], short size)
{
  for (short i = 0; i < size; ++i)
    cout << orig[i];
}