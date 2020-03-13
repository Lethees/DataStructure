/***********************************************************************
 * Module:
 *    Week 11, Sort Heap
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Heap Sort
 ************************************************************************/

#ifndef SORT_HEAP_H
#define SORT_HEAP_H

 /************************************************
 * HEAP
 * A class that represents a tree using an array.
 ***********************************************/
template <class T>
class Heap
{
private:
   T *array;
   int num;
   void percolateDown(int index);
   void swap(int i1, int i2);
public:
   Heap() {
      this->array = NULL;
      num = 0;
   }

   Heap(T *array, int num);

   void sort();
};

/********************************************
* HEAP :: NON DEFAULT CONSTRUCTOR
* Constructor that heapify array
*******************************************/
template <class T>
Heap<T>::Heap(T *array, int num)
{
   this->array = array;         // set pointer to data
   this->num = num;             // number of elements

   // heapify
   for (int i = this->num / 2; i >= 0; i--)
   {
      percolateDown(i);
   }
}

/********************************************
* HEAP :: PERCOLATE DOWN
* Represents a tree as a array
*******************************************/
template <class T>
void Heap<T>::percolateDown(int index)
{
   int indexLeft;           // index for left side
   int indexRight;          // index for right side

   // find left index
   indexLeft = index == 0 ? 0 : (index * 2)-1;

   // find right index
   indexRight = indexLeft+1;

   // change places if right element is the largest
   if (indexRight < num && 
      array[indexRight] > array[indexLeft] &&
      array[indexRight] > array[index])
   {
      swap(index, indexRight);
      // continue to adjust tree
      percolateDown(indexRight);
   }
   else
   {
      // swap if left element is larger than index element
      if (indexLeft < num && array[indexLeft] > array[index])
      {
         swap(index, indexLeft);
         // continue to adjust tree
         percolateDown(indexLeft);
      }
   }
}

/********************************************
* HEAP :: SWAP
* Swap elements in array
*******************************************/
template <class T>
void Heap<T>::swap(int iSource, int iDestination)
{
   T temp;   // temporary element

   // swap elements
   temp = array[iSource];
   array[iSource] = array[iDestination];
   array[iDestination] = temp;
}

/********************************************
* HEAP :: SORT
* The merge sort itself
*******************************************/
template <class T>
void Heap<T>::sort()
{
   // tranverse all elements in array
   while (num > 0)
   {
      // swap elements
      swap(0, num-1);
      num--;

      // ajusts tree
      percolateDown(0);
   }
}

/*****************************************************
 * SORT HEAP
 * Perform the heap sort
 ****************************************************/
template <class T>
void sortHeap(T array[], int num)
{
   Heap<T> h(array, num);

   h.sort();
}
#endif // SORT_HEAP_H
