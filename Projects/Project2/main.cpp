

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms685035(v=vs.85).aspx
// cls using WinAPI
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms682022(v=vs.85).aspx



#include <windows.h>
#include <stdio.h>

string getALine();

HANDLE hStdin; 
DWORD fdwSaveOldMode;

VOID ErrorExit(LPSTR);
VOID KeyEventProc(KEY_EVENT_RECORD); 
VOID MouseEventProc(MOUSE_EVENT_RECORD); 
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD); 
 
int main(VOID) 
{ 
  string input
  input = getALine();
  
  cout << input;
 
  return 0; 
}

string getALine()
{
  DWORD cNumRead, fdwMode, i; 
  INPUT_RECORD irInBuf[128]; 
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

  // Loop to read and handle the next 100 input events.
  bool isLineDone = false;
  while (!isLineDone || counter++ <= 80) //counter left in to cut off lines at 80 char
  { 
      // Wait for the events. 

      if (! ReadConsoleInput( 
              hStdin,      // input buffer handle 
              irInBuf,     // buffer to read into 
              128,         // size of read buffer 
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
                  KeyEventProc(irInBuf[i].Event.KeyEvent); 
                  break; 

              case MOUSE_EVENT: // mouse input 
                  // Ignore Mouse Events: MouseEventProc(irInBuf[i].Event.MouseEvent);
                  printf("Note: MOUSE_EVENT (even though I thought it was turned off...)");
                  counter--; //don't count this to the limit of 100 events
                  break; 

              case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
                  ResizeEventProc( irInBuf[i].Event.WindowBufferSizeEvent ); 
                  break; 

              case FOCUS_EVENT:  // disregard focus events 

              case MENU_EVENT:   // disregard menu events 
                  break; 

              default: 
                  ErrorExit("Unknown event type"); 
                  break; 
          } 
      }
  } 

  // Restore input mode on exit.

  SetConsoleMode(hStdin, fdwSaveOldMode);
}

VOID ErrorExit (LPSTR lpszMessage) 
{ 
    fprintf(stderr, "%s\n", lpszMessage); 

    // Restore input mode on exit.

    SetConsoleMode(hStdin, fdwSaveOldMode);

    ExitProcess(0); 
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

VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
    printf("Mouse event: ");
    
    switch(mer.dwEventFlags)
    {
        case 0:

            if(mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            {
                printf("left button press \n");
            }
            else if(mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
            {
                printf("right button press \n");
            }
            else
            {
                printf("button press\n");
            }
            break;
        case DOUBLE_CLICK:
            printf("double click\n");
            break;
        case MOUSE_HWHEELED:
            printf("horizontal mouse wheel\n");
            break;
        case MOUSE_MOVED:
            printf("mouse moved\n");
            break;
        case MOUSE_WHEELED:
            printf("vertical mouse wheel\n");
            break;
        default:
            printf("unknown\n");
            break;
    }
}

VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
    printf("Resize event\n");
    printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}
