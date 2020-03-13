/***********************************************************************
 * Header:
 *    vector
 * Summary:
 *    This class contains the notion of an vector: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the vector, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       vector             : similar to std::vector
 *       vector :: iterator : an iterator through the vector
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef vector_H
#define vector_H

#include <cassert>  // because I am paranoid

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

/************************************************
 * vector
 * A class that holds stuff
 ***********************************************/
template <class T>
class vector
{
public:
   // constructors and destructors
   vector() : num(0), cap(0), data(NULL) {}
   vector(int num) throw (const char *);
   vector(int num, T & t)                  throw (const char *);
   vector(const vector & rhs)        throw (const char *);
  ~vector()
  {
    if (data != NULL)
    {
       delete[] data;
    }
  }                         
   vector & operator = (const vector & rhs) throw (const char *);
   
   // standard container interfaces
   int  size()     const { return num;                 }
   int  capacity() const { return cap;                 }
   
   bool empty() const  { return num == 0;         }

   // remove all the items from the Vector
   void clear()        { num = 0;                 }
   
   T & operator [] (int index)       throw (const char *)
   {
     try
     {
        if (cap < index)
        {
          cap < index;
        }
     }
     catch (std::bad_alloc)
     {
        throw "ERROR: Invalid index";
     }
     
      return data[index];
   }
   
   const T & operator [] (int index) const throw (const char *)
   {
     try
     {
        if (cap < index)
        {
          cap < index;
        }
     }
     catch (std::bad_alloc)
     {
        throw "ERROR: Invalid index";
     }
     
     return data[index];
   }
   
   void push_back(T a);
   
   
   // the various iterator interfaces
   class iterator;
   iterator begin()      { return iterator (data); }
   iterator end();
   class const_iterator;
   const_iterator cbegin() const      { return const_iterator (data); }
   const_iterator cend() const;

   // a debug utility to display the vector
   // this gets compiled to nothing if NDEBUG is defined
   void display() const; 
   
private:
   T * data;              // dynamically allocated vector of T
   int num;               // both the capacity and the number of elements
   int cap;
};

/***************************************************
 * Vector :: push_back
 * Insert an item on the end of the Vector
 **************************************************/
template <class T>
void vector <T> :: push_back(T a)
{
  if(cap == num)
  {
    if (cap == 0)
    {
      cap++;     
    }
    else if (num == cap)
      cap = cap * 2;
    
    T * dataV = NULL;
    
    dataV = data;
    try
    {
      data = new T[cap];
    }
    catch (std::bad_alloc)
    {
       throw "ERROR: Unable to allocate a new buffer for Vector";
    }
    for (int i = 0; i < num; i++)
    {
       data[i] = dataV[i];
    }
    delete [] dataV;
  }
  data[num] = a;
  num++;             
}

/**************************************************
 * vector ITERATOR
 * An iterator through vector
 *************************************************/
template <class T>
class vector <T> :: iterator
{
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

   // prefix increment and decrement
   iterator & operator ++ ()
   {
      p++;
      return *this;
   }
   
   iterator & operator -- ()
   {
      p--;
      return *this;
   }

   // postfix increment and de crement
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      p++;
      return tmp;
   }
   
   iterator operator -- (int postfix)
   {
      iterator tmp(*this);
      p--;
      return tmp;
   }
   
private:
   T * p;
};

/**************************************************
 * const vector ITERATOR
 * An iterator through vector
 *************************************************/
template <class T>
class vector <T> :: const_iterator
{
public:
   // constructors, destructors, and assignment operator
   const_iterator()      : p1(NULL)      {              }
   const_iterator(T * p1) : p1(p1)         {              }
   const_iterator (const const_iterator & rhs) { *this = rhs; }
   const_iterator &operator = (const const_iterator & rhs)
   {
      this->p1 = rhs.p1;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const const_iterator & rhs) const { return rhs.p1 != this->p1; }
   bool operator == (const const_iterator & rhs) const { return rhs.p1 == this->p1; }

   // dereference operator
         T & operator * ()       { return *p1; }
   const T & operator * () const { return *p1; }

   // prefix increment and decrement
   const_iterator & operator ++ ()
   {
      p1++;
      return *this;
   }
   
   const_iterator & operator -- ()
   {
      p1--;
      return *this;
   }

   // postfix increment and de crement
   const_iterator operator ++ (int postfix)
   {
      const_iterator tmp(*this);
      p1++;
      return tmp;
   }
   
   const_iterator operator -- (int postfix)
   {
      const_iterator tmp(*this);
      p1--;
      return tmp;
   }
   
private:
   T * p1;
};


/********************************************
 * vector :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename vector <T> :: iterator vector <T> :: end ()
{
   return iterator (data + num);
}

/********************************************
 * vector :: CEND
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename vector <T> :: const_iterator vector <T> :: cend () const
{
   return const_iterator (data + num);
}

/*******************************************
 * vector :: Assignment
 *******************************************/
template <class T>
vector <T> & vector <T> :: operator = (const vector <T> & rhs)
          throw (const char *)
{
  if (!rhs.num)
  {
    num = 0;
    return *this;
  }
   
  try
  {
    if(cap < rhs.num)
    {
       delete[]data;
       data = new T[rhs.cap];
       cap = rhs.cap;
    }
  }
  
  catch (std::bad_alloc)
  {
    throw "ERROR: Unable to allocate a new buffer for vector.";
  }
  
  num = rhs.num;


  assert(num == rhs.num);
  for (int i = 0; i < num; i++)
     data[i] = rhs.data[i];

  return *this;
}

/*******************************************
 * vector :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
vector <T> :: vector(const vector <T> & rhs) throw (const char *)
{
   assert(rhs.num >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.num == 0)
   {
      num = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.num];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity
   this->num = rhs.num;
   this->cap = rhs.cap;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < num; i++)
      data[i] = rhs.data[i];
}

/**********************************************
 * vector : NON-DEFAULT CONSTRUCTOR
 * Preallocate the vector to "capacity"
 **********************************************/
template <class T>
vector <T> :: vector(int num) throw (const char *)
{
   assert(num >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an vector, this is kinda pointless
   if (num == 0)
   {
      this->num = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[num];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for vector";
   }

      
   // copy over the stuff
   this->num = 0;
   this->cap = num;
}

/**********************************************
 * vector : NON-DEFAULT CONSTRUCTOR
 * Preallocate the vector to "capacity"
 **********************************************/
template <class T>
vector <T> :: vector(int num, T & t) throw (const char *)
{
   assert(num >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an vector, this is kinda pointless
   if (num == 0)
   {
      this->num = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[num];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for vector";
   }

      
   // copy over the stuff
   this->cap = num;
}

/********************************************
 * vector : DISPLAY
 * A debug utility to display the contents of the vector
 *******************************************/
template <class T>
void vector <T> :: display() const
{
#ifndef NDEBUG
   std::cerr << "vector<T>::display()\n";
   std::cerr << "\tnum = " << num << "\n";
   for (int i = 0; i < num; i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif // NDEBUG
}

}; // namespace custom

#endif // VECTOR_H

