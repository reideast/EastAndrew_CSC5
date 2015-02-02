/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 13, 2015, 6:04 PM
    Purpose: Play a game where you try to launch a rocket to space by guessing force exerted by the engine and length of time to burn the engine
 */

//System Libraries
#include <iostream>
#include <iomanip>
#include <cmath>

//<chrono> for simulation time keeping and <thread> for animation sleeping. I referenced: http://stackoverflow.com/questions/4184468/sleep-for-milliseconds
//chrono needs C++11. To configure g++ in NetBeans, right click on Project. Set Configuration -> Customize. Build -> C++ Compiler. C++ Standard == C++11.
#include <chrono>
#include <thread>
using namespace std;


//Global Constants
//Physics Constants
const float g = 9.80665; // m/s^2 - g_0 at sea level

//Game animation parameters: Tweak these to make the game run differently if there is a lot of flicker on your machine
const int ANIMATION_RATE = 50; //in milliseconds
const int TIME_FACTOR = 100; //speed up simulation time by * 100 to make the game feel less sluggish


//Function Prototypes

//runGame: Run an entire round of the game, taking inputs from <iostream> until user is successful
void runGame(short difficulty);
//preconditions:
//  choice is a valid difficulty: 1, 2, or 3

bool runSimulation(float F_thrust, float time_burn, float Isp, float m_v_empty, float targetAltitude, bool hardMode, float targetVelocityThreshold = 100);
//preconditions:

// targetVelocityThreshold (100 m/s)

//oneFrameCalculateAndDisplay: make all physics calculations at time t and display to <iostream>
bool oneFrameCalculateAndDisplay(float& currentAltitude, float& currentVelocity, float t, float Isp, float time_burn, float m_v0, float mdot, float targetAltitude);
//preconditions:
//  currentAltitude, currentAltitude - initialized variables to hold calculated values
//  t (seconds) - time passed since launch. all calculations will be based around this
//  Isp (seconds) - specific impulse in seconds
//  time_burn (seconds) - how long the rocket will run its engines for
//  m_v0 (kg) - mass of vehicle at time 0, still full of fuel
//  mdot (kg/s) - flow rate of fuel, how much fuel is burned per second
//  targetAltitude (m) - altitude where a rocket launch will "win"
//postconditions:
//  returns true if the rocket has either reached the targetAltitude or crashed back to zero altitude
//  sets currentAltitude (m) to where the rocket is calculated at time t
//  sets currentVelocity (m/s) to velocity of rocket at time t

//drawRocket: draw the position of a rocket from 0 to ceiling, and fit within cols characters wide
void drawRocket(float y, float ceiling, unsigned short cols = 80);
//preconditions:
//  y and ceiling are positive


//Physics Calculations:
//altitudeDuringBurn: get altitude at any time t during the rocket engine
float altitudeDuringBurn(float t, float Isp, float m_v0, float m_curr);
//velocityDuringBurn: get velocity at any time t during the burn
float velocityDuringBurn(float t, float Isp, float m_v0, float mdot);
//ballisticAltitude: get altitude of any object with no forces applied besides gravity at time t
float ballisticAltitude(float t, float v_0, float y_0);
//ballisticVelocity: get velocity of any object with no forces applied besides gravity at time t
float ballisticVelocity(float t, float v_0);


