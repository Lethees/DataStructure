/***********************************************************************
 * Implementation:
 *    PORTFOLIO
 * Summary:
 *    This contains the implementationo Portfolio class which controls
 *    all stocks.
 * Author
 *    Andres Rodriguez, Pedro Bastos, Fangyi Li
 **********************************************************************/

#include "stdafx.h"

#include <iostream>
#include <string>
#include "portfolio.h"

using namespace std;

/************************************************
 * Portfolio :: SELL
 * Sell stocks 
 ***********************************************/
void Portfolio::sell(int quantity, const Dollars &price)
{
   int quantitySold = 0;                     // global stocks sold
   int currentSold = 0;                      // current stocks sold
   Transaction trans(numOperations);         // transaction id

   // iterates until there is stocks available to sell or
   // requested quantity was met
   while (!purchases.empty() && quantitySold != quantity)
   {
      // execute sell
      currentSold = purchases.front().sell(quantity-quantitySold);

      // sum of profits
      sumSells += (price - purchases.front().getPrice()) * currentSold;

      // log the sell
      trans.sell(currentSold, purchases.front().getPrice(), price);
      transactions.push_back(trans);

      // update sell
      quantitySold += currentSold;

      // update a buy transaction
      updateTransaction(purchases.front().getTransactionId(), currentSold);

      // all stock was sold
      if (purchases.front().getQuantity() <= 0)
      {
         purchases.pop();
      }
   }

   // increment number of operations
   numOperations++;
}

/************************************************
 * Portfolio :: BUY 
 * Buy stocks creating a transaction
 ***********************************************/
void Portfolio::buy(int quantity, const Dollars &price)
{
   Purchase purchase(numOperations, quantity, price);   // this purchase
   Transaction trans(numOperations);                    // new transaction

   // insert a buy transaction
   trans.buy(quantity, price);
   
   // queue this buy
   purchases.push(purchase);

   // store this transaction
   transactions.push_back(trans);

   // increments number of operations for next transaction
   numOperations++;
}

/************************************************
 * Portfolio :: DISPLAY 
 * Display all transactions if they are note 
 * completed.
 ***********************************************/
void Portfolio::display()
{
   // diplays buys
   if (countTransactions(TransactionType::Buy) > 0)
   {
      displayTransactions("Currently held:", TransactionType::Buy);
   }

   // display sells
   if (countTransactions(TransactionType::Sell) > 0)
   {
      displayTransactions("Sell History:", TransactionType::Sell);
   }

   // display proceeds
   cout << "Proceeds: " << sumSells << endl;
}

/************************************************
 * Portfolio :: DISPLAY TRANSACTION
 * Private method to really list transactions 
 * by type.
 ***********************************************/
void Portfolio::displayTransactions(string label, TransactionType type)
{
   std::vector <Transaction>::iterator it;    // iterator

   // display label
   cout << label << endl;

   // iterate into transactions vector with a type and excluding
   // those completed
   for (it = transactions.begin(); it != transactions.end(); ++it)
   {
      if ((*it).getType() == type && !(*it).isCompleted() )
      {
         cout << "\t" << *it << endl;
      }
   }
}

/************************************************
 * Portfolio :: UPDATE TRANSACTION
 * Update the quantity sold for a transaction.
 ***********************************************/
void Portfolio::updateTransaction(int transactionId, int quantitySold)
{
   std::vector <Transaction>::iterator it;   // iterator

   // look for provides Id. If found update quantity
   for (it = transactions.begin(); it != transactions.end(); ++it)
   {
      if ((*it).getId() == transactionId)
      {
         (*it).update(quantitySold);
      }
   }
}

/************************************************
 * Portfolio :: COUNT TRANSACTIONS
 * Count the number of uncompleted transactions.
 ***********************************************/
int Portfolio::countTransactions(TransactionType type)
{
   std::vector <Transaction>::iterator it;  // iterator
   int counter = 0;                         // counter

   // count the number of uncompleted transactions of type
   for (it = transactions.begin(); it != transactions.end(); ++it)
   {
      if ((*it).getType() == type && !(*it).isCompleted() )
      {
         counter++;
      }
   }

   // return counter
   return counter;
}