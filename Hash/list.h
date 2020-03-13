/***********************************************************************
 * Header:
 *    List
 * Summary:
 *    This a generic class to store any data-type elements organized
 *    into a linked list.
 *
 * Author
 *    Andres Rodriguez, Pedro Bastos, Fangyi Li
 ************************************************************************/

 // helper for Visual C++
#pragma once

// disable warning on old exception style (Visual C++ specific)
#pragma warning( disable : 4290 )  

#ifndef LIST_H
#define LIST_H

namespace custom {

   /************************************************
      * LIST
      * A class that holds stuff organized at a
      * linked list.
      ***********************************************/
   template <class T>
   class list
   {
   private:
      class Node;              // Node class
      Node *pHead;             // head of the list
      Node *pTail;             // tail of the list

      int numElements;         // elements in list

      // insert node
      Node * insertNode(Node *pCurrent, const T &element, bool after);
      Node * insertNode(Node *pCurrent, const T &element);

      // remove node
      Node * removeNode(Node *pRemove);

      // free data form list
      void freeData(Node *&front);

   public:
      // constructors and destructors
      list();
      list(const list & rhs) throw (const char*);
      ~list() { }

      // assign operator
      list & operator = (const list & rhs) throw (const char*);

      // standard container interfaces
      int size()     const { return numElements; }
      bool empty()   const { return size() == 0; }
      void clear();

      class iterator;          // iterator for list
      class reverse_iterator;  // reverse iterator for list

      // insert an element to head
      void push_front(const T &element);

      // insert an element to tail
      void push_back(const T &element);

      // remove an element from head
      void pop_front();

      // remove an element from tail
      void pop_back();

      // return the element for the head of the list
      const T front() const;

      // return the element for the tail of the list
      const T back() const;

      // return the element for the head of the list
      T &front();

      // return the element for the tail of the list
      T &back();

      // find element
      iterator find(const T & element);

      // stores element 
      iterator insert(iterator it, const T & t) throw (const char *);

      // erase with iterator
      iterator erase(iterator & it);

      // the various iterator interfaces
      iterator begin() const;
      iterator end() const;

      reverse_iterator rbegin() const;
      reverse_iterator rend() const;

   };

   /************************************************
   * LIST NODE
   * A base class to create linked lists.
   ***********************************************/
   template <class T>
   class list <T> ::Node
   {
   public:
      T data;              // data to store
      class Node *pNext;   // next node
      class Node *pPrev;   // previous node

      // default constructor
      Node() : pNext(NULL), pPrev(NULL)
      {
      }

      // non-default constructor
      Node(const T element) : pNext(NULL), pPrev(NULL)
      {
         this->data = element;
      }
   };

   /*******************************************
   * LIST :: DEFAULT CONSTRUCTOR
   *******************************************/
   template <class T>
   list <T> ::list()
   {
      numElements = 0;
      pHead = NULL;
      pTail = NULL;
   }

   /*******************************************
   * LIST :: COPY CONSTRUCTOR
   *******************************************/
   template <class T>
   list <T> ::list(const list <T> & rhs) throw (const char*)
   {
      numElements = 0;
      pHead = NULL;
      pHead = NULL;

      *this = rhs;
   }

   /*******************************************
   * LIST :: Assignment operator
   * Copies elements from rhs to lhs sets
   *******************************************/
   template <class T>
   list <T> & list <T> :: operator = (const list <T> & rhs) throw(const char*)
   {
      // reset number of elements
      numElements = 0;

      // free current data in list
      freeData(this->pHead);

      // reset pTail
      pTail = NULL;

      // insert each node from rhs list to a new one
      for (Node *pSrc = rhs.pHead; pSrc; pSrc = pSrc->pNext)
      {
         push_back(pSrc->data);
      }

      // return current list
      return *this;
   }

   /******************************************
   * LIST :: FREEDATA
   * Deallocate memory
   *****************************************/
   template <class T>
   void list<T> ::freeData(Node *&front)
   {
      Node *pCurrent;    // auxiliary pointer

      // list is already empty
      if (!front)
      {
         return;
      }
      // tranverse list
      while (front)
      {
         // save the next pointer
         pCurrent = front->pNext;

         // deallocate node
         delete front;

         // update new head
         front = pCurrent;
      }

      // points head to NULL (list is empty)
      front = NULL;
   }

   /******************************************
   * LIST :: INSERT NODE
   * Insert a node into the list keeping
   * pointers consistent.
   *****************************************/
   template <class T>
   typename list<T>::Node * list<T> ::insertNode(Node *pCurrent, const T &element)
   {
      return insertNode(pCurrent, element, false);
   }