//Execution Begins Here
int main(int argc, char** argv)
{
  cout << fixed << setprecision(2);
  
  cout << "**********************************************************" << endl;
  cout << "**                                                      **" << endl;
  cout << "**\\   Welcome to the Rocket Launch Simulation Game!     **" << endl;
  cout << "***\\                                                 *  **" << endl;
  cout << "****\\                                          *        **" << endl;
  cout << "****)                                              *    **" << endl;
  cout << "****|)    ----    ---   --  -  -   >=~        *      *  **" << endl;
  cout << "****)                                             *     **" << endl;
  cout << "**********************************************************" << endl;
  cout << endl;
  
  char menuChoice = 0;
  bool stillPlaying = true;
  while (stillPlaying)
  {
    menuChoice = 0;
    cout << "What difficulty would you like to play at?" << endl
         << " A. Easy (one variable)" << endl
         << " B. Medium (two variables)" << endl
         << " C. Hard (two variables and must approach the station at low velocity)" << endl
         << " D. Exit program" << endl;
    cin >> menuChoice;
    cout << endl;
    switch (menuChoice)
    {
      case 'A': case 'a':
        runGame(1);
        break;
      case 'B': case 'b':
        runGame(2);
        break;
      case 'C': case 'c':
        runGame(3);
        break;
      case 'D': case 'd': 
        cout << "Thanks for playing!" << endl;
        stillPlaying = false;
        break;
      default:
        cout << "That was not a valid menu choice! Please enter A, B, C, or D." << endl;
    }
  }
  
  
  return 0;
}



void runGame(short difficulty)
{
  //340 km for the ISS:
  float targetAltitude = 340000;
  
  //rocket parameters (based on the Saturn V first stage):
  // float Isp = 263; // specific impulse of Saturn V first stage = 263 seconds. The Saturn V first stage cannot reach the ISS.
  float Isp = 363; // Modified efficiency of engine to be closer to the space shuttle main engine (366 seconds)
  float m_v_empty = 870000; //total mass for rocket and payload minus stage 1 fuel
  
  short countAttempts = 0;
  bool hardMode = false;
    
  if (difficulty == 1)
  {
    cout << "You are launching a large single-stage rocket to the International Space Station" << endl
         << "in low Earth orbit, " << (targetAltitude / 1000) << " km. The scientists have already determined the" << endl
         << "optimum thrust for the engine. You must figure out how long to burn the engine." << endl
         << "Longer burn will add weight to the rocket from fuel. Good luck!" << endl;
    
    //run simulation
    float F_thrust = 3.402e7; //actual thrust of the Saturn V first stage in Newtons
    float time_burn = 0.0f;
    
    //get input and loop through simulation until user is successful
    do
    {
      do
      {
        cout << endl;
        if (countAttempts > 0)
          cout << "Your last unsuccessful burn time was " << time_burn << " s." << endl;
        cout << "Please input the burn time (in seconds): ";
        cin >> time_burn;
      } while (time_burn < 0);
      ++countAttempts;
      cout << endl;
    } while (runSimulation(F_thrust, time_burn, Isp, m_v_empty, targetAltitude, hardMode));
  }
  else if (difficulty == 2 || difficulty == 3)
  {
    
    cout << "You are launching a large single-stage rocket to the International Space Station" << endl
         << "in low Earth orbit, " << (targetAltitude / 1000) << " km. You must figure out the force from the engine and" << endl
         << "how long to burn the engine. Larger thrust and longer burn will add weight to" << endl
         << "the rocket from fuel.";
    
    float targetVelocityThreshold = 100; //for hard mode
    if (difficulty == 3)
    {
      cout << " And, you must reach the space station traveling" << endl
           << "slower than " << (targetVelocityThreshold) << " m/s to dock, or you will shoot off into space. Tricky!" << endl;
      hardMode = true;
    }
    else
      cout << " Good luck!" << endl;
    
    //run simulation
    float F_thrust = 0.0f;
    float time_burn = 0.0f;
    
    //get input and loop through simulation until user is successful
    do
    {
      do
      {
        cout << endl;
        if (countAttempts > 0)
          cout << "Your last unsuccessful burn time was " << time_burn << " s." << endl;
        cout << "Please input the burn time (in seconds): ";
        cin >> time_burn;
      } while (time_burn < 0);
      do
      {
        cout << endl;
        if (countAttempts > 0)
          cout << "Your last unsuccessful engine thrust was " << (F_thrust) << " kN." << endl;
        cout << "Please input the force of the engine thrust (in kN): ";
        cin >> F_thrust;
      } while (F_thrust < 0);
      ++countAttempts;
      cout << endl;
    } while (runSimulation(F_thrust * 1000, time_burn, Isp, m_v_empty, targetAltitude, hardMode));
  }
  else
  {
    cout << "Invalid difficulty for game: " << difficulty << endl;
    return;
  }
  
  cout << "You were successful in " << countAttempts << " tries." << endl << endl << endl;
}


