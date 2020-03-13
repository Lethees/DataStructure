/***********************************************************************
 * Module:
 *    Assignment 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#ifndef SPELL_CHECK_H
#define SPELL_CHECK_H

#include <string>
#include "hash.h"
#include <cassert>

void spellCheck();

/****************************************
* WORD HASH
* A hash of words of a dictionary
****************************************/
class EntryHash : public Hash <string>
{
public:
   EntryHash(int numBuckets)    throw (const char *) : Hash <string>(numBuckets) {}
   EntryHash(const EntryHash & rhs) throw (const char *) : Hash <string>(rhs) {}

   // hash function for strings will add up all the ASCII values
   int hash(const string & entry) const
   {
      int sum = 0;
      string word = entry;

      for (std::string::iterator it = word.begin(); it != word.end(); ++it) {
         sum += (*it);
      }

      int index = sum % capacity();

      assert(0 <= index && index < capacity());
      return index;
   }
};


#endif // SPELL_CHECK_H
