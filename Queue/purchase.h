/***********************************************************************
* Header:
*    PURCHASE
* Summary:
*    This file contains a stock purchase
* Author
*    Andres Rodriguez, Pedro Bastos, Fangyi Li
************************************************************************/

#ifndef PURCHASE_H
#define PURCHASE_H

#include "dollars.h"

/******************************************
 * PURCHASE
 * This class stores all purchases made. Its
 * elements are stored as a queue for 
 * Portfolio class.
 ******************************************/
class Purchase
{
private:
   int quantity;                // quantity of shares
   Dollars price;               // price of any share
   int transactionId;           // transaction id
public:
   // default constructor
   Purchase()
   {
      this->transactionId = 0;
      this->quantity = 0;
   }

   // constructor with a transaction id (Non-default constructor£©
   Purchase(int transactionId)
   {
      this->transactionId = transactionId;
      this->quantity = 0;
   }

   // complete constructor (Non-default constructor£©
   Purchase(int transactionId, int quantity, const Dollars &price)
   {
      this->price = price;
      this->quantity = quantity;
      this->transactionId = transactionId;
   }

   // destructor
   ~Purchase() {}

   // getters
   int getQuantity() const { return quantity; }
   Dollars getPrice() const { return price; }
   int getTransactionId() const { return transactionId; }

   // sell quantity
   int sell(int quantity)
   { 
      int sold = this->quantity < quantity ? this->quantity : quantity;

      this->quantity -= sold;

      return sold;
   }
   
   // assignment operator
   Purchase& operator = (const Purchase& rhs)
   {
      this->price = rhs.price;
      this->quantity = rhs.quantity;
      this->transactionId = rhs.transactionId;
      return *this;
   }

};

#endif  // PURCHASE_H