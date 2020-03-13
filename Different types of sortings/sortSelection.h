/***********************************************************************
 * Module:
 *    Week 11, Sort Select
 *    Brother Kirby, CS 235
 * Author:
 *    Andres Rodriguez, Pedro Bastos, Fangyi Li
 * Summary:
 *    This program will implement the Selection Sort
 ************************************************************************/

#ifndef SORT_SELECTION_H
#define SORT_SELECTION_H

#include "helpers.h"

/*****************************************************
 * SORT SELECTION
 * Perform the selection sort
 ****************************************************/
template <class T>
void sortSelection(T array[], int num)
{
   int iLargest;       // the largest element index so far
   int iPivot;         // mark until the sorted part of array
   int iCheck;         // counter to the unsorted part of array

   // creates a separation between sorted and unsorted parts of
   // array.
   for (iPivot = num - 1; iPivot > 0; iPivot--)
   {
      // set index to first element
      iLargest = 0;

      // find the index of largest number in array
      for (iCheck = 1; iCheck < iPivot; iCheck++)
      {
         if (array[iLargest] <= array[iCheck])
         {
            iLargest = iCheck;
         }
      }

      // elements are not sorted
      if (array[iLargest] > array[iPivot])
      {
         // swap between them
         swapElements(array, iLargest, iPivot);
      }
   }
}


#endif // SORT_SELECTION_H
