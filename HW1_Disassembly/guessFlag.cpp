#include <iostream>
#include <string>
using namespace std;

int main()
{
  string flag = "Fl@g_1s_JuSt_fL@G";
  string password;
  int chance = 5;
  for(int i=0; i<5; i++){
      cout << "what is the flag(you have " << chance << " chances.) : ";
      cin >> password;
      if (password == flag) 
        {cout << "You make it!" << endl;
        return 0;}
      else
        {cout << "Oh no!" << endl;}
        chance -= 1;
      }
  cout << "byebye!" << endl;
  return 0;
}
