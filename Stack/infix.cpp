/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    Fangyi Li
 * Summary:
 *    This program will implement the testinfixToPostfix()
 *    and testinfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
#include <sstream>
#include "infix.h" 

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::ios;
using std::stringstream;

using namespace custom;

/*****************************************************
 * CONVERT infix TO POSTFIX
 * The priorities of operators
 *****************************************************/
int priority(char a) 
{
    int priority;
    if (a == '^')
        priority = 1;
    else  if (a == '*' || a == '/')
        priority = 2;
    else  if (a == '+' || a == '-')
        priority = 3;
    return priority;
}

/*****************************************************
 * CONVERT infix TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertinfixToPostfix(const string & infix)
{  
   string postfix;
   
   stack <char> stack;
   
   stringstream output;
   
   string space = " ";
   
   for (int i = 0; i < infix.length(); i++)
   {
     if (infix[i] == '+' || infix[i] == '-'
      || infix[i] == '*' || infix[i] == '/' 
      || infix[i] == '^')
     {
       while (!stack.empty() &&
       priority(stack.top()) <= priority(infix[i]))
       {
         output << space + stack.top();
         stack.pop();
       }
       
       stack.push(infix[i]);
     }
     
     else if (infix[i] == '(')
     {
       stack.push(infix[i]);
     }
     
     else if (infix[i] == ')')
     {  
       if (!stack.empty())
       { 
         while (stack.top() != '(')
         {               
           output << space + stack.top();
           stack.pop();         
         }
       stack.pop();
       }
     }

     else 
     {
       if (isspace(infix[i]))
       {
         stack.push(infix[i]);
         stack.pop();
       }
       
       else if (infix[i] == '.' && infix[i - 1] != '+' && infix[i - 1] != ' '
       || isdigit(infix[i + 1]) && isdigit(infix[i]) && !isspace(infix[i - 1])
       || isdigit(infix[i - 1]) && isdigit(infix[i])
       || isalpha(infix[i - 1]) && isalpha(infix[i])
       || isalpha(infix[i - 1]) && isdigit(infix[i])
       || infix[i - 1] == '.' && isdigit(infix[i]))
       {
         output << infix[i];  
       }
       
       else
       {
         output << space + infix[i];
       }
             
     }   
     
   }
   
   while (!stack.empty())
   {
     output << space + stack.top();
     stack.pop();
   }
   
   cout << "\tpostfix: " << output.str() << endl << endl;
  
   return postfix;
}

/*****************************************************
 * TEST infix TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertinfixToPostfix(input);
         //cout << "\tpostfix: " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   string assembly;

   return assembly;
}

/*****************************************************
 * TEST infix TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertinfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}
