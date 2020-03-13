/***********************************************************************
* Header:
*    SUPERVISOR
* Summary:
*    This contains a class to supervise all students requests.
* Author
*    Andres Rodriguez, Pedro Bastos, Fangyi Li
************************************************************************/

#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <string>
#include <stack>
#include "request.h"
#include "deque.h"

using namespace std;

class Supervisor
{
private:
   custom::deque<Request> waitList;    // deque wait list
   Request nowServing;                 // current request
   int elapsedTime;                    // time counter
public:
   // default constructor
   Supervisor()
   {
      // it starts with -1 because the first thing in loop
      // is to advance in time
      elapsedTime = -1;
   }

   // destructor
   ~Supervisor()
   {
   }

   // get time passed since object construction
   int getTime() const { return elapsedTime; }

   // advance in time
   void advance();

   // returns current Request
   const Request & currentRequest() const { return nowServing; }

   // I'm helping someone
   bool isServing() const { return !nowServing.done(); }

   // add a new request 
   void add(const string &className, const string &studentName, int time, bool emergency);
};

#endif // SUPERVISOR_H