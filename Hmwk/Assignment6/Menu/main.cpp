
/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on February 8, 2015, 6:10 PM
    Purpose: Copy and paste all my Assignment 6 Problems into a Menu Program
 */

//System Libraries
#include <iostream>
#include <string> //menu2
#include <cmath> //menu3
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes
void menu1();
bool checkHex(const char digits[], short numDigits);
bool addHexNumbers(const char op1[], const char op2[], char sum[], short numDigits);
void reverseString(const char orig[], char reversed[], short numDigits);
char addHexDigit(const char op1, const char op2, const char carryDigit, char& overflow);
char decToHexDigit(short dec);
short hexToDecDigit(char hex);

void menu2();
void test_menu2(char a[], short size);
short assign(char a[], string toAssign, short MAX);
bool delete_repeats(char orig[], short &size);
bool extract(char orig[], short position, short &size);
void printArray_menu2(const char orig[], short size);

void menu3();
void test_menu3(double a[], int size);
void printArray_menu3(const double orig[], int size);
double stdDev(const double a[], int size);
double avg(const double a[], int size);

void menu4();
void test_menu4(int a[], short size);
void insertionSort(int a[], short size);
void swap_menu4(int &a, int &b);
void printArray_menu4(const int orig[], short size);
bool isSorted(const int *a, int size); //cribbed from my in-class work

void menu5();
int playGame(char players[], int first); //players must be a 2-item array of the tokens to place on the board; first must be 0 or 1
void displayBoard(int board[], char players[]);
void getSquare(int &input, int board[]);
int checkWinner(int board[]); // returns -1 for no win, 0 for first player wins, 1 for second
int sum(int nums[], int first, int last);

void menu6();
void test_menu6(char a[]);
void reverse(char a[]);
void swap_menu6(char *a, char *b);
void printArrayInt(const char a[]);

void menu7();
int* create2DArray(int rows, int columns);
void set(int *arr, int rows, int columns, int desired_row, int desired_column, int val);
int get(int *arr, int rows, int columns, int desired_row, int desired_column);
void fill2DArray(int *arr, int rows, int columns);
void print2DArray(int *arr, int rows, int columns);


//GetInput: Get input from <iostream> between a minimum and maximum value
//  (From my Savitch_9thEd_Chap4_ProgProj1)
void getInput(string prompt, int& input, int min = 0, int max = ~(1 << (sizeof(int) * 8) - 1));


//Execution Begins Here
int main(int argc, char** argv)
{
  //main program, loops until user asks to quit (copied from my Savitch_9thEd_Chap3_ProgProj1)
  bool isUserFinished = false; //controls main loop
  int input = 0;
  while (!isUserFinished)
  {
    cout << "Please choose a menu option:" << endl;
    cout << "  1. Savitch_9thEd_Chap7_ProgProj2 - Hex Numeral Addition" << endl;
    cout << "  2. Savitch_9thEd_Chap7_ProgProj3 - Duplicate Value in Array" << endl;
    cout << "  3. Savitch_9thEd_Chap7_ProgProj4 - Standard Deviation" << endl;
    cout << "  4. Savitch_9thEd_Chap7_ProgProj6 - Insertion Sort" << endl;
    cout << "  5. Savitch_9thEd_Chap7_ProgProj10 - Tic-Tac-Toe" << endl;
    cout << "  6. Savitch_9thEd_Chap9_ProgProj4 - Reverse a C-String" << endl;
    cout << "  7. Savitch_9thEd_Chap9_ProgProj7 - 2D Dynamic Array" << endl;
    cout << "  8. Exit" << endl;
    getInput("> ", input, 1, 8);
    
    switch (input)
    {
      case 1: menu1(); break;
      case 2: menu2(); break;
      case 3: menu3(); break;
      case 4: menu4(); break;
      case 5: menu5(); break;
      case 6: menu6(); break;
      case 7: menu7(); break;
      case 8: isUserFinished = true; break;
      default: cout << "Invalid menu choice." << endl;
    }
  }
  return 0;
}

