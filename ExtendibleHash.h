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
  void split(const int &object);
  int GetBits()const {return bits;}

}; // class ExtendibleHashing

class ExtendibleLeaf
{
public:
  ExtendibleLeaf(int LeafSize);
  void insert(int value);
  void remove(int value);
  void split(ExtendibleLeaf *nextSibling, int bit);
  const int find(const int value);

  ExtendibleHash *parent;
  int *content;

private:
//  int *content;
  int count;
  int size;
};

#include "ExtendibleHash.cpp"

#endif

