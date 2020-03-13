/***********************************************************************
 * Module:
 *    Week 11, Sort Insertion
 *    Brother Kirby, CS 235
 * Author:
 *    Andres Rodriguez, Pedro Bastos, Fangyi Li
 * Summary:
 *    This program will implement the Insertion Sort
 ************************************************************************/

#ifndef SORT_INSERTION_H
#define SORT_INSERTION_H

#include <cassert>
#include "helpers.h"

/*****************************************************
 * SORT INSERTION
 * Perform the insertion sort
 ****************************************************/
template <class T>
void sortInsertion(T array[], int num)
{
   int iInsert;       // the largest element index so far
   int iPivot;         // mark until the sorted part of array
   int iShift;         // counter to the unsorted part of array

   T valuePivot;       // element value from pivot
                       // creates a separation between sorted and unsorted parts of
                       // array.
   for (iPivot = num - 2; iPivot >= 0; iPivot--)
   {
      // get the element from picot
      valuePivot = array[iPivot];

      // find a place to valuePivot
      iInsert = binarySearch(array, valuePivot, iPivot + 1, num - 1);

      // the correct place is the one element before iPivot
      iInsert--;

      // shifts all sorted elements
      for (iShift = iPivot; iShift < iInsert; iShift++)
      {
         array[iShift] = array[iShift + 1];
      }

      // stores the iPivot element
      array[iShift] = valuePivot;
   }

}


#endif // SORT_INSERTION_H
