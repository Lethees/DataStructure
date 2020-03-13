/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    Andres Rodriguez, Pedro Bastos, Fangyi Li
 **********************************************************************/
#include "stdafx.h"

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include <sstream>     // for STRING STREAM
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
#include "dollars.h"   // for DOLLARS
#include "portfolio.h" // for PORTFOLIO

using namespace std;

/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
   // instructions
   cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
   cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   cout << "  display         - Display your current stock portfolio\n";
   cout << "  quit            - Display a final report and quit the program\n";

   string command;            // command (first word in command line) from user
   string token;              // current token
   int quantity;              // quantity of stocks
   Dollars price;             // sell/buy price
   string shell;              // typed command from user
   Portfolio portfolio;       // portfolio to manage all transactions
   
   // ignores any character in cin
   cin.ignore();

   // executes until user type command quit
   do
   {
      // diaplay prompt
      cout << "> ";

      // get a command line
      getline(cin,shell);

      // convert it to a string stream to ease token processing
      istringstream ss(shell);

      // get the command part for command line
      getline(ss, command, ' ');

      // checks if the command requires parameters
      if ( command == "buy" || command == "sell" )
      {
         // get the first parameter
         getline(ss, token, ' ');
         
         // convert string to integer
         quantity = stoi(token);

         // get the second parameter
         getline(ss, token, ' ');

         // remove '$' from string
         auto pos = token.find('$');
         if (pos != string::npos)
         {
            token.erase(pos,1);
         }

         // convert string to Dollars
         price = token;

         // execute the buy method from portfolio
         if (command == "buy")
         {
            portfolio.buy(quantity, price);
         }

         // execute the sell method from portfolio
         if (command == "sell")
         {
            portfolio.sell(quantity, price);
         }
      }

      // display transactions
      if (command == "display")
      {
         portfolio.display();
      }
      
   } while (command != "quit");
}


