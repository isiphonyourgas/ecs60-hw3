// Author: Sean Davis
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "ExtendibleHash.h"

#include <bitset>

using namespace std;
int main(int argc, char* argv[])
// argv[1] is data filename in the form: "Hash-" Maxsize "-" LeafSize "-"
//             StartBits "-" Seed ".dat"
{
  char command, *ptr;
  int value, value2, StartBits, LeafSize;

  ifstream inf(argv[1]);
  strtok(argv[1], "-");
  strtok(NULL, "-");
  LeafSize = atoi(strtok(NULL, "-"));
  StartBits = atoi(strtok(NULL, "-"));
  ExtendibleHash  hash(-1, StartBits, LeafSize);
  bitset<18> set;

  while(inf >> command)
  {

      //hash.print();
    inf >> value;
    set = value;
 //   cout <<value<<endl;
    switch(command)
    {
      case 'i' :
         // cout<<"Insert " << value <<"       "<< set << endl;
          hash.insert(value);
       //   hash.print();
          break;
      case 'd' :
      //    cout << "Remove " << value << "        " <<set << endl;
          hash.remove(value);
      //    hash.print();
          break;
      case 'f' :
          cout<<"Finding Shit: " << set << endl;
          //cout<<value<<endl;
          //hash.print();
        inf >> value2;
        if(value2 != hash.find(value))
          cout << "Bad find: Sought:" << value << " returned: " << hash.find(value) << endl;
        break;
      case 'b' :
        if(value != hash.GetBits())
          cout << "Bad bits: Expected: " << value << " got: " << hash.GetBits() << endl;
    } // switch
    
  } // while more in file
//hash.print();
  return 0;
} // main()
