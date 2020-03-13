/***********************************************************************
* Implementation:
*    TRANSACTION
* Summary:
*    This contains the implementation for class Transaction, which holds
*    a transaction from portifolio.
* Author
*    Andres Rodriguez, Pedro Bastos, Fangyi Li
**********************************************************************/
#include "stdafx.h"

#include <iostream>  // for OSTREAM and ISTREAM

using namespace std;

#include "transaction.h"

/************************************************
 * Transaction :: sell
 * Does something like a setter
 ***********************************************/
void Transaction :: sell(int quantity, const Dollars &originalPrice, const Dollars &sellPrice)
{
   this->quantity = quantity;
   this->price = sellPrice;
   this->type = TransactionType::Sell;
   this->profit = (sellPrice - originalPrice) * quantity;
}

/************************************************
 * Transaction :: buy
 * Does something like a setter
 ***********************************************/
void Transaction::buy(int quantity, const Dollars &price)
{
   this->quantity = quantity;
   this->price = price;
   this->type = TransactionType::Buy;
}

/************************************************
 * Transaction :: insertion operator 
 ***********************************************/
ostream & operator << (ostream & out, const Transaction & rhs)
{
   // checks the type of transaction
   switch (rhs.getType())
   {
   case TransactionType::Sell:
      out << "Sold " << rhs.getQuantity()
         << " shares at " << rhs.getPrice()
         << " for a profit of " << rhs.getProfit();
      break;
   case TransactionType::Buy:
      out << "Bought " << rhs.getQuantity()
         << " shares at " << rhs.getPrice();
      break;
   }

   // returns the stream
   return out;
}