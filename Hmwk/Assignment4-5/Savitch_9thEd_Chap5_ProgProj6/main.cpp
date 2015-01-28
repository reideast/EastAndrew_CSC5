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

//startDuel: run one trial scenario where each person shoots at the person alive who is most accurate
int startDuel(bool& aaronAlive, bool& bobAlive, bool& charlieAlive);

//startNewStrategyDuel: run one trial scenario where Aaron misses first, then each person shoots at the person alive who is most accurate
int startNewStrategyDuel(bool& aaronAlive, bool& bobAlive, bool& charlieAlive);

//shoot: enact one test scenario, using a random outcome to decide if the shooter was accurite
void shoot(bool& targetAlive, double accuracy);
//Preconditions:
//  targetAlive is an initialized variable
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
    
    // const int MAX_TRIALS = 5;
    const int MAX_TRIALS = 1000;
    // const int MAX_TRIALS = 5000;
    // const int MAX_TRIALS = 5000000;
    // const int MAX_TRIALS = 50000000;
    
    cout << "For the \"obvious\" strategy of shooting at the most accurate shooter alive:" << endl;
    for (int count = 1; count <= MAX_TRIALS; ++count)
    {
      aaronAlive = bobAlive = charlieAlive = true;
      startDuel(aaronAlive, bobAlive, charlieAlive);
      if (aaronAlive)
        ++aaronWins;
      if (bobAlive)
        ++bobWins;
      if (charlieAlive)
        ++charlieWins;
    }
    cout << "Final Results:" << endl;
    cout << "Aaron won   " << aaronWins << " trials (" << (static_cast<float>(aaronWins) / MAX_TRIALS * 100) << "%)" << endl;
    cout << "Bob won     " << bobWins << " trials (" << (static_cast<float>(bobWins) / MAX_TRIALS * 100) << "%)" << endl;
    cout << "Charlie won " << charlieWins << " trials (" << (static_cast<float>(charlieWins) / MAX_TRIALS * 100) << "%)" << endl;
    cout << endl;
    
    aaronWins = bobWins = charlieWins = 0;
    cout << "For Aaron's new strategy of missing the first round:" << endl;
    for (int count = 1; count <= MAX_TRIALS; ++count)
    {
      aaronAlive = bobAlive = charlieAlive = true;
      startNewStrategyDuel(aaronAlive, bobAlive, charlieAlive);
      if (aaronAlive)
        ++aaronWins;
      if (bobAlive)
        ++bobWins;
      if (charlieAlive)
        ++charlieWins;
    }
    cout << "Final Results:" << endl;
    cout << "Aaron won   " << aaronWins << " trials (" << (static_cast<float>(aaronWins) / MAX_TRIALS * 100) << "%)" << endl;
    cout << "Bob won     " << bobWins << " trials (" << (static_cast<float>(bobWins) / MAX_TRIALS * 100) << "%)" << endl;
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

int startNewStrategyDuel(bool& aaronAlive, bool& bobAlive, bool& charlieAlive)
{
  float aaronAcc = 1.0f/3, bobAcc = 0.5f, charlieAcc = 1.0f;
  
  int round = 1;
  while (!(
           (aaronAlive&& !bobAlive&& !charlieAlive) ||
           (!aaronAlive&& bobAlive&& !charlieAlive) ||
           (!aaronAlive&& !bobAlive&& charlieAlive)
          ))
  {
    if (round != 1 && aaronAlive) //aaron intentionally misses the first round
      if (charlieAlive)
        shoot(charlieAlive, aaronAcc);
      else if (bobAlive)
        shoot(bobAlive, aaronAcc);
    
    if (bobAlive)
      if (charlieAlive)
        shoot(charlieAlive, bobAcc);
      else if (aaronAlive)
        shoot(aaronAlive, bobAcc);
    
    if (charlieAlive)
      if (bobAlive)
        shoot(bobAlive, charlieAcc);
      else if (aaronAlive)
        shoot(aaronAlive, charlieAcc);

    ++round;
  }
}

int startDuel(bool& aaronAlive, bool& bobAlive, bool& charlieAlive)
{
  float aaronAcc = 1.0f/3, bobAcc = 0.5f, charlieAcc = 1.0f;
  
  while (!(
           (aaronAlive&& !bobAlive&& !charlieAlive) ||
           (!aaronAlive&& bobAlive&& !charlieAlive) ||
           (!aaronAlive&& !bobAlive&& charlieAlive)
          ))
  {
    if (aaronAlive)
      if (charlieAlive)
        shoot(charlieAlive, aaronAcc);
      else if (bobAlive)
        shoot(bobAlive, aaronAcc);
    
    if (bobAlive)
      if (charlieAlive)
        shoot(charlieAlive, bobAcc);
      else if (aaronAlive)
        shoot(aaronAlive, bobAcc);
      
    if (charlieAlive)
      if (bobAlive)
        shoot(bobAlive, charlieAcc);
      else if (aaronAlive)
        shoot(aaronAlive, charlieAcc);
  }
}


void shoot(bool& targetAlive, double accuracy)
{
  if ((rand() / static_cast<float>(RAND_MAX)) <= accuracy)
    targetAlive = false;
}