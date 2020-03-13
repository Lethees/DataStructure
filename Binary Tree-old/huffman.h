/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "bnode.h"         // for BINARY_NODE class definition
#include "list.h"          // for LIST container
#include "stack.h"         // for STACK container
#include "vector.h"        // for STACK container
#include "pair.h"          // for PAIR container

#include <string>
void huffman(const std::string & fileName);

class Huffman
{
private:
   // tokens collection
   custom::vector<custom::pair<string, custom::list<int>*>*> *tokens;

   // the tree collection
   custom::list<BNode <custom::pair<float, string> > *> forest;

   // iterator for vector and used in display
   custom::vector<custom::pair<string, custom::list<int>*>*>::iterator it;

   // parse tree
   void parse(const BNode <custom::pair<float, string> > *pRoot,
      const int arcValue);

   custom::list<int> *walk;
public:

   // default constructor
   Huffman()
   {
      tokens = new custom::vector<custom::pair<string, custom::list<int>*>*>();
      walk = new custom::list<int>();
   }

   ~Huffman()
   {
      delete tokens;
      delete walk;
   }

   // import file
   bool importFile(const string &fileName);

   // generate huffman code
   void generate();

   // display table
   void display();
};

#endif // HUFFMAN_h
