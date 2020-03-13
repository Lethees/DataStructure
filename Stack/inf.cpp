/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    Fangyi Li
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
#include <sstream>
using namespace std;

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * The priorities of operators
 *****************************************************/
int priority(char a) 
{
    int temp;
    if (a == '^')
        temp = 1;
    else  if (a == '*' || a == '/')
        temp = 2;
    else  if (a == '+' || a == '-')
        temp = 3;
    return temp;
}

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{   
   string output;
   
   return output;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
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
        stack <char> stack;

        stringstream output;

        for (int i = 0; i < input.length(); i++) 
        {
          if (input[i] == '+' || input[i] == '-' 
          || input[i] == '*' || input[i] == '/' || input[i] == '^') 
          {
            while (!stack.empty() &&
             priority(stack.top()) <= priority(input[i])) 
              {
                output << stack.top();
                stack.pop();
              }
              stack.push(input[i]);
          } 
          else if (input[i] == '(') 
          {
              stack.push(input[i]);
          } 
          else if (input[i] == ')') 
          {
            while (stack.top() != '(') 
            {
              output << stack.top();
              stack.pop();
            }
            stack.pop();
          } 
          else 
          {          
            if (input[i] == '.' || input[i + 1] == '.' ||
              (isalpha(input[i]) && !isdigit(input[i + 4])) ||
              (isalpha(input[i]) && !isdigit(input[i + 3])) || 
              (isdigit(input[i]) && !isalpha(input[i + 2])) ||
              (isdigit(input[i]) && !isalpha(input[i + 4])) ||
              (isalpha(input[i]) && !isalpha(input[i + 4])) ||
              (isdigit(input[i])))
              output << input[i];            
            else if (input[i] != ' ')
              output << input[i] << ' '; 
            //else
              //output << input[i] << ' ';                        
          }  
        }
        while (!stack.empty()) 
        {
          output << stack.top();
          stack.pop();
        }                
        cout << "\tpostfix:  " << output.str() << endl << endl;
      }
   }
   while (input != "quit");
   
   cin.ignore();
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
 * TEST INFIX TO ASSEMBLY
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
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}
