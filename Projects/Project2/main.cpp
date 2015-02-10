/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on February 5, 2015, 5:54 PM
    Purpose: Play an ASCII-text based RPG/Adventure/Maze game inspired by Rogue
 */


  /*
  implement this:
  
  player is a STRUCT
  monsters struct
  
  all NPC are in a (vector)
  player moves
  then iterate the vector for all NPC to take actions
  
  help screen
  inventory screen
  -> sorting requirement: sort the inventory items
  
  note: (x) -> display msg -> NOT (y/n) -> clear exit state, does NOT clear msg
  
  battle screen
  
  save game to file
  
  reach goals:
  scroll map??
  */


//System Libraries
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

// MSDN Method to Read Unbuffered Input from Keyboard
//  reference:
//    reading input buffer events
//      https://msdn.microsoft.com/en-us/library/windows/desktop/ms685035(v=vs.85).aspx
//    cls using WinAPI
//      https://msdn.microsoft.com/en-us/library/windows/desktop/ms682022(v=vs.85).aspx
#include <windows.h> //for Windows-only implementation of keyboard input and CLS
// #include <stdio.h> //for printf and stderr only, i think. remove those, then disable.

//<chrono> for simulation time keeping and <thread> for animation sleeping.
//  referenced: http://stackoverflow.com/questions/4184468/sleep-for-milliseconds
//<chrono> needs C++11. To configure g++ in NetBeans, right click on Project. Set Configuration -> Customize. Build -> C++ Compiler. C++ Standard == C++11.
#include <chrono>
#include <thread>
using namespace std;

//Global Constants
//Game animation parameters: Tweak these to make the game run differently if there is a lot of flicker on your machine
const int ANIMATION_RATE = 50; //in milliseconds

const int LINE_MAX = 80;
const bool DEBUG_MODE = true;

//Struct Prototypes

//note: I need to force the complier to "see" the inheritance relationship of structs with reinterpret_cast. I don't know if this means I'm doing the whole thing wrong, but I don't want to delve into classes, so I'm sticking with it.
//  example: (reinterpret_cast<Actor*>(newAsset))->display (newAsset is of type Asset*)
struct Asset
{
  string name;
  short assetID;
  char display;
  short x;
  short y;
  
  bool isActor;
  short hp;
  short ac;
  short hitBonus;
  short damage;
  short damageBonus;
  short exp;
  
  bool isPlayer;
  // short mp;
  short qtyPotion;
  short expTotal;
  // short equippedWeaponID;
  // vector<Asset> inventory; //array
  
  // bool isItem;
  // char *art; //string (including \n) of ASCII art of item
};

struct MapSquare
{
  char display;
  Asset* linkedActor;
};

struct GameProperties
{
  MapSquare *map;
  vector<Asset*> gameAssets;
  short playerIndex;
  
  string *currStatus;
  vector<string> statusDictionary;
  
  string saveFolder;
  string loadFolder;
  
  short screenSizeX;
  short screenSizeY;
  short mapSizeX;
  short mapSizeY;
};

//Function Prototypes

//screen display:
// void printStatus(string line1, string line2, short hp = 100, short mp = 100, short qtyPotion = 3);
void printStatus(GameProperties &game);
void printMap(MapSquare *map, short sizeX, short sizeY);
void printControlScheme();
bool cls(bool WIN32_MODE = false);
bool win32_cls();
void switchFromStreamToGet(istream &strm);

//user input:
bool getAKey(char& input, bool WIN32_MODE = false);

//file I/O:
bool loadFromFile(string filename, GameProperties &game);
bool loadAssetFile(GameProperties &game, Asset &assetToLoad);

//system checks:
bool isRunningInAWin32Console();
bool resizeConsole_win32(short cols, short rows);


