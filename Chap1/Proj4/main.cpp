/* 
 * File:   main.cpp
 * Author: Andrew East
 * Purpose: To calculate how far an objects falls in freefall
 *
 * Created on January 8, 2015, 3:59 PM
 */

#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    float time = 0.0f, distance = 0.0f;
    const float GRAVITY = 32.174; //ft per second ^ 2
    
    cout << "How many seconds has the object dropped? ";
    cin >> time;
    
    distance = GRAVITY * time * time / 2;
    
    cout << "The object has fallen " << distance << " feet." << endl;
    
    return 0;
}
