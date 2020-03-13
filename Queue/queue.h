/***********************************************************************
 * Header:
 *    Queue
 * Summary:
 *    This a generic class to store any data-type elements and implements
 *    First-In Firt-Out (FIFO) data structure.
 *
 * Author
 *    Andres Rodriguez, Pedro Bastos, Fangyi Li
 ************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <new>
#include <stdexcept>

namespace custom {

/************************************************
 * QUEUE
 * A class that holds stuff
 ***********************************************/
template <class T>
class queue
{
private:
   T *data;              // dynamically allocated queue of T
   int numPush;          // number of pushes
   int numPop;           // number of pops
   int numCapacity;      // capacity of queue

   // resize capacity
   void resize( int newCapacity );

   // index from head
   int iTail() const { return (numPush - 1) % numCapacity; }

   // index from tail
   int iHead() const { return numPop % numCapacity; }
public:
   // constructors and destructors
   queue();
   queue(int numCapacity)            throw (const char*);
   queue(const queue & rhs)          throw (const char*);
   ~queue() { if (data != NULL) { delete[] data; } }

   // assign operator
   queue & operator = (const queue & rhs) throw (const char*);

   // standard container interfaces
   int size()     const { return numPush - numPop; }
   int capacity() const { return numCapacity; }
   bool empty()   const { return size() == 0; }
   void clear()         { numPush = numPop = 0; }
   
   // stores element and increases data storage space as needed
   void push(const T &element);

   // remove the first element added
   void pop();

   // retrieve first element added
   T & front() throw (const char*);

   // retrieve last element added
   const T & back() throw (const char*);

};

/*******************************************
 * QUEUE :: DEFAULT CONSTRUCTOR
 *******************************************/
template <class T>
queue <T> :: queue()
{
   numPush = 0;
   numPop = 0;
   numCapacity = 0;
   data = NULL;
}

/*******************************************
 * QUEUE :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
queue <T> :: queue(const queue <T> & rhs) throw (const char*)
{
	*this = rhs;
}

/**********************************************
 * QUEUE : NON-DEFAULT CONSTRUCTOR
 * Preallocate the queue to "size"
 **********************************************/
template <class T>
queue <T> :: queue(int size) throw (const char*)
{
	// set new pops and pushes number
	numPop = 0;
	numPush = 0;

	// do nothing if size is 0
   if (size == 0)
   {
	  numCapacity = 0;
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
      throw "ERROR: Unable to allocate a new buffer for queue";
   }

   // set a new capacity
   numCapacity = size;
}

/*******************************************
 * QUEUE :: Assignment operator
 * Copies elements from rhs to lhs queues
 *******************************************/
template <class T>
queue <T> & queue <T> :: operator = (const queue <T> & rhs) throw(const char*)
{
   // lhs is just starting
   numPush = 0;
   numPop = 0;
   numCapacity = 0;
   data = NULL;

   if (capacity() < rhs.size())
   {
      // resize data buffer
      resize(rhs.size());
   }

   // walk throught the array copying elements
   for ( int i = rhs.numPop; i < rhs.numPush; i++ )
   {
      push(rhs.data[i % rhs.capacity()]);
   }
   
   return *this;
}



/********************************************
 * QUEUE : RESIZE
 * Create new room for new elements
 *******************************************/
template <class T>
void queue<T> :: resize( int newCapacity )
{
   T *newData; // new data

   // attempt to allocate
   try
   {
      newData = new T[newCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for queue";
   }

   // walk throught the array copying elements
   for ( int i = numPop; i < numPush; i++ )
   {
	   // copy the items over one at a time using the assignment operator
	   newData[i % newCapacity] = data[i % numCapacity];
   }

   // copy over the capacity
   numCapacity = newCapacity;

   // clear old data
   if (data != NULL)
   {
	   delete[] data;
   }

   // reassign data
   data = newData;
}

/********************************************
 * QUEUE : PUSH
 * Insert element in queue allocating if needed
 *******************************************/
template <class T>
void queue<T> :: push(const T &element)
{
   // checks if need to allocate memory
   if ( size() == capacity() )
   {
      // doubles allocated space
      resize(capacity() == 0 ? 1 : 2 * capacity() );
   }

   // increases number of pushes
   numPush++;

   // store element
   data[iTail()] = element;
}

/********************************************
 * QUEUE : POP
 * Insert element in queue allocating if needed
 *******************************************/
template <class T>
void queue<T> :: pop()
{
   // checks if queue is empty
   if ( !empty() )
   {
      numPop++;
   }
}

/********************************************
 * QUEUE : FRONT
 * Gets the head of the queue
 *******************************************/
template <class T>
T & queue<T> :: front() throw (const char*)
{
   // checks if queue is empty
   if ( empty() )
   {
      throw "ERROR: attempting to access an element in an empty queue";
   }
   else
   {
      return data[iHead()];
   }
}

/********************************************
 * QUEUE : BACK
 * Gets the tail of the queue
 *******************************************/
template <class T>
const T & queue<T> :: back() throw (const char *)
{
   // checks if queue is empty
   if ( empty() )
   {
      throw "ERROR: attempting to access an element in an empty queue";
   }
   else
   {
      return data[iTail()];
   }
}

}  // namespace

#endif /* QUEUE_H */