//Execution Begins Here
int main(int argc, char** argv)
{
  GameProperties game;
  game.loadFolder = "gameMap1";
  
  const string mapFile = game.loadFolder + "\\" + "gameMap.txt";
  
  if (!loadFromFile(mapFile, game))
  {
    cout << "Reading game from disk has failed." << endl;
    delete [] game.map;
    return 1;
  }
  
  
  const short NUM_STATUS = 4;
  string statusDictionary[4];
  const short STATUS_INIT = 0;
  statusDictionary[STATUS_INIT] = "You wake up in a dank room. You hear water slowly dripping, and you feel slimy";
  statusDictionary[STATUS_INIT + 1] = "mold on the floor.";
  const short STATUS_EXIT = 2;
  statusDictionary[STATUS_EXIT] = "Are you sure you want to exit?";
  statusDictionary[STATUS_EXIT + 1] = "(y/n)";
  
  //test for running in the proper console, and give a chance to quit if user wants
  bool WIN32_MODE = isRunningInAWin32Console();
  if (!WIN32_MODE)
  {
    cout << "You are not running this program in a Windows Command Prompt console. Input and\nanimation will be more primitive. It is recommended you quit and run the .exe\nfrom outside any IDE's.\nDo you want to continue anyway? (y/n) ";
    char choice = 0;
    cin >> choice;
    if (choice == 'n' || choice == 'N')
      return 1; //exits with Run Failed
  }
  else
  {
    if (!resizeConsole_win32(game.screenSizeX, game.screenSizeY)) //{cols, rows}
      cout << "Resizing the console window failed. This program will not work right with a console buffer smaller than 100 characters wide by 40 tall. Please use the settings to resize this console window before continuing." << endl;
  }
  
  string statusLine1, statusLine2;
  

  
  // for (y = 0; y < mapSizeMaxY; ++y)
    // for (x = 0; x < mapSizeMaxX; ++x)
    // {
      // map[y * mapSizeMaxX + x] = ' ';
    // }
    
  // MapSquare *playerPtr = &game.map[playerY * mapSizeMaxX + playerX];
  // playerPtr->display = 'Q';
  
  // game.map[11 * mapSizeMaxX + 20].display = 'W';
  
  short currStatusLine = STATUS_INIT;
    
  char input = 0;
  bool isGameRunning = true;
  bool confirmExit = false;
  short confirmExitPrevStatus = 0;
  while (isGameRunning)
  {
    cls(WIN32_MODE);
    printMap(game.map, game.mapSizeX, game.mapSizeY);
    printStatus(game);
    printControlScheme();
    
    if (getAKey(input, WIN32_MODE))
    {
      if (WIN32_MODE) cout << endl;
      switch ((input >= 'a' && input <= 'z') ? (input - 'a' + 'A') : input) //to upper
      {
        case 'W':
          cout << "up" << endl;
          break;
        case 'A':
          cout << "left" << endl;
          break;
        case 'S':
          cout << "down" << endl;
          break;
        case 'D':
          cout << "right" << endl;
          break;
        case 'X':
          // cout << "Are you sure you want to exit? (y/n) ";
          confirmExit = true;
          confirmExitPrevStatus = currStatusLine;
          currStatusLine = STATUS_EXIT;
          break;
        case 'H':
          cout << "DEBUG: Display help here.";
          break;
        case 'Y':
        case 'N':
          if (confirmExit)
          {
            if (input == 'Y' || input == 'y')
            {
              cout << "Thank you for playing!" << endl;
              isGameRunning = false;
            }
            else // input == 'N'
            {
              confirmExit = false;
              currStatusLine = confirmExitPrevStatus;
            }
            break;
          }
        default:
          cout << "Keyboard input doesn't do anything" << endl;
      }
    }
    else
    {
      cout << "Key input failed." << endl;
    }
    
  }
  
  delete [] game.map;
  return 0;
  
  
  //****************************************************************************************************
  //test animation using cls()
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD coordScreen = { 0, 30 };
  //test cls:
  for (int i = 0; i < 77; ++i)
  {
    cls(WIN32_MODE);
    SetConsoleCursorPosition(hStdout, coordScreen);
    cout << string(i, ' ') << ">=-" << endl;
    //wait for ANIMATION_RATE to establish proper frame rate
    this_thread::sleep_for(chrono::milliseconds(ANIMATION_RATE)); //reference: http://stackoverflow.com/questions/4184468/sleep-for-milliseconds
  }
 
  delete [] game.map;
  return 0; 
}



