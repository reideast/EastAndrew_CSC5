/* 
 * File:   main.cpp
 * Author: Andrew East
 * Purpose: To calculate how much change is worth.
 *
 * Created on January 8, 2015, 1:48 PM
 */

#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    int quarters = 0, dimes = 0, nickels = 0;
    float value = 0.0f;
    
    cout << "How much change is in your pocket?" << endl;
    
    cout << "Enter the numbers of quarters: ";
    cin >> quarters;
    cout << "Enter the number of dimes: ";
    cin >> dimes;
    cout << "Enter the number of nickels: ";
    cin >> nickels;
    
    value = 0.25f * quarters + 0.1f * dimes + 0.05f * nickels;
    
    cout << "The values of your coins is $" << value << "." << endl;
    
    return 0;
}

