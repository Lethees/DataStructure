/***********************************************************************
* Header:
*    BST
* Summary:
*    This a generic class to store any data-type elements organized
*    into a binary search tree.
*
* Author
*    Austin & Marvin
************************************************************************/ 
#ifndef BST_H
#define BST_H

#include <iostream>  

namespace custom
{
   /************************************************
   * BST
   * A class that holds stuff organized at a
   * Binary Search Tree.
   ***********************************************/
   template <class T>
   class BST
   {
   private:
      // Class of BNode
      class BNode;

      // BNode root
      BNode * root;

      // Number of Elements
      int numElements;

      // Delete Binary trees
      void deleteBinaryTree(BNode *&pNode);

      // Copy Binary Tree
      BNode *copyBinaryTree(const BNode *pSrc) throw (const char *);

      // Search
      BNode * search(BNode *pNode, const T& element);

      // Insert
      BNode * insert(BNode *pNode, const T & element) throw (const char *);

   public:
      // Iterator Class
      class iterator;

      // Default Constructor
      BST() : root(NULL), numElements(0) { }

      // Non-default constructor
      BST(const BST & rhs) throw (const char*);

      // Destructor
      ~BST() { deleteBinaryTree(root); }

      // Assignment operator
      BST & operator = (const BST & rhs) throw (const char*);

      // Standard Container interfaces
      int size()     const { return numElements; }
      bool empty()   const { return root == NULL; }
      void clear();

      // Insert
      void insert(const T & t) throw (const char *);

      // Erase of Iterator
      void erase(iterator & it);

      // Find of iterator
      iterator find(const T & element);

      // Iterator methods
      iterator begin() const;
      iterator end() const;
      iterator rbegin() const;
      iterator rend() const;

   };

/********************************************
* BST :: NON DEFAULT CONSTRUCTOR
* Constructor that copies a tree
*******************************************/
template <class T>
BST<T>::BST(const BST<T> & rhs) throw (const char*)
{
   // Copy RHS tree
   root = copyBinaryTree(rhs.root);

   numElements = rhs.numElements;
}

  
   /********************************************
   * BST :: DELETE BINARY TREE
   * Delete the binary tree
   *******************************************/
   template <class T>
   void BST<T> ::deleteBinaryTree(BNode *&pNode)
   {
      //  Stop Condition
      if (!pNode)
      {
         return;
      }

      // Delete LHS
      deleteBinaryTree(pNode->pLeft);

      // Delete RHS
      deleteBinaryTree(pNode->pRight);

      // Delete pNode
      delete pNode;

      // Set to NULL pNode
      pNode = NULL;
   }

/**********************************************
* COPY BINARY TREE
* A recursive function to copy trees
**********************************************/
template <class T>
typename BST<T>::BNode *BST<T>::copyBinaryTree(const typename BST<T>::BNode *pSrc) throw (const char *)
{
   BNode *destination;   // destination node

   // Return in case of a leaf
   if (!pSrc)
   {
      return NULL;
   }

   // Attempt to allocate
   try
   {
      destination = new BNode(pSrc->data);
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }

   // Go to left side of tree
   destination->pLeft = copyBinaryTree(pSrc->pLeft);

   if (destination->pLeft)
   {
      destination->pLeft->pParent = destination;
   }

   // Go to right side of tree
   destination->pRight = copyBinaryTree(pSrc->pRight);

   if (destination->pRight)
   {
      destination->pRight->pParent = destination;
   }

   // returns from function
   return destination;
}

/*******************************************
* BST :: Assignment operator
* Copies elements from rhs to lhs BSTs
*******************************************/
template <class T>
BST <T> & BST <T> :: operator = (const BST  <T> & rhs) throw(const char*)
{
   // Clear tree
   if (root != NULL)
   {
      clear();
   }

   // Copy RHS Tree
   root = copyBinaryTree(rhs.root);

   numElements = rhs.numElements;

   // Return Current tree
   return *this;
}

/********************************************
* BST :: CLEAR
* Clear BST setting elements to zero.
*******************************************/
template <class T>
void BST<T> ::clear()
{
   // Delete data
   deleteBinaryTree(this->root);

   // Set to 0
   root = NULL;
   numElements = 0;
}

