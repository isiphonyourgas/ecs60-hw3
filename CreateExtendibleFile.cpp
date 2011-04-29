#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "QuadraticProbing.h"
#include "ExtendibleHash.h"

using namespace std;

int main()
{
  int i, MaxSize, LeafSize, seed, StartBits, back, *UnUsedArray,
    *InsertedArray, UnUsedCount, InsertedCount = 0, value;

  char filename[80];
  do 
  {
    cout  << "Maximum size (5- ): ";
    cin >> MaxSize;
  } while(MaxSize < 5);

  QuadraticHashTable <int> QHash(-1, MaxSize * 2);
  UnUsedArray = new int[MaxSize];
  InsertedArray = new int[MaxSize];

  for(int i = 0; i < MaxSize; i++)
  {
    do   // guarantee unique values
    {
      value = (rand() * rand()) & 0x3FFFF;
    } while(QHash.find(value) != -1);

    QHash.insert(value);
    UnUsedArray[i] = value;
  } // for i to MaxSize

  UnUsedCount = MaxSize;

  do 
  {
    cout  << "Leaf size (1 - 10000): ";
    cin >> LeafSize;
  } while(LeafSize < 1 || LeafSize > 10000);


  do 
  {
    cout  << "Start bits (1 - 18): ";
    cin >> StartBits;
  }  while(StartBits < 1 || StartBits > 18);


  ExtendibleHash hash(-1, StartBits, LeafSize);

  cout << "Seed: ";
  cin >> seed;

  sprintf(filename, "Hash-%d-%d-%d-%d.dat", MaxSize, LeafSize, StartBits, seed);
  ofstream outf(filename);
  srand(seed);
  int *array = new int[2 * MaxSize + 1];

  for(i = 0; i < 2 * MaxSize; i++)
    array[i] = 0;  // not really needed, just for my debugging of this code

  while(InsertedCount < MaxSize)
  {  // three times as many inserts the deletes 10% find, 10% Get Bits
    i = rand() % 10;
    if(i < 6)
    {  // insert
      i = abs(rand() * rand()) % UnUsedCount;
      value = UnUsedArray[i];
      UnUsedArray[i] = UnUsedArray[--UnUsedCount];
      InsertedArray[InsertedCount++] = value;
      outf << 'i' << value << endl;
      hash.insert(value);
    } // if i < 6
    else
      if(i < 8 && InsertedCount > 0)
      {  // remove
        i = abs(rand() * rand()) % InsertedCount;
        value = InsertedArray[i];
        InsertedArray[i] = InsertedArray[--InsertedCount];
        UnUsedArray[UnUsedCount++] = value;
        outf << 'd' << value << endl;
        hash.remove(value);
      } // if 6 <= i < 8
      else
        if(i == 8 && InsertedCount > 0)
        { // find
          i = rand() % 2;
          if(i)  // look for something that is inserted
          {
            i = abs(rand() * rand()) % InsertedCount;
            value = InsertedArray[i];
            outf << 'f' << value << " " << value << endl;
          }  // if
          else  // look for something not in the hash
          {
            i = abs(rand() * rand()) % UnUsedCount;
            value = UnUsedArray[i];
            outf << 'f' << value << " -1" << endl;
          } // else
        } // if i == 8 and something in table
        else
        {
          value = hash.GetBits();
          outf << 'b' << value << endl;
        } // else i == 9
  } // while MaxSize not reached
  value = hash.GetBits();
  outf << 'b' << value << endl;
  outf.close();
  return 0;
} // main()
