/***********************************************************************
* Header:
*    BNode
* Summary:
*    This a generic class to store any data-type elements organized
*    into a binary tree.
*
* Author
*    Andres Rodriguez, Pedro Bastos, Fangyi Li
************************************************************************/

// helper for Visual C++
#pragma once

// disable warning on old exception style (Visual C++ specific)
#pragma warning( disable : 4290 )  

#include <iostream>    // for CIN and COUT

using namespace std;

#ifndef BNODE_H
#define BNODE_H

/************************************************
* BNODE
* A class that holds a node for a Binary Tree.
***********************************************/
template <class T>
class BNode
{
public:
   T data;
   class BNode *pLeft;      // left node
   class BNode *pRight;     // right node
   class BNode *pParent;    // parent node

   // default constructor
   BNode() : pLeft(NULL), pRight(NULL), pParent(NULL)
   {
   }

   // non default constructor
   BNode(const T &element) : pLeft(NULL), pRight(NULL), pParent(NULL)
   {
      // set data to user parameter
      data = element;
   }
};

/**********************************************
* ADD LEFT
* Add a new B node with provided data.
**********************************************/
template <class T>
void addLeft(BNode<T> *&pParent, const T &element)  throw (const char*)
{
   BNode<T> *newNode;   // new BNode

   // attempt to allocate
   try
   {
      newNode = new BNode<T>(element);
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }

   addLeft(pParent, newNode);
}

/**********************************************
* ADD LEFT
* Connects current node to a parent
**********************************************/
template <class T>
void addLeft(BNode<T> *pParent, BNode<T> *pCurrent)
{
   // sanity check
   if (pCurrent)
   {
      pCurrent->pParent = pParent;
   }

   // connects parent and left child
   pParent->pLeft = pCurrent;
}

/**********************************************
* ADD RIGHT
* Add a new B node with provided data.
**********************************************/
template <class T>
void addRight(BNode<T> *pParent, const T &element ) throw (const char*)
{
   BNode<T> *newNode;   // new BNode

   // attempt to allocate
   try
   {
      newNode = new BNode<T>(element);
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }

   // connects nodes
   addRight(pParent, newNode);
}

/**********************************************
* ADD RIGHT
* Connects current node to a parent
**********************************************/
template <class T>
void addRight(BNode<T> *pParent, BNode<T> *pCurrent)
{
   // sanity check
   if (pCurrent)
   {
      pCurrent->pParent = pParent;
   }

   // connects parent and left child
   pParent->pRight = pCurrent;
}

/**********************************************
* COPY TREE
* A recursive function to copy trees
**********************************************/
template <class T>
BNode <T> *copyBTree(const BNode <T> *pSrc) throw (const char *)
{
   BNode<T> *destination;   // destination node

   // return in case of a leaf
   if (!pSrc)
   {
      return NULL;
   }

   // attempt to allocate
   try
   {
      destination = new BNode<T>(pSrc->data);
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }

   // go to left side of tree
   destination->pLeft = copyBTree(pSrc->pLeft);

   // connect its parent
   if (destination->pLeft)
   {
      destination->pLeft->pParent = destination;
   }

   // go to right side of tree
   destination->pRight = copyBTree(pSrc->pRight);

   // connect its parent
   if (destination->pRight)
   {
      destination->pRight->pParent = destination;
   }

   // returns from function
   return destination;
}

/**********************************************
* DELETE TREE
* A recursive function to delete tree
**********************************************/
template <class T>
void deleteBTree(BNode <T> *&pNode)
{
   // recursion stop condition
   if (!pNode)
   {
      return;
   }

   deleteBTree(pNode->pLeft);
   deleteBTree(pNode->pRight);

   // deallocate node
   delete pNode;

   // sets to NULL
   pNode = NULL;
}

/**********************************************
* SIZE BTREE
* A recursive function to count the number
* of nodes in a tree.
**********************************************/
template <class T>
int sizeBTree(BNode <T> *pNode)
{
   // recursion stop condition
   if (!pNode)
   {
      return 0;
   }

   // return pNode size recursively
   return sizeBTree(pNode->pLeft) + 1 + sizeBTree(pNode->pRight);
}

/**********************************************
* OPERATOR INSERTTION << 
* A recursive function to display all nodes in a tree.
**********************************************/
template <class T>
ostream & operator << (ostream & out, const BNode <T> * rhs)
{
   if (rhs == NULL)
   {
      return out;
   }
   
   out << rhs->pLeft;
   out << rhs->data << " ";
   out << rhs->pRight;

   return out;
}

/**********************************************
* OPERATOR  <
* Compares data
**********************************************/
template <class T>
bool operator < (const BNode <T> &lhs, const BNode <T> &rhs)
{
   return lhs.data < rhs.data;
}

/**********************************************
* OPERATOR  <=
* Compares data
**********************************************/
template <class T>
bool operator <= (const BNode <T> &lhs, const BNode <T> &rhs)
{
   return lhs.data <= rhs.data;
}

/**********************************************
* OPERATOR  >
* Compares data
**********************************************/
template <class T>
bool operator > (const BNode <T> &lhs, const BNode <T> &rhs)
{
   return lhs.data > rhs.data;
}

/**********************************************
* OPERATOR  >=
* Compares data
**********************************************/
template <class T>
bool operator >= (const BNode <T> &lhs, const BNode <T> &rhs)
{
   return lhs.data >= rhs.data;
}

/**********************************************
* OPERATOR  ==
* Compares data
**********************************************/
template <class T>
bool operator == (const BNode <T> &lhs, const BNode <T> &rhs)
{
   return lhs.data == rhs.data;
}

/**********************************************
* OPERATOR  !=
* Compares data
**********************************************/
template <class T>
bool operator != (const BNode <T> &lhs, const BNode <T> &rhs)
{
   return lhs.data != rhs.data;
}

#endif // BNODE_H
