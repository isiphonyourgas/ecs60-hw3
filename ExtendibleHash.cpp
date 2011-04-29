#include "ExtendibleHash.h"
#include <bitset>

using namespace std;

int Ehash(int value, int bits)
{
  return value >> (18 - bits) ;
} // Ehash()

ExtendibleHash::ExtendibleHash(const int & notFound, int b, int LSize) :
  bits(b), LeafSize(LSize)
{
  int i;
  size = 1;
  bit = 1;
  for(i = 0; i < b; i++)
    size = size * 2;
  Directory = new ExtendibleLeaf*[size];

  

  for(i = 0; i < size; i++)
  {
    Directory[i] = new ExtendibleLeaf(LSize);
    Directory[i]->parent = this;
  }
  LeafSize = LSize;
  
} // ExtendibleHash()

void ExtendibleHash::insert(const int &object)
{
  int i, j, k;
  int temp;
  k = size;//Initializes k for future use
  j = 0;

  bitset<18> bits;//Converts into bits
  bits = object;
  for(i = 0; i < bit; i++)//Iterates to where the insertion needs to be
  {
      k = k / 2;//Calculates spaces moved
    if(bits[18 - i] == 1)//If current bit is 1
    {
      j = j + k;;//Does actual move
    }
  }
  Directory[j]->insert(object);
  
} // insert()


void ExtendibleHash::remove(const int &object)
{
  int i, j, k;
  k = size;
  j = 0;

  bitset<18> bits;
  bits = object;
  for(i = 0; i < bit; i++)
  {
    k = k / 2;
    if(bits[18 -i] == 1)
    {
      j = j + k;
    }
  }
  Directory[j]->remove(object);

}  // remove()


const int & ExtendibleHash::find(const int &object)
{
  int i, j, k;
  k = size;
  j = 0;
  
  bitset<18> bits;
  bits = object;
  for(i = 0; i < bit; i++)
  {
    k = k / 2;
    if(bits[18 - i] == 1)
    {
      j = j + k;
    }
  }
  target=  Directory[j]->find(object);
  return target;
}  // find()



void ExtendibleHash::split(const int &object)
{
  int i;
  ExtendibleLeaf **ptr, **temp;
  ptr = new ExtendibleLeaf*[size * 2];
  for(i = 0; i < bit; i++)
  {
    ptr[2*i] = Directory[i];
    ptr[(2 * i ) + 1] = new ExtendibleLeaf(LeafSize);
    ptr[2 * i]->split(ptr[(2 * i) + 1], bit);//Getting an error on this line function
  }//for
  size = size * 2;
  bit++;
  temp = Directory;
  delete temp;
  Directory = ptr;
}  // split()

ExtendibleLeaf::ExtendibleLeaf(const int LeafSize)
{
  content = new int[LeafSize];
  count = 0;
  size = LeafSize;
}//Extendible Leaf

void ExtendibleLeaf::insert(int value)
{
  if(count == size)
    parent->split(1);

  content[count] = value;
  count++;


}//Leaf Insert

void ExtendibleLeaf::remove(int value)
{
  int i, j;
  for(i = 0; i < count; i++)
  {
    if((content[i] == value) && i < (count - 1))
    {
      for(j = i; j < (count - 1); j++)
        content[j] = content[j + 1];
      break;
    }
    if((content[i] == value) && i == (count - 1))
      break;
  }
  count--;


}//Leaf Remove

void ExtendibleLeaf::split(ExtendibleLeaf *nextSibling, int bit)
{
  bitset<18> bits;
  int i;
  for(i = 0; i < count; i++)
  {
    bits = content[i];
    if(bits[bit] == 1)//If the next bit to be measured is 1
    {
      nextSibling->insert(content[i]);
      this->remove(content[i]);
    }  

  }
}

const int  ExtendibleLeaf::find(const int value)
{
  int i;
  for(i = 0; i < count; i++)
  {
    if(value == content[i])
    {
      return content[i];
    }
  }
  return -1;
}
