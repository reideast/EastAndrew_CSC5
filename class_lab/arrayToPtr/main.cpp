/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on Feb 3, 2015, 9:00 AM
 *      Purpose:  Developing a sorting routine
 */

//System Libraries
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries

//Global constants

//Function prototypes
void filAray(int *,int *,int);
void prntAry(const int *,const int *,int,int);
void prntAry(const int *,int,int);
// void swap(int *,int *);//With xor's
// void swap(int &,int &);//With xor's
void markSrt(const int *,int *,int);//Mark Sort in one function 

bool isSorted(const int *, const int *, int);

//Execution Begins Here
int main(int argc, char** argv) {
    //Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));
    //Declare variables and arrays
    int row=100000;
    int pFilRow=100,perLine=10;
    int *array = new int[row];
    int *index = new int[row];
    //Fill the Arrays
    filAray(array,index,pFilRow);
    //Print the originals
    cout<<"Originals Before the Sort"<<endl;
    cout<<"Random Array"<<endl;
    prntAry(array,pFilRow,perLine);
    cout << "Is sorted? " << (isSorted(array,index,pFilRow) ? "True" : "False") << endl;
    cout<<"Index"<<endl;
    prntAry(index,pFilRow,perLine);

    //Sort using Mark Sort
    markSrt(array,index,pFilRow);
    
    //Print the sorted array
    cout<<"The array using the sorted index"<<endl;
    prntAry(array,index,pFilRow,perLine);
    cout << "Is sorted? " << (isSorted(array,index,pFilRow) ? "True" : "False") << endl;

    //Print the originals
    cout<<"Originals After the Sort"<<endl;
    cout<<"Random Array"<<endl;
    prntAry(array,pFilRow,perLine);
    cout<<"Index"<<endl;
    prntAry(index,pFilRow,perLine);
    //Exit stage right
    delete array;
    delete index;
    exit(0);
}

bool isSorted(const int *a, const int *indx, int n)
{
  bool itemsSorted = true;
  for(int i=0;i<((n-1));i++) //one less than length, since loop compares two each pass
  {
    if (!(*(a + *(indx + i)) <= *(a + *(indx + (i + 1)))))
      itemsSorted = false;
  }
  
  return itemsSorted;
}

void markSrt(const int *a,int *indx,int n){
    //Apply swapMin from beginning to end
    for(int i=0;i<n-1;i++){
        //Swap elements at the top of the list
        //with the minimum
        for(int j=i+1;j<n;j++){
            //Swap individual elements with smaller
            if(*(a + *(indx + i))>*(a + *(indx + j)))
                swap(*(indx + i),*(indx + j));
        }
    }
}

// void swap(int *a,int *b){
    // cout << "ptr: a=" << a << " / *a=" << *a << endl;
    // *a=*a^*b;
    // *b=*a^*b;
    // *a=*a^*b;
// }

// void swap(int &a, int &b)
// {
    // cout << "address: a=" << a << endl; //" / *a=" << *a << endl;
    // int temp = a;
    // a = b;
    // b = temp;
// }

//Print perLine Columns for the array output by row
void prntAry(const int *a,int n,int perLine){
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<setw(2)<<*(a+i)<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

//Print perLine Columns for the array output by row
void prntAry(const int *a,const int *indx,int n,int perLine){
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<*(a + *(indx + i))<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

//Randomly fill the array with 2-digit numbers
void filAray(int *a,int *indx,int n){
    for(int i=0;i<n;i++){
        *(a+i)=rand()%90+10;
        *(indx+i)=i;
    }
}