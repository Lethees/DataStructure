/***********************************************************************
 * Module:
 *    Week 11, Sort Quick
 *    Brother Helfrich, CS 235
 * Author:
 *    <author>
 * Summary:
 *    This program will implement the Quick Sort
 ************************************************************************/

#ifndef SORT_QUICK_H
#define SORT_QUICK_H

#include "helpers.h"

/*****************************************************
 * SORT QUICK
 * Perform the quick sort
 ****************************************************/
template <class T>
void sortQuick(T array[], int num)
{
   int iUp;             // counter from beginning and up
   int iDown;           // counter from ending and down
   int iEnd;            
   T pivotValue;

   // recursion stop condition
   if (num <= 1)
   {
      return;
   }

   // starts from ending
   iDown = iEnd = num - 1;

   // starts from beginning
   iUp = 0;

   // the pivot is the middle element
   pivotValue = array[iEnd / 2];


   while (iUp <= iDown)
   {
      // it will stop when it finds an element less than pivot
      while (iUp <= iEnd && pivotValue > array[iUp])
      {
         iUp++;
      }
      // it will stop when it finds an element great than pivot
      while (iDown >= 0 && array[iDown] > pivotValue)
      {
         iDown--;
      }

      // an element was found to get swapped
      if (iUp <= iDown)
      {
         swapElements(array, iUp++, iDown--);
      }
   }

   // the first half (0-iUp) will be sorted
   sortQuick(array, iUp);

   // the second half (num-1 to iDown) will be sorted
   sortQuick(array + iUp, iEnd - iUp + 1);
}


#endif // SORT_QUICK_H