//******************************************************************************
//********************************   Graphics   ********************************
//******************************************************************************

void printStatus(GameProperties &game)
{
  cout << endl;
  cout << *(game.currStatus) << endl;
  cout << endl;
  cout << " [ HP: " << game.gameAssets[game.playerIndex].hp << " ]   [ Potions: " << game.gameAssets[game.playerIndex].qtyPotion << " ]   [ EXP: " << game.gameAssets[game.playerIndex].expTotal << " ]" << endl;
}

void printMap(MapSquare *map, short sizeX, short sizeY)
{
  short x, y;
  for (y = 0; y < sizeY; ++y)
  {
    // cout << setw(2) << y << " - "; // DEBUG
    for (x = 0; x < sizeX; ++x)
    {
      // if (!(x % 10))
        // cout << x;
      cout << map[y * sizeX + x].display;
    }
    cout << endl;
  }
}

void printControlScheme()
{
  cout << endl;
  cout << "Move:     (W)      (Q) Quaff Potion           (C) Save (V) Load" << endl;
  cout << "       (A)(S)(D)   (H) Help                       (X) Exit" << endl;
  cout << "> ";
}





//******************************************************************************
//******************************   Save Game   *********************************
//******************************************************************************





//******************************************************************************
//******************************   Load Game   *********************************
//******************************************************************************

// bool loadFromFile(string filename, char *map, short maxX, short maxY)
bool loadFromFile(string filename, GameProperties &game)
{
  ifstream mapFile;
  mapFile.open(filename);
  if (mapFile.fail())
  {
    return false;
  }
  else
  {
    mapFile >> game.screenSizeX >> game.screenSizeY >> game.mapSizeX >> game.mapSizeY;
    
    
    //consume line break left in from >> operator:
    switchFromStreamToGet(mapFile);
    
    game.map = new MapSquare[game.mapSizeX * game.mapSizeY];

    // while (mapFile.get(c) && y <= game.mapSizeY && x <= game.mapSizeX)
    // char* line;
    string line;
    short x = 0, y = 0;
    while (y < game.mapSizeY && getline(mapFile, line).good())
    {
      // cout << "DEBUG: y=" << y << ", line=\"" << line << "\"" << endl;
      x = 0;
      //parse line:
      while (x < line.length() && line.at(x) != '\n' && line.at(x) != '\r')
      {
        // cout << "DEBUG: x=" << x << ",c=" << line.at(x) << endl;;
        game.map[y * game.mapSizeX + x].display = line.at(x++);
      }
      if (x != game.mapSizeX)
      {
        cout << "Improperly formatted Map file (" << filename << "). Line num " << (y + 1) << " is " << x << " wide, not the proper length of " << game.mapSizeX << "." << endl;
        return false;
      }
      ++y;
    }
    if (y != game.mapSizeY && x != game.mapSizeX)
    {
      cout << "Map file (" << filename << ") was not " << game.mapSizeX << " wide by " << game.mapSizeY << " tall. It was " << x << " by " << y << "." << endl;
      return false;
    }
    
    // link these assets we're about to find into GameProperties game and MapSquares
    // how to dynamically allocate game.gameAssets when we don't know how many assets there are?
    
    
    //read asset list at the bottom
    short linePos = 0;
    short data = 0;
    string currItem = "";
    short countActors = -1;
    while (getline(mapFile, line).good())
    {
      //line is not full enough to be a full asset line. ignore it.
      if (line.length() < 1)
        continue;
      
      //parse line:
      linePos = 0;
      
      game.gameAssets.push_back(new Asset);
      countActors++;
      
      //read char display
      game.gameAssets[countActors].display = line.at(linePos++);
      // reinterpret_cast<Actor*>(&game.gameAssets[countActors])->display = line.at(linePos++);
      // cout << "DEBUG: display=" << game.gameAssets[countActors].display << endl;
      ++linePos; //skip comma
      
      // read x coordinate
      while (linePos < line.length() && line.at(linePos) != '\n' && line.at(linePos) != '\r' && line.at(linePos) != ',')
        currItem += line.at(linePos++);
      game.gameAssets[countActors].x = atoi(currItem.c_str());
      // cout << "Data converted: newAsset->x=" << game.gameAssets[countActors].x << endl;
      currItem = "";
      ++linePos; //skip comma
      
      // read y coordinate
      while (linePos < line.length() && line.at(linePos) != '\n' && line.at(linePos) != '\r' && line.at(linePos) != ',')
        currItem += line.at(linePos++);
      game.gameAssets[countActors].y = atoi(currItem.c_str());
      // cout << "Data converted: newAsset->y=" << game.gameAssets[countActors].y << endl;
      currItem = "";
      ++linePos; //skip comma
      
      // read assetID
      while (linePos < line.length() && line.at(linePos) != '\n' && line.at(linePos) != '\r')
        currItem += line.at(linePos++);
      game.gameAssets[countActors].assetID = atoi(currItem.c_str());
      // cout << "Data converted: newAsset->assetID=" << game.gameAssets[countActors].assetID << endl;
      currItem = "";
      
      //P.S. I just gave in and used <sstream> in the function I wrote second, loadAssetFile(). I only left this mess here because I worked hard on it, and I'm therefore attached to it. **eye roll**
      
      (*(game.map + y * game.mapSizeX + x)).linkedActor = &game.gameAssets[countActors];
      (*(game.map + y * game.mapSizeX + x)).display = game.gameAssets[countActors].display;
      
      if (!loadAssetFile(game, game.gameAssets[countActors]))
      {
        cout << "Loading game asset (ID#" << game.gameAssets[countActors].assetID << ") failed. Cannot load save." << endl;
        return false;
      }
      
      if (game.gameAssets[countActors].isPlayer)
      {
        // game.player = &game.gameAssets[countActors];
        game.playerIndex = countActors;
        cout << "DEBUG: This asset was player: " << game.gameAssets[countActors].name << endl;  
      }
    }
    
    //Future idea: Move x/y and display from mapFile to assetFiles. They really belong there...
    
    //Future idea: add capability to put Items at the end of the list of Actors
    
    mapFile.close();
    return true;
  }
}