void getInput(string prompt, int& input, int min, int max)
{
  bool isInputValid = false; //controls input loop (ie, loop until input is right)
  while (!isInputValid)
  {
    cout << prompt;
    cin >> input;
    if (input < min)
      cout << "The input cannot be less than " << min << ". Please input again." << endl;
    else if (input > max)
      cout << "The input cannot be greater than " << max << ". Please input again." << endl;
    else
      isInputValid = true;
  }
}

//**********************************************************************
//**********************************************************************
//**********************************************************************
void menu1()
{
  //main program, loops until user asks to quit (copied from my Savitch_9thEd_Chap3_ProgProj1)
  bool isUserFinished = false; //controls main loop
  char quit = 0;
  while (!isUserFinished)
  {
    const short MAX_DIGITS = 11; // 10 + '\0'
    
    char operand[2][MAX_DIGITS] = {{},{}}, sum[MAX_DIGITS] = {};
    
    for (int i = 0; i < 2; ++i)
    {
      bool isInputDone = false;
      do
      {
        cout << "Please input hex operand #" << (i + 1) << ": ";
        cin >> operand[i];
        if (checkHex(operand[i], MAX_DIGITS))
          isInputDone = true;
        else
          cout << "\"" << operand[i] << "\" is not a valid hexadecimal numeral. Try again." << endl;
      } while (!isInputDone);
    }
    
    if (addHexNumbers(operand[0], operand[1], sum, MAX_DIGITS))
      cout << operand[0] << " + " << operand[1] << " = " << sum << endl;
    else
      cout << "Addition Overflow" << endl;
    
    
    //determine if the user would like to repeat the calculation (copied from my Savitch_9thEd_Chap3_ProgProj1)
    cout << endl;
    cout << "Would you like to do more calculations? (N to quit) ";
    cin >> quit;
    if (quit == 'N' || quit == 'n')
      isUserFinished = true;
    else
      cout << endl; //a blank line for readability
  }
}



bool checkHex(const char digits[], short numDigits)
{
  for (int i = 0; i < (numDigits - 1); ++i) //don't check null terminator char
  {
    if (digits[i] == '\0')
      break;
    else
    {
      if (!((digits[i] >= '0' && digits[i] <= '9') ||
           (digits[i] >= 'A' && digits[i] <= 'F') ||
           (digits[i] >= 'a' && digits[i] <= 'f')))
      {
        return false;
      }
    }
  }
  return true;
}

bool addHexNumbers(const char op1[], const char op2[], char sum[], short numDigits)
{
  char *reversed1 = new char[numDigits], *reversed2 = new char[numDigits], *reversedSum = new char[numDigits];
  
  reverseString(op1, reversed1, numDigits);
  reverseString(op2, reversed2, numDigits);
  
  char carryDigit = '0';
  bool endOf1 = false, endOf2 = false;
  for (short i = 0; i < (numDigits - 1); ++i) //don't add the null terminator
  {
    if (reversed1[i] == '\0') endOf1 = true;
    if (reversed2[i] == '\0') endOf2 = true;
    if (!endOf1 && !endOf2)
    {
      reversedSum[i] = addHexDigit((endOf1 ? '0' : reversed1[i]), (endOf2 ? '0' : reversed2[i]), carryDigit, carryDigit);
    }
    else
    {
      reversedSum[i] = '\0';
      break;
    }
  }
  reverseString(reversedSum, sum, numDigits);
  
  if (carryDigit == '0') //the final addition carried anything but a 0
    return true;
  else
    return false;
}