bool runSimulation(float F_thrust, float time_burn, float Isp, float m_v_empty, float targetAltitude, bool hardMode, float targetVelocityThreshold)
{
  //derive properties from inputs:
  float mdot = F_thrust / (Isp * g); //substitution from: mdot = F_thrust / v_e;
  float m_fuel = mdot * time_burn;
  float m_v0 = m_v_empty + m_fuel;
  
  float currAltitude = 0.0f;
  float maxAltitude = 0.0f;
  float currVelocity = 0.0f;

  //run simulation
  chrono::steady_clock::time_point startTime = chrono::steady_clock::now(); //C++11 time keeping. referenced: http://www.cplusplus.com/reference/chrono/duration/
  float t = (chrono::duration<float>(chrono::steady_clock::now() - startTime)).count() * TIME_FACTOR; //actual time adjusted by TIME_FACTOR to speed up simulation
  
  //run one stage of the animation, which returns false if the simulation has completed
  while (oneFrameCalculateAndDisplay(currAltitude, currVelocity, t, Isp, time_burn, m_v0, mdot, targetAltitude))
  {
    if (currAltitude > maxAltitude)
      maxAltitude = currAltitude;
    //wait for ANIMATION_RATE to establish proper frame rate
    this_thread::sleep_for(chrono::milliseconds(ANIMATION_RATE)); //reference: http://stackoverflow.com/questions/4184468/sleep-for-milliseconds

    //adjust t by actual time elapsed by computer clock
    t = (chrono::duration<float>(chrono::steady_clock::now() - startTime)).count() * TIME_FACTOR;
  }
  if (currAltitude > maxAltitude)
    maxAltitude = currAltitude;
  
  //simulation is done and resultant parameters have been returned
  //check parameters vs. win conditions
  if (currAltitude > targetAltitude) //reached space
  {
    cout << "You have made it to the target altitude.";
    if (hardMode && currVelocity <= targetVelocityThreshold)
    {
      cout << endl << "And you're going slow enough to dock! Welcome to the space station!" << endl;
      return false;
    }
    else if (hardMode)
    {
      cout << endl << "But you were going too fast and overshot your target! Deep space is lonely..." << endl;
      return true;
    }
    else //not hardMode
    {
      cout << " Space, ahoy!" << endl;
      return false;
    }
  }
  else if (currAltitude < 0) //crashed back to the launch pad
  {
    if (abs(currVelocity) <= targetVelocityThreshold)
      cout << "Your rocket is not exerting enough force to overcome its mass to lift off." << endl;
    else
      cout << "You have crashed! Phooey..." << endl;
    cout << "The highest altitude your rocket reached was " << (maxAltitude / 1000) << " km." << endl;
    return true;
  }
  else //(simulation calculators really shouldn't return this)
  {
    cout << "The rocket stopped somewhere hovering above the launch pad."
         << "This is a bug in either the game or physics itself."
         << "Please report this problem to the programmer or NASA, appropriately." << endl;
    return true;
  }
}