bool loadAssetFile(GameProperties &game, Asset &assetToLoad)
{
  ostringstream concatenator;
  concatenator << game.loadFolder << "\\" << assetToLoad.assetID << ".txt";
  string filename = concatenator.str();
  ifstream assetFile;
  assetFile.open(filename);
  if (assetFile.fail())
  {
    // cout << "DEBUG: Asset file open fail (ID#" << assetToLoad.assetID << ")" << endl;
    return false;
  }
  else
  {
    //didn't really want to use a string stream, but the alternative is either to_string() (which isn't found in <string> even with my complier set to C++11 mode...) or something messy like atoi(valueString.c_str()). ug.
    stringstream reader;
    string line, attribute;
    while (getline(assetFile, line).good())
    {
      reader << line;
      reader >> attribute;
      if (attribute == "name")
        reader >> assetToLoad.name;
      else if (attribute == "isPlayer")
        reader >> assetToLoad.isPlayer;
      else if (attribute == "isActor")
        reader >> assetToLoad.isActor;
      else if (attribute == "hp")
        reader >> assetToLoad.hp;
      else if (attribute == "ac")
        reader >> assetToLoad.ac;
      else if (attribute == "hitBonus")
        reader >> assetToLoad.hitBonus;
      else if (attribute == "damage")
        reader >> assetToLoad.damage;
      else if (attribute == "damageBonus")
        reader >> assetToLoad.damageBonus;
      else if (attribute == "qtyPotion")
        reader >> assetToLoad.qtyPotion;
      else if (attribute == "expTotal")
        reader >> assetToLoad.expTotal;
    }
    // cout << "name: " << assetToLoad.name << endl;
    // cout << "isplayer: " << assetToLoad.isPlayer << endl;
    // cout << "isActor: " << assetToLoad.isActor << endl;
    // cout << "hp: " << assetToLoad.hp << endl;
    // cout << "ac: " << assetToLoad.ac << endl;
    // cout << "hitBonus: " << assetToLoad.hitBonus << endl;
    // cout << "damage: " << assetToLoad.damage << endl;
    // cout << "damageBonus: " << assetToLoad.damageBonus << endl;
    // cout << "qtyPotion: " << assetToLoad.qtyPotion << endl;
    // cout << "expTotal: " << assetToLoad.expTotal << endl;
  }
  assetFile.close();
  return true;
}




