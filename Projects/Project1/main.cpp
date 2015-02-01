/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 13, 2015, 6:04 PM
    Purpose: test writing to a screen and animate it
 */

//System Libraries
#include <iostream>
#include <cmath>
#include <cstdlib>

#include <iomanip>
#include <string>

//for sleeping. referece: http://stackoverflow.com/questions/4184468/sleep-for-milliseconds
//chrono needs C++11. In NetBeans, right click on Project. Set Configuration -> Customize. Build -> C++ Compiler. C++ Standard == C++11.
#include <chrono>
#include <thread>

using namespace std;

//User Libraries

//Global Constants
const float g = 9.80665; // m/s^2 g_0 at sea level

//should these be global, or passed to function??
// const int ANIMATION_RATE = 50; //miliseconds
// const int TIME_FACTOR = 4; //speed up simulation time by * 4 to make the game progress faster
const int TIME_FACTOR = 20;
// const int ANIMATION_RATE = 25; //miliseconds
const int ANIMATION_RATE = 50; //miliseconds

const int WINDOW_COLUMNS = 80;
const int WINDOW_ROWS = 25;

//Function Prototypes
bool writeScreen(int x, int y); //write a screen with a '*' at (x, y)
void testWriteScreen();

void cls(); //clear the screen by writing 100 new lines

float velocityDuringBurn(float t, float Isp, float m_v0, float mdot);
float altitudeDuringBurn(float t, float Isp, float m_v0, float m_curr);
float fuelRemaining(float t, float m_fuel, float mdot);

bool calcNow(float& curr_alt, float t, float Isp, float t_b, float m_v0, float mdot, float targetAltitude);

void drawRocket(float y, float ceiling, unsigned short cols = 80);

//Execution Begins Here
int main(int argc, char** argv)
{
  cout << fixed << setprecision(2);
  //testWriteScreen();
  
  // float v_e = 2579.148; // velocity of exhaust in m/s
  // float m_fuel = 2100000; //from stage 1 info
  // float t_b = 165; //the saturn 5 rocket stage 1 burns for 165 s

  // float curr_mass_vehicle = 0.0f;
  // float curr_velocity = 0.0f;
  // float curr_height = 0.0f;
  
  float height_at_end_of_burnout = 0.0f; //will be in m
  float velocity_at_end_of_burnout = 0.0f; //will be in m/s
  
  //properties of game:
  // float targetAltitude = 200000; // m
  float targetAltitude = 300000; // m
  
  //values defined for stage 1 of Saturn V rocket
  float Isp = 263; // 263 seconds = specific impulse
  float v_e = Isp * g;
  float m_v_empty = 870000; //total mass for rocket - stage 1 fuel
  
  //inputs:
  float F_thrust = 0.0f;
  float time_burn = 0.0f;
  
  F_thrust = 34020000;
  time_burn = 165;
  
  //derive properties from inputs:
  float mdot = F_thrust / (Isp * g); //substitution from: mdot = F_thrust / v_e;
  float m_fuel = mdot * time_burn;
  float m_v0 = m_v_empty + m_fuel;
  
/*   // chrono::milliseconds ms = chrono::duration_cast< chrono::milliseconds >(chrono::high_resolution_clock::now().time_since_epoch());
  chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
  for (int i = 1; i < 100000; ++i) cout << "*";
  chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
  for (int i = 1; i < 100000; ++i) cout << "*";
  chrono::steady_clock::time_point t3 = chrono::steady_clock::now();
  for (int i = 1; i < 100000; ++i) cout << "*";
  chrono::steady_clock::time_point t4 = chrono::steady_clock::now();
  // chrono::duration<long, chrono::milliseconds> time_span = chrono::duration_cast<chrono::duration<long, chrono::milliseconds>>(t2 - t1);
  chrono::duration<float> diff;
  diff = t2-t1;
  chrono::milliseconds first = chrono::duration_cast<chrono::milliseconds>(diff);
  chrono::milliseconds second = chrono::duration_cast<chrono::milliseconds>(t3-t2);
  chrono::milliseconds third = chrono::duration_cast<chrono::milliseconds>(t4-t3);
  chrono::milliseconds all = chrono::duration_cast<chrono::milliseconds>(t3-t1);
  cout << diff.count() << " " << first.count() << " + " << second.count() << " + " << third.count() << " = " << all.count() << endl; */
  
  // float m_vfinal = m_v_empty;
  
  // int startTime = time(0);
  chrono::steady_clock::time_point startTime = chrono::steady_clock::now();
  // cout << "startTime=" << startTime << endl;
  float t_really = (chrono::duration<float>(chrono::steady_clock::now() - startTime)).count();
  cout << "t_really=" << t_really << endl;

  float t = t_really * TIME_FACTOR;
  float currAltitude = 0.0f;
  // while (t <= time_burn)
  while (calcNow(currAltitude, t, Isp, time_burn, m_v0, mdot, targetAltitude))
  {
    //wait for ANIMATION_RATE to establish proper frame rate
    this_thread::sleep_for(chrono::milliseconds(ANIMATION_RATE)); //reference: http://stackoverflow.com/questions/4184468/sleep-for-milliseconds

    t_really = (chrono::duration<float>(chrono::steady_clock::now() - startTime)).count();
    t = t_really * TIME_FACTOR;
  }
  
  if (currAltitude > targetAltitude)
  {
    cout << "You have made it to the target altitude. Space, ahoy!" << endl;
  }
  else if (currAltitude < 0)
  {
    cout << "You have crashed! Phooey..." << endl;
  }
  else
  {
    cout << "The rocket stopped somewhere hovering above the launch pad."
         << "This is a bug in either the game or physics itself."
         << "Please report this but to the programmer or NASA, appropriately." << endl;
  }
  
  return 0;
}




