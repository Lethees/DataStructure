/***********************************************************************
* Header:
*    goFish
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
* Author:
*    Andres Rodriguez, Pedro Bastos, Fangyi Li
************************************************************************/
#include <iostream>
#include <sstream>
#include <fstream>
#include "set.h"
#include "card.h"
#include "goFish.h"
using namespace std;

#ifdef __linux__ 
#define GOFISH_FILE "/home/cs235/week05/hand.txt"
#else
#define GOFISH_FILE ""
#endif

/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
   custom::set<Card> cards;            // set of cards
   Card card;                          // current card
   custom::set <Card> ::iterator it;   // set iterator
   int found = 0;                      // found counter
   string line;                        // a line from file

   // intordutory message
   cout << "We will play 5 rounds of Go Fish.  Guess the card in the hand" << endl;

   // create object to handle file
   ifstream handsFile(GOFISH_FILE);

   // opens stream
   if (handsFile.is_open())
   {
      // assuming there is only one line in file
      getline(handsFile, line);

      // close stream
      handsFile.close();
   }

   // string stream token parser
   stringstream ss(line);
   while (ss >> card)
   {
      // insert new card into set
      cards.insert(card);
   }
  
   // loop throught 5 rounds
   for (int i = 1; i <= 5; i++)
   {
      // output prompt
      cout << "round " << i << ": ";

      // wait for input from user
      cin >> card;

      // look for that card
      it = cards.find(card);

      // if found
      if (it != cards.end())
      {
         // increments counter
         found++;

         // remove card from set
         cards.erase(it);

         // print a match message to user
         cout << "\tYou got a match!" << endl;
      }
      else
      {
         // nothing found
         cout << "\tGo Fish!" << endl;
      }
   }

   // prints summary 
   cout << "You have " << found << " matches!" << endl;
   cout << "The remaining cards: ";

   // list all remaining cards
   for (it = cards.begin(); it != cards.end(); )
   {
      cout << *(it);

      ++it;

      // it is not the end of set yet!
      if (it != cards.end())
      {
         cout << ", ";
      }
   }

   // print a newfeed
   cout << endl;
}
