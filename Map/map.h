/***********************************************************************
* Component:
*    Assignment 10, Map
*    Brother Kirby, CS 235
* Author:
*    Andres Rodriguez, Pedro Bastos, Fangyi Li
* Summary:
*    Create a map
************************************************************************/

// helper for Visual C++
#pragma once

// disable warning on old exception style (Visual C++ specific)
#pragma warning( disable : 4290 )  

#include "pair.h"           // pair class
#include "bst.h"            // binary search tree class

#ifndef MAP_H
#define MAP_H

namespace custom
{
   /************************************************
   * MAP
   * A data type storing a collection of values
   * that are indexed by a key.
   ***********************************************/
   template <class T1, class T2>
   class map
   {
   private:
      BST <pair<T1, T2>> bst;       // binary search tree to store map
   public:
      class iterator;              // class iterator declaration

      // default constructor
      map() { }

      // default destructor
      ~map() { }

      // non default constructor
      map(const map<T1, T2> & rhs) throw (const char*);

      // assignment operator
      map & operator = (const map & rhs) throw (const char*)
      {
         // copy tree
         this->bst = rhs.bst;

         // return this map
         return *this;
      }

      // standard container interfaces
      int size() const { return bst.size(); }
      bool empty() const { return bst.empty(); }
      void clear() { bst.clear(); }

      // mutator operator
      T2 &operator [] (const T1 & rhs)
      {
         // a new pair to find
         pair<T1, T2> key;

         // set key for pair
         key.first = rhs;

         // create an interator for tree
         typename BST<pair<T1, T2>>::iterator it;

         // search key in tree
         it = bst.find(key);

         // if not exists
         if (it == bst.end())
         {
            // create a new key
            insert(key);

            // get the iterator
            it = bst.find(key);
         }

         // return the value reference
         return (*it).second;
      }

      // acessor operator
      const T2 &operator [] (const T1 & rhs) const
      {
         // a new pair to find
         pair<T1, T2> key;

         // set the key part of pair
         key.first = rhs;

         // new iterator for BST
         typename BST<pair<T1, T2>>::iterator it;

         // find the key
         it = bst.find(key);

         // return value
         return (*it).getSecond();
      }

      // two ways to insert elements in map
      void insert(const pair<T1, T2> &element);
      void insert(const T1 &key, const T2 &value);

      // find element
      iterator find(const T1 & element);

      // iterator interfaces
      iterator begin() const;
      iterator end() const;
   };


   /********************************************
   * MAP :: NON DEFAULT CONSTRUCTOR
   * Constructor that copies a map
   *******************************************/
   template <class T1, class T2>
   map<T1, T2>::map(const map<T1, T2> & rhs) throw (const char*)
   {
      // copy BST's
      this->bst = rhs.bst;
   }

   /********************************************
   * MAP :: INSERT
   * Insert an element from a pair
   *******************************************/
   template <class T1, class T2>
   void map<T1, T2> ::insert(const pair<T1, T2> &element)
   {
      // insert into BST
      bst.insert(element);
   }

   /********************************************
   * MAP :: INSERT
   * Insert an element from a key/value tuple
   *******************************************/
   template <class T1, class T2>
   void map<T1, T2> ::insert(const T1 &key, const T2 &value)
   {
      // create a new pair
      pair<T1, T2> element(key, value);

      // insert into BST
      bst.insert(element);
   }

   /**************************************************
   * MAP :: ITERATOR
   * An iterator through MAP
   *************************************************/
   template <class T1, class T2>
   class map <T1, T2> ::iterator
   {
   private:
      typename BST<pair<T1, T2>>::iterator it;
   public:
      // constructors, destructors
      iterator() :it(NULL) { }
      iterator(const iterator & rhs) { *this = rhs; }
      iterator(const typename BST<pair<T1, T2>>::iterator & rhs) { it = rhs; }

      // assign operator
      iterator & operator = (const iterator & rhs)
      {
         // just copy iterators
         this->it = rhs.it;
         return *this;
      }

      // equals, not equals operators
      bool operator != (const iterator & rhs) const { return it != rhs.it; }
      bool operator == (const iterator & rhs) const { return it == rhs.it; }

      // dereference operator
      pair<T1, T2> & operator * () { return *it; }
      const pair<T1, T2> & operator * () const { return *it; }

      // decrement
      iterator & operator -- ();

      // increment
      iterator & operator ++ (int postfix);

      iterator & operator ++ ();
   };


   /**************************************************
   * MAP ITERATOR :: DECREMENT PREFIX
   * Decrement BST iterator
   *************************************************/
   template <class T1, class T2>
   typename map <T1, T2> ::iterator & map <T1, T2> ::iterator :: operator -- ()
   {
      // call BST operator
      --it;

      return *this;
   }

   /**************************************************
   * MAP ITERATOR :: INCREMENT POSTFIX
   * Advance iterator by one.
   *************************************************/
   template <class T1, class T2>
   typename map <T1, T2> ::iterator &map <T1, T2> ::iterator :: operator ++ (int postfix)
   {
      // call BST operator
      it++;

      return *this;
   }

   /**************************************************
   * MAP ITERATOR :: INCREMENT PREFIX
   * Advance iterator by one.
   *************************************************/
   template <class T1, class T2>
   typename map <T1, T2> ::iterator &map <T1, T2> ::iterator :: operator ++ ()
   {
      // call BST operator
      it++;

      return *this;
   }

   /********************************************
   * MAP :: FIND
   * Find an element in map
   *******************************************/
   template <class T1, class T2>
   typename map <T1, T2> ::iterator map <T1, T2> ::find(const T1 & key)
   {
      // create a new pair to find
      pair<T1, T2> element;
      
      // set the first element (key) to find 
      element.first = key;

      // create a new BST iterator and find element in BST
      typename BST<pair<T1, T2>>::iterator it = bst.find(element);

      // return new iterator
      return iterator(it);
   }

   /********************************************
   * MAP :: BEGIN
   * Return an iterator
   ********************************************/
   template <class T1, class T2>
   typename map<T1,T2> ::iterator map <T1,T2> ::begin() const
   {
      // uses BST iterator
      return bst.begin();
   }


   /********************************************
   * MAP :: END
   * Return an iterator
   ********************************************/
   template <class T1, class T2>
   typename map<T1, T2> ::iterator map <T1, T2> ::end() const
   {
      // uses BST iterator
      return iterator(bst.end());
   }

   
} // namespace custom


#endif // MAP_H