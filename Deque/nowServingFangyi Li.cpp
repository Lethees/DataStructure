/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    Fangyi Li
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::ios;
//using namespace std;
using namespace custom;

class Student
{
public:
  //default constructor
  Student() :classes(""), name(""), min(0), emergency(false) {}
  
  //non-default constructor
  Student(string classes, string name, int min)
  {
    this->classes = classes;
    this->name = name;
    this->min = min;
    this->emergency = false;
  }
  
  //non-default constructor
  Student(string classes, string name, int min, bool emergency)
  {
    this->classes = classes;
    this->name = name;
    this->min = min;
    this->emergency = emergency;
  }
  
  //display the messages
  void display()
  {
    if(emergency)
    {
      cout << "\tEmergency for " << name << " for class " << classes << ". Time left: " << min << endl;
    }
    else
      cout << "\tCurrently serving " << name << " for class " << classes << ". Time left: " << min << endl;
  }
  
  //minutes  
  int min;
  
private:
  string classes;
  string name;
  bool emergency;
  
};

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
   
   //declarations
   deque <Student> student;
   int order = 0;
   string command = "";
   string classes;
   string name;
   int min;
   bool emergency;
   
   //do while loop
   do
     {
       cout << "<" << order << ">" << " ";
       cin >> command;
       order++;
       
       if(command == "!!")
       {        
         cin >> classes;
         cin >> name;
         cin >> min;
         emergency = true;
         Student temporary = student.front();
         Student information = Student(classes, name, min, emergency);
         student.pop_front();
         student.push_front(information);  
         student.push_front(temporary);     
       }
       
       else if(command != "!!" && command != "none" && command != "finished")
       {
         classes = command;
         cin >> name;
         cin >> min;
         emergency = false;
         Student information(classes, name, min);
         student.push_back(information);
       }
      
       if(!student.empty())
       {
         student.front().display();
         student.front().min--;
         if(student.front().min == 0)
         {
           student.pop_front();
         }
       }
       continue;  
          
       if(!student.empty())
       {
         student.front().display();
         student.front().min--;
       }
       
       if (student.front().min == 0)
       {
         student.pop_front();
       }
       else               
         student.front().display(); 
   }
   while(command != "finished");
   // end
   cout << "End of simulation\n";
}