   /********************************************
   * BST :: INSERT
   * Insert element to the tree
   *******************************************/
   template <class T>
   void BST <T> ::insert(const T & element) throw (const char *)
   {
      BNode *pNode;
      BNode *pParent;

      if (root == NULL)
      {
        
         try
         {
            root = new BNode(element);
         }
         catch (std::bad_alloc)
         {
            throw "ERROR: Unable to allocate a node";
         }

         // NumElements increase
         numElements++;

         return;
      }

      // Start from root
      pNode = pParent = root;

      // Find a place to new node
      while (pNode)
      {
         // Copy Parent
         pParent = pNode;

         // choose right or left to go
         pNode = element < pNode->data ?
            pNode->pLeft : pNode->pRight;
      }

      //Try
      try
      {
         pNode = new BNode(element, true);
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a node";
      }

      // Increase numElements
      numElements++;

      if (element < pParent->data)
      {
         pParent->pLeft = pNode;
      }
      else
      {
         pParent->pRight = pNode;
      }

      // Set Parent
      pNode->pParent = pParent;

      // pNode Balance
      pNode->balance();
   }

   /********************************************
   * BST :: INSERT
   * Insert element recursively
   *******************************************/
   template <class T>
   typename BST<T> ::BNode * BST <T> ::insert(typename BST<T> ::BNode *pNode, const T & element) throw (const char *)
   {
      // the root is NULL then I reached a leaf, so create a new node
      if (pNode == NULL)
      {
         BNode *newNode;   // New BNode

         try
         {
            newNode = new BNode(element);
         }
         catch (std::bad_alloc)
         {
            throw "ERROR: Unable to allocate a node";
         }

         // Increase numElements
         numElements++;

         // return newly created node
         return newNode;
      }

// elements will be at left
      if (pNode->data > element)
      {
         // create a new child
         BNode *child = insert(pNode->pLeft, element);

         // first time here
         if (pNode->pLeft != child)
         {
            // set the left node to the child
            pNode->pLeft = child;

            // set parent to current node
            child->pParent = pNode;

            // set to red as newly inserted node
            child->isRed = true;

            // balance RB
            child->balance();
         }
      }

      // elements will be at right
      if (pNode->data < element)
      {
         BNode *child = insert(pNode->pRight, element);

         // first time here
         if (pNode->pRight != child)
         {
            // set the right node to the child
            pNode->pRight = child;

            // set parent to current node
            child->pParent = pNode;

            // set to red as newly inserted node
            child->isRed = true;

            // balance RB
            child->balance();
         }

      }

      // return node
      return pNode;
   }

/********************************************
* BST :: SEARCH
* Search a node to insert a new node
*******************************************/
template <class T>
typename BST<T>::BNode * BST<T>::search(typename BST<T>::BNode *pNode, const T& element)
{
   if (pNode == NULL || pNode->data == element)
   {
      return pNode;
   }

   // Go to right if element > root
   if (element > pNode->data )
   {
      return search(pNode->pRight, element);
   }

   // Else go to left 
   return search(pNode->pLeft, element);
}

/************************************************
* BST :: BNODE
* A class that holds a node for a Binary Tree.
***********************************************/
   template <class T>
   class BST<T> ::BNode
   {
   private:
   //Declare Private Methods
      void verifyRB(const int &depth);
      void verifyBST();
      void balance(BNode *pNode);
   public:
   //Declare public variable and methods
      T data;
      class BNode *pLeft;     
      class BNode *pRight;     
      class BNode *pParent;    
      bool isRed;              

      // Default constructor
      BNode() : pLeft(NULL), pRight(NULL), pParent(NULL), isRed(false)
      {
      }

      // Non default constructor
      BNode(const T &element) : pLeft(NULL), pRight(NULL), pParent(NULL), isRed(false)
      {
       
         data = element;
      }

      // Non default constructor RED
      BNode(const T &element, const bool &isRed) : pLeft(NULL), pRight(NULL), pParent(NULL)
      {
        
         data = element;

         // Set is Red
         this->isRed = isRed;
      }
	//Call balance method
      void balance();

   };

   /********************************************
   * BST :: BNODE :: VERIFY RB
   * Recursive, useful for verifying property d)
   * of a red-black tree.
   *******************************************/
   template <class T>
   void BST <T>::BNode::verifyRB(const int &depth)
   {
	   //Not was necessary
   }

   /********************************************
   * BST :: BNODE :: VERIFY BST
   * Ensures that the subtree under a given node
   * is a valid BST.
   *******************************************/
   template <class T>
   void BST <T>::BNode::verifyBST()
   {
		//Not was necessary
   }

   /********************************************
   * BST :: BNODE :: BALANCE
   * Contains all the red-black balancing logic.
   *******************************************/
   template <class T>
   void BST <T>::BNode::balance()
   {
      balance(this);
   }

