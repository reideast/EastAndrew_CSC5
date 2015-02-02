

const int ANIMATION_RATE = 50; //miliseconds

const int WINDOW_COLUMNS = 80;
const int WINDOW_ROWS = 25;

bool writeScreen(int x, int y); //write a screen with a '*' at (x, y)
void testWriteScreen();
void cls(); //clear the screen by writing 100 new lines


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
