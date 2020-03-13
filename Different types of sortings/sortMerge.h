/***********************************************************************
 * Module:
 *    Week 11, Sort Merge
 *    Brother Kirby, CS 235
 * Author:
 *    Andres Rodriguez, Pedro Bastos, Fangyi Li
 * Summary:
 *    This program will implement the Merge Sort
 ************************************************************************/

#ifndef SORT_MERGE_H
#define SORT_MERGE_H

#include "helpers.h"

/*****************************************************
 * SORT MERGE
 * Perform the merge sort
 ****************************************************/
template <class T>
void sortMerge(T array[], int num)
{
   T *source = new T[num];          // source data
   T *destination = new T[num];     // data after merge
   T *pTemp;                        // temporary pointer for swapping

   int numMerges;                   // number of merges performed
   int iBegin1, iBegin2;            // beginning indices for sub-arrays
   int iEnd1, iEnd2;                // ending indices for sub-arrays
   int destinationSize;             // the size of destination data

   // copy array into source
   for (int i = 0; i < num; i++)
   {
      source[i] = array[i];
   }

   do
   {
      // initialization
      iBegin1 = 0;
      numMerges = 0;
      destinationSize = 0;

      // perform merges until end of array
      while (iBegin1 < num)
      {
         // find the first ending for the first sub-array
         for (iEnd1 = iBegin1 + 1;
            iEnd1 < num && !(source[iEnd1 - 1] > source[iEnd1]);
            iEnd1++);

         // the begin for sub-array 2 will be the end of sub-array 1
         iBegin2 = iEnd1;

         // find the second ending for the second sub-array
         for (iEnd2 = iBegin2 + 1;
            iEnd2 < num && !(source[iEnd2 - 1] > source[iEnd2]);
            iEnd2++);

         // a merge is needed
         if (iBegin2 < num)
         {
            // merge sub-arrays into destination
            merge(destination,
               destinationSize,
               source + iBegin1,
               iEnd1 - iBegin1,
               source + iBegin2,
               iEnd2 - iBegin2);

            // increments number of merges
            numMerges++;
         }

         // the beginning 1 is the ending 2
         iBegin1 = iEnd2;
      }

      // swap pointers
      pTemp = source;
      source = destination;
      destination = pTemp;

      // there is more sub-arrays to merge
   } while (numMerges > 1);

   // we're unlucky and need to copy source into array
   if (!isEqual(source, array, num))
   {
      // copy array
      for (int i = 0; i < num; i++)
      {
         array[i] = source[i];
      }
   }
}
#endif // SORT_MERGE_H
