/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include <iostream>        // for CIN and COUT
#include <fstream>         // for IFSTREAM
#include <cassert>         // for ASSERT
#include <sstream>
#include <string>          // for STRING: binary representation of codes
#include "bnode.h"         // for BINARY_NODE class definition
#include "list.h"          // for LIST container
#include "stack.h"         // for STACK container
#include "vector.h"        // for STACK container
#include "pair.h"          // for PAIR container
#include "huffman.h"       // for HUFFMAN() prototype

using std::cout;
using std::cin;
using std::ifstream;
using std::endl;
using std::string;
using std::bad_alloc;
using std::getline;

using namespace custom;


/*******************************************
* HUFFMAN
* Driver program to exercise the huffman generation code
*******************************************/
void huffman(const string & fileName)
{
   Huffman huffman;

   huffman.importFile(fileName);

   huffman.generate();
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
         forest.push_back(new BNode<custom::pair<float, string> >(*pair));

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
   BNode <custom::pair<float, string> > *left, *right, *newTree;

   // iterator for the first (left) and second (right) nodes
   list<BNode <custom::pair<float, string> > *>::iterator itLeft;
   list<BNode <custom::pair<float, string> > *>::iterator itRight;

   // a pair to be created
   custom::pair<float, string> *pair;

   // while there is more than one tree in list
   while (forest.size() > 1)
   {
      // sort list
      forest.sort();

      // get the pointers to left and right trees
      itLeft= forest.begin(); 
      left = *itLeft; 
      itRight = forest.begin();
      right = *(++itRight);

      if (left->data.getFirst() == right->data.getFirst() && left->data.getSecond().length() > 0)
      {
         BNode <custom::pair<float, string> > *temp;
         temp = right;
         right = left;
         left = temp;
      }

      // create a new pair
      pair = new custom::pair<float, string>(left->data.getFirst()+right->data.getFirst(), "");

      // create a new subtree
      newTree = new BNode<custom::pair<float, string> >(*pair);

      // connect parent to children
      newTree->pLeft = left;
      newTree->pRight = right;

      // connect children to parent
      left->pParent = newTree;
      right->pParent = newTree;

      // remove nodes (they were moved to a new tree)
      forest.erase(itLeft);
      forest.erase(itRight);

      // push new tree to list
      forest.push_front(newTree);
   }
}

/*******************************************
* HUFFMAN DISPLAY
* Display Huffman codes
*******************************************/
void Huffman::display()
{
   parse(forest.front(),-1);

   for (it = tokens->begin(); it != tokens->end(); ++it)
   {
      cout << (*it)->getFirst() << " = " << *((*it)->getSecond()) << endl;
   }
}

/*******************************************
* HUFFMAN DISPLAY
* Display Huffman codes
*******************************************/
void Huffman::parse(const BNode <custom::pair<float, string> > *pRoot,
   const int arcValue)
{
   // end recursion clausule
   if (pRoot == NULL)
   {
      return;
   }

   if (arcValue >= 0)
   {
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
