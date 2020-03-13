/***********************************************************************
 * Module:
 *    Assignment 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "spellCheck.h"
#include "hash.h"
#include "vector.h"
using namespace std;

#ifdef __linux__ 
#define DICTIONARY_FILE "/home/cs235/week12/dictionary.txt"
#else
#define DICTIONARY_FILE "dictionary.txt"
#endif

/******************************************
* OPERATOR <<
* Print list of mispelled words
*****************************************/
ostream & operator << (ostream & out, custom::vector<string> &rhs)
{
   custom::vector<string>::iterator it;

   for (it = rhs.begin(); it != rhs.end(); )
   {
      out << (*it);

      if ((++it) != rhs.end())
      {
         out << ", ";
      }
   }
   return out;
}

/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/
void spellCheck()
{
   ifstream dictionaryFile(DICTIONARY_FILE);   // file stream for dictionary
   string fileName;                            // file name to parse
   string word;                                // current word in file
   EntryHash dictionary(500);                  // hash table
   custom::vector<string> misSpelled;          // misspelled words

   // opens stream
   if (dictionaryFile.is_open())
   {
      // read one word for line
      while (getline(dictionaryFile, word))
      {
         // insert the word into hash table
         dictionary.insert(word);
      }

      // close stream
      dictionaryFile.close();
   }
   else
   {
      cout << "Could not open file '" << DICTIONARY_FILE << "';" << endl;
      return;
   }

   // request a file from user
   cout << "What file do you want to check? ";
   cin >> fileName;

   ifstream textFile(fileName);       // file stream
   string lowerWord;                  // only lower words will be inserted into table

   // opens stream
   if (textFile.is_open())
   {
      // read every word in stream
      while (textFile >> word)
      {
         // to convert to lower
         lowerWord = word;

         // convert to lower case
         for (auto& c : lowerWord)
         {
            c = tolower(c);
         }

         // word not present in dictionary
         if (!dictionary.find(lowerWord))
         {
            // add to list of misspelled words
            misSpelled.push_back(word);
         }

      }

      // close stream
      textFile.close();

      // there are misspelled words
      if (misSpelled.size() > 0)
      {
         cout << "Misspelled: " << misSpelled << endl;
      }
      else
      {
         cout << "File contains no spelling errors" << endl;
      }
   }
   else
   {
      cout << "Unable to open file." << endl;
   }
}
