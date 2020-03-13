/***********************************************************************
* Implementation:
*    SUPERVISOR
* Summary:
*    This contains the implementation for class Supervisor. This class
*    supervises and control requests.
* Author
*    Andres Rodriguez, Pedro Bastos, Fangyi Li
**********************************************************************/

#include "stdafx.h"
#include "supervisor.h"


/************************************************
* Supervisor:: ADVANCE
* Advance in time
***********************************************/
void Supervisor::advance()
{
   // increments time
   elapsedTime++;

   // if there is a work in progress
   if (isServing())
   {
      nowServing.advance();

      // this work is not yeat completed
      if (!nowServing.done())
      {
         return;
      }
   }

   // get a new request from wait list
   if (!waitList.empty())
   {
      nowServing = waitList.front();
      waitList.pop_front();
   }
}

/************************************************
* Supervisor:: ADD
* Add a new request to deque
***********************************************/
void Supervisor::add(const string &className, const string &studentName, int time, bool emergency)
{
   Request newRequest(className, studentName, time);   // the new request

   // dont need to put in deque if there is not work in progress
   if (!isServing())
   {
      nowServing = newRequest;
      return;
   }

   // if emergency then put request in front of deque
   if (emergency)
   {
      newRequest.setEmergency(emergency);

      waitList.push_front(newRequest);
   }
   else
   {
      waitList.push_back(newRequest);
   }
}