void reverseString(const char orig[], char reversed[], short numDigits)
{
  short length = 0;
  while (length < numDigits && orig[length] != '\0') // less than (not equal to) assumes the last char of array is null term. depending on && short-circuit to not read invalid memory
    length++;
  // cout << "DEBUG: length=" << length << endl;
  short start, end;
  for (start = 0, end = (length - 1); start < length; ++start, --end)
  {
    // cout << "DEBUG: reversed[" << start << "]=" << reversed[start] << " set to orig[" << end << "]=" << orig[end] << endl;
    reversed[start] = orig[end];
  }
  reversed[start] = '\0';
  // cout << "DEBUG reverseString: orig=\"" << orig << "\", reversed=\"" << reversed << "\"" << endl;
}

char addHexDigit(const char op1, const char op2, const char carryDigit, char& overflow)
{
  short sum = hexToDecDigit(op1) + hexToDecDigit(op2) + hexToDecDigit(carryDigit);
  // cout << "DEBUG addHexDigit: " << hexToDecDigit(op1) << " + " << hexToDecDigit(op2) << " + " << hexToDecDigit(carryDigit) << " = " << sum << endl;
  if (sum > 15)
  {
    // cout << "DEBUG addHexDigit: overflow=" << decToHexDigit(sum - 15) << ", sum=" << decToHexDigit(15) << endl;
    overflow = decToHexDigit(sum - 15);
    return decToHexDigit(15);
  }
  else
  {
    // cout << "DEBUG addHexDigit: overflow=" << decToHexDigit(0) << ", sum=" << decToHexDigit(sum) << endl;
    overflow = decToHexDigit(0);
    return decToHexDigit(sum);
  }
}

char decToHexDigit(short dec)
{
  if (dec >= 0 && dec <= 9)
    return dec + '0';
  else if (dec >= 10 && dec <= 15)
    return dec - 10 + 'A';
  else
    return '*';
}

short hexToDecDigit(char hex)
{
  if (hex >= '0' && hex <= '9')
    return hex - '0';
  else if (hex >= 'A' && hex <= 'F')
    return hex - 'A' + 10;
  else if (hex >= 'a' && hex <= 'f')
    return hex - 'a' + 10;
  else
    return 0;
}


//**********************************************************************
//**********************************************************************
//**********************************************************************
void menu2()
{
  const short MAX = 30;
  short size = 4;
  char a[MAX] = {'a', 'b', 'a', 'c'};

  test_menu2(a, size);
  
  // a = {'a', 'b', 'c', 'd', 'e'};
  size = assign(a, string("abcde"), MAX); //5 no dupe
  test_menu2(a, size);
  size = assign(a, string("abcdefghij"), MAX); //10 no dupe
  test_menu2(a, size);
  size = assign(a, string(""), MAX); //empty therefore no dupe
  test_menu2(a, size);
  
  //testing not all duplicates being removed:
  size = assign(a, string("aaaaaaaaaa"), MAX); //10 --> returns "aaa"!!
  test_menu2(a, size);
  size = assign(a, string("aaaaaaaaa"), MAX); //9 --> also returns "aaa"
  test_menu2(a, size);
  size = assign(a, string("aaaaaa"), MAX); //6 --> but this returns "aa"
  test_menu2(a, size);
  size = assign(a, string("aabbccddee"), MAX); // --> works
  test_menu2(a, size);
  size = assign(a, string("aaaaabcde"), MAX); // "aaaaa" 5 -> "aa" 2
  test_menu2(a, size);
  //OK, fixed: I wasn't examining the index that got shifted down after a delete
  
  size = assign(a, string("asdfdsggfd"), MAX); // asdfg
  test_menu2(a, size);
  size = assign(a, string("a man a plan a canal panama"), MAX);
  test_menu2(a, size);
  size = assign(a, string("i prefer pi"), MAX);
  test_menu2(a, size);
  size = assign(a, string("abcdefghijlkmnopqrstuvwxyz"), MAX);
  test_menu2(a, size);
  size = assign(a, string("blahblahblah"), MAX);
  test_menu2(a, size);
}

void test_menu2(char a[], short size)
{
  printArray_menu2(a, size);
  cout << endl;
  if (!delete_repeats(a, size))
    cout << "Deletion of repeats from array failed." << endl;
  printArray_menu2(a, size);
  cout << endl;
}

