/***********************************************************************
* Header:
*    Node
* Summary:
*    This a generic class to store any data-type elements, creating
*    a base for linked list elements.
*
* Author
*    Andres Rodriguez, Pedro Bastos, Fangyi Li
************************************************************************/

// helper for Visual C++
#pragma once

// disable warning on old exception style (Visual C++ specific)
#pragma warning( disable : 4290 )  

#include <iostream>       // for CIN and COUT

using namespace std;

#ifndef NODE_H
#define NODE_H

/************************************************
* NODE
* A base class to create linked lists.
***********************************************/
template <class T>
class Node
{
public:
   T data;                 // data to store
   class Node<T> *pNext;   // next node
   class Node<T> *pPrev;   // previous node

   // default constructor
   Node() : pNext(NULL), pPrev(NULL)
   {
   }

   // non-default constructor
   Node(const T element) : pNext(NULL), pPrev(NULL)
   {
      this->data = element;
   }
};

/******************************************
* INSERT
* Insert a node into the list keeping 
* pointers consistent.
*****************************************/
template <class T>
Node<T> * insert(Node<T> *pCurrent, const T &element, bool after = false)
{
   Node<T> *pNew = new Node<T>(element);     // new node

   // list is not empty
   if (pCurrent)
   {
      // it is diffent inserting from left or right 

      // inserting into right
      if (after)
      {
         // reposition pointers to keep a list
         pNew->pPrev = pCurrent;
         pNew->pNext = pCurrent->pNext;
         pCurrent->pNext = pNew;

         if (pNew->pNext)
         {
            pNew->pNext->pPrev = pNew;
         }
      }
      else  // inserting into left
      {
         // reposition pointers to keep a list
         pNew->pNext = pCurrent;
         pNew->pPrev = pCurrent->pPrev;
         pCurrent->pPrev = pNew;

         if (pNew->pPrev)
         {
            pNew->pPrev->pNext = pNew;
         }
      }
   }

   // returns newsly created node
   return pNew;
}

/******************************************
* COPY
* Copy one list to another
*****************************************/
template <class T>
Node <T> * copy(Node <T> *rhs)
{
   Node<T> *pDestination = new Node<T>(rhs->data);  // create a new node copying data value
   Node<T> *pSrc;                                   // auxiliary pointer from source
   Node<T> *pDst;                                   // auxiliary pointer to destination

   // new list head
   pDst = pDestination;

   // insert each node from rhs list to a new one
   for (pSrc = rhs->pNext; pSrc; pSrc = pSrc->pNext)
   {
      pDst = insert(pDst, pSrc->data, true);
   }

   // return head from new list
   return pDestination;
}

/******************************************
* FIND
* Find an element in list
*****************************************/
template <class T>
Node <T> * find( Node <T> *pHead, const T &element)
{
   Node<T> *pCurrent;            // current node

   // tranverse all nodes from list
   for (pCurrent = pHead; pCurrent; pCurrent = pCurrent->pNext)
   {
      // current data is the same as element
      if (pCurrent->data == element)
      {
         // returns current node
         return pCurrent;
      }
   }
   
   // nothing was found
   return NULL;
}

/******************************************
* REMOVE
* Remove an element from list
*****************************************/
template <class T>
Node <T> * remove(Node <T> *pRemove)
{
   Node <T> *pReturn;        // pointer to return

   // node is null
   if (!pRemove)
   {
      return pRemove;
   }

   // reconnect pointers to nodes
   if (pRemove->pPrev)
   {
      pRemove->pPrev->pNext = pRemove->pNext;
   }

   if (pRemove->pNext)
   {
      pRemove->pNext->pPrev = pRemove->pPrev;
   }

   // will be the left or the right node
   pReturn = pRemove->pPrev ? pRemove->pPrev : pRemove->pNext;
   
   // deallocate node
   delete pRemove;
   
   // pRemove pointer will point to left/right node 
   pRemove = pReturn;

   // returns new position for pRemove
   return pReturn;
}

/******************************************
* DISPLAY
* Display the contents of the list
*****************************************/
template <class T>
ostream & operator << (ostream & out,  Node <T> * front)
{
   Node <T> *pCurrent;   // auxiliary pointer

   // tranverse list
   for (pCurrent = front; pCurrent; )
   {
      // copy current data to stream
      out << pCurrent->data;

      // next node
      pCurrent = pCurrent->pNext;

      // there are more nodes to visit
      if (pCurrent)
      {
         out << ", ";
      }
   }

   // returns stream
   return out;
}

/******************************************
* FREEDATA
* Deallocate memory
*****************************************/
template <class T>
void freeData(Node <T> *&front)
{
   Node <T> *pCurrent;    // auxiliary node

   // tranverse list
   while (front)
   {
      // move to next node
      pCurrent = front->pNext;

      // deallocate node
      delete front;

      // update new head
      front = pCurrent;
   }

   // points head to NULL (list is empty)
   front = NULL;
}
#endif   // NODE_H