   /********************************************
   * BST :: BNODE :: BALANCE
   * Contains all the red-black balancing logic.
   *******************************************/
   template <class T>
   void BST <T>::BNode::balance(BNode *pNode)
   {
      // Save pGrandParent
      BNode *pParent, *pGrandParent = NULL, *pGreat = NULL;

      // Save Parent
      pParent = pNode->pParent;

      // Case 1: No parent
      if (pParent == NULL)
      {
         pNode->isRed = false;
         return;
      }

      // Case 2: Parent is black
      if (!pParent->isRed && pNode->isRed)
      {
         return;
      }

      // Save pGrandparent
      if (pParent)
      {
         pGrandParent = pParent->pParent;
      }
      if (pGrandParent)
      {
         pGreat = pGrandParent->pParent;
      }

      // Case 3: Parent and aunt are red (left)
      if (pParent->isRed &&
         pGrandParent &&
         !pGrandParent->isRed &&
         pGrandParent->pLeft &&
         pGrandParent->pLeft != pParent &&
         pGrandParent->pLeft->isRed)
      {
         
         pGrandParent->pLeft->isRed = false;

         // Change parent
         pParent->isRed = false;

         // Change grandparent if it's not root
         if (pGrandParent->pParent)
         {
            pGrandParent->isRed = true;
         }

         //Return When pGrandParent is Red
         return;
      }

      // Case 3: Parent and aunt are red (right)
      if (pParent->isRed &&
         pGrandParent &&
         !pGrandParent->isRed &&
         pGrandParent->pRight &&
         pGrandParent->pRight != pParent &&
         pGrandParent->pRight->isRed)
      {
      
         pGrandParent->pRight->isRed = false;

         // Change parent
         pParent->isRed = false;

         // Change grandparent if it's not root
         if (pGrandParent->pParent)
         {
            pGrandParent->isRed = true;
         }

         // Return When GreatpGrandParent is Red
         return;
      }

      // Case 4: 
      if (pParent->isRed &&
         !pGrandParent->isRed
         )
      {
         // Case 4.a
         if (pParent->pLeft == pNode &&
            pGrandParent->pLeft == pParent)
         {
            // Update grandparent(left)
            pGrandParent->pLeft = pParent->pRight;

            
            if (pParent->pRight)
            {
               pParent->pRight->pParent = pGrandParent;
            }

            pGrandParent->pParent = pParent;

            // Update Grandparent Color
            pGrandParent->isRed = true;

            // Update Parent (Right)
            pParent->pRight = pGrandParent;
            pParent->isRed = false;
            pParent->pParent = pGreat;

            // Update Great Grandparent
            if (pGreat)
            {
              
               if (pGreat->pLeft == pGrandParent)
               {
                  pGreat->pLeft = pParent;
               }
               if (pGreat->pRight == pGrandParent)
               {
                  pGreat->pRight = pParent;
               }
            }

            return;
         }

         // Case 4.b
         if (pParent->pRight == pNode &&
            pGrandParent->pRight == pParent)
         {
            // Update Grandparent (right)
            pGrandParent->pRight = pParent->pLeft;

            if (pParent->pLeft)
            {
               pParent->pLeft->pParent = pGrandParent;
            }

            // Update Grandparent Color
            pGrandParent->isRed = true;

            // Update Grandparent & Parent
            pGrandParent->pParent = pParent;

            // Update Parent (Left)
            pParent->pLeft = pGrandParent;
            pParent->isRed = false;
            pParent->pParent = pGreat;

            // Update Great Grandparent
            if (pGreat)
            {
               if (pGreat->pLeft == pGrandParent)
               {
                  pGreat->pLeft = pParent;
               }
               if (pGreat->pRight == pGrandParent)
               {
                  pGreat->pRight = pParent;
               }
            }

            return;
         }

         // Case 4.c
         if (pParent->pRight == pNode &&
            pGrandParent &&
            pGrandParent->pLeft == pParent)
         {
            BNode *pL, *pR;

            // Save Left & Right Children
            pL = pNode->pLeft;
            pR = pNode->pRight;

            // Swap
            pNode->pLeft = pParent;
            pNode->pRight = pGrandParent;
            pGrandParent->pParent = pNode;
            pParent->pParent = pNode;
            pNode->pParent = pGreat;

            // Change colors
            pNode->isRed = false;
            pGrandParent->isRed = true;

            // Distribute L
            pParent->pRight = pL;
            if (pL)
            {
               pL->pParent = pParent;
            }

            // Distribute R
            pGrandParent->pLeft = pR;
            if (pR)
            {
               pR->pParent = pGrandParent;
            }

            // Update Great Grandparent
            if (pGreat)
            {
               if (pGreat->pLeft == pGrandParent)
               {
                  pGreat->pLeft = pNode;
               }
               if (pGreat->pRight == pGrandParent)
               {
                  pGreat->pRight = pNode;
               }
            }

            return;
         }

         // Case 4.d
         if (pParent->pLeft == pNode &&
            pGrandParent &&
            pGrandParent->pRight == pParent)
         {
            BNode *pL, *pR;

            // Save Left & Right Children
            pL = pNode->pLeft;
            pR = pNode->pRight;

            // Swap
            pNode->pLeft = pGrandParent;
            pNode->pRight = pParent;
            pGrandParent->pParent = pNode;
            pParent->pParent = pNode;
            pNode->pParent = pGreat;

            // Distribute R
            pParent->pLeft = pR;
            if (pR)
            {
               pR->pParent = pParent;
            }

            // Change colors
            pNode->isRed = false;
            pGrandParent->isRed = true;

            // Distribute L
            pGrandParent->pRight = pL;
            if (pL)
            {
               pL->pParent = pGrandParent;
            }

            // Update
            if (pGreat)
            {
              
               if (pGreat->pLeft == pGrandParent)
               {
                  pGreat->pLeft = pNode;
               }
               if (pGreat->pRight == pGrandParent)
               {
                  pGreat->pRight = pNode;
               }
            }

         }

      }
   }

/**************************************************
* BST :: ITERATOR
* An iterator through BST
*************************************************/
template <class T>
class BST <T> ::iterator
{
private:
   BNode * pNode;
public:
   // Constructors, Destructors, and Assignment Operator
   iterator() : pNode(NULL) { }
   iterator(BNode * p) : pNode(p) { }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      this->pNode = rhs.pNode;
      return *this;
   }