short assign(char a[], string toAssign, short MAX)
{
  short i;
  for (i = 0; i < toAssign.length() && i < MAX; ++i)
  {
    a[i] = toAssign.at(i); //string.at() see savitch ch 8 pg 483
  }
  return i; //will be (last array index + 1) because of failed test
}

bool delete_repeats(char orig[], short &size)
{
  // cout << "CYBERMAN SAYS? DELETED!" << endl;
  for (short master = 0; master < size; ++master)
  {
    for (short inspecting = (master + 1); inspecting < size; ++inspecting)
      if (orig[master] == orig[inspecting])
        if (!extract(orig, inspecting, size)) //this changes size!! so, both for loops will now end earlier than before
        {
          cout << "Extraction of " << orig[inspecting] << " at position " << inspecting << " from ";
          printArray_menu2(orig, size);
          cout << " failed." << endl;
          return false;
        }
        else
        {
          --inspecting; //since we shifted down one, look backwards one as well on the next loop
        }
  }
  return true;
}

bool extract(char orig[], short position, short &size)
{
  if (position >= size)
  {
    return false;
  }
  else
  {
    for (short i = position; i < (size - 1); ++i)
      orig[i] = orig[i + 1];
    --size;
    return true;
  }
}

void printArray_menu2(const char orig[], short size)
{
  for (short i = 0; i < size; ++i)
    cout << orig[i];
}

//**********************************************************************
//**********************************************************************
//**********************************************************************
void menu3()
{
  const int MAX = 30; //changed to int from last project's short since stats seems to imply larger sets of data
  
  //the problem calls for doubles, not float!
  double a[MAX] = {2,4,4,4,5,5,7,9};
  int size = 8;
  test_menu3(a, size); //should equal 2, using http://en.wikipedia.org/wiki/Standard_deviation example
  cout << endl;
  
  size = 9;
  double b[MAX] = {5,5,5,4,4,4,6,6,6};
  test_menu3(b, size); //should equal 0.816497 -- calculated by using Excel's STDEV.P (stdDev of population)
  cout << endl;
  
  size = 150;
  double c[150] = {0.914929861,0.564349087,0.885806521,0.603609491,0.454379346,0.765151102,0.584846129,0.019502871,0.234403163,0.586901117,0.451764229,0.562081862,0.197208196,0.227841036,0.101653056,0.627899866,0.408974938,0.796044692,0.9354066,0.925672432,0.504521033,0.977841096,0.650971272,0.260848498,0.595359832,0.146035243,0.648885703,0.717429256,0.744153859,0.884223182,0.541893651,0.527313116,0.864619188,0.406176226,0.231451514,0.245832965,0.634160545,0.489097164,0.472778748,0.100975816,0.63725689,0.869062193,0.44452822,0.508956377,0.693411348,0.841410988,0.306377828,0.711677059,0.127486358,0.858950969,0.318225694,0.843128751,0.488413995,0.203936548,0.956011262,0.27439189,0.393961243,0.567957232,0.926873759,0.253949612,0.668291558,0.743994799,0.588836876,0.995153819,0.344310777,0.277925469,0.86863972,0.647169432,0.137620815,0.377275169,0.442809145,0.942728561,0.405974521,0.535912645,0.945777762,0.941508347,0.226023018,0.38052311,0.955067578,0.123669503,0.416274037,0.4158651,0.494115649,0.622345341,0.677601809,0.923116515,0.512262606,0.447137442,0.02481415,0.395436852,0.36754954,0.109297144,0.300635836,0.287795944,0.715176299,0.570399785,0.11429222,0.16788241,0.161776885,0.462453898,0.849062127,0.492502279,0.824561279,0.322999219,0.00422824,0.375404207,0.847592023,0.368493148,0.668897231,0.768302671,0.137701099,0.800313074,0.295057848,0.993219166,0.131106307,0.456418226,0.125862394,0.604509693,0.105294419,0.973618553,0.390940273,0.332653297,0.117683403,0.119960872,0.538742799,0.854912869,0.085596296,0.336876141,0.065170342,0.363303568,0.90649738,0.924189777,0.429570942,0.281618391,0.702784124,0.892028341,0.877906655,0.138877088,0.785345592,0.730322395,0.452672304,0.87842379,0.322490615,0.981851469,0.132378609,0.431408788,0.245110004,0.777392306,0.161517543,0.57714993};
  test_menu3(c, size); // should be 0.27839018 (from excel)
  cout << endl;
  
  size = 150;
  double d[150] = {481,838,874,729,738,781,483,714,956,637,85,425,622,513,402,473,519,351,371,699,670,602,534,189,872,507,206,832,121,669,183,319,46,687,659,70,690,558,684,608,768,646,688,653,859,318,99,626,922,605,348,824,944,471,987,696,660,502,223,104,737,162,619,324,688,223,648,584,828,585,513,163,459,483,890,452,532,589,979,767,643,866,164,146,565,44,661,492,694,635,443,706,381,432,16,248,343,818,642,970,464,343,22,326,487,431,979,579,490,46,412,513,190,709,207,344,783,333,836,706,526,152,382,177,318,785,894,286,893,900,390,39,530,368,11,273,599,670,124,206,265,301,659,859,659,279,984,201,367,57};
  test_menu3(d, size); //259.2270404 from excel
  cout << endl;
}

