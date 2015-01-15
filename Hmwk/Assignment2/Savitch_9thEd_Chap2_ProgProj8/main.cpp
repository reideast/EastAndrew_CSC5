/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 12, 2015, 9:49 PM
    Purpose: Calculate the number of payments required and the interest paid on a loan
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
  //set output formatting
  cout << fixed << setprecision(2) << showpoint;
  
  //set up parameters
  float loan = 1000.0f, interestMonthly = .015f, payment = 50.0f;
  cout << "The loan is for $" << loan << " at " << interestMonthly * 100 * 12 << "% yearly interest, and you will pay $" << payment << " per month." << endl;
  
  //working and total variables
  float totalPaidInterest = 0.0f;
  float interestThisMonth = 0.0f;
  int countMonths = 0;
  
  //set up the first month's interest
  interestThisMonth = loan * interestMonthly; //interest accrued over the last month
  loan += interestThisMonth;
  
  //loop while the remaining principle + this month's interest is not less than the payment
  while (loan > payment)
  {
    //this month
    ++countMonths;
    totalPaidInterest += interestThisMonth; //record the amount of interest accrued this month
    loan -= payment; //pay down interest and principle
    
    //cout << "DEBUG: month#" << countMonths << " remaining debt: $" << loan << " interestThisMonth: $" << interestThisMonth << " principle reduced by: $" << payment - interestThisMonth << endl;
    
    //next month
    interestThisMonth = loan * interestMonthly; //interest accrued over the last month
    loan += interestThisMonth;
  }
  
  //final month's payment (with interest already included), since it will be less than the value of payment
  ++countMonths;
  float lastMonthPayment = loan;
  totalPaidInterest += interestThisMonth; //record the amount of interest accrued this month
  //cout << "DEBUG: month#" << countMonths << " final payment: $" << lastMonthPayment << " interestThisMonth: $" << interestThisMonth << " principle reduced by: $" << loan - interestThisMonth << endl;
  
  cout << "The loan took " << countMonths << " months to pay off, and the interest paid over the life of the loan was $" << totalPaidInterest << "." << endl;
  
  return 0;
}