   // Equals Operator
   bool operator != (const iterator & rhs) const { return rhs.pNode != this->pNode; }
   bool operator == (const iterator & rhs) const { return rhs.pNode == this->pNode; }

   // Dereference operator
   const T & operator * () { return pNode->data; }

   // Reference operator
   BNode * operator & () { return pNode; }

   iterator & operator -- ();

   // Prefix increment
   iterator & operator ++ (int postfix);

};


/**************************************************
* BST ITERATOR :: DECREMENT PREFIX
*     advance by one.
* Author:      Br. Helfrich
* Performance: O(log n) though O(1) in the common case
*************************************************/
template <class T>
typename BST <T> ::iterator & BST <T> ::iterator :: operator -- ()
{
   // If there nothing finish this function
   if (NULL == pNode)
      return *this;

   // If there is a left node
   if (NULL != pNode->pLeft)
   {
      // Go to left
      pNode = pNode->pLeft;
      
      while (pNode->pRight)
         pNode = pNode->pRight;
      return *this;
   }

   //If there's not left children use the right
   assert(NULL == pNode->pLeft);
   BNode * pSave = pNode;

   pNode = pNode->pParent;

   // Finish the function
   if (NULL == pNode)
      return *this;

   // If right is ok, so go to parent class
   if (pSave == pNode->pRight)
      return *this;

   while (NULL != pNode && pSave == pNode->pLeft)
   {
      pSave = pNode;
      pNode = pNode->pParent;
   }

   return *this;
}

/**************************************************
* BST ITERATOR :: INCREMENT PREFIX
* Advance iterator by one.
*************************************************/
template <class T>
typename BST <T> ::iterator & BST <T> ::iterator :: operator ++ (int postfix)
{
   // Finish the function if there's not nothing
   if (pNode == NULL )
      return *this;

   // If there is a right node
   if (pNode->pRight != NULL)
   {
      // go right
      pNode = pNode->pRight;

      while (pNode->pLeft)
      {
         pNode = pNode->pLeft;
      }

      // Return a node
      return *this;
   }

   // If statement
   if (pNode->pRight == NULL && pNode->pParent->pLeft == pNode)
   {
      pNode = pNode->pParent;
	//Return node
      return *this;
   }

   // If statement
   if (pNode->pRight == NULL && pNode->pParent->pRight == pNode)
   {
      while (pNode->pParent != NULL && pNode->pParent->pRight == pNode)
      {
         pNode = pNode->pParent;
      }

      pNode = pNode->pParent;

      return *this;
   }
}

/********************************************
* BST :: FIND
* Find an element in tree
*******************************************/
   template <class T>
   typename BST <T> ::iterator BST <T> ::find(const T & element)
   {
      BNode *pNode;

      pNode = search(root, element);

      return iterator(pNode);
   }

