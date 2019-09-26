#define MACOS

#ifdef MACOS
#define clearScreen(); system("clear");
#else
#define clearScreen(); system("cls");
#endif

#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

// argument - ilość wywołań
// średni czas wykonania
// progress bar przy dużej ilości wywołań
// argument export do pliku
// "result afrer x iteration"

clock_t cpu_benchmark();
clock_t hdd_benchmark();
clock_t ram_benchmark();

bool cpu_test, hdd_test, ram_test;
unsigned long long cpu_result, hdd_result, ram_result;
unsigned char crc_sum=0;

int main(int argc, char const *argv[])
{
 // begin of config section
  if(!(argc==2))
  {
    cerr << "\n! ARG fault! ";
    (argc>2) ? cerr << "Too much !\n" : cerr << "Not enough !\n";

    return -1;
  }

  int argslen=strlen(argv[1]);
  if(argslen>3)
  {
    cerr << "\n! ARG fault! Too much letters :P !\n";
    return -1;
  }



  if(argslen==3)
  {
    switch (argv[1][0])
    {
      case 'c': cpu_test=true; break;
      case 'h': hdd_test=true; break;
      case 'r': ram_test=true; break;
      default: cerr << "\n! ARG fault! Bad letter !\n"; return -1;
    }
    switch (argv[1][1])
    {
      case 'c': cpu_test=true; break;
      case 'h': hdd_test=true; break;
      case 'r': ram_test=true; break;
      default: cerr << "\n! ARG fault! Bad letter !\n"; return -1;
    }
    switch (argv[1][2])
    {
      case 'c': cpu_test=true; break;
      case 'h': hdd_test=true; break;
      case 'r': ram_test=true; break;
      default: cerr << "\n! ARG fault! Bad letter !\n"; return -1;
    }
  }
  else if(argslen==2)
  {
    switch (argv[1][0])
    {
      case 'c': cpu_test=true; break;
      case 'h': hdd_test=true; break;
      case 'r': ram_test=true; break;
      default: cerr << "\n! ARG fault! Bad letter !\n"; return -1;
    }
    switch (argv[1][1])
    {
      case 'c': cpu_test=true; break;
      case 'h': hdd_test=true; break;
      case 'r': ram_test=true; break;
      default: cerr << "\n! ARG fault! Bad letter !\n"; return -1;
    }
  }
  else if(argslen==1)
  {
    switch (argv[1][0])
    {
      case 'c': cpu_test=true; break;
      case 'h': hdd_test=true; break;
      case 'r': ram_test=true; break;
      default: cerr << "\n! ARG fault! Bad letter !\n"; return -1;
    }
  }
  else
  {
    cerr << "\n! Unknown error !\n";
    return -1;
  }

  cout << "Debug: " << cpu_test << hdd_test << ram_test << " \n";
 // end of config section




  clearScreen();
  cout << "\nRESULT (less is beter): ";
  cout << "\nCPU test: "; cpu_test ? cout << cpu_benchmark() : cout <<"not tested";
  cout << "\nHDD test: "; hdd_test ? cout << hdd_benchmark() : cout <<"not tested";
  cout << "\nRAM test: "; ram_test ? cout << ram_benchmark() : cout <<"not tested";
  crc_sum^=cpu_result;
  crc_sum^=hdd_result;
  crc_sum^=ram_result;
  cout << "\n\nCRC: " << (int)crc_sum;

  cout << "\n\n\n";

  return 0;
}


clock_t cpu_benchmark()
{
  clock_t begin, end;
  unsigned long long a=0, b=1;
  begin=clock();

  for (size_t i = 0; i < 9999999; i++)
  {
    for (size_t j = 0; j < 100; j++)
    {
      b+=a;
      a=b-a;
    }
    a=0;
    b=1;
  }
  end=clock();
  cpu_result=(end-begin);
  return (end-begin);
}
clock_t hdd_benchmark()
{

  clock_t begin, end;
  string s;
  fstream file;
  file.open("SimpleBenchmark_temp.txt");
  begin=clock();

  for (size_t i = 0; i < 10000000; i++)
  {
    file << "xxxxxxxxxxxxx";
    getline(file,s);
  }
  file.close();


  end=clock();
  hdd_result=(end-begin);
  return (end-begin);



}
clock_t ram_benchmark()
{
  clock_t begin, end;
  int* arr;
  begin=clock();

  for (size_t i = 0; i < 10000; i++)
  {
    arr=new int[99999];
    for (size_t j = 0; j < 99999; j++)
    {
      arr[i]=i;
      arr[i]++;
    }

    delete []arr;
  }

  end=clock();
  ram_result=(end-begin);
  return (end-begin);

}
