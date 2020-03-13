/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    Implements a insertion sort. It uses a list to sort an array.
 * Author
 *    Andres Rodriguez, Pedro Bastos, Fangyi Li
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "node.h"

/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{
   Node <T> *head = NULL;   // new list head (empyu list)
   Node <T> *pCurrent;      // auxiliary current pointer
   Node <T> *pPrevious;     // auxiliary previous pointer
   int i;                   // index for array

   // insert the first element into list
   head = insert(head, array[0]);

   // read all elements in array inserting into list
   for (i = 1; i < num; i++)
   {
      // initialize pointer to head of list
      pCurrent = pPrevious = head;

      // tranverse list to find where to put new node
      while (pCurrent && array[i] > pCurrent->data)
      {
         pPrevious = pCurrent;
         pCurrent = pCurrent->pNext;
      }

      // insert before pPrevious node
      if (array[i] < pPrevious->data)
      {
         // insert current array element into list
         pCurrent = insert(pPrevious, array[i]);

         // check if the new node will be the head
         if (array[i] < head->data)
         {
            // update head
            head = pCurrent;
         }
      }
      else
      {
         // insert after pPrevious node 
         insert(pPrevious, array[i], true);
      }
   }

   // index reuse to put array elements in order
   i = 0;

   // points to list head
   pCurrent = head;

   // tranverse all list
   while (pCurrent)
   {
      // put the node data into array
      array[i++] = pCurrent->data;

      // move forward
      pCurrent = pCurrent->pNext;
   }
}

#endif // INSERTION_SORT_H

