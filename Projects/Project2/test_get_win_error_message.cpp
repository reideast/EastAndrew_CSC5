if(!SetConsoleWindowInfo(hStdout, true, &windowSize ))
    {
      cout << "Setting the window size failed." << endl;
    
      CHAR msgText[256];
      getLastErrorText(msgText,sizeof(msgText));
      cout << msgText;
    }
      

//based on an MSDN community user's code:
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms679360(v=vs.85).aspx
// usage
//     CHAR msgText[256];
//     getLastErrorText(msgText,sizeof(msgText));
static CHAR *                      //   return error message
getLastErrorText(                  // converts "Lasr Error" code into text
CHAR *pBuf,                        //   message buffer
ULONG bufSize)                     //   buffer size
{
     DWORD retSize;
     LPTSTR pTemp=NULL;

     if (bufSize < 16) {
          if (bufSize > 0) {
               pBuf[0]='\0';
          }
          return(pBuf);
     }
     retSize=FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|
                           FORMAT_MESSAGE_FROM_SYSTEM|
                           FORMAT_MESSAGE_ARGUMENT_ARRAY,
                           NULL,
                           GetLastError(),
                           LANG_NEUTRAL,
                           (LPTSTR)&pTemp,
                           0,
                           NULL );
     if (!retSize || pTemp == NULL) {
          pBuf[0]='\0';
     }
     else {
          pTemp[strlen(pTemp)-2]='\0'; //remove cr and newline character
          sprintf(pBuf,"%0.*s (0x%x)",bufSize-16,pTemp,GetLastError());
          LocalFree((HLOCAL)pTemp);
     }
     return(pBuf);
}

