/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 13, 2015, 6:04 PM
    Purpose: test ncurses for project
 */

//System Libraries
#include <iostream>


//need "libncurses-devel package" in cygwin!?!
#include <curses.h>
using namespace std;

//User Libraries
//Global Constants
//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv)
{
  //from: http://www.cplusplus.com/forum/articles/10515/
  
  
  char users_name[ 100 ];

  initscr();
  (void)echo();

  addstr( "What is your name> " );
  refresh();
  getnstr( users_name, sizeof( users_name ) - 1 );

  clear();

  printw( "Greetings and salutations %s!\n", users_name );
  refresh();

  printw( "\n\n\nPress ENTER to quit." );
  refresh();
  getnstr( users_name, sizeof( users_name ) - 1 );

  endwin();
  return 0;
}
