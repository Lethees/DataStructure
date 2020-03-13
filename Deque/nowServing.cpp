/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    Andres Rodriguez, Pedro Bastos, Fangyi Li
 **********************************************************************/

#include "stdafx.h"     // for visual studio

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <sstream>      // for STRING STREAM
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
#include "supervisor.h" // for SUPERVISOR

using namespace std;

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   string className;              // class name from user
   string studentName;            // student name
   int minutes;                   // time required
   string shell;                  // typed command from user
   bool isEmergency;              // an emergency request
   string strMinutes;             // a stri8ng representing minutes
   string command;                // the first word should be a command the class name
   
   Supervisor supervisor;         // controls all operations

   // ignores any previous character in cin
   cin.ignore();

   // executes until user type command finished
   while(true)
   {
      // show current work in progress
      if (supervisor.isServing())
      {
         cout << "\t" << supervisor.currentRequest() << endl;
      }

      // moves forward in time
      supervisor.advance();

      // it is not an emergency
      isEmergency = false;

      // clean up all previous values
      className = "";
      studentName = "";
      strMinutes = "";

      // display prompt
      cout << "<" << supervisor.getTime() << "> ";

      // get a command line
      getline(cin, shell);

      // convert it to a string stream to ease token processing
      istringstream ss(shell);

      // get the command part from command line
      getline(ss, command, ' ');

      // ends loop if finished was typed
      if (command == "finished")
      {
         break;
      }

      // go to beginning of loop
      if (command == "none")
      {
         continue;
      }

      // checks if it is an emergency
      if (command == "!!")
      {
         isEmergency = true;
      }
      
      try
      {
         if (isEmergency)
         {
            // get the student name
            getline(ss, className, ' ');
         }
         else
         {
            // get the class from command line
            className = command;
         }

         // get the student name
         getline(ss, studentName, ' ');

         // get the minutes as string
         getline(ss, strMinutes, ' ');

         // convert string to integer
         minutes = stoi(strMinutes);
      }
      catch (const std::exception&)
      {
         cout << "Invalid syntax" << endl;
         continue;
      }

      try {
         // add new request
         supervisor.add(className, studentName, minutes, isEmergency);
      }
      catch (const std::exception&)
      {
         cout << "Unable to add new request" << endl;
      }
      
   }
   cout << "End of simulation\n";
}


