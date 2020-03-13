/***********************************************************************
* Header:
*    PORTFOLIO
* Summary:
*    This file contains stocks portfolio
* Author
*    Andres Rodriguez, Pedro Bastos, Fangyi Li
************************************************************************/

#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <string>
#include <vector>
#include "queue.h"
#include "purchase.h"
#include "transaction.h"

using namespace std;

/******************************************
 * PORTFOLIO
 * This class operates all user's requesting
 * regarding buy and sell of stocks. It holds
 * stocks in a queue (purchases) and log all
 * buys and sells in a vector (transactions)
 ******************************************/
class Portfolio
{
private:

   std::vector<Transaction> transactions;    // holds all transactions
   custom::queue<Purchase> purchases;        // holds all purchases
   int numOperations;                        // number of operations
   Dollars sumSells;                         // sum of sells made

   // display transactions
   void displayTransactions(string label, TransactionType type);

   // update a transaction
   void updateTransaction(int transactionId, int quantitySold);

   // count the number of transactions
   int countTransactions(TransactionType type);

public:
   // default constructor
   Portfolio()
   {
      this->sumSells = 0;
      this->numOperations = 0;
   }

   // destructor
   ~Portfolio() {}

   // sell shares
   void sell(int quantity, const Dollars &price);
   
   // buy shares
   void buy(int quantity, const Dollars &price);

   // display transations
   void display();

   // sum of all sells
   const Dollars & proceeds() const { return sumSells; }
};

#endif // PORTFOLIO_H

