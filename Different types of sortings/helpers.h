/***********************************************************************
* Module:
*    Week 11, Helpers
*    Brother Kirby, CS 235
* Author:
*    Andres Rodriguez, Pedro Bastos, Fangyi Li
* Summary:
*    This file contains some helpers to sorting algortithms
************************************************************************/

#ifndef HELPERS_H
#define HELPERS_H

/*****************************************************
* SWAP
* Swaps elements in array for data sorting.
****************************************************/
template <class T>
void swapElements(T array[], int iFrom, int iTo)
{
   T temporary;        // a temporary element to swap 

   temporary = array[iFrom];
   array[iFrom] = array[iTo];
   array[iTo] = temporary;
}


/*****************************************************
* BINARY SEARCH
* Performs a recursive binary search
****************************************************/
template <class T>
int binarySearch(T array[], T element, int iBegin, int iEnd)
{
   // the middle of array
   int iMiddle = (iBegin + iEnd) / 2;

   // recursion stop condition
   if (iBegin > iEnd)
   {
      return iBegin;
   }

   // element to find is in the middle (lucky!)
   if (array[iMiddle] == element)
   {
      return iMiddle;
   }

   // what side element is? right or left?
   if (element > array[iMiddle])
   {
      return binarySearch(array, element, iMiddle + 1, iEnd);
   }
   else
   {
      return binarySearch(array, element, iBegin, iMiddle - 1);
   }
}

/*****************************************************
* MERGE
* Performs a merge between two sorted arrays
****************************************************/
template <class T>
void merge(T *destination, 
   int &destinationSize,
   T *source1, int size1, 
   T *source2, int size2)
{
   int i1 = 0;            // index for source1 sub-array
   int i2 = 0;            // index for source2 sub-array
   int iDestination;      // index for destination sub-array

   // iterates through all elements in source1 and source2
   for (iDestination = destinationSize; iDestination < destinationSize + size1 + size2; iDestination++)
   {
      // select elements from first or second sub-array, storing
      // in destination sub-array.
      if (i1 < size1 && (i2 == size2 || source1[i1] < source2[i2]))
      {
         destination[iDestination] = source1[i1++];
      }
      else
      {
         destination[iDestination] = source2[i2++];
      }

   }

   // increments size of destination
   destinationSize = iDestination;
}



/*****************************************************
* IS EQUAL
* Check if arrays are equals
****************************************************/
template <class T>
bool isEqual (T *lhs, T *rhs, int num)
{
   for (int i = 0; i < num; i++)
   {
      if (lhs[i] != rhs[i])
      {
         return false;
      }
   }

   return true;
}


#endif // HELPERS_H

