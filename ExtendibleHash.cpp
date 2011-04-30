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
  bits = b;
  ExtendibleLeaf *ptr;
  ptr = new ExtendibleLeaf(LSize, 0, bits);
  ptr->parent = this;
  for(i = 0; i < b; i++)
    size = size * 2;
  Directory = new ExtendibleLeaf*[size];

  

 /* for(i = 0; i < size; i++)
  {
    Directory[i] = ptr;
  }*/
  Directory[0] = new ExtendibleLeaf(LSize, 0, bits);
  Directory[1] = new ExtendibleLeaf(LSize, 0, bits);
  LeafSize = LSize;
  
} // ExtendibleHash()

void ExtendibleHash::insert(const int &object)
{
  int i, j, k;
  int temp;
  k = size;//Initializes k for future use
  j = 0;

  bitset<18> bitCheck;//Converts into bits
  bitCheck = object;
  for(i = 0; i < bits; i++)//Iterates to where the insertion needs to be
  {
      k = k / 2;//Calculates spaces moved
    if(bitCheck[18 - (i+1)] == 1)//If current bit is 1
    {
      j = j + k;;//Does actual move
    }
  }
  Directory[j]->insert(object);
 // cout << j << endl;
  
} // insert()


void ExtendibleHash::remove(const int &object)
{
  int i, j, k;
  k = size;
  j = 0;

  bitset<18> bitCheck;
  bitCheck = object;
  for(i = 0; i < bits; i++)
  {
    k = k / 2;
    if(bitCheck[18 -i] == 1)
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
  
  bitset<18> bitCheck;
  bitCheck = object;
  for(i = 0; i < bits; i++)
  {
    k = k / 2;
    if(bitCheck[18 - i] == 1)
    {
      j = j + k;
    }
  }
  target=  Directory[j]->find(object);
  return target;
}  // find()



void ExtendibleHash::split(const int &object)
{
  int pos = object;
  int i = pos;
  int counter = 0;
  while(i < size)
  {
    if(Directory[pos] == Directory[i])
    {
      counter++;
    } else {
      break;
    }
    i++;
  }//get amount of shared node
  if(counter == 1)
  {
    this->rehash();
    ExtendibleLeaf *ptr = new ExtendibleLeaf(LeafSize, (2 * pos) + 1, bits + 1);
    Directory[2 * pos]->split(ptr);
    Directory[(2 * pos) + 1] = ptr;
  } else {
    ExtendibleLeaf *ptr = new ExtendibleLeaf(LeafSize, pos +(counter/2), 0);
    Directory[pos]->split(ptr);
    for(i = (counter/2); i < counter; i++)
    {
      Directory[pos + i] = ptr;
    }//sets new ptrs
  }
  //bits++;
cout << "split: "<< bits<<endl;
}  // split();

void ExtendibleHash::splitCheck()
{

}

void ExtendibleHash::rehash()
{
  int i;
cout << "rehashed\n";
  ExtendibleLeaf **ptr;
  ptr = new ExtendibleLeaf*[size * 2];
  bits++;
  for(i = 0; i < size; i++)
  {
    ptr[2 * i] = Directory[i];
    ptr[(2 * i) + 1] = Directory[i];
    Directory[i]->setpos(2 * i);
  }//Seting new pointers
  size = size * 2;
  Directory = ptr;
}

void ExtendibleHash::print()
{
  int i;
  for(i = 0; i < size; i++)
  {
    cout<< "Hash index: " << i << endl;
    Directory[i]->print();
  }
}

void ExtendibleHash::insertNext(int value, int pos)
{
  Directory[pos + 1]->insert(value);
}

ExtendibleLeaf::ExtendibleLeaf(const int LeafSize, int pos, int bit)
{
  position = pos;
  bits = bit;
  //check = checks;
  content = new int[LeafSize];
  count = 0;
size = 1000;
 // size = LeafSize;
}//Extendible Leaf

void ExtendibleLeaf::insert(int value)
{
  if(count == size)
  {
    parent->split(position);
    bitset<18> bitCheck (value);
    if(bitCheck[18 - (bits - 1)] == 0)
    {
      content[count] = value;
      count++;
    } else {
      parent->insertNext(value, position);
    }
  } else {
  
  content[count] = value;
  count++;
  }
 // cout << value << " in slot " << count - 1 << " in ";

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

void ExtendibleLeaf::split(ExtendibleLeaf *nextSibling)
{
  int i;
cout << "                                                  " << bits << endl;
  nextSibling->setbit(bits + 1);
  bitset<18> bitCheck;
  for(i = 0; i < count; i++)
  {
    bitCheck = content[i];
    if(bitCheck[18 - (bits - 1)] == 1)
    {
      nextSibling->insert(content[i]);
      this->remove(content[i]);
    }
  }
  bits++;
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

void ExtendibleLeaf::setbit(int i)
{
  bits = i;
}

void ExtendibleLeaf::setpos(int i)
{
  position = i;
}

void ExtendibleLeaf::print()
{
  int i;
  bitset<18> bitCheck;
  for(i = 0; i < count; i++)
  {
    bitCheck = content[i];
    cout<<i<<". "<<content[i] << "  bits: " << bitCheck << endl;
  }
}