double stdDev(const double a[], int size)
{
  double averageAll = avg(a, size);
  double runningTotal = 0.0f;
  for (int i = 0; i < size; ++i)
    runningTotal += (a[i] - averageAll) * (a[i] - averageAll); //difference squared
  runningTotal /= size;
  return sqrt(runningTotal);
}

double avg(const double a[], int size)
{
  double sum = 0.0f;
  for (int i = 0; i < size; ++i)
    sum += a[i];
  sum /= size;
  return sum;
}

void test_menu3(double a[], int size)
{
  printArray_menu3(a, size);
  cout << endl;
  double stDev = stdDev(a, size);
  cout << "stdDev()=" << stDev << endl;
}

void printArray_menu3(const double orig[], int size)
{
  for (int i = 0; i < size; ++i)
    cout << orig[i] << " ";
}

//**********************************************************************
//**********************************************************************
//**********************************************************************
void menu4()
{
  const short MAX = 30;
  short size = 10;
  int a[MAX] = {8,6,10,2,16,4,18,14,12,10};
  
  test_menu4(a, size);
  
  int b[150] = {10,13,8,20,3,13,13,12,10,13,7,13,1,16,1,18,7,12,10,4,20,18,19,18,12,9,10,2,20,4,11,10,15,18,17,3,18,7,8,18,18,5,6,5,14,16,17,13,12,11,16,2,17,18,10,6,10,2,7,4,8,14,9,2,2,18,16,15,5,15,18,5,10,17,8,10,13,2,11,19,16,18,5,15,20,13,17,2,5,19,10,1,11,17,1,7,9,20,7,14,14,20,10,5,16,5,11,19,20,17,14,8,14,19,14,11,13,14,3,16,18,18,1,14,18,3,17,13,8,15,4,6,4,6,18,12,6,19,3,16,16,3,1,10,19,18,11,1,7,20};
  size = 150;
  test_menu4(b, size);
  
  int c[150] = {7,-1,6,10,11,1,3,9,0,-5,11,-2,-6,-18,16,-8,14,-16,-3,-20,3,-1,4,-1,19,4,3,-19,14,-8,3,1,-20,-7,-9,-1,-19,-10,-16,10,-3,3,14,-14,-4,-17,-9,20,-7,3,1,20,13,14,15,20,17,1,-7,1,0,16,-16,-4,-9,-6,18,-15,-2,2,11,6,6,-3,12,7,18,15,-4,2,-7,13,0,-18,-11,13,18,-14,9,-19,12,10,20,-15,-11,-19,-6,-1,20,-2,-18,-5,9,11,-2,15,-3,8,-5,-16,20,5,16,4,-13,0,-6,-17,-20,-19,-13,13,-17,-12,20,3,17,-3,10,5,2,-2,-17,-13,-2,11,7,10,-2,-19,-14,-9,12,0,14,9,-17,16,6,4};
  size = 150;
  test_menu4(c, size);
}

