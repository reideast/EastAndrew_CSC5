

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms685035(v=vs.85).aspx
// cls using WinAPI
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms682022(v=vs.85).aspx



#include <windows.h>
#include <stdio.h>

#include <iostream>
#include <string>

using namespace std;


HANDLE hStdin; 
DWORD fdwSaveOldMode;

bool getALine(string& input);

VOID ErrorExit(LPSTR);
VOID KeyEventProc(KEY_EVENT_RECORD); 
VOID MouseEventProc(MOUSE_EVENT_RECORD); 
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD); 
 
int main(VOID) 
{ 
  string input = "";
  getALine(input);
  
  cout << "You typed in: \"" << input << "\"";
  
  
  int pause;
  cin >> pause;
 
  return 0; 
}

bool getALine(string& input)
{
  const int BUFF_SIZE = 128;
  
  DWORD cNumRead, fdwMode, i;
  INPUT_RECORD irInBuf[BUFF_SIZE];
  int counter=0;

  // Get the standard input handle.
  hStdin = GetStdHandle(STD_INPUT_HANDLE);
  if (hStdin == INVALID_HANDLE_VALUE)
    ErrorExit("GetStdHandle");

  // Save the current input mode, to be restored on exit. 
  if (! GetConsoleMode(hStdin, &fdwSaveOldMode) )
    ErrorExit("Getting the Console State Failed: No Console Found\nPlease run this program in a Windows Command Prompt console!"); 

  // Enable the window and mouse input events. 
  fdwMode = ENABLE_WINDOW_INPUT; // fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT; 
  if (! SetConsoleMode(hStdin, fdwMode) ) 
    ErrorExit("SetConsoleMode"); 

  // Loop to read and handle the next 80 input events.
  KEY_EVENT_RECORD ker;
  char temp = 0;
  bool isLineDone = false;
  while (!isLineDone && counter++ <= 80) //counter left in to cut off lines at 80 char
  {
    // Wait for the events. 

    if (! ReadConsoleInput( 
                            hStdin,      // input buffer handle 
                            irInBuf,     // buffer to read into 
                            BUFF_SIZE,         // size of read buffer 
                            &cNumRead) ) // number of records read 
      ErrorExit("ReadConsoleInput");

    // Dispatch the events to the appropriate handler. 
    if (cNumRead > 1)
      printf("Note: cNumRead was greater than 1 (%d)", cNumRead);

    for (i = 0; i < cNumRead; i++) 
    {
      switch(irInBuf[i].EventType) 
      {
        case KEY_EVENT: // keyboard input 
          //KeyEventProc(irInBuf[i].Event.KeyEvent); 

          ker = irInBuf[i].Event.KeyEvent;
          //ctrl+c: has to check dwControlKeyState using bit masks
          if (ker.wVirtualKeyCode == 0x43 && (ker.dwControlKeyState & 0x0008 || ker.dwControlKeyState & 0x0004) && !ker.bKeyDown)
            ErrorExit("");
          if (ker.wVirtualKeyCode >= 0x30 && ker.wVirtualKeyCode <= 0x39)
          {
            printf("numeric: %d '%c'", ker.wVirtualKeyCode - 0x30, ker.wVirtualKeyCode - 0x30);
            temp = ker.wVirtualKeyCode - 0x30;
            if(!ker.bKeyDown) //key release event
              input += temp;
          }
          else if (ker.wVirtualKeyCode >= 0x41 && ker.wVirtualKeyCode <= 0x5A)
          {
            printf("alphabetic %d '%c' ", ker.wVirtualKeyCode, ker.wVirtualKeyCode);
            temp = ker.wVirtualKeyCode - 0x30;
            if(!ker.bKeyDown) //key release event
              input += temp;
          }
          else if (ker.wVirtualKeyCode == 0x20)
          {
            printf("spacebar ");
          }
          else if (ker.wVirtualKeyCode == 13 && !ker.bKeyDown)
          {
            printf("note: enter key");
            //input += '\n';
            isLineDone = true;
          }
          
cout << input;

          if(ker.bKeyDown)
            printf("#%d pressed\n", ker.wVirtualKeyCode);
          else
            printf("#%d released\n", ker.wVirtualKeyCode);
        break; 

        case MOUSE_EVENT: // mouse input 
          // Ignore Mouse Events: MouseEventProc(irInBuf[i].Event.MouseEvent);
          printf("Note: MOUSE_EVENT (even though I thought it was turned off...)");
          counter--; //don't count this to the limit of 80 events
          break; 

        case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
          //ignore: ResizeEventProc( irInBuf[i].Event.WindowBufferSizeEvent ); 
          counter--;
          break; 

        case FOCUS_EVENT:  // disregard focus events 
          counter--;
          break;

        case MENU_EVENT:   // disregard menu events 
          counter--;
          break; 

        default: 
          printf("Unknown event type"); //ErrorExit("Unknown event type");
          counter--;
          break;
      }
    }
  }

  // Restore input mode on exit.

  SetConsoleMode(hStdin, fdwSaveOldMode);
}


VOID KeyEventProc(KEY_EVENT_RECORD ker)
{
  //ctrl+c: has to check dwControlKeyState using bit masks
  if (ker.wVirtualKeyCode == 0x43 && (ker.dwControlKeyState & 0x0008 || ker.dwControlKeyState & 0x0004))
    ExitProcess(0);
  if (ker.wVirtualKeyCode >= 0x30 && ker.wVirtualKeyCode <= 0x39)
    printf("numeric: %d ", ker.wVirtualKeyCode - 0x30);
  else if (ker.wVirtualKeyCode >= 0x41 && ker.wVirtualKeyCode <= 0x5A)
    printf("alphabetic %d '%c' ", ker.wVirtualKeyCode, ker.wVirtualKeyCode);
  else if (ker.wVirtualKeyCode == 0x20)
    printf("spacebar ");
  
  
  if(ker.bKeyDown)
    printf("pressed\n");
  else
    printf("released\n");
  
}

VOID ErrorExit (LPSTR lpszMessage) 
{ 
    fprintf(stderr, "%s\n", lpszMessage); 

    // Restore input mode on exit.

    SetConsoleMode(hStdin, fdwSaveOldMode);

    ExitProcess(0); 
}