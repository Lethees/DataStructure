/***********************************************************************
* Header:
*    Huffman
* Summary:
*    This class implements data compression using Huffman codes.
*
* Author
*    Andres Rodriguez, Pedro Bastos, Fangyi Li
************************************************************************/

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "bnode.h"         // for BINARY_NODE class definition
#include "list.h"          // for LIST container
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

   // walk stack
   custom::list<int> *walk;

   // calculate distance from list front to iterator
   int delta(const custom::list<BNode <custom::pair<float, string>> *>::iterator &it) const;

public:

   // default constructor
   Huffman()
   {
      tokens = new custom::vector<custom::pair<string, custom::list<int>*>*>();
      walk = new custom::list<int>();
   }

   // destructor
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