void insertionSort(int a[], short size)
{
  const bool DEBUG_MODE = false;
  short posToSort, posToCompare;
  for (short posToSort = 1; posToSort < size; ++posToSort) //starting at second position, select the next value to sort into "sorted sub-array"
  {
    if (DEBUG_MODE) cout << "Outer(" << posToSort << ") item=" << a[posToSort] << " arr: ";
    if (DEBUG_MODE) printArray_menu4(a, size);
    if (DEBUG_MODE) cout << endl;
    for (posToCompare = (posToSort - 1); posToCompare >= 0; --posToCompare) //goes from the current items existing position to zero, swapping if needed. won't swap beyond the start of the array
    {
      if (DEBUG_MODE) cout << "  Compare a[" << posToCompare << "] > a[" << (posToCompare + 1) << "]: " << a[posToCompare] << " vs " << a[posToCompare + 1] << endl;
      if (a[posToCompare] > a[posToCompare + 1]) //starting with curr and curr-1, go all the way to 1 and 0
      {
        swap_menu4(a[posToCompare], a[posToCompare + 1]);
        if (DEBUG_MODE) cout << "    Inner(" << posToCompare << ") arr: ";
        if (DEBUG_MODE) printArray_menu4(a, size);
        if (DEBUG_MODE) cout << endl;
      }
      else //no swap needed, element is bubbled up to correct spot
      {
        if (DEBUG_MODE) cout << "    Inner(" << posToCompare << ") arr: ";
        if (DEBUG_MODE) printArray_menu4(a, size);
        if (DEBUG_MODE) cout << " - no swap" << endl;
        break; //exit inner loop for some efficiency
      }
    }
  }
}

void swap_menu4(int &a, int &b)
{
  int temp = a;
  a = b;
  b = temp;
}

void test_menu4(int a[], short size)
{
  cout << "Before: ";
  printArray_menu4(a, size);
  cout << endl;
  insertionSort(a, size);
  cout << "After:  ";
  printArray_menu4(a, size);
  cout << " - isSorted? " << (isSorted(a, size) ? "True" : "False");
  cout << endl;
}

void printArray_menu4(const int orig[], short size)
{
  for (short i = 0; i < size; ++i)
    cout << orig[i] << ' ';
}


bool isSorted(const int *a, int size)
{
  bool itemsSorted = true;
  for(int i = 0; i < ((size - 1)); i++) //one less than length, since loop compares two each pass
  {
    if (!(*(a + i) <= *(a + i + 1)))
      itemsSorted = false;
  }
  
  return itemsSorted;
}

//**********************************************************************
//**********************************************************************
//**********************************************************************
void menu5()
{
  //main program, loops until user asks to quit (copied from my Savitch_9thEd_Chap3_ProgProj1)
  bool isUserFinished = false; //controls main loop
  char quit = 0;
  char players[2] = {'X','O'};
  int score[2] = {0,0};
  int winner = 0;
  int first = 0;
  while (!isUserFinished)
  {
    cout << "Let's play Tic-Tac-Toe!" << endl;
    
    winner = playGame(players, first);
    if (winner >= 0) //did not play to a draw
      score[winner]++;
    
    cout << "The current score is: Player " << players[0] << " - " << score[0] << " vs. Player " << players[1] << " - " << score[1] << endl;
    
    first = !first;
    
    //determine if the user would like to repeat the calculation (copied from my Savitch_9thEd_Chap3_ProgProj1)
    cout << endl;
    cout << "Would you like to play again? (N to quit) ";
    cin >> quit;
    if (quit == 'N' || quit == 'n')
      isUserFinished = true;
    else
      cout << endl; //a blank line for readability
  }
}


