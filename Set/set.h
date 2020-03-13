/***********************************************************************
 * Header:
 *    Set
 * Summary:
 *    This a generic class to store any data-type elements and implements
 *    First-In Firt-Out (FIFO) data structure.
 *
 * Author
 *    Andres Rodriguez, Pedro Bastos, Fangyi Li
 ************************************************************************/

 // helper for Visual C++
#pragma once

// disable warning on old exception style (Visual C++ specific)
#pragma warning( disable : 4290 )  

#ifndef SET_H
#define SET_H

#define NOT_FOUND -1

namespace custom {

/************************************************
 * SET
 * A class that holds stuff
 ***********************************************/
template <class T>
class set
{
private:
   T *data;              // dynamically allocated set of T
   int numCapacity;      // capacity of set
   int numElements;      // elements in set

   // resize capacity
   void resize( int newCapacity );

   // find index for object
   int findIndex(const T &element) const;

   // find index for object for insert
   int findInsertIndex(const T &element) const;

public:
   // constructors and destructors
   set();
   set(int numCapacity) throw (const char*);
   set(const set & rhs) throw (const char*);

   ~set() { if (data != NULL) { delete[] data; } }

   class iterator;
   class const_iterator;

   // assign operator
   set & operator = (const set & rhs) throw (const char*);

   // standard container interfaces
   int size()     const { return numElements; }
   int capacity() const { return numCapacity; }
   bool empty()   const { return size() == 0; }
   void clear();
   
   // find element
   iterator find(const T & element);

   // stores element 
   void insert(const T & t) throw (const char *);

   // erase with iterator
   void erase(iterator & it);

   // union operator
   set <T> operator || (const set <T> & rhs) throw (const char *);

   // intersection
   set <T> operator && (const set <T> & rhs) throw (const char *);

   // difference
   set <T> operator - (const set <T> & rhs) throw (const char *);

   // compliment
   void operator - () throw (const char *);

   // the various iterator interfaces
   iterator begin();
   iterator end();

