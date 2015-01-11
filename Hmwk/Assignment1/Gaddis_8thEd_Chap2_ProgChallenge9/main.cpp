/* 
   File:   main.cpp
   Author: Andrew Reid East
   Class: CSC-5 40718
   Created on January 10, 2015, 1:45 PM
   Purpose: Display the data type sizes of the machine running this program
 */
 
//System Libraries
#include <iostream>
#include <iomanip>
using namespace std;

//User Libraries
//Global Constants
//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv)
{
    //set up the formatted output
    int columnSize = 15;
    
    cout << "The amount of memory in bytes of these data types on your computer are:" << endl;
    cout << setw(columnSize) << "bool:" << setw(3) << sizeof(bool) << endl;
    cout << setw(columnSize) << "char:" << setw(3) << sizeof(char) << endl;
    cout << setw(columnSize) << "short:" << setw(3) << sizeof(short) << endl;
    cout << setw(columnSize) << "int:" << setw(3) << sizeof(int) << endl;
    cout << setw(columnSize) << "unsigned int:" << setw(3) << sizeof(unsigned int) << endl;
    cout << setw(columnSize) << "long:" << setw(3) << sizeof(long) << endl;
    cout << setw(columnSize) << "float:" << setw(3) << sizeof(float) << endl;
    cout << setw(columnSize) << "double:" << setw(3) << sizeof(double) << endl;
    cout << setw(columnSize) << "long double:" << setw(3) << sizeof(long double) << endl;
    
    return 0;
}
