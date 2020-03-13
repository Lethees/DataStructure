/***********************************************************************
 * Header:
 *    Stack
 * Summary:
 *    This a generic class to store any data-type elements and implements
 *    Last-In-First-Out (LIFO) data structure.
 *
 * Author
 *    Pedro Pereira
 ************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <new>

namespace custom {

/************************************************
 * STACK
 * A class that holds stuff
 ***********************************************/
template <class T>
class stack
{
private:
   T *data;              // dynamically allocated stack of T
   int numElements;      // number of elements
   int numCapacity;      // capacity of stack

   // resize capacity
   void resize( int numElements );

public:
   // constructors and destructors
   stack();
   stack(int size)                   throw (const char *);
   stack(const stack & rhs)          throw (const char *);
  ~stack()                           { delete [] data;   }

  // assign operator
   stack & operator = (const stack & rhs)     throw (const char *);

   // standard container interfaces
   int size()     const { return numElements; }
   int capacity() const { return numCapacity; }
   bool empty()   const { return numElements == 0; }
   void clear()         { numElements = 0; }
   
   // stores element and increases data storage space as needed
   void push(const T &element) throw (const char *);

   // remove element
   void pop() throw (const char *);

   // retrieve last element added
   const T & top() throw (const char *);
};

/*******************************************
 * STACK :: DEFAULT CONSTRUCTOR
 *******************************************/
template <class T>
stack <T> :: stack()
{
  numElements = 0;
  numCapacity = 0;
  data = NULL;
}

/*******************************************
 * STACK :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
stack <T> :: stack(const stack <T> & rhs) throw (const char *)
{
   // initializes current stack
   if (rhs.size() == 0)
   {
      numElements = 0;
      numCapacity = 0;
      data = NULL;
      
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.capacity()];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for stack";
   }

   // copy over the capacity and elements
   numCapacity = rhs.capacity();
   numElements = rhs.size();

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++)
   {
      data[i] = rhs.data[i];
   }
}

/**********************************************
 * STACK : NON-DEFAULT CONSTRUCTOR
 * Preallocate the stack to "size"
 **********************************************/
template <class T>
stack <T> :: stack(int size) throw (const char *)
{
   // do nothing if size is 0
   if (size == 0)
   {
      numCapacity = 0;
      numElements = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[size];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for stack";
   }

   // set a new capacity
   numCapacity = size;
   
   // set new elements number
   numElements = 0;
}

/*******************************************
 * STACK :: Assignment operator
 * Copies elements from rhs to lhs stacks
 *******************************************/
template <class T>
stack <T> & stack <T> :: operator = (const stack <T> & rhs)
          throw (const char *)
{
   T *newData;          // new data in case allocation needed

   if (rhs.capacity() > numCapacity)
   {
      // delete previous data
      delete [] data;

       // attempt to allocate
      try
      {
         newData = new T[rhs.capacity()];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for stack.";
      }

      // points to new memory
      data = newData;
   }

   // copy data   
   for (int i = 0; i < rhs.size(); i++)
   {
      data[i] = rhs.data[i];
   }

   // copy number of elements and capacity
   numElements = rhs.size();
   numCapacity = rhs.capacity();
   
   return *this;
}

/********************************************
 * STACK : RESIZE
 * Create new room for new elements
 *******************************************/
template <class T>
void stack<T> :: resize( int newCapacity )
{
   T *newData;          // new data

   // clear current data
   if (newCapacity == 0)
   {
      delete [] data;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      newData = new T[newCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   // copy over the capacity
   numCapacity = newCapacity;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++)
   {
      newData[i] = data[i];
   }

   // clear old data
   delete [] data;

   // reassign data
   data = newData;
}

/********************************************
 * STACK : PUSH
 * Insert element in stack allocating if needed
 *******************************************/
template <class T>
void stack<T> :: push(const T &element) throw (const char *)
{
   // checks if need to allocate memory
   if ( size() == capacity() )
   {
      // allocate only 1 if is empty
      resize((empty() ? 1 : 2 * capacity()) );
   }

   // store element
   data[numElements++] = element;
}

/********************************************
 * STACK : POP
 * Insert element in stack allocating if needed
 *******************************************/
template <class T>
void stack<T> :: pop() throw (const char *)
{
   // checks if stack is empty
   if ( !empty() )
   {
      --numElements;
   }
}

/********************************************
 * STACK : TOP
 * Insert element in stack allocating if needed
 *******************************************/
template <class T>
const T & stack<T> :: top() throw (const char *)
{
   // checks if stack is empty
   if ( empty() )
   {
      throw "ERROR: Unable to reference the element from an empty Stack";
   }
   
   // returns the lest element added
   return data[size()-1];
}


}
#endif /* STACK_H */
