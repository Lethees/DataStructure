#ifndef STACK_H
#define STACK_H

#include <stack>
#include <cassert>

template <class T>
class Stack
{
public:
   // default constructor : empty and kinda useless
   Stack() : numItems(0), cap(0), data(NULL) {}

   // copy constructor : copy it
   Stack(const Stack & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Stack(int capacity) throw (const char *);
   
   // destructor : free everything
   ~Stack()        { if (cap) delete [] data; }
   
   // is the container currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the Stack
   void clear()        { numItems = 0;                 }

   // how many items are currently in the Stack?
   int size() const    { return numItems;              }
   
   // the capacity of the Stack
   int capacity() const { return cap;                  }   
   
   // push...
   void push(T a) throw (const char *);
   
   // Removes an item from the end of the stack
   void pop() throw (const char *);
   
   // Returns the item currently at the end of the stack. 
   T & top() throw (const char *);
   
   // Assignment operator.
   Stack <T> & operator = (const Stack <T> & rhs) throw (const char *);
   
private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the 
   int cap;           // how many items can I put on the Stack before full?
};

/**********************************************
 * Stack : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Stack <T> :: Stack(int capacity) throw (const char *)
{
   assert(capacity >= 0);
   
   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      this->cap = this->numItems = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->cap = capacity;
   this->numItems = 0;

   // initialize the container by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}

/*******************************************
 * Stack :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Stack <T> :: Stack(const Stack <T> & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = numItems = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
   cap = rhs.cap;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numItems; i < cap; i++)
      data[i] = T();
}

/***************************************************
 * Stack :: push
 * Insert an item on the end of the container
 **************************************************/
template <class T>
void Stack <T> :: push(T a) throw (const char *)
{         
  if (numItems == cap)
  {
    if (cap == 0)
    {
      cap = 1;
    } 
    else    
      cap = cap * 2;
    T * newStack = NULL;         
    try
    { 
      newStack = new T[cap];
    }
    catch (std::bad_alloc)
    {
      throw "Unable to allocate a new buffer for Stack";
    }
  
    for (int i = 0; i < numItems; i++)
    {
      newStack[i] = data[i];
    }

    delete [] data;
    data = newStack; 
  }

  data[numItems] = a;
  numItems++;               
}

/***************************************************
 * operator =
 **************************************************/
template <class T>
Stack <T> & Stack <T> :: operator = (const Stack <T> & rhs) throw (const char *)
{
  if (!rhs.numItems)
  {
    numItems = 0;
    data = NULL;
    return *this;
  }
  
  try
  {
    if(cap < rhs.numItems)
    {
      if(cap)
        delete[]data;
        data = new T[rhs.cap];
        cap = rhs.cap;
    }
  }
  catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer for Stack";
   }
  
  numItems = rhs.numItems;
  
  for (int i = 0; i< numItems; i++)
    data[i] = rhs.data[i];
    return *this;
}

/***************************************************
 * Removes an item from the end of the stack
 **************************************************/
template <class T>
void Stack <T> :: pop() throw (const char *)
{
  if (numItems == 0)
  {
    throw "ERROR: Unable to pop from an empty Stack";
  }
  else
    numItems--;  
}
 
/***************************************************
 * Returns the item currently at the end of the stack. 
 **************************************************/
template <class T>
T & Stack <T> :: top() throw (const char *)
{
  if (!numItems)
  {
    throw "ERROR: Unable to reference the element from an empty Stack";
  }
  else
    return data[numItems-1];   
}
 
#endif // Stack.h


