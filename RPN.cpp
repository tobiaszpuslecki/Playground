#include <iostream>
#include <stack>
#include <stdlib.h>

// ujemne liczby
// ułamki


using namespace std;

std::stack<float> mainStack;

float x;

string s = "25489 4233 ";
//3 + 5 *";
string ss;


unsigned int toNumber(char c)
{
  return c-'0';
}

bool isNumber(char c)
{
  return (toNumber(c) >= 0 && toNumber(c) <= 9) ? true : false;
}




int main(int argc, char const *argv[])
{
  mainStack.push(2.34);
  x=mainStack.top();
  mainStack.pop();
  //cout << endl << x << " " << mainStack.empty() << endl;


  int i = 0;
  double buffer;
  double currentPow=1;
  bool mantissa=false;
  double mantissaPower=0.1;
  while(s[i]!='\0')
  {
    if(isNumber(s[i]))
    {
        buffer = buffer*10 + toNumber(s[i]);
    }
    if(mantissa)
    {
      buffer = buffer + toNumber(s[i])*mantissaPower;
      mantissaPower = mantissa * 0.1;
      //cout << buffer << endl;
    }
    if(s[i]=='.')
    {
      mantissa=true;
    }

    else if(s[i]==' ' || s[i]=='\0')
    {
      cout << "\n#" << buffer << "#";
      buffer=0;
      mantissa=false;
      mantissaPower=0.1;

    }

    i++;

  }



  return 0;
}
