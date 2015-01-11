/* 
   File:   main.cpp
   Author: Andrew Reid East
   Class: CSC-5 40718
   Created on January 10, 2015, 2:05 PM
   Purpose: To display a sales recept
 */
 
//System Libraries
#include <iostream>
#include <iomanip>
using namespace std;

//User Libraries
//Global Constants
const float TAX_RATE = 0.07f;
//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv)
{
    //set up the formatted output
    int columnSize = 11;
    cout << fixed << setprecision(2) << showpoint;
    
    //create all variables
    float subtotal = 0.0f, taxes = 0.0f, total = 0.0f;
    float priceItem1 = 15.95f;
    float priceItem2 = 24.95f;
    float priceItem3 = 6.95f;
    float priceItem4 = 12.95f;
    float priceItem5 = 3.95f;
    
    //do calculations
    subtotal = priceItem1 + priceItem2 + priceItem3 + priceItem4 + priceItem5;
    taxes = subtotal * TAX_RATE;
    total = subtotal + taxes;
    
    //show formatted output
    cout << "Items Purchased" << endl;
    cout << setw(columnSize) << "Item1: $" << setw(5) << priceItem1 << endl;
    cout << setw(columnSize) << "Item2: $" << setw(5) << priceItem2 << endl;
    cout << setw(columnSize) << "Item3: $" << setw(5) << priceItem3 << endl;
    cout << setw(columnSize) << "Item4: $" << setw(5) << priceItem4 << endl;
    cout << setw(columnSize) << "Item5: $" << setw(5) << priceItem5 << endl;
    cout << endl;
    cout << "Subtotal: $" << subtotal << endl;
    cout << "Tax (" << (int) (TAX_RATE * 100) << "%): $" << taxes << endl;
    cout << endl;
    cout << "Total: $" << total << endl;
    
    return 0;
}
