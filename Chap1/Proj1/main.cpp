/* 
 * File:   main.cpp
 * Author: Andrew East
 * Purpose: To add and multiply two integers
 *
 * Created on January 8, 2015, 1:22 PM
 */

#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    int a = 0, b = 0, sum, product;
    
    cout << "Please enter two whole numbers, and the press enter: ";
    cin >> a >> b;
    
    sum = a + b;
    product = a * b;
    
    cout << "The sum of "  << a << " and " << b << " is " << sum << endl;
    cout << "The product of " << a << " and " << b << " is " << product << endl;
    
    return 0;
}