/********************************************
* BST :: ERASE
* Erase element from tree using iterator
*******************************************/
template <class T>
void BST <T> ::erase(typename BST <T> ::iterator & it)
{
   //  Pointer
   BNode *pNode = (&it);

   // Finish the function if there's not nothing
   if (pNode == NULL)
   {
      return;
   }

   // Case 1
   if (pNode->pRight == NULL && pNode->pLeft == NULL)
   {
      // Close right side
      if (pNode->pParent != NULL && pNode->pParent->pRight == pNode)
      {
         pNode->pParent->pRight = NULL;
      }

      // Close left side
      if (pNode->pParent != NULL && pNode->pParent->pLeft == pNode)
      {
         pNode->pParent->pLeft = NULL;
      }

      //Free pNode
      delete pNode;

      it = iterator(NULL);

      return;
   }

   // Case 2:
   if (pNode->pRight == NULL && pNode->pLeft != NULL)
   {
      // Refresh
      pNode->pLeft->pParent = pNode->pParent;

      if (pNode->pParent != NULL && pNode->pParent->pRight == pNode)
      {
         pNode->pParent->pRight = pNode->pLeft;
      }

      if (pNode->pParent != NULL && pNode->pParent->pLeft == pNode)
      {
         pNode->pParent->pLeft = pNode->pLeft;
      }

      // Refresh root
      if (pNode == root)
      {
         root = pNode->pLeft;
      }

      // Free pNode
      delete pNode;

      it = iterator(NULL);

      return;
   }

   // Right Case
   if (pNode->pLeft == NULL && pNode->pRight != NULL)
   {
      // Update
      pNode->pRight->pParent = pNode->pParent;

      if (pNode->pParent != NULL && pNode->pParent->pRight == pNode)
      {
         pNode->pParent->pRight = pNode->pRight;
      }

      if (pNode->pParent != NULL && pNode->pParent->pLeft == pNode)
      {
         pNode->pParent->pLeft = pNode->pRight;
      }

      // Update root
      if (pNode == root)
      {
         root = pNode->pRight;
      }

      // Free pNode
      delete pNode;

      it = iterator(NULL);

      return;
   }

   // Case 3
   if (pNode->pLeft != NULL && pNode->pRight != NULL)
   {
      BNode *pSucessor = pNode->pRight;

      // Successor
      while (pSucessor->pLeft)
      {
         pSucessor = pSucessor->pLeft;
      }

      // Left side
      pSucessor->pParent->pLeft = pSucessor->pRight;
      
      // Left side parent
      if (pSucessor->pRight)
      {
         pSucessor->pRight->pParent = pSucessor->pParent;
      }

      // Left side of sucessor
      pSucessor->pLeft = pNode->pLeft;
      pNode->pLeft->pParent = pSucessor;

      // Connects right side of sucessor
      pSucessor->pRight = pNode->pRight;
      pNode->pRight->pParent = pSucessor;

      // Connects parent's right side to sucessor
      if (pNode->pParent && pNode->pParent->pRight == pNode)
      {
         pNode->pParent->pRight = pSucessor;
      }

      if (pNode->pParent && pNode->pParent->pLeft == pNode)
      {
         pNode->pParent->pLeft = pSucessor;
      }

      // Refresh successor
      pSucessor->pParent = pNode->pParent;

      // Refresh root
      if (pNode == root)
      {
         root = pSucessor;
      }

      //free pNode
      delete pNode;

      it = iterator(NULL);
   }
}
/********************************************
* BST :: BEGIN
* Return an iterator
********************************************/
   template <class T>
   typename BST <T> ::iterator BST <T> ::begin() const
   {
      BNode *pNode = this->root;

      if (pNode == NULL)
      {
         return iterator(NULL);
      }
      //Always to Left
      while (pNode->pLeft)
      {
         pNode = pNode->pLeft;
      }

      // Return an iterator
      return iterator(pNode);
   }


/********************************************
* BST :: END
* Return an iterator
   ********************************************/
   template <class T>
   typename BST <T> ::iterator BST <T> ::end() const
   {
      return iterator(NULL);
   }

/********************************************
* BST :: RBEGIN
* Return an iterator
********************************************/
   template <class T>
   typename BST <T> ::iterator BST <T> ::rbegin() const
   {
      BNode *pNode = this->root;

      if (pNode == NULL)
      {
         return iterator(NULL);
      }

      // Always to Right
      while (pNode->pRight)
      {
         pNode = pNode->pRight;
      }

      // Return an iterator
      return iterator(pNode);
   }


/********************************************
* BST :: REND
* Return an iterator
********************************************/
   template <class T>
   typename BST <T> ::iterator BST <T> ::rend() const
   {
	   //Return iterator to NULL
      return iterator(NULL);
   }
}

#endif // BST_H
