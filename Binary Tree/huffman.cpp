/***********************************************************************
* Module:
*    Huffman
* Summary:
*    This class implements data compression using Huffman codes.
* Author
*    Andres Rodriguez, Pedro Bastos, Fangyi Li
************************************************************************/

#include <iostream>        // for CIN and COUT
#include <fstream>         // for IFSTREAM
#include <cassert>         // for ASSERT
#include <sstream>         // for STRINGSTREAM
#include <string>          // for STRING: binary representation of codes
#include "bnode.h"         // for BINARY_NODE class definition
#include "list.h"          // for LIST container
#include "vector.h"        // for VECTOR container
#include "pair.h"          // for PAIR container
#include "huffman.h"       // for HUFFMAN() prototype

using std::cout;
using std::cin;
using std::ifstream;
using std::endl;
using std::string;
using std::bad_alloc;
using std::getline;

/*******************************************
* HUFFMAN
* Driver program to exercise the huffman generation code
*******************************************/
void huffman(const string & fileName)
{
   Huffman huffman;     // huffman object

   // importe file into list 
   huffman.importFile(fileName);      

   // generate Huffman code
   huffman.generate();

   // display table
   huffman.display();
}


/******************************************
* OPERATOR <<
* Print reversely contents of a list into a list
*****************************************/
ostream & operator << (ostream & out, const custom::list<int> &rhs)
{
   custom::list<int>::reverse_iterator it;

   for (it = rhs.rbegin(); it != rhs.rend(); ++it)
   {
      out << (*it);
   }
   return out;
}

/*******************************************
* HUFFMAN IMPORT FILE
* Import file into forest
*******************************************/
bool Huffman::importFile(const string & fileName)
{
   // create object to handle file
   ifstream huffmanFile(fileName);

   string line;        // line from file
   string token;       // token to store in tree
   string frequency;   // frequency of the token

   // a pair to be created
   custom::pair<float, string> *pair;

   // opens stream
   if (huffmanFile.is_open())
   {
      // read every line in file
      while (getline(huffmanFile, line))
      {
         // parses line
         stringstream ss(line);
         ss >> token;
         ss >> frequency;

         // create a new pair
         pair = new custom::pair<float, string>(stof(frequency), token);

         // store pair into forest
         forest.push_back(new BNode<custom::pair<float, string>>(*pair));

         // store pair into tokens collection
         tokens->push_back(new custom::pair<string, custom::list<int>*>(token, new custom::list<int>()));
      }

      // close stream
      huffmanFile.close();
   }
   else
   {
      return false;
   }

   return true;
}

/*******************************************
* HUFFMAN GENERATE
* Generate Huffman codes
*******************************************/
void Huffman::generate()
{
   // auxiliaries pointers to Tree Nodes
   BNode <custom::pair<float, string>> *left = NULL, *right = NULL, *newTree;

   // iterator for the first (left) and second (right) nodes
   custom::list<BNode <custom::pair<float, string>> *>::iterator it;
   custom::list<BNode <custom::pair<float, string>> *>::iterator itLeft;
   custom::list<BNode <custom::pair<float, string>> *>::iterator itRight;

   // a pair to be created
   custom::pair<float, string> *pair;

   // sorted list
   custom::list<BNode <custom::pair<float, string> > *> sortedForest;

   // while there is more than one tree in list
   while (forest.size() > 1)
   {
      // copy forest to a temp list
      sortedForest = forest;

      // sort temp list
      sortedForest.sort();

      // get two minima numbers in forest
      it = sortedForest.begin();
      left = *it;
      ++it;
      right = *it;

      // deallocate used memory
      sortedForest.clear();

      // find trees in current forest
      itLeft = forest.find(left);
      itRight = forest.find(right);

      // find leftmost slot
      if (delta(itLeft) > delta(itRight))
      {
         it = itRight;
         itRight = itLeft;
         itLeft = it;
      }

      // create a new pair
      pair = new custom::pair<float, string>(left->data.getFirst() + right->data.getFirst(), "");

      // create a new subtree
      newTree = new BNode<custom::pair<float, string>>(*pair);

      // connect parent to children
      newTree->pLeft = left;
      newTree->pRight = right;

      // connect children to parent
      left->pParent = newTree;
      right->pParent = newTree;

      // update itLeft with the new tree
      forest.insert(itLeft, newTree);
      forest.erase(itLeft);

      // move the back of the list into itRight
      forest.insert(itRight, forest.back());
      forest.erase(itRight);

      // remove last element from list
      forest.pop_back();
   }

}

/*******************************************
* HUFFMAN DISPLAY
* Display Huffman codes
*******************************************/
void Huffman::display()
{
   parse(forest.front(), -1);

   for (it = tokens->begin(); it != tokens->end(); ++it)
   {
      cout << (*it)->getFirst() << " = " << *((*it)->getSecond()) << endl;
   }
}

/*******************************************
* HUFFMAN PARSE
* Parse Huffman trees
*******************************************/
void Huffman::parse(const BNode <custom::pair<float, string>> *pRoot,
   const int arcValue)
{
   // end recursion clausule
   if (pRoot == NULL)
   {
      return;
   }

   // initial call will be -1. And will not be considered.
   if (arcValue >= 0)
   {
      // push arc value in stack
      walk->push_front(arcValue);
   }

   // recursively find frequencies for left side
   parse(pRoot->pLeft, 0);

   // check if the a node is a leaf
   if (pRoot->pLeft == NULL && pRoot->pRight == NULL)
   {
      for (it = tokens->begin(); it != tokens->end(); ++it)
      {
         if ((*it)->getFirst() == pRoot->data.getSecond())
         {
            break;
         }
      }

      // copy walk stack
      *((*it)->second) = *(walk);
   }

   // recursively find frequencies for left side
   parse(pRoot->pRight, 1);

   // remove first element in list
   if (walk->size() > 0)
   {
      walk->pop_front();
   }
}

/*******************************************
* HUFFMAN DELTA
* Get distance between head and iterator
*******************************************/
int Huffman :: delta(const custom::list<BNode <custom::pair<float, string>> *>::iterator &it) const
{
   // distance
   int d;

   // temporary iterator
   custom::list<BNode <custom::pair<float, string>> *>::iterator itTemp;

   // iterates until it
   for (d = 0, itTemp = forest.begin(); itTemp != it; ++itTemp, ++d);

   // return dstance from front
   return d;
}


