/***********************************************************************
 * Header:
 *    stack
 * Summary:
 *    This class contains the notion of an stack: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the stack, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       stack             : similar to std::stack
 *       stack :: iterator : an iterator through the stack
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef stack_H
#define stack_H

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
 * stack
 * A class that holds stuff
 ***********************************************/
template <class T>
class stack
{
public:
   // constructors and destructors
   stack() : num(0), cap(0), data(NULL) {}
   stack(int num) throw (const char *);
   stack(int num, T & t)                  throw (const char *);
   stack(const stack & rhs)        throw (const char *);
  ~stack()
  {
    if (data != NULL)
    {
       delete[] data;
    }
  }                         
   stack & operator = (const stack & rhs) throw (const char *);
   
   // standard container interfaces
   int  size()     const { return num;                 }
   int  capacity() const { return cap;                 }
   
   bool empty() const  { return num == 0;         }

   // remove all the items from the stack
   void clear()        { num = 0;                 }
   
   void pop() throw (const char *)
   {
     if (num >= 0)
     {
       num--;
     }
   }
   
   T & top() throw (const char *)
   {
     if (num == 0)
     {
        throw "ERROR: Unable to reference the element from an empty Stack";
     }
     
     else
     {
        return data[num - 1];
     }     
   }
   
   const T & top() const throw (const char *)
   {
     if (num == 0)
     {
        throw "ERROR: Unable to reference the element from an empty Stack";
     }
     
     else
     {
        return data[num - 1];
     }     
   }
   
   void push(T a);

   // a debug utility to display the stack
   // this gets compiled to nothing if NDEBUG is defined
   void display() const; 
   
private:
   T * data;              // dynamically allocated stack of T
   int num;               // both the capacity and the number of elements
   int cap;
};

/***************************************************
 * stack :: push
 * Insert an item on the end of the stack
 **************************************************/
template <class T>
void stack <T> :: push(T a)
{
  if (num == cap)
  {
    if (cap == 0)
    {
      cap++;
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
  
    for (int i = 0; i < num; i++)
    {
      newStack[i] = data[i];
    }

    delete [] data;
    data = newStack; 
  }

  data[num] = a;
  num++;              
}

/*******************************************
 * stack :: Assignment
 *******************************************/
template <class T>
stack <T> & stack <T> :: operator = (const stack <T> & rhs)
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
    throw "ERROR: Unable to allocate a new buffer for Stack.";
  }
  
  num = rhs.num;


  assert(num == rhs.num);
  for (int i = 0; i < num; i++)
     data[i] = rhs.data[i];

  return *this;
}

/*******************************************
 * stack :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
stack <T> :: stack(const stack <T> & rhs) throw (const char *)
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
 * stack : NON-DEFAULT CONSTRUCTOR
 * Preallocate the stack to "capacity"
 **********************************************/
template <class T>
stack <T> :: stack(int num) throw (const char *)
{
   assert(num >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an stack, this is kinda pointless
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
      throw "ERROR: Unable to allocate a new buffer for Stack";
   }

      
   // copy over the stuff
   this->num = 0;
   this->cap = num;
}

/**********************************************
 * stack : NON-DEFAULT CONSTRUCTOR
 * Preallocate the stack to "capacity"
 **********************************************/
template <class T>
stack <T> :: stack(int num, T & t) throw (const char *)
{  
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
      throw "ERROR: Unable to allocate a new buffer for Stack";
   }

      
   // copy over the stuff
   this->cap = num;
}

/********************************************
 * stack : DISPLAY
 * A debug utility to display the contents of the stack
 *******************************************/
template <class T>
void stack <T> :: display() const
{
#ifndef NDEBUG
   std::cerr << "stack<T>::display()\n";
   std::cerr << "\tnum = " << num << "\n";
   for (int i = 0; i < num; i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif // NDEBUG
}

}; // namespace custom

#endif // STACK_H

