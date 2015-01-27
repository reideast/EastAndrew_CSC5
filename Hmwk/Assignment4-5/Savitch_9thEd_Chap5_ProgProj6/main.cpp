/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 25, 2015, 11:40 PM
    Purpose: Estimate the best solution to a puzzle involving probability by example random outputs
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes
bool XOR(bool a, bool b);

//startDuel: run one trial scenario where each person shoots at the person alive who is most accurate
int startDuel(bool& aaronAlive, bool& bobAlive, bool& charlieAlive);

//shoot: enact one test scenario, using a random outcome to decide if the shooter was accurite
void shoot(bool& targetAlive, double accuracy);
//Preconditions:
//  targetAlive is an initilaized variable
//  accuracy is a fraction between 0 and 1 that is the chance the shooter will hit the target
//Postconditions
//  targetAlive will be set to false if rand() was >= accuracy


//Execution Begins Here
int main(int argc, char** argv)
{
  srand(time(0));
  
  //main program, loops until user asks to quit (copied from my Savitch_9thEd_Chap3_ProgProj1)
  bool isUserFinished = false; //controls main loop
  char quit = 0;
  while (!isUserFinished)
  {
    bool aaronAlive = true, bobAlive = true, charlieAlive = true;
    int aaronWins = 0, bobWins = 0, charlieWins = 0;
    
    const int MAX_TRIALS = 5;
    int count;
    for (count = 1; count <= MAX_TRIALS; ++count)
    {
      aaronAlive = true, bobAlive = true, charlieAlive = true;
      startDuel(aaronAlive, bobAlive, charlieAlive);
      if (aaronAlive)
      {
        cout << "Aaron won trial #" << count << endl;
        ++aaronWins;
      }
      if (bobAlive)
      {
        cout << "Bob won trial #" << count << endl;
        ++bobWins;
      }
      if (charlieAlive)
      {
        cout << "Charlie won trial #" << count << endl;
        ++charlieWins;
      }
    }
    cout << endl << "Final Results:" << endl;
    cout << "Aaron won " << aaronWins << " trials (" << (static_cast<float>(aaronWins) / MAX_TRIALS * 100) << "%)" << endl;
    cout << "Bob won " << bobWins << " trials (" << (static_cast<float>(bobWins) / MAX_TRIALS * 100) << "%)" << endl;
    cout << "Charlie won " << charlieWins << " trials (" << (static_cast<float>(charlieWins) / MAX_TRIALS * 100) << "%)" << endl;
    
    //determine if the user would like to repeat the calculation (copied from my Savitch_9thEd_Chap3_ProgProj1)
    cout << endl;
    cout << "Would you like to do more calculations? (N to quit) ";
    cin >> quit;
    if (quit == 'N' || quit == 'n')
      isUserFinished = true;
    else
      cout << endl; //a blank line for readability
  }
  return 0;
}

int startDuel(bool& aaronAlive, bool& bobAlive, bool& charlieAlive)
{
  float aaronAcc = 1.0f/3, bobAcc = 0.5f, charlieAcc = 1.0f;
  
  int round = 1;
  // while (aaronAlive ^ bobAlive ^ charlieAlive) //does bitwise XOR work on bool or just int?
  while (XOR(XOR(aaronAlive, bobAlive), charlieAlive)) //does bitwise XOR work on bool or just int?
  {
    if (aaronAlive)
    {
      if (charlieAlive)
      {
        shoot(charlieAlive, aaronAcc);
        if (!charlieAlive)
          cout << "Round #" << round << ": charlie shot by aaron" << endl;
      }
      else if (bobAlive)
      {
        shoot(bobAlive, aaronAcc);
        if (!bobAlive)
          cout << "Round #" << round << ": bob shot by aaron" << endl;
      }
    }
    
    if (bobAlive)
    {
      if (charlieAlive)
      {
        shoot(charlieAlive, bobAcc);
        if (!charlieAlive)
          cout << "Round #" << round << ": charlie shot by bob" << endl;
      }
      else if (aaronAlive)
      {
        shoot(aaronAlive, bobAcc);
        if (!aaronAlive)
          cout << "Round #" << round << ": charlie shot by bob" << endl;
      }
    }
      
    if (charlieAlive)
    {
      if (bobAlive)
      {
        shoot(bobAlive, charlieAcc);
        if (!bobAlive)
          cout << "Round #" << round << ": bob shot by charlie" << endl;
      }
      else if (aaronAlive)
      {
        shoot(aaronAlive, charlieAcc);
        if (!aaronAlive)
          cout << "Round #" << round << ": bob shot by charlie" << endl;
      }
    }
      
    ++round;
  }
}

bool XOR(bool a, bool b)
{
  if (a)
    if (b)
      return false;
    else
      return true;
  else
    if (b)
      return true;
    else
      return false;
}

void shoot(bool& targetAlive, double accuracy)
{
  float temp = (rand() / static_cast<float>(RAND_MAX));
  cout << "random=" << temp << " vs. " << accuracy << endl;
  // if ((rand() / static_cast<float>(RAND_MAX)) >= accuracy)
  if (temp <= accuracy)
    targetAlive = false;
}