int playGame(char players[], int current)
{
  int board[9] = {-10,-10,-10,-10,-10,-10,-10,-10,-10};
  int input = 0;
  int winner = -1;
  while ((winner = checkWinner(board)) == -1)
  {
    displayBoard(board, players);
    cout << "Player " << players[current] << endl << "Please choose a square (1-9): ";
    getSquare(input, board);
    board[(input - 1)] = current;
    current = !current;
  }
  
  if (winner == 2)
  {
    displayBoard(board, players);
    cout << endl << "The game ended in a draw." << endl;
    return -1;
  }
  else
  {
    displayBoard(board, players);
    cout << endl << "Player " << players[winner] << " has won!" << endl;
    return winner;
  }
}

void getSquare(int &input, int board[])
{
  bool isInputValid = false; //controls input loop (ie, loop until input is right)
  while (!isInputValid)
  {
    cout << "> ";
    cin >> input;
    if (input < 1)
      cout << "The square cannot be less than 1. Please choose again." << endl;
    else if (input > 9)
      cout << "The square cannot be greater than 9. Please choose again." << endl;
    else if (board[input - 1] >= 0)
      cout << "That square has already been chosen." << endl;
    else
      isInputValid = true;
  }
}

void displayBoard(int board[], char players[])
{
  cout << "     |     |     " << endl;
  for (int i = 0; i < 9; ++i)
  {
    cout << "  " << static_cast<char>(((board[i] >= 0) ? players[board[i]] : (i + 1 + '0'))) << "  ";
    if ((i + 1) % 3 == 0)
      if (i == 8)
        cout << endl << "     |     |     " << endl;
      else
        cout << endl << "-----|-----|-----" << endl;
    else
      cout << "|";
  }
}
int checkWinner(int board[]) // returns -1 for no win, 0 for first player wins, 1 for second, 2 for draw
{
  //note: all these use the fact that the board is initialized to -10, and players are 0 and 1
  int total = 0;
  
  //rows:
  total = sum(board, 0, 2);
  if (total == 0) return 0;
  else if (total == 3) return 1;
  total = sum(board, 3, 5);
  if (total == 0) return 0;
  else if (total == 3) return 1;
  total = sum(board, 6, 8);
  if (total == 0) return 0;
  else if (total == 3) return 1;
  
  //cols:
  total = board[0] + board[3] + board[6];
  if (total == 0) return 0;
  else if (total == 3) return 1;
  total = board[1] + board[4] + board[7];
  if (total == 0) return 0;
  else if (total == 3) return 1;
  total = board[2] + board[5] + board[8];
  if (total == 0) return 0;
  else if (total == 3) return 1;
  
  //diagonals:
  total = board[0] + board[4] + board[8];
  if (total == 0) return 0;
  else if (total == 3) return 1;
  total = board[6] + board[4] + board[2];
  if (total == 0) return 0;
  else if (total == 3) return 1;
  
  if (sum(board, 0, 8) > 0) //all spaces have been played, yet none of the other win conditions were true
    return 2;
  
  return -1;
}

//I realized after I made this that function isn't all that useful compared to just adding 3 numbers.
//But I left it in because I like the example
int sum(int nums[], int first, int last)
{
  int sum = 0;
  for ( ; first <= last; ++first)
    sum += nums[first];
  return sum;
}

//**********************************************************************
//**********************************************************************
//**********************************************************************
void menu6()
{
  const short MAX = 100;
  char a[MAX] = "abcde"; //odd
  test_menu6(a);
  
  char b[MAX] = "abcdef"; //even
  test_menu6(b);
  
  char c[MAX] = "A man, a plan, a canal: Panama."; //odd
  test_menu6(c);
  char d[MAX] = "amanaplanacanalpanama"; //odd
  test_menu6(d);
  
  char e[MAX] = "I prefer Pi!"; //even
  test_menu6(e);
  char f[MAX] = "ipreferpi"; //odd
  test_menu6(f);
}

