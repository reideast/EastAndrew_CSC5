/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on February 5, 2015, 5:54 PM
    Purpose: Play an ASCII-text based RPG/Adventure/Maze game inspired by Rogue
 */


  /*
  implement this:
  
  DONE: player is a STRUCT
  DONE: monsters struct
  
  DONE: all NPC are in a (vector)
  player moves
  then iterate the vector for all NPC to take actions
  
  help screen
  inventory screen
  -> sorting requirement: sort the inventory items
  
  note: (x) -> display msg -> NOT (y/n) -> clear exit state, does NOT clear msg
  
  DONE: battle screen
  
  status dictionary from file
  
  save game to file
  save/load: Move x/y and display from mapFile to assetFiles. They really belong there...
  
  search/sort:
  game.assets[] -> sort, then binary search?
  
  DONE: remove DEBUG_MODE global
  chg SQ_EMPTY '#' and ' ' and to non-global
  
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
#include <cstdlib>

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

const char SQ_EMPTY = ' ';
const char SQ_WALL = '#';

const int LINE_MAX = 80;


//Struct Prototypes
struct Asset
{
  short assetID;
  char display;
  short x;
  short y;
  
  string name;
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
  short potionHeals;
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

enum class GameState {Map, Fight, Dead, Save, Load, Help, Dialog, Exit};

struct GameProperties
{
  GameState gameState;
  
  MapSquare *map;
  
  vector<Asset *> gameAssets;
  Asset *player;
  
  short currStatus;
  vector<string> statusDictionary;
  
  string dataFolder; //default to "gameMap1"
  bool userRenamedSave;
  
  short mapSizeX;
  short mapSizeY;
  short screenSizeX;
  short screenSizeY;
};

//Function Prototypes

//screen display:
// void printStatus(string line1, string line2, short hp = 100, short mp = 100, short qtyPotion = 3);
void printStatus(GameProperties &game);
void printHelp();
void printMap(MapSquare *map, short sizeX, short sizeY);
void printFight(GameProperties &game, Asset* monster, Asset* player);
void printControlScheme(GameState currState);
bool cls(bool WIN32_MODE = false);
bool cls_win32();
void clearStreamNewlines(istream &strm);

//execute actions
bool playerTurn(GameProperties &game, bool WIN32_MODE = false);
bool monstersTurn(GameProperties &game);
bool movePlayer(GameProperties &game, short x, short y, bool WIN32_MODE = false);
bool overwriteSquare(MapSquare *from, MapSquare *to);
bool fightMonster(GameProperties &game, Asset* monster, Asset* player, bool WIN32_MODE = false);
short rollDie(short d);
bool drinkPotion(Asset *player); //returns false if there wasn't a potion to drink
short findAssetIndex(vector<Asset *> &assets, short assetID);

//user input:
bool getAKey(char& input, bool WIN32_MODE = false);

//file I/O:
bool loadFromFile(GameProperties &game);
bool loadAssetFile(GameProperties &game, Asset &assetToLoad);
bool saveToFile(GameProperties &game);

//system checks:
bool isRunningInAWin32Console();
bool resizeConsole_win32(short cols, short rows);
















//Execution Begins Here
int main(int argc, char** argv)
{
  srand(chrono::system_clock::now().time_since_epoch().count());

  // int rolls[7] = {};
  // for (int i = 0; i < 100000; ++i)
    // rolls[rollDie(6)]++;
  // for (int i = 1; i <= 6; ++i)
    // cout << rolls[i] << endl;;
  
  GameProperties game;
  game.dataFolder = "gameMap1"; //default game folder
  game.userRenamedSave = false; //user has not used SaveAs to rename the load/save dir
  
  //get properties and assets from save files
  if (!loadFromFile(game))
  {
    cout << "Reading game from disk has failed." << endl;
    delete [] game.map;
    return 1;
  }
  
  
  //note: move this into the struct Game
  short countStatus = 0;
  game.statusDictionary.push_back("You wake up in a dank room. You hear water slowly dripping,\nand you feel slimy mold on the floor.");
  short STATUS_INIT = countStatus++;
  // game.statusDictionary.push_back("Are you sure you want to exit?\n(y/n)");
  // short STATUS_EXIT = countStatus++;
  game.currStatus = STATUS_INIT;
  game.statusDictionary.push_back("You have died. Hopefully the next adventurer will have more luck.");
  short STATUS_DEAD = countStatus++;
  game.currStatus = STATUS_INIT;
  
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
  else //user is running a win32 console; resize it to size requested by gameMap.txt
  {
    if (!resizeConsole_win32(game.screenSizeX, game.screenSizeY)) //{cols, rows}
      cout << "Resizing the console window failed. This program will not work right with a console buffer smaller than 100 characters wide by 40 tall. Please use the settings to resize this console window before continuing." << endl;
  }
  
  //game running loop
  //each iteration represents one "turn"
  char input = 0;
  bool isGameRunning = true;
  while (isGameRunning)
  {
    cls(WIN32_MODE);
    
    if (game.gameState == GameState::Map)
    {
      printMap(game.map, game.mapSizeX, game.mapSizeY);
      printStatus(game);
      printControlScheme(game.gameState);
      
      if (playerTurn(game, WIN32_MODE)) //true if player made an actual move, so give the monsters a turn
        monstersTurn(game);
    }
    else if (game.gameState == GameState::Help)
    {
      printHelp();
      printControlScheme(game.gameState);
      getAKey(input, WIN32_MODE); //get a key and trash it
      game.gameState = GameState::Map;
    }
    else if (game.gameState == GameState::Exit)
    {
      cout << endl << "Would you like to quit the game?" << endl;
      cout << "  (C) Save and quit" << endl;
      cout << "  (Y) Yes, quit now" << endl;
      cout << "  (N) Cancel" << endl;
      cout << "> ";
      if (getAKey(input, WIN32_MODE))
      {
        switch (input)
        {
          case 'C': case 'c':
            cout << "Saving game now." << endl;
            if (!saveToFile(game))
            {
              cout << "The game save failed. Are you sure you want to exit without saving? (y/n) ";
              if (getAKey(input, WIN32_MODE))
              {
                if (input != 'Y' && input != 'y')
                {
                  game.gameState = GameState::Map;
                  break;
                }
                else
                  cout << "The game was not saved.";
              }
              else
                cout << "Key input failed." << endl;
            }
            else
            {
              cout << "Saved to " << game.dataFolder << "." << endl;
            }
          case 'Y': case 'y':
            cout << "Thank you for playing!" << endl;
            isGameRunning = false;
            break;
          case 'N': case 'n':
          default:
            game.gameState = GameState::Map;
        }
      }
      else
      {
        cout << "Key input failed." << endl;
      }
    }
    else if (game.gameState == GameState::Dead)
    {
      game.currStatus = STATUS_DEAD;
      printMap(game.map, game.mapSizeX, game.mapSizeY);
      printStatus(game);
      
      printControlScheme(GameState::Dialog);
      getAKey(input, WIN32_MODE); //get a key and trash it
      
      cout << "Please try again!" << endl;
      isGameRunning = false;
    }
    else if (game.gameState == GameState::Load)
    {
      cout << "Are you sure you want to load a game?" << endl << "You will loose any unsaved progress. (y/n) " <<endl;
      if (getAKey(input, WIN32_MODE))
      {
        if (input == 'Y' || input == 'y')
        {
          if (!game.userRenamedSave) //user has not provided a folder name yet
          {
            cout << "What is the folder name of your existing save game?" << endl;
            cout << "If it doesn't exist, the load will fail." << endl;
            cout << "> ";
            cin >> game.dataFolder;
            if (game.dataFolder.size() == 0)
            {
              cout << "The save folder cannot be blank." << endl;
              printControlScheme(GameState::Dialog);
              getAKey(input, WIN32_MODE); //get a key and trash it
              game.gameState = GameState::Map;
            }
            else if (game.dataFolder == "gameMap1")
            {
              cout << "That is the default load directory." << endl;
              printControlScheme(GameState::Dialog);
              getAKey(input, WIN32_MODE); //get a key and trash it
              game.gameState = GameState::Map;
            }
            else
            {
              game.userRenamedSave = true;
            }
          }
          
          if (game.userRenamedSave) //there is now a proper load name
          {
            if (!loadFromFile(game))
            {
              cout << "Load from folder named " << game.dataFolder << " failed!" << endl;
              game.userRenamedSave = false;
            }
            else
              cout << "Loaded game from " << game.dataFolder << "." << endl;
            printControlScheme(GameState::Dialog);
            getAKey(input, WIN32_MODE); //get a key and trash it
            game.gameState = GameState::Map;
          }
        }
        else // 'N' no, do not save
        {
          game.gameState = GameState::Map;
        }
      }
      else
      {
        cout << "Key input failed." << endl;
      }
    }
    else if (game.gameState == GameState::Save)
    {
      if (!game.userRenamedSave) //user has not provided a folder name yet
      {
        cout << "What is the folder name of your save game?" << endl;
        cout << "If it already exists, it will be overwritten." << endl;
        cout << "> ";
        cin >> game.dataFolder;
        if (game.dataFolder.size() == 0)
        {
          cout << "The save folder cannot be blank." << endl;
          printControlScheme(GameState::Dialog);
          getAKey(input, WIN32_MODE); //get a key and trash it
          game.gameState = GameState::Map;
        }
        else if (game.dataFolder == "gameMap1")
        {
          cout << "You cannot save to the default load directory." << endl;
          printControlScheme(GameState::Dialog);
          getAKey(input, WIN32_MODE); //get a key and trash it
          game.gameState = GameState::Map;
        }
        else
        {
          game.userRenamedSave = true;
        }
      }
      
      if (game.userRenamedSave) //there is now a proper save name
      {
        if (!saveToFile(game))
        {
          cout << "Save to folder named " << game.dataFolder << " failed!" << endl;
          game.userRenamedSave = false;
        }
        else
          cout << "Saved to " << game.dataFolder << "." << endl;
        printControlScheme(GameState::Dialog);
        getAKey(input, WIN32_MODE); //get a key and trash it
        game.gameState = GameState::Map;
      }
    }
    else
    {
      cout << "Error: The game is in an invalid state and cannot continue." << endl;
      isGameRunning = false;
      printControlScheme(GameState::Dialog);
      getAKey(input, WIN32_MODE); //get a key and trash it
    }
  }
  
  delete [] game.map;
  return 0;
}



//******************************************************************************
//********************************   Do Game    ********************************
//******************************************************************************

bool playerTurn(GameProperties &game, bool WIN32_MODE)
{
  char input = 0;
  if (getAKey(input, WIN32_MODE))
  {
    if (WIN32_MODE)
      cout << endl;
    switch ((input >= 'a' && input <= 'z') ? (input - 'a' + 'A') : input) //to upper
    {
      //movement
      case 'W':
        return movePlayer(game, game.player->x, game.player->y - 1, WIN32_MODE); //returns false if move was invalid (like trying to go out of bounds) so this turn will not count
      case 'A':
        return movePlayer(game, game.player->x - 1, game.player->y, WIN32_MODE);
      case 'S':
        return movePlayer(game, game.player->x, game.player->y + 1, WIN32_MODE);
          cout << "Move successful!";
      case 'D':
        return movePlayer(game, game.player->x + 1, game.player->y, WIN32_MODE);
        
      //other game controls (quaff potion, inventory, etc)
      case 'Q':
        return drinkPotion(game.player); //true if potion was drunk and counts as a move, false if no potion
        
      //meta-game control (exit, help, save)
      case 'X':
        game.gameState = GameState::Exit;
        return false;
      case 'H':
        game.gameState = GameState::Help;
        return false;
      case 'C':
        game.gameState = GameState::Save;
        return false;
      case 'V':
        game.gameState = GameState::Load;
        return false;
      
      //any other valid keyboard key was returned
      default:
        // cout << "Keyboard input doesn't do anything" << endl;
        return false; //incorrect key, so don't give the monsters a turn
    }
  }
  else
  {
    cout << "Key input failed." << endl;
    return false;
  }
}

//returns false if there wasn't a potion to drink
bool drinkPotion(Asset *player)
{
  // cout << "DEBUG: heals:"<<player->potionHeals<<endl;
  if (player->isPlayer)
    if (player->qtyPotion > 0)
    {
      player->hp += player->potionHeals;
      --player->qtyPotion;
      return true;
    }
  
  return false;
}

bool movePlayer(GameProperties &game, short x, short y, bool WIN32_MODE)
{
  // cout << "DEBUG: Moving player to (" << x << "," << y << ")" << endl;
  // cout << "DEBUG: mapSize: (" << game.mapSizeX << "," << game.mapSizeY << ")" << endl;
  if (x >= 0 && x < game.mapSizeX && y >= 0 && y < game.mapSizeY)
  {
    MapSquare *potentialMove = (game.map + y * game.mapSizeX + x);
    if (potentialMove->display == SQ_EMPTY)
    {
      overwriteSquare((game.map + game.player->y * game.mapSizeX + game.player->x), potentialMove);
      game.player->x = x;
      game.player->y = y;
      return true;
    }
    else if (potentialMove->display == SQ_WALL)
    {
      //no move
    }
    else
    {
      //not a wall and not an empty square
      //what is it??
      if (potentialMove->linkedActor->isActor)
      {
        game.gameState = GameState::Fight;
        fightMonster(game, potentialMove->linkedActor, game.player, WIN32_MODE);
      }
    }
  }
  else
  {
    // cout << "DEBUG: Tried to move player out-of-bounds." << endl;
    return false;
  }
}

//This is a dumb function. It does not test for existence first, and it simply overwrites what is in "to" and simply leaves "from" to set to SQ_EMPTY;
bool overwriteSquare(MapSquare *from, MapSquare *to)
{
  to->display = from->display;
  from->display = SQ_EMPTY;
  to->linkedActor = from->linkedActor;
  from->linkedActor = NULL; //nothing pointer
}

bool fightMonster(GameProperties &game, Asset* monster, Asset* player, bool WIN32_MODE)
{
  cls(WIN32_MODE);
  cout << "You are attacking a " << monster->name << "!" << endl;
  
  bool playerActionValid = false;
  short playerAtkRoll = 0, playerDmgRoll = 0, monsterAtkRoll = 0, monsterDmgRoll = 0, playerDefenseBonus = 0, monsterDefenseBonus = 0;
  char input = 0;
  while (monster->hp > 0 && player->hp > 0)
  {
    playerActionValid = true;
    playerAtkRoll = 0, playerDmgRoll = 0, monsterAtkRoll = 0, monsterDmgRoll = 0, playerDefenseBonus = 0;
    
    // cls(WIN32_MODE);
    printFight(game, monster, player);
    printControlScheme(game.gameState);
    
    if (getAKey(input, WIN32_MODE))
    {
      cls(WIN32_MODE);
      switch ((input >= 'a' && input <= 'z') ? (input - 'a' + 'A') : input) //to upper
      {
        case 'A':
          playerAtkRoll = rollDie(20);
          cout << "You attack the " << monster->name << "! ";
          if (monsterDefenseBonus > 0) cout << "It is defending. ";
          cout << "You roll a " << playerAtkRoll << " on a 20-sided die." << endl;
          if ((playerAtkRoll + player->hitBonus) >= (monster->ac + monsterDefenseBonus))
          {
            playerDmgRoll = rollDie(player->damage);
            cout << "You hit the " << monster->name << " with a total attack of " << (playerAtkRoll + player->hitBonus) << "!" << endl;
            cout << "You deal " << (playerDmgRoll + player->damageBonus) << " damage!" << endl;
            monster->hp -= (playerDmgRoll + player->damageBonus);
          }
          else
          {
            cout << "You miss the " << monster->name << " with your attack total of " << (playerAtkRoll + player->hitBonus) << "." << endl << endl;
          }
          break;
        
        case 'D':
          playerDefenseBonus = 5;
          cout << "You are defending! You get + " << playerDefenseBonus << " AC." << endl << endl << endl;
          break;
         
        case 'Q':
          if (playerActionValid = drinkPotion(player)) //true if potion was drunk and counts as a move, false if no potion
            cout << "You drink a potion to heal " << player->potionHeals << " HP!" << endl << endl << endl;
          else
            cout << "You do not have a potion to drink." << endl << endl << endl;
          break;
          
        default:
          cout << "That key does nothing." << endl << endl << endl;
          playerActionValid = false; //incorrect key, so don't give the monsters a turn
      }
    }
    else
    {
      cout << "Key input failed." << endl << endl << endl;
      playerActionValid = false;
    }
    
    if (playerActionValid)
    {
      monsterDefenseBonus = 0;
      cout << endl;
      if (monster->hp > 0)
      {
        //monster "AI" == 80% random chance to attack, 20% to defend
        if (rollDie(10) < 9) //attack on a 1-8
        {
          monsterAtkRoll = rollDie(20);
          cout << "The " << monster->name << " attacks you! It rolls a " << monsterAtkRoll << " on a 20-sided die." << endl;
          if ((monsterAtkRoll + monster->hitBonus) >= (player->ac + playerDefenseBonus))
          {
            monsterDmgRoll = rollDie(monster->damage);
            cout << "The monster hits with a total attack of " << (monsterAtkRoll + monster->hitBonus) << "." << endl;
            cout << "It does " << (monsterDmgRoll + monster->damageBonus) << " damage to you!" << endl;
            player->hp -= (monsterDmgRoll + monster->damageBonus);
          }
          else
          {
            cout << "The monster misses you!" << endl << endl;
          }
        }
        else //defend on a 9-10
        {
          monsterDefenseBonus = 5;
          cout << "The monster defends for +" << monsterDefenseBonus << " AC." << endl << endl << endl;
        }
      }
    }
    else
    {
      cout << endl << endl << endl << endl;
    }
  }
  
  if (monster->hp <= 0)
  {
    cout << endl << endl << endl;
    printFight(game, monster, player);
    cout << endl;
    cout << "You are victorious! You have killed the " << monster->name << "! You gain " << monster->exp << " experience points." << endl;
    player->expTotal += monster->exp;
    
    printControlScheme(GameState::Dialog);
    getAKey(input, WIN32_MODE); //get a key and trash it
    
    //remove monster from map and game asset vector
    (game.map + monster->y * game.mapSizeX + monster->x)->display = SQ_EMPTY;
    (game.map + monster->y * game.mapSizeX + monster->x)->linkedActor = nullptr;
    short found = findAssetIndex(game.gameAssets, monster->assetID);
    // cout << "DEBUG: monster found in asset vector as pos=" << found << endl;
    if (found != -1)
      game.gameAssets.erase(game.gameAssets.begin() + found);
    else
      cout << "Error: Monster was not in the game's asset list." << endl;
    
    game.gameState = GameState::Map;
  }
  if (player->hp <= 0)
  {
    cout << endl << endl << endl;
    printFight(game, monster, player);
    cout << "You have been killed by the " << monster->name << "." << endl;

    //show deceased player as 'x' on the map
    (game.map + player->y * game.mapSizeX + player->x)->display = 'x';
    
    printControlScheme(GameState::Dialog);
    getAKey(input, WIN32_MODE); //get a key and trash it

    game.gameState = GameState::Dead;
  }
}

short rollDie(short d)
{
  if (d > 0)
    return rand() % d + 1;
  else
    return -1;
}

short findAssetIndex(vector<Asset *> &assets, short assetID)
{
  for (short i = 0; i < assets.size(); ++i)
    if (assets[i]->assetID == assetID)
      return i;
    
  return -1;
}

bool monstersTurn(GameProperties &game)
{
  //implement monster AI here!
  
  //move towards PC when PC is in radius monster->sightRange
  //move away from PC if monster is timid (or PC is higher level?)
  //wander around the dungeon sometimes
  
  //group with similar monsters?
}


//******************************************************************************
//********************************   Graphics   ********************************
//******************************************************************************

void printStatus(GameProperties &game)
{
  cout << endl;
  cout << game.statusDictionary[game.currStatus] << endl;
  cout << endl;
  cout << " [ HP: " << game.player->hp << " ]   [ Potions: " << game.player->qtyPotion << " ]   [ EXP: " << game.player->expTotal << " ]" << endl;
}

void printMap(MapSquare *map, short sizeX, short sizeY)
{
  short x, y;
  for (y = 0; y < sizeY; ++y)
  {
    // cout << setw(2) << y << " - "; // DEBUG
    for (x = 0; x < sizeX; ++x)
      cout << map[y * sizeX + x].display;
    cout << endl;
  }
}

void printControlScheme(GameState currState)
{
  cout << endl;
  if (currState == GameState::Map)
    cout << "Move:     (W)      (Q) Quaff Potion           (C) Save (H) Help" << endl
         << "       (A)(S)(D)                              (V) Load (X) Exit" << endl;
  else if (currState == GameState::Fight)
    cout << "     (A) Attack   (D) Defend   (Q) Quaff Potion" << endl << endl;
  // else if (currState == GameState::Exit)
    // cout << "                                              (C) Save (V) Load" << endl
         // << "                                                  (X) Exit" << endl;
  else if (currState == GameState::Help || currState == GameState::Dialog)
    cout << " (R) Return to previous screen" << endl << endl;
  else
    cout << endl << endl;
  cout << "> ";
}

void printHelp()
{
  cout << "Welcome to the Adventures of \"Q\"!" << endl;
  cout << endl;
  cout << "You are an eager dungeon-delver named Q, and you must navigate a" << endl;
  cout << "dungeon full of monsters to win the game." << endl;
  cout << endl;
  cout << "Use the WASD keys to navigate the dungeon map. When you run into a monster," << endl;
  cout << "you will fight it! You can drink a potion to regain hit points with the Q key." << endl;
  cout << endl;
  cout << "In a battle, you can attack with your sword or defend with your shield." << endl;
  cout << "Hit the monster to damage its hp before it depletes yours!" << endl;
  cout << endl;
  cout << "Use the C key to save your game to a folder name you type in. It will overwrite" << endl;
  cout << "anything previously under that name. Use the V key to load back from a file." << endl;
  cout << endl;
  cout << endl;
  cout << "Can you defeat the terrifying dragon at the end of the dungeon??" << endl;
  cout << endl;
  cout << endl;
  cout << endl;
}

void printFight(GameProperties &game, Asset* monster, Asset* player)
{
  cout << endl;
  cout << endl;
  cout << setw(20) << "Player" << setw(20) << monster->name << endl;
  cout << setw(20) << "--------------" << setw(20) << "--------------" << endl;
  cout << setw(15) << "HP" << setw(5) << player->hp << setw(15) << "HP" << setw(5) << monster->hp << endl;
  cout << setw(15) << "Attack" << setw(5) << player->hitBonus << setw(15) << "Attack" << setw(5) << monster->hitBonus << endl;
  cout << setw(15) << "Damage 1d" << setw(2) << left << player->damage << "+" << right << setw(2) << player->damageBonus << setw(15) << "Damage 1d" << left << setw(2) << monster->damage << "+" << right << setw(2) << monster->damageBonus << endl;
  cout << setw(15) << "AC" << setw(5) << player->ac << setw(15) << "AC" << setw(5) << monster->ac << endl;
  cout << setw(15) << "Potions" << setw(5) << player->qtyPotion << endl;
}

















































//******************************************************************************
//******************************   Save Game   *********************************
//******************************************************************************


bool saveToFile(GameProperties &game)
{
  
  //return true if save is good
  
  //return false if save is bad
  
  return false;
  return true;
}


//******************************************************************************
//******************************   Load Game   *********************************
//******************************************************************************

// bool loadFromFile(string filename, char *map, short maxX, short maxY)
bool loadFromFile(GameProperties &game)
{
  if (game.userRenamedSave) //user has asked to load/save already, so delete GameProperties
  {
    delete [] game.map;
    
  }
  
  ostringstream concatenator;
  concatenator << game.dataFolder << "\\" << "gameMap.txt";
  string filename = concatenator.str();
 
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
    clearStreamNewlines(mapFile);
    
    game.map = new MapSquare[game.mapSizeX * game.mapSizeY]; //malloc??

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
    
    
    // Read asset list
    short linePos = 0;
    string currItem = "";
    Asset *newAsset;
    bool foundPlayer = false;
    while (getline(mapFile, line).good())
    {
      //line is not full enough to be a full asset line. ignore it.
      if (line.length() < 1)
        continue;
      
      //parse line:
      linePos = 0;
      
      // newAsset = new Asset; // Note: The parens() are IMPORTANT! It initializes all members of the struct to default values (zero) when called as "new Asset()"!!
      newAsset = new Asset();
      game.gameAssets.push_back(newAsset);
      
      //read char display
      newAsset->display = line.at(linePos++);
      // reinterpret_cast<Actor*>(&game.gameAssets[countActors])->display = line.at(linePos++);
      // cout << "DEBUG: display=" << game.gameAssets[countActors].display << endl;
      ++linePos; //skip comma
      
      // read x coordinate
      while (linePos < line.length() && line.at(linePos) != '\n' && line.at(linePos) != '\r' && line.at(linePos) != ',')
        currItem += line.at(linePos++);
      newAsset->x = atoi(currItem.c_str());
      // cout << "Data converted: newAsset->x=" << game.gameAssets[countActors].x << endl;
      currItem = "";
      ++linePos; //skip comma
      
      // read y coordinate
      while (linePos < line.length() && line.at(linePos) != '\n' && line.at(linePos) != '\r' && line.at(linePos) != ',')
        currItem += line.at(linePos++);
      newAsset->y = atoi(currItem.c_str());
      // cout << "Data converted: newAsset->y=" << game.gameAssets[countActors].y << endl;
      currItem = "";
      ++linePos; //skip comma
      
      // read assetID
      while (linePos < line.length() && line.at(linePos) != '\n' && line.at(linePos) != '\r')
        currItem += line.at(linePos++);
      newAsset->assetID = atoi(currItem.c_str());
      // cout << "Data converted: newAsset->assetID=" << game.gameAssets[countActors].assetID << endl;
      currItem = "";
      
      //P.S. I just gave in and used <sstream> in the function I wrote second, loadAssetFile(). I only left this mess here because I worked hard on it, and I'm therefore attached to it. **eye roll**
      
      (game.map + newAsset->y * game.mapSizeX + newAsset->x)->linkedActor = newAsset;
      (game.map + newAsset->y * game.mapSizeX + newAsset->x)->display = newAsset->display;
      
      if (!loadAssetFile(game, *newAsset))
      {
        cout << "Loading game asset (ID#" << newAsset->assetID << ") failed. Cannot load this save folder." << endl;
        mapFile.close();
        return false;
      }
      
      if (newAsset->isPlayer)
      {
        if (foundPlayer) //already found
          cout << "More than one player asset was found. This is surely an error. Only the first one will be on your side..." << endl;
        else
          game.player = newAsset;
        foundPlayer = true;
      }
    }
    if (!foundPlayer)
    {
      cout << "A player asset was not loaded from this save file. The game cannot continue." << endl;
      mapFile.close();
      return false;
    }
    
    
    //Future idea: Move x/y and display from mapFile to assetFiles. They really belong there...
    
    //Future idea: add capability to put Items at the end of the list of Actors
    
    mapFile.close();
    
    //set up game as it should start
    game.gameState = GameState::Map;
    
    return true;
  }
}


bool loadAssetFile(GameProperties &game, Asset &assetToLoad)
{
  ostringstream concatenator;
  concatenator << game.dataFolder << "\\" << assetToLoad.assetID << ".txt";
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
      else if (attribute == "exp")
        reader >> assetToLoad.exp;
      else if (attribute == "isPlayer")
        reader >> assetToLoad.isPlayer;
      else if (attribute == "qtyPotion")
        reader >> assetToLoad.qtyPotion;
      else if (attribute == "potionHeals")
        reader >> assetToLoad.potionHeals;
      else if (attribute == "expTotal")
        reader >> assetToLoad.expTotal;
    }
    // cout << "name: " << assetToLoad.name << endl;
    // cout << "display: " << assetToLoad.display << endl;
    // cout << "x: " << assetToLoad.x << endl;
    // cout << "y: " << assetToLoad.y << endl;
    // cout << "assetID: " << assetToLoad.assetID << endl;
    // cout << "isPlayer: " << assetToLoad.isPlayer << endl;
    // cout << "isActor: " << assetToLoad.isActor << endl;
    // cout << "hp: " << assetToLoad.hp << endl;
    // cout << "ac: " << assetToLoad.ac << endl;
    // cout << "hitBonus: " << assetToLoad.hitBonus << endl;
    // cout << "damage: " << assetToLoad.damage << endl;
    // cout << "damageBonus: " << assetToLoad.damageBonus << endl;
    // cout << "qtyPotion: " << assetToLoad.qtyPotion << endl;
    // cout << "potionHeals: " << assetToLoad.potionHeals << endl;
    // cout << "expTotal: " << assetToLoad.expTotal << endl;
    // cout << "exp: " << assetToLoad.exp << endl;
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
//********************************   Input   ***********************************
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
    
      // if (cNumRead > 1)
        // cout << "Warning: For this cycle, more than one (" << cNumRead << ") input event was read." << endl;

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
    cls_win32();
  else //will create a lot of flicker! ew.
    for (int i = 0; i < 30; ++i)
      cout << endl;
}

//MSDN method of clearing the console by writing ' ' to every spot
//Reference: https://msdn.microsoft.com/en-us/library/windows/desktop/ms682022(v=vs.85).aspx
bool cls_win32()
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
void clearStreamNewlines(istream &strm)
{
  char temp;
  do
  {
    strm.get(temp);
    // cout << static_cast<int>(temp) << endl;
  } while (temp != '\n' && temp != '\0');
}

  //****************************************************************************************************
  //test animation using cls()
/*   HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD coordScreen = { 0, 30 };
  //test cls:
  for (int i = 0; i < 77; ++i)
  {
    cls(WIN32_MODE);
    SetConsoleCursorPosition(hStdout, coordScreen);
    cout << string(i, ' ') << ">=-" << endl;
    //wait for ANIMATION_RATE to establish proper frame rate
    this_thread::sleep_for(chrono::milliseconds(ANIMATION_RATE)); //reference: http://stackoverflow.com/questions/4184468/sleep-for-milliseconds
  } */
  //****************************************************************************************************
 