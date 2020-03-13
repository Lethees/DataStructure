/***********************************************************************
* Implementation:
*    REQUEST
* Summary:
*    This contains the implementation for class Request. It holds
*    all info from user's request.
* Author
*    Andres Rodriguez, Pedro Bastos, Fangyi Li
**********************************************************************/
#include "stdafx.h"

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT

#include "request.h"

/************************************************
* Friend operator << 
* Streams out message to user
***********************************************/
std::ostream & operator << (std::ostream & out, const Request & rhs)
{
   // there is nothing to show
   if (rhs.done())
   {
      return out;
   }

   // it is an emergency or not
   // messages are diferent for each
   if (rhs.emergency)
   {
      out << "Emergency for ";
   }
   else
   {
      out << "Currently serving ";
   }

   // creates a stream to ostrem
   out << rhs.studentName << " for class " << rhs.className
      << ". Time left: " << rhs.ttl;

   // returns current out stream
   return out;
}

/************************************************
* Request :: operator =
* Copies a request (rhs) to current object
***********************************************/
Request & Request :: operator = (const Request &rhs)
{
   this->className = rhs.className;
   this->emergency = rhs.emergency;
   this->studentName = rhs.studentName;
   this->ttl = rhs.ttl;
   
   return *this;
}
