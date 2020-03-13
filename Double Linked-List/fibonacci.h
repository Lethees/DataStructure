/***********************************************************************
* Header:
*    FIBONACCI
* Summary:
*    This will contain just the prototype for fibonacci(). You may
*    want to put other class definitions here as well.
*
* Author
*    Andres Rodriguez, Pedro Bastos, Fangyi Li
************************************************************************/

#include <string>       // for STRING
#include <sstream>      // for STRING STREAM
#include <math.h>       // for log10

#include "list.h"

#ifndef FIBONACCI_H
#define FIBONACCI_H

#define BASE 1000

using namespace std;

/************************************************
* WHOLE NUMBER
* A class to create numbers with huge length 
* in digits.
***********************************************/
class WholeNumber
{
private:
   // linked list to hold digits
   custom::list <int> digits;

   // numeric base
   int base;

   // private method to import an int number
   void importNumber(int number);

public:
   // default constructor
   WholeNumber()
   {
      base = BASE;
   }

   // non default constructor
   WholeNumber(const int &in);

   // destructor
   ~WholeNumber() { digits.clear(); }

   // add operator
   friend WholeNumber operator + (const WholeNumber & lhs, const WholeNumber & rhs);
   // insertion operator
   friend ostream & operator << (ostream &out, const WholeNumber &rhs);
   
   // extraction operator
   friend istream & operator >> (istream &in, WholeNumber &rhs);

   // how many nodes (symbols) there are in thisnumber
   int size() const { return digits.size(); }

   // how many digits per symbol
   int numDigits() const { return (int)log10(base); }
};

// get fibonacci number
WholeNumber getFibonacciNumber(const int &n);

// the interactive fibonacci program
void fibonacci();

#endif // FIBONACCI_H