   /******************************************
   * LIST :: INSERT NODE
   * Insert a node into the list keeping
   * pointers consistent.
   *****************************************/
   template <class T>
   typename list<T>::Node * list<T> ::insertNode(Node *pCurrent, const T &element, bool after)
   {
      Node *pNew = new Node(element);     // new node

      // list is not empty
      if (pCurrent)
      {
         // it is different inserting from left or right 

         // inserting into right
         if (after)
         {
            // reposition pointers to keep a list
            pNew->pPrev = pCurrent;
            pNew->pNext = pCurrent->pNext;
            pCurrent->pNext = pNew;

            if (pNew->pNext)
            {
               pNew->pNext->pPrev = pNew;
            }
         }
         else  // inserting into left
         {
            // reposition pointers to keep a list
            pNew->pNext = pCurrent;
            pNew->pPrev = pCurrent->pPrev;
            pCurrent->pPrev = pNew;

            if (pNew->pPrev)
            {
               pNew->pPrev->pNext = pNew;
            }
         }
      }

      // increments number of elements
      numElements++;

      // returns newsly created node
      return pNew;
   }

   /********************************************
   * LIST : REMOVE NODE
   * Remove node from list using pointer
   *******************************************/
   template <class T>
   typename list<T>::Node * list<T>::removeNode(Node *pRemove)
   {
      Node *pReturn;        // pointer to return

      // node is null
      if (!pRemove)
      {
         return NULL;
      }

      // reconnect pointers to nodes
      if (pRemove->pPrev)
      {
         pRemove->pPrev->pNext = pRemove->pNext;
      }

      if (pRemove->pNext)
      {
         pRemove->pNext->pPrev = pRemove->pPrev;
      }

      // will be the left or the right node
      pReturn = pRemove->pPrev ? pRemove->pPrev : pRemove->pNext;

      // deallocate node
      delete pRemove;

      // pRemove pointer will point to left/right node 
      pRemove = pReturn;

      // decrements number of elements
      numElements--;

      // return a new pointer
      return pReturn;
   }

   /********************************************
   * LIST : PUSH FRONT
   * Insert element to head
   *******************************************/
   template <class T>
   void list<T> ::push_front(const T &element)
   {
      pHead = insertNode(pHead, element);

      if (!pTail)
      {
         pTail = pHead;
      }

   }

   /********************************************
   * LIST : PUSH BACK
   * Insert element to tail
   *******************************************/
   template <class T>
   void list<T> ::push_back(const T &element)
   {
      pTail = insertNode(pTail, element, true);

      if (!pHead)
      {
         pHead = pTail;
      }
   }

   /********************************************
   * LIST : POP FRONT
   * Remove element from head
   *******************************************/
   template <class T>
   void list<T> ::pop_front()
   {
      pHead = removeNode(pHead);
   }

   /********************************************
   * LIST : POP BACK
   * Remove element from tail
   *******************************************/
   template <class T>
   void list<T> ::pop_back()
   {
      pTail = removeNode(pTail);
   }

   /********************************************
   * LIST : CLEAR
   * Clear list putting capacity and elements
   * quantities to zero.
   *******************************************/
   template <class T>
   void list<T> ::clear()
   {
      // free data
      freeData(this->pHead);

      pHead = NULL;
      pTail = NULL;

      numElements = 0;
   }
   /*
   /********************************************
   * LIST : FRONT
   * Returns the element for the head of the list.
   *******************************************/
   template <class T>
   const T list<T> ::front() const {

      if (pHead)
      {
         return pHead->data;
      }

      throw "ERROR: unable to access data from an empty list";
   }

   /********************************************
   * LIST : BACK
   * Returns the element for the head of the list.
   *******************************************/
   template <class T>
   const T list<T> ::back() const {

      if (pTail)
      {
         return pTail->data;
      }

      throw "ERROR: unable to access data from an empty list";
   }

   /********************************************
   * LIST : FRONT
   * Returns the element for the head of the list.
   *******************************************/
   template <class T>
   T &list<T> ::front() {

      if (pHead)
      {
         return pHead->data;
      }

      throw "ERROR: unable to access data from an empty list";
   }

   /********************************************
   * LIST : BACK
   * Returns the element for the head of the list.
   *******************************************/
   template <class T>
   T &list<T> ::back() {

      if (pTail)
      {
         return pTail->data;
      }

      throw "ERROR: unable to access data from an empty list";
   }

   /**************************************************
   * LIST ITERATOR
   * An iterator through list
   *************************************************/
   template <class T>
   class list <T> ::iterator
   {
   private:
      Node * p;
   public:
      // constructors, destructors, and assignment operator
      iterator() : p(NULL) {              }
      iterator(Node * p) : p(p) {              }
      iterator(const iterator & rhs) { *this = rhs; }
      iterator & operator = (const iterator & rhs)
      {
         this->p = rhs.p;
         return *this;
      }

      // equals, not equals operator
      bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
      bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

      // dereference operator
      T & operator * () { return p->data; }
      //T & operator ** () { return p->data; }

      // reference operator
      Node * operator & () { return p; }

      // prefix increment
      iterator & operator ++ ()
      {
         if (p)
         {
            p = p->pNext;
         }
         return *this;
      }

      // postfix increment
      iterator operator ++ (int postfix)
      {
         iterator tmp(&this);
         if (p)
         {
            p = p->pNext;
         }
         return tmp;
      }