bool oneFrameCalculateAndDisplay(float& currentAltitude, float& currentVelocity, float t, float Isp, float time_burn, float m_v0, float mdot, float targetAltitude)
{
  float current_mass_vehicle = 0.0f;
  float currentFuel = 0.0f;
  // changed to by-reference variable: float currentVelocity = 0.0f;
  // changed to by-reference variable: float currentAltitude = 0.0f;
  
  if (t <= time_burn) //during burn
  {
    current_mass_vehicle = m_v0 - mdot * t;
    currentFuel = (time_burn * mdot) - (t * mdot); //max - current
    currentAltitude = altitudeDuringBurn(t, Isp, m_v0, current_mass_vehicle);
    currentVelocity = velocityDuringBurn(t, Isp, m_v0, mdot);
  }
  else //after burn, add in ballistic flight
  {
    current_mass_vehicle = m_v0 - mdot * time_burn;
    float altAtEndOfBurn = altitudeDuringBurn(time_burn, Isp, m_v0, current_mass_vehicle);
    float velocityAtEndOfBurn = velocityDuringBurn(time_burn, Isp, m_v0, mdot);
    currentVelocity = ballisticVelocity((t - time_burn), velocityAtEndOfBurn);
    currentAltitude = ballisticAltitude((t - time_burn), velocityAtEndOfBurn, altAtEndOfBurn);
  }
  
  cout << setw(7) << t << " sec" << ", ";
  cout << "Altitude: " << setw(6) << (currentAltitude / 1000) << " km, ";
  cout << "Velocity: " << setw(8) << currentVelocity << " m/s" << ", ";
  cout << ((currentFuel > 0) ? "Fuel Remaining: " : "BURN COMPLETED: ") << setw(5) << (currentFuel / (mdot * time_burn) * 100) << "%" << endl;
  
  drawRocket(currentAltitude, targetAltitude);
  
  cout << endl;
  
  if (currentAltitude > targetAltitude || currentAltitude < 0)
    return false;
  else
    return true;
}

float velocityDuringBurn(float t, float Isp, float m_v0, float mdot)
{
  return g * (Isp * log(m_v0 / (m_v0 - mdot * t)) - t);
}
float altitudeDuringBurn(float t, float Isp, float m_v0, float m_curr)
{
  return g * ( -t * Isp * ((log(m_v0 / m_curr)) / ((m_v0 / m_curr) - 1)) + t * Isp - 0.5 * t * t);
  // return g * ( -t * Isp * ((log(m_v0 / m_curr)) / ((m_v0 / m_curr) - 1)) + t * Isp - 1/2.0f * t * t);
}
float ballisticAltitude(float t, float v_0, float y_0)
{
  return y_0 + v_0 * t - 0.5f * t * t * g; //unit check: m + m/s * s + s*s*m/s^2
}
float ballisticVelocity(float t, float v_0)
{
  return v_0 - t * g; //unit check: m/s - s * m/s^2
}


void drawRocket(float y, float ceiling, unsigned short cols)
{
  unsigned short i;
  
  //draw a line before:
  // for (i = 1; i <= cols; ++i)
    // cout << "-";
  // cout << endl;
  
  //a "crashed" rocket will be drawn on the launchpad
  if (y < 0)
  {
    y = 0;
  }

  if (ceiling < 0)
  {
    cout << "Cannot draw rocket. Target altitude cannot be negative." << endl;
  }
  else if (y > ceiling) //if progressed to the goal, just draw the ">" at the ending goal mark
  {
    cout << "|";
    for (i = 1; i <= (cols - 4); ++i)
      cout << " ";
    cout << ">=~";
    cout << endl;
  }
  else
  {
    unsigned short spacesProgressed = ((y / ceiling) * (cols - 3)); // y percent of ceiling * number of characters total (minus 1 for final char)
    
    if (spacesProgressed != 0)
    {
      cout << "|";
      for (i = 0; i < (spacesProgressed - 1); ++i)
        cout << " ";
      // cout << "i="<< i;
    }
    
    cout << ">=~";
    
    // cout << "i="<< (cols - 2);
    // int count = 0;
    for (i = (cols - 4); i > spacesProgressed; --i)
    {
      cout << " ";
      // ++count;
    }
    // cout << "count=" << count;
    
    cout << "|";// << endl;
    
    // cout << "spcProg=" << spacesProgressed << " (" << ((y / ceiling) * 100) << "%)";
    cout << endl;
  }
  
  //draw a line after
  for (i = 1; i <= cols; ++i)
    cout << ".";
  cout << endl;
}
