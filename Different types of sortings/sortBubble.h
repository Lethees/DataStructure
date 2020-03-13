/***********************************************************************
 * Module:
 *    Week 11, Sort Bubble
 *    Brother Kirby, CS 235
 * Author:
 *    Andres Rodriguez, Pedro Bastos, Fangyi Li
 * Summary:
 *    This program will implement the Bubble Sort
 ************************************************************************/

#ifndef SORT_BUBBLE_H
#define SORT_BUBBLE_H

#include "helpers.h"

 /*****************************************************
  * SORT BUBBLE
  * Perform the bubble sort
  ****************************************************/
template <class T>
void sortBubble(T array[], int num)
{
   bool swapped;       // flag to indicate that swap occurred 
   int iPivot;         // mark until the sorted part of array
   int iCheck;         // counter to the unsorted part of array

   // creates a separation between sorted and unsorted parts of
   // array.
   for (iPivot = num - 1; iPivot > 1; iPivot--)
   {
      // there were not swapps yet
      swapped = false;

      // sort the unsorted part of array
      for (iCheck = 0; iCheck < iPivot; iCheck++)
      {
         // elements are not sorted
         if (array[iCheck] > array[iCheck + 1])
         {
            // swap between them
            swapElements(array, iCheck, iCheck + 1);

            // there was a swap
            swapped = true;
         }
      }

      // there is no swaps left, so the array is sorted
      if (!swapped)
      {
         return;
      }
   }
}


#endif // SORT_BUBBLE_H
