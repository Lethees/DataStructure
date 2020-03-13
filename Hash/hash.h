/***********************************************************************
* Header:
*    Hash
* Summary:
*    This a generic class to store any data-type elements organized
*    into a hash table.
*
* Author
*    Andres Rodriguez, Pedro Bastos, Fangyi Li
************************************************************************/

// helper for Visual C++
#pragma once

// disable warning on old exception style (Visual C++ specific)
#pragma warning( disable : 4290 )  

#ifndef HASH_H
#define HASH_H
#include <iostream>

#include "vector.h"
#include "list.h"

using namespace custom;

/************************************************
* HASH
* A class that holds stuff organized at a
* hash table.
***********************************************/

template <class T>
class Hash
{
private:
   vector<list<T> *> table;

   int numElements;
   int numBuckets;

public:
   Hash(int numBuckets) throw (const char *);
   Hash(const Hash<T> &rhs) throw (const char *);

   ~Hash() { }

   Hash <T> & operator = (const Hash <T> & rhs) throw(const char*);

   virtual int hash(const T &element ) const = 0;

   bool empty() const { return numElements == 0; }
   int size() const { return numElements; }
   int capacity() const { return numBuckets; }

   void clear() {
      table.clear();
      this->numBuckets = 0;
      this->numElements = 0;
   }

   void insert(const T &element) throw(const char*);

   bool find(const T& element);

   void print();
};

/**********************************************
* HASH : NON-DEFAULT CONSTRUCTOR
* Preallocate the hash to "numBuckets"
**********************************************/
template <class T>
Hash<T>::Hash(int numBuckets) throw (const char *) {
   try
   {
      for (int i = 0; i < numBuckets; i++)
      {
         table.push_back(NULL);
      }
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate memory for the hash.";
   }

   this->numBuckets = numBuckets;
   this->numElements = 0;
}

/*******************************************
* HASH :: COPY CONSTRUCTOR
*******************************************/
template <class T>
Hash <T> ::Hash(const Hash <T> & rhs) throw (const char*)
{
   clear();

   *this = rhs;
}

/*******************************************
* HASH :: Assignment operator
* Copies elements from rhs to lhs hash
*******************************************/
template <class T>
Hash <T> & Hash <T> :: operator = (const Hash <T> & rhs) throw(const char*)
{
   // lhs is just starting
   table.clear();

   // copy data
   this->table = rhs.table;

   this->numBuckets = rhs.numBuckets;
   this->numElements = rhs.numElements;

   return *this;
}

/*******************************************
* HASH :: INSERT
* Insert element in hash after element hashing
*******************************************/
template <class T>
void Hash <T> :: insert(const T &element ) throw(const char*)
{
   int hashValue = hash(element);          // compute hash value
   list<T> *pList = table[hashValue];      // find the list of that hashValue

   // there is no word yet
   if (pList == NULL)
   {
      // create a new list
      pList = new list<T>();

      // store the list into table
      table[hashValue] = pList;
   }

   // insert element in list
   pList->push_front(element);

   // increases number of elements
   numElements++;
}

/*******************************************
* HASH :: FIND
* Copies elements from rhs to lhs hash
*******************************************/
template <class T>
bool Hash <T> :: find (const T & element) 
{
   int hashValue = hash(element);          // compute hash value
   list<T> *pList = table[hashValue];      // find the list of that hashValue

   // find element in list
   return !(pList != NULL && pList->find(element) == pList->end());
}

/*******************************************
* HASH :: PRINT   
* Print all hash table
*******************************************/
template <class T>
void Hash <T> ::print()
{
   typename vector<list<T>*>::iterator it1;
   typename list<T>::iterator it2;
   list<T> *l;
   int i = 0;

   for (it1 = table.begin(); it1 != table.end(); ++it1)
   {
      l = (*it1);

      if (l == NULL) {
         std::cout << "table[" << i << "] = NULL" << endl;
      }
      else
      {
         std::cout << "table[" << i << "] = {";
         for (it2 = l->begin(); it2 != l->end(); )
         {
            std::cout << (*it2);

            ++it2;
            if (it2 == l->end())
            {
               cout << ", ";
            }
         }
         std::cout << "}" << endl;
      }
      i++;
   }
}
#endif /* HASH_H */
