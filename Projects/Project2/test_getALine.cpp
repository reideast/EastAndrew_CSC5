

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms685035(v=vs.85).aspx
// cls using WinAPI
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms682022(v=vs.85).aspx



#include <windows.h>
#include <stdio.h> //for printf and stderr only, i think! remove those, then disable.



#include <iostream>
#include <string>

using namespace std;

const bool DEBUG_MODE = true;


bool getALine(string& input);

VOID ErrorExit(LPSTR);

//Execution Begins Here
int main(int argc, char** argv)
{
  string input = "";
  getALine(input);
 
  cout << "You typed in: \"" << input << "\"";
 
  
  // int pause;
  // cin >> pause;
 
  return 0; 
}

bool getALine(string& input)
{
  HANDLE hStdin;
  DWORD fdwSaveOldMode;
  
  const short BUFF_SIZE = 8; // original buffer size: const int BUFF_SIZE = 128;
  const short LINE_MAX = 80;
  
  DWORD cNumRead, fdwMode;
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

  // chnage console mode to non-buffered input, allowing the Windows console to send input to C++ w/o waiting for the {Enter} key
  fdwMode = ENABLE_WINDOW_INPUT;
  if (!SetConsoleMode(hStdin, fdwMode))
  {
    cout << "Error: SetConsoleMode" << endl;
    SetConsoleMode(hStdin, fdwSaveOldMode); // Restore input mode on exit.
    return false; //ExitProcess(0);
  }

  // Loop to read and handle the next LINE_MAX input events.
  KEY_EVENT_RECORD keyEventRecord;
  int counter = 0, i = 0;
  char temp = 0;
  bool isLineDone = false;
  while (!isLineDone && counter++ <= LINE_MAX) //counter left in to cut off lines at LINE_MAX char
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
          //KeyEventProc(irInBuf[i].Event.KeyEvent);

          keyEventRecord = irInBuf[i].Event.KeyEvent;
          // ctrl+c: has to check dwControlKeyState using bit masks
          // if (keyEventRecord.wVirtualKeyCode == 0x43 && (keyEventRecord.dwControlKeyState & 0x0008 || keyEventRecord.dwControlKeyState & 0x0004) && !keyEventRecord.bKeyDown)
            // ErrorExit("");
          if (keyEventRecord.bKeyDown) //if the keyboard key has not been released yet, ignore it
          {
            --counter;
          }
          else //this is a key release event
          {
            //note: these "Virtual Key Codes" are from MSDN: https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
            if (keyEventRecord.wVirtualKeyCode >= 0x30 && keyEventRecord.wVirtualKeyCode <= 0x39)
            {
              printf("numeric: %d '%c'", keyEventRecord.wVirtualKeyCode - 0x30, keyEventRecord.wVirtualKeyCode - 0x30);
              // temp = keyEventRecord.wVirtualKeyCode - 0x30 + '0';
              input += keyEventRecord.wVirtualKeyCode - 0x30 + '0';
            }
            else if (keyEventRecord.wVirtualKeyCode >= 0x41 && keyEventRecord.wVirtualKeyCode <= 0x5A)
            {
              printf("alphabetic %d '%c' ", keyEventRecord.wVirtualKeyCode, keyEventRecord.wVirtualKeyCode);
              // temp = keyEventRecord.wVirtualKeyCode - 0x41 + 'A';
              input += keyEventRecord.wVirtualKeyCode - 0x41 + 'A';
            }
            else if (keyEventRecord.wVirtualKeyCode == 0x20) //spacebar
            {
              // printf("spacebar ");
              input += ' ';
            }
            else if (keyEventRecord.wVirtualKeyCode == 13)
            {
              // printf("note: enter key");
              //input += '\n';
              isLineDone = true;
            }
            if (DEBUG_MODE) cout << "DEBUG: string to return: \"" << input << "\"";
          }
        break;

        // Ignore all other potential event types
        case MOUSE_EVENT: // mouse input
        case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
        case FOCUS_EVENT:  // disregard focus events
        case MENU_EVENT:   // disregard menu events
        default:
          counter--; //don't count this to the limit of LINE_MAX events
          break;
      }
    }
  }
  
  // Restore input mode on exit.
  SetConsoleMode(hStdin, fdwSaveOldMode);
  return true; //no errors
}


// VOID ErrorExit (LPSTR lpszMessage)
// {
    // fprintf(stderr, "%s\n", lpszMessage);
    // Restore input mode on exit.
    // SetConsoleMode(hStdin, fdwSaveOldMode);
    // ExitProcess(0);
// }