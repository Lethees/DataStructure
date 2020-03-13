/***********************************************************************
 * Module:
 *    Week 11, Sort Binary
 *    Brother Kirby, CS 235
 * Author:
 *    Andres Rodriguez, Pedro Bastos, Fangyi Li
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"
#include <cassert>

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
   custom::BST<T> bst;
   typename custom::BST<T>::iterator it;
   int i;

   // add all elements to a BST
   for (i = 0; i < num; i++)
   {
      bst.insert(array[i]);
   }

   // creates an iterator and put back in the array
   for (it = bst.begin(), i=0; it != bst.end(); it++, i++)
   {
      array[i] = *it;
   }
}


#endif // SORT_BINARY_H
