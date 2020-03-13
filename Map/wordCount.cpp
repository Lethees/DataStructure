/***********************************************************************
 * Module:
 *    Week 10, WORD COUNT
 *    Brother Helfrich, CS 235
 * Author:
 *    Andres Rodriguez, Pedro Bastos, Fangyi Li
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/

#include "map.h"           // for MAP
#include "wordCount.h"     // for wordCount() prototype
#include <iostream>        // for CIN and COUT
#include <string>          // for STRING
#include <fstream>         // for IFSTREAM
#include <sstream>         // for STRINGSTREAM
#include <string>          // for STRING: binary representation of codes


// standard namespace 
using namespace std;

void readFile(custom::map <string, int> & counts, const string & fileName)
{
   // create object to handle file
   ifstream wordsFile(fileName);

   string token;       // token to store in tree
   custom::map<string, int>::iterator it;

   // opens stream
   if (wordsFile.is_open())
   {
      while (wordsFile >> token)
      {
         it = counts.find(token);

         if (it == counts.end())
         {
            counts.insert(token, 1);
         }
         else
         {
            (*it).second++;
         }
      }

      // close stream
      wordsFile.close();
   }
}

/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount()
{
   string fileName;
   string word;

   custom::map<string,int> mapFile;

   cout << "What is the filename to be counted? ";

   cin >> fileName;

   readFile(mapFile, fileName);

   cout << "What word whose frequency is to be found. Type ! when done" << endl;

   while (1)
   {
      cout << "> ";
      cin >> word;

      if (word == "!")
      {
         break;
      }

      cout << "\t" << word << " : " << mapFile[word] << endl;
   }

}