//tests if there is a win32 console running this program right now
bool isRunningInAWin32Console()
{
  // uses a function (from the Input Buffer Read method), then ignores the result
  DWORD fdwSaveOldMode;
  if (GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &fdwSaveOldMode))
    return true; //console was found
  else
    return false; //console not found
}


//MSDN Method to resize the console window, increase buffer size
//https://msdn.microsoft.com/en-us/library/windows/desktop/ms686044(v=vs.85).aspx
bool resizeConsole_win32(short cols, short rows)
{
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD consoleSize = {cols, rows}; //{cols, rows}
  SMALL_RECT windowSize = {0, 0, static_cast<short>(cols - 1), static_cast<short>(rows - 1)};
  if(!SetConsoleScreenBufferSize(hStdout, consoleSize))
  {
    cout << "Setting the console size failed." << endl;
    return false;
  }
  if(!SetConsoleWindowInfo(hStdout, true, &windowSize ))
  {
    cout << "Setting the window size failed." << endl;
    return false;
  }
  return true;
}


//******************************************************************************
//***************************   Input / Output   *******************************
//******************************************************************************

//MSDN Method to read unbuffered console input
//https://msdn.microsoft.com/en-us/library/windows/desktop/ms685035(v=vs.85).aspx
bool getAKey(char& input, bool WIN32_MODE)
{
  if(!WIN32_MODE)
  {
    cin >> input;
    return true;
  }
  else
  {
    cout.flush(); //necessary to display anything in cout before ReadConsoleInput starts polling?
    
    HANDLE hStdin;
    DWORD fdwSaveOldMode;
    DWORD cNumRead, fdwMode;
    const short BUFF_SIZE = 8; // original buffer size: const int BUFF_SIZE = 128;
    INPUT_RECORD irInBuf[BUFF_SIZE];
    
    // Get the standard input handle.
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
    {
      cout << "Error: GetStdHandle" << endl;
      // SetConsoleMode(hStdin, fdwSaveOldMode); // Restore input mode on exit.
      return false; //ExitProcess(0);
    }

    // Save the current input mode, to be restored on exit.
    if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
    {
      cout << "Error: Getting the Console State Failed: No Console Found\nPlease run this program in a Windows Command Prompt console if you would like to enable input w/o pressing the enter key." << endl;
      // SetConsoleMode(hStdin, fdwSaveOldMode); // Restore input mode on exit.
      return false; //ExitProcess(0);
    }

    // change console mode to non-buffered input, allowing the Windows console to send input to C++ w/o waiting for the {Enter} key
    fdwMode = ENABLE_WINDOW_INPUT;
    if (!SetConsoleMode(hStdin, fdwMode))
    {
      cout << "Error: SetConsoleMode" << endl;
      SetConsoleMode(hStdin, fdwSaveOldMode); // Restore input mode on exit.
      return false; //ExitProcess(0);
    }

    // Loop to read and handle inputs until a valid character is read
    KEY_EVENT_RECORD keyEventRecord;
    int i = 0;
    bool isInputDone = false;
    while (!isInputDone)
    {
      // Wait for the events.
      if (!ReadConsoleInput(hStdin, irInBuf, BUFF_SIZE, &cNumRead))
      {
        cout << "Error: While waiting for ReadConsoleInput" << endl;
        SetConsoleMode(hStdin, fdwSaveOldMode); // Restore input mode on exit.
        return false; //ExitProcess(0);
      }
      
      if (DEBUG_MODE)
        if (cNumRead > 1)
          cout << "Warning: For this cycle, more than one (" << cNumRead << ") input event was read." << endl;

      // Check all events in the buffer (should be only one)
      for (i = 0; i < cNumRead; i++)
      {
        switch(irInBuf[i].EventType) //filter out all events that are not KEY_EVENT
        {
          case KEY_EVENT: // keyboard input
            keyEventRecord = irInBuf[i].Event.KeyEvent;
            //note: the hexadecimal "Virtual Key Codes" are from MSDN: https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
            // ctrl+c: has to check dwControlKeyState using bit masks
            if (keyEventRecord.wVirtualKeyCode == 0x43 && (keyEventRecord.dwControlKeyState & 0x0008 || keyEventRecord.dwControlKeyState & 0x0004) && !keyEventRecord.bKeyDown)
            {
              cout << "Ctrl+C has been used to kill the process." << endl;
              ExitProcess(0); //from MSDN methods
            }
            if (!keyEventRecord.bKeyDown) //if the keyboard key has not been released yet, ignore it
            {
              isInputDone = true; //assume input is good. change it to false if input is actually bad
              
              //test if this is an allowed character
              if (keyEventRecord.wVirtualKeyCode >= '0' && keyEventRecord.wVirtualKeyCode <= '9')
                input = keyEventRecord.wVirtualKeyCode; // - 0x30 + '0'; //note: that was useless, 0x30=='0'==48. I need to check my ASCII table better!
              else if (keyEventRecord.wVirtualKeyCode >= 'A' && keyEventRecord.wVirtualKeyCode <= 'Z')
                input = keyEventRecord.wVirtualKeyCode;
              else if (keyEventRecord.wVirtualKeyCode == ' ') //space bar
                input = ' ';
              else if (keyEventRecord.wVirtualKeyCode == 13) //carriage return
                input = '\n';
              else
                isInputDone = false;
              if (isInputDone)
                // printf("%c", input); //no longer needed b/c I figured out cout.flush() before opening up the buffer to wait for input
                cout << input;
            }
          break;

          // Ignore all other potential event types
          case MOUSE_EVENT: // mouse input
          case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
          case FOCUS_EVENT:  // disregard focus events
          case MENU_EVENT:   // disregard menu events
          default:
            break;
        }
      }
    }
    
    // Restore input mode on exit.
    SetConsoleMode(hStdin, fdwSaveOldMode);
    return true; //no errors
  }
}

