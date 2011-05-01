#ifndef EXTENDIBLE_HASH_H
  #define EXTENDIBLE_HASH_H

class ExtendibleLeaf;

class ExtendibleHash
{
  ExtendibleLeaf  **Directory;
  int bits;
  int size;
  int LeafSize;
  int bit;
  int target;

public:
  ExtendibleHash(const int & notFound, int s, int LSize = 2);
  void insert(const int &object);
  void remove(const int &object);
  const int & find(const int &object);
  void split(const int & object);
  void splitCheck();
  void rehash();
  void insertNext(int value, int position);
  int GetBits()const {return bits;}
  void print();

}; // class ExtendibleHashing

class ExtendibleLeaf
{
public:
  ExtendibleLeaf(int LeafSize, int pos, int bit);
  void insert2(int value);
  int insert(int value);
  void remove(int value);
  void split(ExtendibleLeaf *nextSibling);
  void split2();
  const int find(const int value);
  void setbit(int i);
  void setpos(int i);
  void print();

  ExtendibleHash *parent;
  int *content;

private:
//  int *content;
  int position;
  int count;
  int size;
  int check;
  int bits;
};

#include "ExtendibleHash.cpp"

#endif

