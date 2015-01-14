#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
  cout << "bitwise even test" << endl << endl;
  cout << "12 & 1 = " << (12 & 1) << endl;
  cout << "13 & 1 = " << (13 & 1) << endl;
  int num = 24;
  cout << num << " ";
  if (num & 1)
    cout << "odd" << endl;
  else
    cout << "even" << endl;

  num = 25;
  cout << num << " ";
  if (num & 1)
    cout << "odd" << endl;
  else
    cout << "even" << endl;
  
  return 0;
}