void test_menu6(char a[])
{
  cout << "Original string \"" << a << "\" = ";
  printArrayInt(a);
  cout << endl;
  reverse(a);
  cout << "Reversed string \"" << a << "\" = ";
  printArrayInt(a);
  cout << endl;
}

//This code was going to be based upon my Savitch_9thEd_Chap7_ProgProj2, but that code doesn't apply at all, since it uses a loop counter.
//so, the whole thing is redone using purely pointers
void reverse(char* a)
{
  //took this method of counting the length out in favor of a pointer loop through a[] to find rear
  // short length = 0;
  // while (a[length]) //loops until '\0' (which equals 0)
    // length++;
  // cout << "DEBUG: length=" << length << endl;
  
  char *front = a, *rear = a;// = &a[length-1];
  while (*rear) rear++; //while *rear is not '\0', increment rear
  --rear; //go back one from '\0'
  // cout << "DEBUG: front and rear start at: " << *front << "/" << *rear << endl;
  while (front != rear && ((front - 1) != rear)) //odd length && even length (they do not overlap cases)
    swap_menu6(front++, rear--);
  // cout << "DEBUG reverseString: reversed=\"" << a << "\"" << endl;
}

void swap_menu6(char *a, char *b)
{
  char temp = *a;
  *a = *b;
  *b = temp;
}

void printArrayInt(const char orig[])
{
  cout << '{';
  int i = 0;
  while (orig[i])
  {
    cout << static_cast<int>(orig[i++]) << ',';
  }
  cout << static_cast<int>(orig[i]); // \0
  cout << '}';
}

//**********************************************************************
//**********************************************************************
//**********************************************************************
void menu7()
{
  int rows = 3, cols = 4;
  int *arr = create2DArray(rows, cols);
  
  cout << "Uninitialized:" << endl;
  print2DArray(arr, rows, cols);
  cout << endl;
  
  cout << "Filled:" << endl;
  fill2DArray(arr, rows, cols);
  print2DArray(arr, rows, cols);
  cout << endl;
  
  cout << "Changed (1, 1) to 42:" << endl;
  set(arr, rows, cols, 1, 1, 42);
  print2DArray(arr, rows, cols);
  cout << endl;
  
  cout << "The item at index (1, 1) is: " << get(arr, rows, cols, 1, 1) << endl << endl;
}


int* create2DArray(int rows, int columns)
{
  return new int[rows * columns];
}

void set(int *arr, int rows, int columns, int desired_row, int desired_column, int val)
{
  if (desired_row >= rows || desired_row < 0)
  {
    cout << "Invalid row index requested." << endl;
    return;
  }
  if (desired_column >= columns || desired_column < 0)
  {
    cout << "Invalid column index requested." << endl;
    return;
  }

  *(arr + (desired_row * columns + desired_column)) = val;
}

int get(int *arr, int rows, int columns, int desired_row, int desired_column)
{
  if (desired_row >= rows || desired_row < 0)
  {
    cout << "Invalid row index requested." << endl;
    return -1;
  }
  if (desired_column >= columns || desired_column < 0)
  {
    cout << "Invalid column index requested." << endl;
    return -1;
  }
  
  return *(arr + (desired_row * columns + desired_column));
}

void fill2DArray(int *arr, int rows, int columns)
{
  int count = 1;
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < columns; ++j)
      set(arr, rows, columns, i, j, count++);
}


void print2DArray(int *arr, int rows, int columns)
{
  for (int i = 0; i < rows; ++i)
  {
    cout << '{';
    for (int j = 0; j < columns; ++j)
    {
      cout << get(arr, rows, columns, i, j) << ((j == columns - 1) ? "" : ", ");
    }
    cout << '}' << endl;
  }
}
