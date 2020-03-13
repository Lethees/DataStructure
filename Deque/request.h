/***********************************************************************
* Header:
*    REQUEST
* Summary:
*    This contains a class for detail of each request.
* Author
*    Andres Rodriguez, Pedro Bastos, Fangyi Li
************************************************************************/

#ifndef REQUEST_H
#define REQUEST_H

#include <string>

using namespace std;

class Request
{
private:
   string className;            // class name from user
   string studentName;          // student name
   int ttl;                     // time to live of request
   bool emergency;              // emergency flag
public:

   // default constructor
   Request() : emergency(false)
   {
      className = "";
      studentName = "";
      ttl = 0;
      emergency = false;
   }

   // non default constructor
   Request(string className, string studentName, int ttl) : emergency(false)
   {
      this->className = className;
      this->studentName = studentName;
      this->ttl = ttl;
   }

   // constructor
   ~Request()
   {
   }

   // advancing in time means decrease its time to live
   void advance() { ttl--; };

   // this request is done
   bool done() const { return ttl <= 0; }

   // set emergency flag
   void setEmergency(bool emergency) { this->emergency = emergency; }

   // output operator
   friend std::ostream & operator << (std::ostream & out, const Request & rhs);

   // assigment/copy operator
   Request & operator = (const Request &rhs);
};

#endif  // REQUEST_H