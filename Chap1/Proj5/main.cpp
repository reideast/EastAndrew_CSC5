/* 
 * File:   main.cpp
 * Author: Andrew East
 * Purpose: To display a large block letter "C" in a character of your choice
 *
 * Created on January 8, 2015, 4:20 PM
 */

#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    char c = '\0';
    
    cout << "What character would you like to use? ";
    cin >> c;
    
    cout << "   " << c << " " << c << " " << c << endl;
    cout << "  " << c << "    " << c << endl;
    cout << " " << c << endl;
    cout << " " << c << endl;
    cout << " " << c << endl;
    cout << " " << c << endl;
    cout << " " << c << endl;
    cout << "  " << c << "    " << c << endl;
    cout << "   " << c << " " << c << " " << c << endl;
    
    return 0;
}
