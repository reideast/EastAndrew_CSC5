/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 6, 2015, 6:05 PM
    Purpose: template
 */

//System Libraries
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

//User Libraries
//Global Constants
//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv)
{
  cout << setprecision(16);
  for (int x = 1; x < 10; ++x)
  {
    {
      float exactEx, approxEx = 1, term = 1, tol = 1e-6f;
      
      int i;
      for (i = 1; term > tol; ++i)
      {
          term *= static_cast<float>(x) / i;
          approxEx += term;
      }
      //cout << "Num terms: " << i << endl;
      cout << "Approx: " << approxEx << endl;
      
      exactEx = exp(x);
      cout << "Exact:  " << exactEx << endl;
    }
    
    {
      double exactEx, approxEx = 1, term = 1, tol = 1e-6f;
      
      int i;
      for (i = 1; term > tol; ++i)
      {
          term *= static_cast<double>(x) / i;
          approxEx += term;
      }
      //cout << "Num terms: " << i << endl;
      cout << "Approx: " << approxEx << endl;
      
      exactEx = exp(x);
      cout << "Exact:  " << exactEx << endl;
    }
    
    cout << endl;
  }
  
  return 0;
}
