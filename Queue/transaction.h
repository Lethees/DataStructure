/***********************************************************************
* Header:
*    TRANSACTION
* Summary:
*    This file contains stocks portifolio
* Author
*    Andres Rodriguez, Pedro Bastos, Fangyi Li
************************************************************************/


#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "dollars.h"


enum class TransactionType {  Sell, Buy };

/************************************************
 * Transaction
 * A class that holds stuff
 ***********************************************/
class Transaction
{
private:
   int quantity;              // how many stocks 
   Dollars price;             // what price traded
   Dollars profit;            // in case was a sell
   TransactionType type;      // type of transaction
   int id;                    // transaction ID

public:
   // non-default constructor
   Transaction(int id)
   { 
      this->id = id;
      this->quantity = 0;
   }
   // Destructor
   ~Transaction() { }

   // operations on this transaction
   void sell(int quantity, const Dollars &originalPrice, const Dollars &sellPrice);
   void buy(int quantity, const Dollars &price);

   // getters
   Dollars getPrice()              const { return price; }
   int getQuantity()               const { return quantity; }
   TransactionType getType()       const { return type; }
   Dollars getProfit()             const { return profit; }
   int getId()                     const { return id; }
   bool isCompleted()              const { return quantity == 0; }


   // setters
   void update(int quantitySold) { this->quantity -= quantitySold; }

   // input and output
   friend std::ostream & operator << (std::ostream & out, const Transaction & rhs);

   // Assignment operator of Transaction class
   Transaction& operator = (const Transaction& rhs)
   {
      this->price = rhs.price;
      this->quantity = rhs.quantity;
      this->id = rhs.id;
      this->type = rhs.type;
      this->profit = rhs.profit;

      return *this;
   }

};

#endif // TRANSACTION_H
