/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    Andres Rodriguez, Pedro Bastos, Fangyi Li
 **********************************************************************/

#include <iostream>
#include <string>        // for STRING
#include <sstream>       // for STRING STREAM
#include <iomanip>       // for leading 0
#include "list.h"        // for LIST
#include "fibonacci.h"   // for fibonacci() prototype

using namespace std;

/*******************************************
* WHOLE NUMBER :: NON DEFAULT CONSTRUCTOR
*******************************************/
WholeNumber :: WholeNumber(const int &in) : base(BASE)
{
   // find the number of digits
   int d = (int)ceil(log10(in));

   // if it is larger than number of digits for base
   if (d > numDigits())
   {
      // convert to alist
      importNumber(in);
   }
   else
   {
      // add to linked list
      digits.push_back(in);
   }
}

/*******************************************
* WHOLE NUMBER :: IMPORT NUMBER
* Import a 'int' to list
*******************************************/
void WholeNumber :: importNumber(int number)
{
   int n;       // current number

   n = number;

   // loop number breaking its digits
   do
   {
      // put a digit into a list
      digits.push_front(n % base);
   } while ((n = (int)n / base));
}

/*******************************************
* WHOLE NUMBER :: INSERTION OPERATOR
* Convert a whole number to a stream
*******************************************/
ostream & operator << (ostream &out, const WholeNumber &rhs)
{
   // iterator for digits 
   typename custom::list <int> ::iterator it;

   // num digits for each part of number
   int digits = rhs.size() > 1 ? rhs.numDigits() : 0;

   // iterate in every node of list
   for (it = rhs.digits.begin(); it != rhs.digits.end(); ++it)
   {
      // display nth part of number
      out << setfill('0') << setw(digits) << *it;

      // comma helper
      if ((&it)->pNext != NULL)
      {
         out << ",";
      }
   }

   // return stream
   return out;
}

/*******************************************
* WHOLE NUMBER :: EXTRATION OPERATOR
* Convert a stream to a whole number
*******************************************/
istream & operator >> (istream &in, WholeNumber &rhs)
{
   string str;
   
   in >> str;

   // convert it to a string stream to ease token processing
   istringstream ss(str);
   string token;

   while (getline(ss, token, ','))
   {
      rhs.digits.push_back(stoi(token));
   }

   return in;
}

/*******************************************
* WHOLE NUMBER :: ADD OPERATOR
* Add two while numbers
*******************************************/
WholeNumber operator + (const WholeNumber & lhs, const WholeNumber & rhs)
{
   // iterators
   custom::list<int> ::reverse_iterator itRhs, itLhs, itEnd;
   custom::list<int> ::iterator it;

   // this will hold the result from sum
   WholeNumber result;

   int carrier = 0;            // a carrier if sum was over base
   int sum;                    // temporary sum
   int rhsValue;               // value from rhs operand

   // this will find the longest number in digits
   if (lhs.size() >= rhs.size())
   {
      itRhs = rhs.digits.rbegin();
      itLhs = lhs.digits.rbegin();
      itEnd = lhs.digits.rend();
   }
   else
   {
      itRhs = lhs.digits.rbegin();
      itLhs = rhs.digits.rbegin();
      itEnd = rhs.digits.rend();
   }
   
   // iterator for result number
   it = result.digits.begin();

   // walk thought all digits from lhs (meaning the longest number in digits)
   for (; itLhs != itEnd; ++itLhs)
   {
      // there is no more siginificant digits
      rhsValue = (itRhs == itEnd) ? 0 : *itRhs;

      // computes sum
      sum = (*itLhs + rhsValue) + carrier;

      // find if carier is needed
      if (sum >= result.base)
      {
         // remaing from base
         sum -= result.base;

         // we need carrier
         carrier = 1;
      }
      else
      {
         carrier = 0;
      }

      // advancig the shorter number iterator
      if (itRhs != itEnd)
      {
         ++itRhs;
      }

      // there is no node to this digit
      if (it == result.digits.end())
      {
         // add a new node (significant digit)
         result.digits.push_front(sum);
      }
      else
      {
         *it = sum;
         it = result.digits.end();
      }

      // add a new node to hold carrier
      if (carrier == 1)
      {
         result.digits.push_front(1);
         it = result.digits.begin();
      }

   }

   // operation was successful
   return result;
}

/*******************************************
* GET FIBONACCI NUMBER
* Compute a Fibonacci number using dynamic 
* programming.
*******************************************/
WholeNumber getFibonacciNumber(const int &n)
{
   WholeNumber result;

   WholeNumber two(2);
   WholeNumber nMinusOne(1);
   WholeNumber nMinusTwo(1);

   if (n <= 0)
   {
      return WholeNumber(0);
   }
   else
   {
      if (n <= 2)
      {
         return WholeNumber(1);
      }
   }

   for (int i=2; i < n; i++)
   {
      result = nMinusOne + nMinusTwo;

      nMinusTwo = nMinusOne;
      nMinusOne = result;
   }

   return result;
}

/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
   // show the first serveral Fibonacci numbers
   int number;
   int in;

   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;

   for (int i = 1; i <= number; i++)
   {
      cout << "\t" << getFibonacciNumber(i) << endl;
   }
   
   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin >> in;

   cout << "\t" << getFibonacciNumber(in) << endl;
}
