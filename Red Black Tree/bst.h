/***********************************************************************
 * Component:
 *    Assignment 09, Binary Search Tree (BST)
 *    Brother <your instructor name here>, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    Create a binary search tree
 ************************************************************************/
 
 // helper for Visual C++
#pragma once

 // disable warning on old exception style (Visual C++ specific)
#pragma warning( disable : 4290 )  

#ifndef BST_H
#define BST_H

namespace custom
{
/************************************************
* LIST
* A class that holds stuff organized at a
* linked list.
***********************************************/
template <class T>
class BST
{
public:
   class iterator;
   class BNode;

   BST() : root(NULL), numElements(0) { }
   BST(const BST & rhs) throw (const char*);

   ~BST() { deleteBinaryTree(root); }

   // assignment operator
   BST & operator = (const BST & rhs) throw (const char*);

   // standard container interfaces
   int size()     const { return numElements; }
   bool empty()   const { return root == NULL; }
   void clear();

   // stores element 
   void insert(const T & t) throw (const char *);

   // erase with iterator
   void erase(iterator & it);

   // find element
   iterator find(const T & element);

   // the various iterator interfaces
   iterator begin() const;
   iterator end() const;
   iterator rbegin() const;
   iterator rend() const;

   // get current tree root
   BNode * getRoot() { return root; }

private:
   BNode * root;
   int numElements;

   void deleteNode(BNode *pNode, const bool &right);
   void deleteBinaryTree(BNode *pNode);
   
   BNode *copyBinaryTree(const BNode *pSrc) throw (const char *);

   BNode * search(BNode *pNode, const T& element);
   BNode * insert(BNode *pNode, const T & element) throw (const char *);

};

/********************************************
* BST :: NON DEFAULT CONSTRUCTOR
* Constructor that copies a tree
*******************************************/
template <class T>
BST<T>::BST(const BST<T> & rhs) throw (const char*)
{
   // copy RHS tree
   root = copyBinaryTree(rhs.root);

   numElements = rhs.numElements;
}

/********************************************
* BST :: DELETE NODE
* Remove a node from a BST
*******************************************/
template <class T>
void BST<T> ::deleteNode(BNode *pNode, const bool &right)
{

}

/********************************************
* BST :: DELETE BINARY TREE
* Delete the binary tree
*******************************************/
template <class T>
void BST<T> ::deleteBinaryTree(BNode *pNode)
{

}

/**********************************************
* COPY BINARY TREE
* A recursive function to copy trees
**********************************************/
template <class T>
typename BST<T>::BNode *BST<T>::copyBinaryTree(const typename BST<T>::BNode *pSrc) throw (const char *)
{
   BNode *destination;   // destination node

   // return in case of a leaf
   if (!pSrc)
   {
      return NULL;
   }

   // attempt to allocate
   try
   {
      destination = new BNode(pSrc->data, pSrc->isRed);
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }

   // go to left side of tree
   destination->pLeft = copyBinaryTree(pSrc->pLeft);

   // connect its parent
   if (destination->pLeft)
   {
      destination->pLeft->pParent = destination;
   }

   // go to right side of tree
   destination->pRight = copyBinaryTree(pSrc->pRight);

   // connect its parent
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
   // if there is already a tree, then clear it
   if (root != NULL)
   {
      clear();
   }

   // copy RHS tree
   root = copyBinaryTree(rhs.root);

   numElements = rhs.numElements;

   // return current tree
   return *this;
}

/********************************************
* BST :: CLEAR
* Clear BST setting elements to zero.
*******************************************/
template <class T>
void BST<T> ::clear()
{
   // free data
   deleteBinaryTree(this->root);

   // setting to zero
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
      // attempt to allocate
      try
      {
         root = new BNode(element);
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a node";
      }

      // increase number of elements
      numElements++;

      return;
   }

   // starts from root
   pNode = pParent = root;

   // find a spot to place new node
   while (pNode)
   {
      // save parent
      pParent = pNode;

      // choose right or left to go
      pNode = element < pNode->data ?
         pNode->pLeft : pNode->pRight;
   }