//clear screen (will do it nicely using MSDN's console-handle method if enabled by WIN32_MODE
bool cls(bool WIN32_MODE)
{
  if (WIN32_MODE)
    win32_cls();
  else //will create a lot of flicker! ew.
    for (int i = 0; i < 30; ++i)
      cout << endl;
}

//MSDN method of clearing the console by writing ' ' to every spot
//Reference: https://msdn.microsoft.com/en-us/library/windows/desktop/ms682022(v=vs.85).aspx
bool win32_cls()
{
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD coordScreen = {0, 0}; // top, left corner of the console
  DWORD cCharsWritten;
  CONSOLE_SCREEN_BUFFER_INFO csbi; 
  DWORD dwConSize;

  // Get the number of character cells in the current buffer. 
  if(!GetConsoleScreenBufferInfo(hConsole, &csbi))
    return false;
  dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

  // Fill the entire screen with blanks.
  if( !FillConsoleOutputCharacter(hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten))
    return false;
  // Get the current text attribute.
  if(!GetConsoleScreenBufferInfo(hConsole, &csbi))
    return false;
  // Set the buffer's attributes accordingly.
  if(!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten)) // Receive number of characters written
    return false;

  // Put the cursor at its home coordinates.
  SetConsoleCursorPosition(hConsole, coordScreen);
  
  return true;
}

//function from Savitch 9th ed Ch 6 pg 347
void switchFromStreamToGet(istream &strm)
{
  char temp;
  do
  {
    strm.get(temp);
    // cout << static_cast<int>(temp) << endl;
  } while (temp != '\n' && temp != '\0');
}
