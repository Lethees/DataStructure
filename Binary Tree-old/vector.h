/***********************************************************************
 * Header:
 *    Vector
 * Summary:
 *    This a generic class to store any data-type elements. 
 *    It will grow as more room is needed to store more elements. 
 *
 *    This will contain the class definition of:
 *       vector                   : similar to std::vector
 *       vector :: iterator       : an iterator through the vector
 *       vector :: const_iterator : an constant iterator through the vector
 * Author
 *    Pedro Pereira
 ************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <new>

using namespace std;

namespace custom {

/************************************************
 * VECTOR
 * A class that holds stuff
 ***********************************************/
template <class T>
class vector
{
private:
   T *data;              // dynamically allocated vector of T
   int numElements;      // number of elements
   int numCapacity;      // capacity of vector

   // resize capacity
   void resize( int numElements );

public:
   // constructors and destructors
   vector();
   vector(const vector & rhs)          throw (const char *);
   vector(int size)                    throw (const char *);
   vector(int size, const T & element) throw (const char *);
  ~vector()                            { delete [] data;   }

  // assign operator
   vector & operator = (const vector & rhs)     throw (const char *);

   // standard container interfaces
   int size()     const { return numElements; }
   int capacity() const { return numCapacity; }
   bool empty()   const { return numElements == 0; }
   void clear()         { numElements = 0; }
   
   // returns a value within the container by reference
   T & operator [] (int index)       throw (const char *);

   // returns a value within the container by constant reference
   const T & operator [] (int index) const throw (const char *);

   // the various iterator interfaces
   class iterator;
   iterator begin()      { return iterator (data); }
   iterator end();

   // the various constant iterator interfaces
   class const_iterator;
   const_iterator cbegin() const     { return const_iterator (data); }
   const_iterator cend() const;


   // stores elements and increases data storage space as needed
   void push_back(const T &element) throw (const char *);
};

/*******************************************
 * VECTOR :: DEFAULT CONSTRUCTOR
 *******************************************/
template <class T>
vector <T> :: vector()
{
  numElements = 0;
  numCapacity = 0;
  data = NULL;
}

/*******************************************
 * VECTOR :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
vector <T> :: vector(const vector <T> & rhs) throw (const char *)
{
   // initializes current vector
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
      throw "ERROR: Unable to allocate a new buffer for vector";
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

/*******************************************
 * VECTOR :: NON-DEFAULT CONSTRUCTOR
 *******************************************/
template <class T>
vector <T> :: vector(int size, const T &element) throw (const char *)
{
   // do nothing if the size is 0
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
      throw "ERROR: Unable to allocate a new buffer for vector";
   }

   // copy over the capacity and elements
   numCapacity = size;
   numElements = size;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++)
   {
      data[i] = element;
   }
}

/**********************************************
 * VECTOR : NON-DEFAULT CONSTRUCTOR
 * Preallocate the vector to "size"
 **********************************************/
template <class T>
vector <T> :: vector(int size) throw (const char *)
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
      throw "ERROR: Unable to allocate a new buffer for vector";
   }

   // set a new capacity
   numCapacity = size;
   
   // set new elements number
   numElements = size;
}

/*******************************************
 * VECTOR :: Assignment operator
 * Copies elements from rhs to lhs vectors
 *******************************************/
template <class T>
vector <T> & vector <T> :: operator = (const vector <T> & rhs)
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
         throw "ERROR: Unable to allocate a new buffer for vector.";
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
 * VECTOR : operator []
 * Returns the element from container
 *******************************************/
template <class T>
T & vector<T> :: operator [] (int index) throw (const char *)
{
   // checks if the element exists
   if ( index < 0 || index >= numElements )
   {
       throw "ERROR: Invalid index";
   }
 
   return data[index];
}

/********************************************
 * VECTOR : operator []
 * Returns the element from container as 
 * constant.
 *******************************************/
template <class T>
const T & vector<T> ::operator [] (int index) const throw (const char *)
{
   // checks if the element exists
   if ( index < 0 || index >= numElements )
   {
       throw "ERROR: Invalid index";
   }

   return data[index];
}

/********************************************
 * VECTOR : RESIZE
 * Create new room for new elements
 *******************************************/
template <class T>
void vector<T> :: resize( int newCapacity )
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
 * VECTOR : PUSH_BACK
 * Insert element in vector allocating if needed
 *******************************************/
template <class T>
void vector<T> :: push_back(const T &element) throw (const char *)
{
   // checks if need to allocate memory
   if ( numElements == numCapacity )
   {
      // allocate only 1 if is empty
      resize((empty() ? 1 : 2 * numCapacity) );
   }

   // store element
   data[numElements++] = element;
}



/**************************************************
 * VECTOR ITERATOR
 * An iterator through vector
 *************************************************/
template <class T>
class vector <T> :: iterator
{
private:
   T * p;

public:
   // constructors, destructors, and assignment operator
   iterator()      : p(NULL)      {              }
   iterator(T * p) : p(p)         {              }
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
         T & operator * ()       { return *p; }
   const T & operator * () const { return *p; }

   T * operator & () { return p; }

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
 * VECTOR CONST_ITERATOR
 * A constant iterator through vector
 *************************************************/
template <class T>
class vector <T> :: const_iterator
{
private:
   const T * p;

public:
   // constructors, destructors, and assignment operator
   const_iterator()      : p(NULL) {              }
   const_iterator(T * p) : p(p)    {              }
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
* VECTOR :: END
* Return an iterator
********************************************/
template <class T>
typename vector <T> ::iterator vector <T> ::end()
{
   return iterator(data + numElements);
}


/********************************************
* VECTOR :: CEND
* Return an constant interactor
********************************************/
template <class T>
typename vector <T> ::const_iterator vector <T> ::cend() const
{
   return const_iterator(data + numElements);
}

}  // custom name space



#endif /* VECTOR_H */

