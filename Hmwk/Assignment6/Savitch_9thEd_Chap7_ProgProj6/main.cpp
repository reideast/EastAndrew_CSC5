/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on February 8, 2015, 12:32 PM
    Purpose: Implement an insertion sort on an array of integers
 */

//System Libraries
#include <iostream>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes
void test(int a[], short size);

void insertionSort(int a[], short size);
void swap(int &a, int &b);

void printArray(const int orig[], short size);


bool isSorted(const int *a, int size); //cribbed from my in-class work


//Execution Begins Here
int main(int argc, char** argv)
{
  const short MAX = 30;
  short size = 10;
  int a[MAX] = {8,6,10,2,16,4,18,14,12,10};
  
  test(a, size);
  
  int b[150] = {10,13,8,20,3,13,13,12,10,13,7,13,1,16,1,18,7,12,10,4,20,18,19,18,12,9,10,2,20,4,11,10,15,18,17,3,18,7,8,18,18,5,6,5,14,16,17,13,12,11,16,2,17,18,10,6,10,2,7,4,8,14,9,2,2,18,16,15,5,15,18,5,10,17,8,10,13,2,11,19,16,18,5,15,20,13,17,2,5,19,10,1,11,17,1,7,9,20,7,14,14,20,10,5,16,5,11,19,20,17,14,8,14,19,14,11,13,14,3,16,18,18,1,14,18,3,17,13,8,15,4,6,4,6,18,12,6,19,3,16,16,3,1,10,19,18,11,1,7,20};
  size = 150;
  test(b, size);
  
  int c[150] = {7,-1,6,10,11,1,3,9,0,-5,11,-2,-6,-18,16,-8,14,-16,-3,-20,3,-1,4,-1,19,4,3,-19,14,-8,3,1,-20,-7,-9,-1,-19,-10,-16,10,-3,3,14,-14,-4,-17,-9,20,-7,3,1,20,13,14,15,20,17,1,-7,1,0,16,-16,-4,-9,-6,18,-15,-2,2,11,6,6,-3,12,7,18,15,-4,2,-7,13,0,-18,-11,13,18,-14,9,-19,12,10,20,-15,-11,-19,-6,-1,20,-2,-18,-5,9,11,-2,15,-3,8,-5,-16,20,5,16,4,-13,0,-6,-17,-20,-19,-13,13,-17,-12,20,3,17,-3,10,5,2,-2,-17,-13,-2,11,7,10,-2,-19,-14,-9,12,0,14,9,-17,16,6,4};
  size = 150;
  test(c, size);

  
  return 0;
}

void insertionSort(int a[], short size)
{
  const bool DEBUG_MODE = false;
  short posToSort, posToCompare;
  for (short posToSort = 1; posToSort < size; ++posToSort) //starting at second position, select the next value to sort into "sorted sub-array"
  {
    if (DEBUG_MODE) cout << "Outer(" << posToSort << ") item=" << a[posToSort] << " arr: ";
    if (DEBUG_MODE) printArray(a, size);
    if (DEBUG_MODE) cout << endl;
    for (posToCompare = (posToSort - 1); posToCompare >= 0; --posToCompare) //goes from the current items existing position to zero, swapping if needed. won't swap beyond the start of the array
    {
      if (DEBUG_MODE) cout << "  Compare a[" << posToCompare << "] > a[" << (posToCompare + 1) << "]: " << a[posToCompare] << " vs " << a[posToCompare + 1] << endl;
      if (a[posToCompare] > a[posToCompare + 1]) //starting with curr and curr-1, go all the way to 1 and 0
      {
        swap(a[posToCompare], a[posToCompare + 1]);
        if (DEBUG_MODE) cout << "    Inner(" << posToCompare << ") arr: ";
        if (DEBUG_MODE) printArray(a, size);
        if (DEBUG_MODE) cout << endl;
      }
      else //no swap needed, element is bubbled up to correct spot
      {
        if (DEBUG_MODE) cout << "    Inner(" << posToCompare << ") arr: ";
        if (DEBUG_MODE) printArray(a, size);
        if (DEBUG_MODE) cout << " - no swap" << endl;
        break; //exit inner loop for some efficiency
      }
    }
  }
}

void swap(int &a, int &b)
{
  int temp = a;
  a = b;
  b = temp;
}

void test(int a[], short size)
{
  cout << "Before: ";
  printArray(a, size);
  cout << endl;
  insertionSort(a, size);
  cout << "After:  ";
  printArray(a, size);
  cout << " - isSorted? " << (isSorted(a, size) ? "True" : "False");
  cout << endl;
}

void printArray(const int orig[], short size)
{
  for (short i = 0; i < size; ++i)
    cout << orig[i] << ' ';
}


bool isSorted(const int *a, int size)
{
  bool itemsSorted = true;
  for(int i = 0; i < ((size - 1)); i++) //one less than length, since loop compares two each pass
  {
    if (!(*(a + i) <= *(a + i + 1)))
      itemsSorted = false;
  }
  
  return itemsSorted;
}