   // attempt to allocate
   try
   {
      pNode = new BNode(element, true);
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }

   // increase number of elements
   numElements++;

   // which size to put in
   if (element < pParent->data)
   {
      pParent->pLeft = pNode;
   }
   else
   {
      pParent->pRight = pNode;
   }

   // sets parent
   pNode->pParent = pParent;

   // balance RB tree
   pNode->balance();
}

/********************************************
* BST :: INSERT
* Insert element recursively
*******************************************/
template <class T>
typename BST<T> :: BNode * BST <T> ::insert(typename BST<T> ::BNode *pNode, const T & element) throw (const char *)
{
   // the root is NULL then I reached a leaf, so create a new node
   if (pNode == NULL)
   {
      BNode *newNode;   // new BNode

      // attempt to allocate
      try
      {
         newNode = new BNode(element);
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a node";
      }

      // increase number of elements
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

   // go to right because element is greater than root
   if (element > pNode->data )
   {
      return search(pNode->pRight, element);
   }

   // go to left 
   return search(pNode->pLeft, element);
}

/************************************************
* BST :: BNODE
* A class that holds a node for a Binary Tree.
***********************************************/
template <class T>
class BST<T> :: BNode
{
private:
   void verifyRB(const int &depth);
   void verifyBST();
   void balance(BNode *pNode);
public:
   T data;
   class BNode *pLeft;      // left node
   class BNode *pRight;     // right node
   class BNode *pParent;    // parent node
   bool isRed;              // check if is a red node
   
   // default constructor
   BNode() : pLeft(NULL), pRight(NULL), pParent(NULL), isRed(false)
   {
   }

   // non default constructor
   BNode(const T &element) : pLeft(NULL), pRight(NULL), pParent(NULL), isRed(false)
   {
      // set data to user parameter
      data = element;
   }

   // non default constructor
   BNode(const T &element, const bool &isRed) : pLeft(NULL), pRight(NULL), pParent(NULL)
   {
      // set data to user parameter
      data = element;

      // set isRed flag
      this->isRed = isRed;
   }

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
}

/********************************************
* BST :: BNODE :: VERIFY BST
* Ensures that the subtree under a given node 
* is a valid BST.
*******************************************/
template <class T>
void BST <T>::BNode::verifyBST()
{

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
   // save great grandparent
   BNode *pParent, *pGrandParent = NULL, *pGreat = NULL;

   // save parent
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

   // save grandparent
   if (pParent)
   {
      pGrandParent = pParent->pParent;
   }
   // save great grandparent
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
      // change aunt
      pGrandParent->pLeft->isRed = false;

      // change parent
      pParent->isRed = false;

      // change grandparent if it is not root
      if (pGrandParent->pParent)
      {
         pGrandParent->isRed = true;
      }

      // TODO: More work when great-grandparent is red
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
      // change aunt
      pGrandParent->pRight->isRed = false;

      // change parent
      pParent->isRed = false;

      // change grandparent if it is not root
      if (pGrandParent->pParent)
      {
         pGrandParent->isRed = true;
      }
      
      // TODO: More work when great-grandparent is red
      return;
   }

   // Case 4: 
   if (pParent->isRed && 
      !pGrandParent->isRed
      )
   {
      // case 4.a
      if (pParent->pLeft == pNode &&
         pGrandParent->pLeft == pParent)
      {
         // update grandparent with sibling (left)
         pGrandParent->pLeft = pParent->pRight;

         // update sibling's parent
         if (pParent->pRight)
         {
            pParent->pRight->pParent = pGrandParent;
         }

         // update grandparent parent
         pGrandParent->pParent = pParent;

         // update grandparent color
         pGrandParent->isRed = true;

         // update parent (right)
         pParent->pRight = pGrandParent;
         pParent->isRed = false;
         pParent->pParent = pGreat;

         // update great grandparent
         if (pGreat)
         {
            // which side the grand parent came
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

      // case 4.b
      if (pParent->pRight == pNode &&
         pGrandParent->pRight == pParent)
      {
         // update grandparent with sibling (right)
         pGrandParent->pRight = pParent->pLeft;

         // update sibling's parent
         if (pParent->pLeft)
         {
            pParent->pLeft->pParent = pGrandParent;
         }

         // update grandparent color
         pGrandParent->isRed = true;

         // update grandparent parent
         pGrandParent->pParent = pParent;

         // update parent (left)
         pParent->pLeft = pGrandParent;
         pParent->isRed = false;
         pParent->pParent = pGreat;

         // update great grandparent
         if (pGreat)
         {
            // which side the grand parent came
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

      // case 4.c
      if (pParent->pRight == pNode &&
         pGrandParent &&
         pGrandParent->pLeft == pParent)
      {
         BNode *pL, *pR;

         // save L and R children
         pL = pNode->pLeft;
         pR = pNode->pRight;

         // swap N and G
         pNode->pLeft = pParent;
         pNode->pRight = pGrandParent;
         pGrandParent->pParent = pNode;
         pParent->pParent = pNode;
         pNode->pParent = pGreat;

         // change colors
         pNode->isRed = false;
         pGrandParent->isRed = true;

         // distribute L
         pParent->pRight = pL;
         if (pL)
         {
            pL->pParent = pParent;
         }

         // distribute R
         pGrandParent->pLeft = pR;         
         if (pR)
         {
            pR->pParent = pGrandParent;
         }

         // update great grandparent
         if (pGreat)
         {
            // which side the grand parent came
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

      // case 4.d
      if (pParent->pLeft == pNode &&
         pGrandParent &&
         pGrandParent->pRight == pParent)
      {
         BNode *pL, *pR;

         // save L and R children
         pL = pNode->pLeft;
         pR = pNode->pRight;

         // swap N and G
         pNode->pLeft = pGrandParent;
         pNode->pRight = pParent;
         pGrandParent->pParent = pNode;
         pParent->pParent = pNode;
         pNode->pParent = pGreat;

         // distribute R
         pParent->pLeft = pR;
         if (pR)
         {
            pR->pParent = pParent;
         }

         // change colors
         pNode->isRed = false;
         pGrandParent->isRed = true;

         // distribute L
         pGrandParent->pRight = pL;
         if (pL)
         {
            pL->pParent = pGrandParent;
         }

         // update great grandparent
         if (pGreat)
         {
            // which side the grand parent came
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
   // constructors, destructors, and assignment operator
   iterator() : pNode(NULL) { }
   iterator(BNode * p) : pNode(p) { }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      this->pNode = rhs.pNode;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.pNode != this->pNode; }
   bool operator == (const iterator & rhs) const { return rhs.pNode == this->pNode; }

   // dereference operator
   const T & operator * () { return pNode->data; }

   // reference operator
   BNode * operator & () { return pNode; }

   iterator & operator -- ();

   // prefix increment
   iterator & operator ++ (int postfix);

   // postfix increment
  /* iterator & operator ++ (int postfix)
   {
      return *this;
   }*/

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
   // do nothing if we have nothing
   if (NULL == pNode)
      return *this;

   // if there is a left node, take it
   if (NULL != pNode->pLeft)
   {
      // go left
      pNode = pNode->pLeft;

      // jig right - there might be more right-most children
      while (pNode->pRight)
         pNode = pNode->pRight;
      return *this;
   }

   // there are no left children, the right are done
   assert(NULL == pNode->pLeft);
   BNode * pSave = pNode;

   // go up
   pNode = pNode->pParent;

   // if the parent is the NULL, we are done!
   if (NULL == pNode)
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == pNode->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
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
   // do nothing if we have nothing
   if (pNode == NULL )
      return *this;

   // if there is a right node, take it
   if (pNode->pRight != NULL)
   {
      // go right
      pNode = pNode->pRight;

      // jig left
      while (pNode->pLeft)
      {
         pNode = pNode->pLeft;
      }

      // found a node
      return *this;
   }

   // no right child and we are at left side of our parent
   if (pNode->pRight == NULL && pNode->pParent->pLeft == pNode)
   {
      pNode = pNode->pParent;

      return *this;
   }

   // no right child and we are at right side of our parent
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
   // auxiliary pointer
   BNode *pNode = (&it);

   // do nothing
   if (pNode == NULL)
   {
      return;
   }

   // Case 1: it is a leaf
   if (pNode->pRight == NULL && pNode->pLeft == NULL)
   {
      // disconect right side
      if (pNode->pParent != NULL && pNode->pParent->pRight == pNode)
      {
         pNode->pParent->pRight = NULL;
      }

      // disconnect left side
      if (pNode->pParent != NULL && pNode->pParent->pLeft == pNode)
      {
         pNode->pParent->pLeft = NULL;
      }

      // unallocate memory
      delete pNode;

      it = iterator(NULL);

      return;
   }

   // case 2: only one child
   // left case
   if (pNode->pRight == NULL && pNode->pLeft != NULL)
   {
      // update parent
      pNode->pLeft->pParent = pNode->pParent;

      if (pNode->pParent != NULL && pNode->pParent->pRight == pNode)
      {
         pNode->pParent->pRight = pNode->pLeft;
      }

      if (pNode->pParent != NULL && pNode->pParent->pLeft == pNode)
      {
         pNode->pParent->pLeft = pNode->pLeft;
      }

      // update root
      if (pNode == root)
      {
         root = pNode->pLeft;
      }

      // unallocate memory
      delete pNode;

      it = iterator(NULL);

      return;
   }

   // right case
   if (pNode->pLeft == NULL && pNode->pRight != NULL)
   {
      // update parent
      pNode->pRight->pParent = pNode->pParent;

      if (pNode->pParent != NULL && pNode->pParent->pRight == pNode)
      {
         pNode->pParent->pRight = pNode->pRight;
      }

      if (pNode->pParent != NULL && pNode->pParent->pLeft == pNode)
      {
         pNode->pParent->pLeft = pNode->pRight;
      }

      // update root
      if (pNode == root)
      {
         root = pNode->pRight;
      }

      // unallocate memory
      delete pNode;

      it = iterator(NULL);

      return;
   }

   // Case 3: Node has left and right children
   if (pNode->pLeft != NULL && pNode->pRight != NULL)
   {
      BNode *pSucessor = pNode->pRight;

      // find sucessor
      while (pSucessor->pLeft)
      {
         pSucessor = pSucessor->pLeft;
      }

      // connects left side
      if (pSucessor->pParent != pNode)
      {
         pSucessor->pParent->pLeft = pSucessor->pRight;
      }

      // connects left side parent
      if (pSucessor->pRight)
      {
         pSucessor->pRight->pParent = pSucessor->pParent;
      }

      // connects left side of sucessor
      if (pSucessor != pNode->pLeft)
      {
         pSucessor->pLeft = pNode->pLeft;
         if (pNode->pLeft)
         {
            pNode->pLeft->pParent = pSucessor;
         }
      }

      // connects right side of sucessor
      if (pSucessor != pNode->pRight)
      {
         pSucessor->pRight = pNode->pRight;
         if (pNode->pRight)
         {
            pNode->pRight->pParent = pSucessor;
         }
      }
      // connects parent's right side to sucessor
      if (pNode->pParent && pNode->pParent->pRight == pNode)
      {
         pNode->pParent->pRight = pSucessor;
      }

      if (pNode->pParent && pNode->pParent->pLeft == pNode)
      {
         pNode->pParent->pLeft = pSucessor;
      }

      // update parent
      pSucessor->pParent = pNode->pParent;

      // update root
      if (pNode == root)
      {
         root = pSucessor;
      }

      // remove node
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
   // go always to left
   while (pNode->pLeft)
   {
      pNode = pNode->pLeft;
   }

   // return an iterator
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

   // go always to right
   while (pNode->pRight)
   {
      pNode = pNode->pRight;
   }

   // return an iterator
   return iterator(pNode);
}


/********************************************
* BST :: REND
* Return an iterator
********************************************/
template <class T>
typename BST <T> ::iterator BST <T> ::rend() const
{
   return iterator(NULL);
}


} // namespace custom

#endif // BST_H