float fuelRemaining(float t, float m_fuel, float mdot)
{
  
}
float velocityDuringBurn(float t, float Isp, float m_v0, float mdot)
{
  return g * (Isp * log(m_v0 / (m_v0 - mdot * t)) - t);
}
float altitudeDuringBurn(float t, float Isp, float m_v0, float m_curr)
{
  // return g * ( -t * Isp * ((log(m_v0 / m_curr)) / ((m_v0 / m_curr) - 1)) + t * Isp - 0.5 * t * t);
  return g * ( -t * Isp * ((log(m_v0 / m_curr)) / ((m_v0 / m_curr) - 1)) + t * Isp - 1/2.0f * t * t);
}
float ballisticAltitude(float t, float v_0, float y_0)
{
  return y_0 + v_0 * t - 0.5f * t * t * g; //unit check: m + m/s * s + s*s*m/s^2
}
float ballisticVelocity(float t, float v_0)
{
  return v_0 - t * g; //unit check: m/s - s * m/s^2
}

bool calcNow(float& curr_alt, float t, float Isp, float t_b, float m_v0, float mdot, float targetAltitude)
{
  float curr_mass_vehicle = 0.0f;
  float curr_velocity = 0.0f;
  // float curr_alt = 0.0f;
  float curr_fuel = 0.0f;
  
  float v_e = Isp * g;
  // float Isp = v_e / g;
  
  if (t <= t_b) //during burn
  {
    curr_mass_vehicle = m_v0 - mdot * t;
    curr_fuel = (t_b * mdot) - (t * mdot); //max - current
    curr_alt = altitudeDuringBurn(t, Isp, m_v0, curr_mass_vehicle);
    curr_velocity = velocityDuringBurn(t, Isp, m_v0, mdot);
  }
  else //after burn
  {
    curr_mass_vehicle = m_v0 - mdot * t_b;
    float altAtEndOfBurn = altitudeDuringBurn(t_b, Isp, m_v0, curr_mass_vehicle);
    float velocityAtEndOfBurn = velocityDuringBurn(t_b, Isp, m_v0, mdot);
    curr_velocity = ballisticVelocity((t - t_b), velocityAtEndOfBurn);
    curr_alt = ballisticAltitude((t - t_b), velocityAtEndOfBurn, altAtEndOfBurn);
  }
  
  cout << setw(7) << t << " sec" << ", ";
  cout << "Altitude: " << setw(6) << (curr_alt / 1000) << " km, ";
  cout << "Velocity: " << setw(8) << curr_velocity << " m/s" << ", ";
  cout << ((curr_fuel > 0) ? "Fuel Remaining: " : "BURN COMPLETED: ") << setw(5) << (curr_fuel / (mdot * t_b) * 100) << "%" << endl;
  
  drawRocket(curr_alt, targetAltitude);
  
  cout << endl;
  
  if (curr_alt > targetAltitude || curr_alt < 0)
    return false;
  else
    return true;
}

void drawRocket(float y, float ceiling, unsigned short cols)
{
/*
80 columns:
>                                                                              |
|>                                                                             |
| >                                                                            |
|                                                                            > |
|                                                                             >|
|                                                                              >
*/
  unsigned short i;
  
  //draw a line before:
  // for (i = 1; i <= cols; ++i)
    // cout << "-";
  // cout << endl;

  if (y > ceiling) //if progressed to the goal, just draw the ">" at the ending goal mark
  {
    cout << "|";
    for (i = 1; i <= (cols - 2); ++i)
      cout << " ";
    cout << ">";
    cout << endl;
  }
  else
  {
    unsigned short spacesProgressed = ((y / ceiling) * (cols - 1)); // y percent of ceiling * number of characters total (minus 1 for final char)
    
    if (spacesProgressed != 0)
    {
      cout << "|";
      for (i = 0; i < (spacesProgressed - 1); ++i)
        cout << " ";
      // cout << "i="<< i;
    }
    
    cout << ">";
    
    // cout << "i="<< (cols - 2);
    // int count = 0;
    for (i = (cols - 2); i > spacesProgressed; --i)
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
    cout << "-";
  cout << endl;
}




void testWriteScreen()
{
  int x = WINDOW_COLUMNS / 2;
  for (int y = 0; y < WINDOW_ROWS; ++y)
  {
    cls();
    writeScreen(x, y);
    this_thread::sleep_for(chrono::milliseconds(ANIMATION_RATE)); //reference: http://stackoverflow.com/questions/4184468/sleep-for-milliseconds
  }
}

bool writeScreen(int x, int y)
{
  if (x < 1 || x > WINDOW_COLUMNS)
  {
    cout << "Error in writeScreen: horizontal (" << x << ") is out of bounds.";
    return 1;
  }
  else if (y < 1 || y > WINDOW_ROWS)
  {
    cout << "Error in writeScreen: vertical (" << y << ") is out of bounds.";
    return 1;
  }
  else 
  {
    cout << WINDOW_ROWS << string(WINDOW_COLUMNS - 3, '-') << endl;; //line WINDOW_ROWS
    
    int row, col;
    for (row = (WINDOW_ROWS - 1); row > 0; --row)
    {
      cout << setw(2) << row;
      if (row == y)
      {
        //for (col = 0; col < x; ++col)
        //  cout << ' ';
        //cout << '*';
        cout << string(x, ' ') << '*';
      }
      cout << endl;
    }
    
    cout << " 0" << string(WINDOW_COLUMNS - 3, '-') << endl; //line 0
  }
}

void cls()
{
  for (int i = 0; i < 100; ++i)
    cout << endl;
  return;
}