   // the various constant iterator interfaces
   const_iterator cbegin() const;
   const_iterator cend() const;

};

/*******************************************
 * SET :: DEFAULT CONSTRUCTOR
 *******************************************/
template <class T>
set <T> :: set()
{
   numElements = 0;
   numCapacity = 0;
   data = NULL;
}

/*******************************************
 * SET :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
set <T> :: set(const set <T> & rhs) throw (const char*)
{
   numElements = 0;
   numCapacity = 0;
   data = NULL;
   
   *this = rhs;
}

/**********************************************
 * SET : NON-DEFAULT CONSTRUCTOR
 * Preallocate the set to "size"
 **********************************************/
template <class T>
set <T> :: set(int size) throw (const char*)
{
   numElements = 0;
   numCapacity = 0;
   data = NULL;
   
   // do nothing if size is 0
   if (size == 0)
   {
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[size];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for set";
   }

   // set a new capacity
   numCapacity = size;
}

/*******************************************
 * SET :: Assignment operator
 * Copies elements from rhs to lhs sets
 *******************************************/
template <class T>
set <T> & set <T> :: operator = (const set <T> & rhs) throw(const char*)
{
   // resize only if is needed
   if (numCapacity < rhs.capacity())
   {
      // resize data buffer
      resize(rhs.capacity());
   }

   // clear elements
   numElements = 0;

   // walk throught the array copying elements
   for (int i=0; i < rhs.size(); i++ )
   {
      insert(rhs.data[i]);
   }
   
   return *this;
}

/********************************************
 * SET : RESIZE
 * Create new room for new elements
 *******************************************/
template <class T>
void set<T> :: resize( int newCapacity )
{
   T *newData;   // new data

   if (newCapacity == 0)
   {
      return;
   }

   // attempt to allocate
   try
   {
      newData = new T[newCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for set";
   }

   // walk throught the array copying elements
   for(int i = 0; i < size(); i++)
   {
      // copy element
      newData[i] = data[i];
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

/******************
* SET : FIND INSERT INDEX
* Find a position to a new element 
*******************************************/
template <class T>
int set <T> ::findInsertIndex(const T &element) const
{
   // find element in set
   for (int i = 0; i < size(); i++)
   {
      if (data[i] >= element)
      {
         return i;
      }
   }

   // if not found
   return numElements;
}
/********************************************
* SET : FIND INDEX
* Find an element in array
*******************************************/
template <class T>
int set <T> :: findIndex(const T &element) const
{
   int index;
   // index to return

   // find element in set
   for (int i = 0; i < size(); i++)
   {
      if (data[i] == element)
      {
         return i;
      }
   }

   // if not found
   return NOT_FOUND;
}

/********************************************
 * SET : INSERT 
 * Insert element in set allocating if needed
 *******************************************/
template <class T>
void set <T> ::insert(const T & element) throw (const char *)
{
   int iInsert;     // index where a similar element is found

   // checks if need to allocate memory
   if ( numElements == numCapacity )
   {
      // doubles allocated space
      resize(numCapacity == 0 ? 1 : 2 * numCapacity );
   }

   // find an insert index
   iInsert = findInsertIndex(element);

   // checks if the element is present in array
   if (data[iInsert] != element )
   {
      // shift all elements to right
      for (int i = numElements-1; i >= iInsert; i--)
      {
         data[i + 1] = data[i];
      }

      // stores element
      data[iInsert] = element;

      // increments elements counter
      numElements++;
   }
}

/********************************************
 * SET : OPERATOR UNION (II)
 * Implements Union of two sets
 *******************************************/
template <class T>
set <T> set <T> :: operator || (const set <T> & rhs) throw (const char *)
{
   set <T> setReturn = *this;

   for (int i = 0; i < rhs.size(); i++)
   {
      setReturn.insert(rhs.data[i]);
   }

   return setReturn;
}

/********************************************
* SET : OPERATOR INTERSECTION (&&)
* Implements Intersection between two sets
*******************************************/
template <class T>
set <T> set <T> :: operator && (const set <T> & rhs) throw (const char *)
{
   set <T> setReturn;

   for( int i=0; i < size(); i++ )
   { 
      if (rhs.findIndex(data[i]) != NOT_FOUND)
      {
         setReturn.insert(data[i]);
      }
   }

   return setReturn;
}

/********************************************
 * SET : OPERATOR DIFFERENCE (-) 
 * Elements not repeated in both sets (binary)
 *******************************************/
template <class T>
set <T> set <T> :: operator - (const set <T> & rhs) throw (const char *)
{
   set <T> setReturn;

   for (int i = 0; i < size(); i++)
   {
      if (rhs.findIndex(data[i]) == NOT_FOUND)
      {
         setReturn.insert(data[i]);
      }
   }

   return setReturn;
}

/********************************************
* SET : OPERATOR COMPLEMENT (-)
* Elements not present in lhs (unary)
*******************************************/
template <class T>
void set <T> :: operator - () throw (const char *)
{
   return;
}

/********************************************
* SET : CLEAR
* Clear set putting capacity and elements 
* quantities to zero.
*******************************************/
template <class T>
void set<T> :: clear()
{
   // set to 0
   numElements = 0;
   numCapacity = 0;

   // clear data
   if (data != NULL) 
   { 
      delete[] data; 
   }

   data = NULL;
}



/**************************************************
* SET ITERATOR
* An iterator through set
*************************************************/
template <class T>
class set <T> ::iterator
{
private:
   T * p;

public:
   // constructors, destructors, and assignment operator
   iterator() : p(NULL) {              }
   iterator(T * p) : p(p) {              }
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
   T & operator * () { return *p; }
   const T & operator * () const { return *p; }

   // reference operator
   T ** operator & () { return &p; }

   // prefix increment
   iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      p++;
      return tmp;
   }

   // prefix decrement
   iterator & operator -- ()
   {
      p--;
      return *this;
   }

   // postfix decrement
   iterator operator -- (int postfix)
   {
      iterator tmp(*this);
      p--;
      return tmp;
   }
};

/**************************************************
* SET CONST_ITERATOR
* A constant iterator through set
*************************************************/
template <class T>
class set <T> ::const_iterator
{
private:
   const T * p;

public:
   // constructors, destructors, and assignment operator
   const_iterator() : p(NULL) {              }
   const_iterator(T * p) : p(p) {              }
   const_iterator(const const_iterator & rhs) { *this = rhs; }

   const const_iterator & operator = (const const_iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const const_iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const const_iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
   const T & operator * () const { return *p; }

   // prefix increment
   const const_iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   const const_iterator operator ++ (int postfix)
   {
      const_iterator tmp(*this);
      p++;
      return tmp;
   }

   // prefix decrement
   const const_iterator & operator -- ()
   {
      p--;
      return *this;
   }

   // postfix decrement
   const const_iterator operator -- (int postfix)
   {
      const_iterator tmp(*this);
      p--;
      return tmp;
   }

};

/********************************************
* SET :: END
* Return an iterator
********************************************/
template <class T>
typename set <T> ::iterator set <T> ::end()
{
   return iterator(data + numElements);
}


/********************************************
* SET :: CEND
* Return an constant interactor
********************************************/
template <class T>
typename set <T> ::const_iterator set <T> ::cend() const
{
   return const_iterator(data + numElements);
}

/********************************************
* SET :: BEGIN
* Return an iterator
********************************************/
template <class T>
typename set <T> ::iterator set <T> ::begin()
{
   return iterator(data);
}


/********************************************
* SET :: CBEGIN
* Return an constant interactor
********************************************/
template <class T>
typename set <T> ::const_iterator set <T> ::cbegin() const
{
   return const_iterator(data);
}

/********************************************
* SET : FIND
* Find an element in array
*******************************************/
template <class T>
typename set <T> ::iterator set <T> ::find(const T & element)
{
   // find the index for element
   int index = findIndex(element);

   // checks if found
   if (index == NOT_FOUND)
   {
      return this->end();
   }

   // creates an iterator 
   set <T> ::iterator it (&data[index]);

   // return iterator
   return it;
}

/********************************************
* SET : ERASE
* Erase element from set using iterator
*******************************************/
template <class T>
void set <T> ::erase(typename set <T> ::iterator & it)
{
   // iterator from begining to it
   set <T> ::iterator itRemove = this->begin();
   
   
   int index = 0;   // index to find
   int i = 0;       // counter

   // walk "itReemove" until "it"
   while (itRemove++ != it)
   {
      index++;
   }

   // counter starts with index found
   i = index;

   // shift in the remaing elements
   while (i < numElements - 1)
   {
      data[i] = data[i + 1];

      i++;
   }

   // decrements number of elements
   numElements--;
}

}  // namespace

#endif /* SET_H */
