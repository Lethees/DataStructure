/***********************************************************************
 * Header:
 *    Deque
 * Summary:
 *    This a generic class to store any data-type elements and implements
 *    First-In Firt-Out (FIFO) data structure.
 *
 * Author
 *    Andres Rodriguez, Pedro Bastos, Fangyi Li
 ************************************************************************/

#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <new>

namespace custom {

/************************************************
 * DEQUE
 * A class that holds stuff
 ***********************************************/
template <class T>
class deque
{
private:
   T *data;              // dynamically allocated deque of T
   int iFront;           // index of the front
   int iBack;            // index of the back
   int numCapacity;      // capacity of deque

   // resize capacity
   void resize(int newCapacity);

   // find the real index to array
   int iNormalize(int i) const;
public:
   // constructors and destructors
   deque();
   deque(int numCapacity)            throw (const char*);
   deque(const deque & rhs)          throw (const char*);
   ~deque() { if (data != NULL) { delete[] data; } }

   // assign operator
   deque & operator = (const deque & rhs) throw (const char*);

   // standard container interfaces
   int size()     const { return iBack - iFront + 1; }
   int capacity() const { return numCapacity; }
   bool empty()   const { return size() == 0; }
   void clear();
   
   // stores element to back and increases data storage space as needed
   void push_back(const T &element);

   // stores element to front and increases data storage space as needed
   void push_front(const T &element);

   // remove the element from back
   void pop_back();

   // remove the element from from
   void pop_front();

   // retrieve first element added
   T & front() throw (const char*);

   // retrieve last element added
   T & back() throw (const char*);

   // find the real index to iFront
   int iFrontNormalize() const { return iNormalize(iFront); }

   // find the real index to iBack
   int iBackNormalize() const { return iNormalize(iBack); }
};

/*******************************************
 * DEQUE :: DEFAULT CONSTRUCTOR
 *******************************************/
template <class T>
deque <T> :: deque()
{
   iFront = 0;
   iBack = -1;
   numCapacity = 0;
   data = NULL;
}

/*******************************************
 * DEQUE :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
deque <T> :: deque(const deque <T> & rhs) throw (const char*)
{
   data = NULL;
   numCapacity = 0;

   clear();

	*this = rhs;
}

/**********************************************
 * DEQUE : NON-DEFAULT CONSTRUCTOR
 * Preallocate the deque to "size"
 **********************************************/
template <class T>
deque <T> :: deque(int size) throw (const char*)
{
	// clear indexes
   clear();

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
      throw "ERROR: Unable to allocate a new buffer for deque";
   }

   // set a new capacity
   numCapacity = size;
}

/*******************************************
 * DEQUE :: Assignment operator
 * Copies elements from rhs to lhs deques
 *******************************************/
template <class T>
deque <T> & deque <T> :: operator = (const deque <T> & rhs) throw(const char*)
{
   // lhs is just starting
   clear();

   if (capacity() < rhs.size())
   {
      // resize data buffer
      resize(rhs.capacity());
   }

   // walk throught the array copying elements
   for ( int i = rhs.iFront; i <= rhs.iBack; i++ )
   {
      push_back(rhs.data[iNormalize(i)]);
   }
   
   return *this;
}

/********************************************
 * DEQUE : RESIZE
 * Create new room for new elements
 *******************************************/
template <class T>
void deque<T> :: resize( int newCapacity )
{
   T *newData;                 // new data
   int oldIFront = iFront;     // save current iFront
   int oldIBack = iBack;       // save current iBack

   // clear iFront and iBack
   clear();

   // attempt to allocate
   try
   {
      newData = new T[newCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for deque";
   }

   // walk throught the array copying elements
   // this is the sabe method of push_back
   for (int i = oldIFront; i <= oldIBack; i++)
   {
      iBack++;
      newData[iBackNormalize()] = data[iNormalize(i)];
   }

   // set new capacity
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
 * DEQUE : PUSH BACK
 * Insert element in deque allocating if needed
 *******************************************/
template <class T>
void deque<T> :: push_back(const T &element)
{
   // checks if need to allocate memory
   if ( size() == capacity() )
   {
      // doubles allocated space
      resize(capacity() == 0 ? 1 : 2 * capacity() );
   }

   // increases number of pushes in back
   iBack++;

   // store element
   data[iBackNormalize()] = element;
}

/********************************************
* DEQUE : PUSH FRONT
* Insert element in deque allocating if needed
*******************************************/
template <class T>
void deque<T> ::push_front(const T &element)
{
	// checks if need to allocate memory
	if (size() == capacity())
	{
		// doubles allocated space
		resize(capacity() == 0 ? 1 : 2 * capacity());
	}

	// increases number of pushes
	iFront--;

	// store element
	data[iFrontNormalize()] = element;
}


/********************************************
 * DEQUE : POP FRONT
 * Insert element in deque allocating if needed
 *******************************************/
template <class T>
void deque<T> :: pop_front()
{
   // checks if deque is empty
   if ( !empty() )
   {
      iFront++;
   }
}

/********************************************
* DEQUE : POP BACK
* Insert element in deque allocating if needed
*******************************************/
template <class T>
void deque<T> ::pop_back()
{
	// checks if deque is empty
	if (!empty())
	{
		iBack--;
	}
}

/********************************************
 * DEQUE : FRONT
 * Gets the head of the deque
 *******************************************/
template <class T>
T & deque<T> :: front() throw (const char*)
{
   // checks if deque is empty
   if ( empty() )
   {
      throw "ERROR: unable to access data from an empty deque";
   }
   else
   {
      return data[iFrontNormalize()];
   }
}

/********************************************
 * DEQUE : BACK
 * Gets the tail of the deque
 *******************************************/
template <class T>
T & deque<T> :: back() throw (const char *)
{
   // checks if deque is empty
   if ( empty() )
   {
      throw "ERROR: unable to access data from an empty deque";
   }
   else
   {
      return data[iBackNormalize()];
   }
}

/********************************************
* DEQUE : CLEAR
* Clear deque putting indexes as original 
* position.
*******************************************/
template <class T>
void deque<T> :: clear()
{
	iFront = 0;
   iBack = -1;
}

/********************************************
* DEQUE : I NORMALIZE
* Normalize index 
*******************************************/
template <class T>
int deque<T> :: iNormalize(int i) const
{
   int idx = i % capacity();

   if (idx < 0)
   {
      return capacity() + idx;
   }

   return idx;
}


}  // namespace

#endif /* DEQUE_H */