      // prefix decrement
      iterator & operator -- ()
      {
         if (p)
         {
            p = p->pPrev;
         }
         return *this;
      }

      // postfix decrement
      iterator operator -- (int postfix)
      {
         iterator tmp(*this);
         if (p)
         {
            p = p->pPrev;
         }
         return tmp;
      }
   };


   /********************************************
   * LIST :: END
   * Return an iterator
   ********************************************/
   template <class T>
   typename list <T> ::iterator list <T> ::end() const
   {
      return iterator(NULL);
   }

   /********************************************
   * LIST :: BEGIN
   * Return an iterator
   ********************************************/
   template <class T>
   typename list <T> ::iterator list <T> ::begin() const
   {
      return iterator(this->pHead);
   }

   /**************************************************
   * LIST REVERSE ITERATOR
   * A reverse iterator through list
   *************************************************/
   template <class T>
   class list <T> ::reverse_iterator
   {
   private:
      Node * p;

   public:
      // constructors, destructors, and assignment operator
      reverse_iterator() : p(NULL) {              }
      reverse_iterator(Node * p) : p(p) {              }
      reverse_iterator(const reverse_iterator & rhs) { *this = rhs; }
      reverse_iterator & operator = (const reverse_iterator & rhs)
      {
         this->p = rhs.p;
         return *this;
      }

      reverse_iterator & operator = (const T & rhs)
      {
         this->p->data = rhs;
         return *this;
      }

      // equals, not equals operator
      bool operator != (const reverse_iterator & rhs) const { return rhs.p != this->p; }
      bool operator == (const reverse_iterator & rhs) const { return rhs.p == this->p; }

      // dereference operator
      T & operator * () { return p->data; }
      //T & operator ** () { return p->data; }

      // reference operator
      Node * operator & () { return p; }

      // prefix increment
      reverse_iterator & operator ++ ()
      {
         if (p)
         {
            p = p->pPrev;
         }
         return *this;
      }

      // postfix increment
      reverse_iterator operator ++ (int postfix)
      {
         reverse_iterator tmp(*this);
         if (p)
         {
            p = p->pPrev;
         }
         return tmp;
      }

      // prefix decrement
      reverse_iterator & operator -- ()
      {
         if (p)
         {
            p = p->pNext;
         }
         return *this;
      }

      // postfix decrement
      reverse_iterator operator -- (int postfix)
      {
         reverse_iterator tmp(*this);
         if (p)
         {
            p = p->pNext;
         }
         return tmp;
      }
   };

   /********************************************
   * LIST :: REND
   * Return an iterator
   ********************************************/
   template <class T>
   typename list <T> ::reverse_iterator list <T> ::rend() const
   {
      return reverse_iterator(NULL);
   }

   /********************************************
   * LIST :: RBEGIN
   * Return an iterator
   ********************************************/
   template <class T>
   typename list <T> ::reverse_iterator list <T> ::rbegin() const
   {
      return reverse_iterator(this->pTail);
   }


   /********************************************
   * LIST : FIND
   * Find an element in array
   *******************************************/
   template <class T>
   typename list <T> ::iterator list <T> ::find(const T & element)
   {
      Node *pCurrent;            // current node

      // tranverse all nodes from list
      for (pCurrent = pHead; pCurrent; pCurrent = pCurrent->pNext)
      {
         // current data is the same as element
         if (pCurrent->data == element)
         {
            // returns current node
            list <T> ::iterator it(pCurrent);

            // return iterator
            return it;
         }
      }

      // nothing was found
      return this->end();
   }

   /********************************************
   * LIST : ERASE
   * Erase element from list using iterator
   *******************************************/
   template <class T>
   typename list <T> ::iterator list <T> ::erase(typename list <T> ::iterator & it)
   {
      Node *pReturn;        // pointer to return

      // remove node
      pReturn = removeNode(&it);

      // ajusts a new head
      if (&it == pHead)
      {
         pHead = pReturn;
      }

      // ajusts a new tail
      if (&it == pTail)
      {
         pTail = pReturn;
      }

      // creates an iterator 
      list <T> ::iterator newIt(pReturn);

      // return a newly created iterator
      return newIt;
   }


   /********************************************
   * LIST : INSERT
   * Insert element from list using iterator
   *******************************************/
   template <class T>
   typename list <T> ::iterator list <T> ::insert(typename list <T> ::iterator it, const T & t) throw (const char *)
   {
      bool after = (&it == pTail || it == this->end());   // will insert after pointer if it is in the tail
      Node *pReturn;
      Node *pInsertIn;

      pInsertIn = it == this->end() ? pTail : &it;

      // insert a new node
      pReturn = insertNode(pInsertIn, t, after);

      // ajusts a new head
      if (&it == pHead)
      {
         pHead = pReturn;
      }

      // ajusts a new tail
      if (&it == pTail)
      {
         pTail = pReturn;
      }

      // creates an iterator 
      list <T> ::iterator newIt(pReturn);

      // return a newly created iterator
      return newIt;
   }
} // namespace

#endif /* LIST_H */
