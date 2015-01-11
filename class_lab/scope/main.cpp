/* 
 * File:   main.cpp
 * Author: Magister
 *
 * Created on January 10, 2015, 9:49 PM
 */

#include <iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{
    {
        int x = 1;
        cout << x << endl;
        {
            cout << " " << x << endl;
            int x = 2;
            cout << " "  << x << endl;
            {
                cout << " "  << " "  << x << endl;
                int x = 3;
                cout << " "  << " "  << x << endl;
            }
            cout << " "  << x << endl;
        }
        cout << x << endl;
    }
    return 0;
}

