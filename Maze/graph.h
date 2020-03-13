/***********************************************************************
* Header:
*    Graph
* Summary:
*    This a generic class to create a graph using adjacent list.
*
* Author
*    Andres Rodriguez, Pedro Bastos, Fangyi Li
************************************************************************/

// helper for Visual C++
#pragma once

// disable warning on old exception style (Visual C++ specific)
#pragma warning( disable : 4290 )  


#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

#include "set.h"
#include "list.h"
#include "vector.h"
#include "vertex.h"

using namespace custom;

/************************************************
* GRAPH
* A class that represents a graph.
***********************************************/
class Graph
{
private:
   set <Vertex> *vertices;            // set of vertices
   bool *grid;                        // adjacent matrix
   int numCapacity;                   // number of elements in grid
   int numVertices;                   // number of vertices

   int findIndex(const Vertex &rhs);
   Vertex & findVertex(const int index);

   // get an index from grid matrix from column and row
   int getGridIndex(int column, int row) const {
      return (size() * row) + column;
   }

   // get an index from grid matrix from source and destination vertices
   int getGridIndex(const Vertex &source, const Vertex &destination) const {
      return getGridIndex(source.index(), destination.index());
   }

   int getGridRow(int iGrid) const
   {
      return iGrid / numVertices;
   }

   int getGridColumn(int iGrid) const
   {
      return iGrid % numVertices;
   }

public:
   // copy constructor
   Graph(const Graph & rhs) throw (const char*);

   // non-default constructor
   Graph(int numVerticies) throw (const char*);

   // destructor
   ~Graph() {
   }

   // assign operator
   Graph & operator = (const Graph & rhs) throw (const char*);

   // check if graph is empty
   bool empty() const { return vertices->capacity() == 0; }

   // return the number of verticiess 
   int size() const { return vertices->capacity(); }

   // return the number of edges
   int capacity() const { return numCapacity; }

   // clear the data
   void clear();

   // add an edge
   void add(const Vertex &source, const Vertex &destination);

   // add an edge with a set of vertices
   void add(const Vertex &source, set<Vertex> &verticiess);

   // is an edge
   bool isEdge(const Vertex &source, Vertex &destination) const
   {
      return isEdge(source.index(), destination.index());
   }

   // is an edge
   bool isEdge(const int source, const int destination) const
   {
      return grid[getGridIndex(source, destination)];
   }

   // return all edges
   set <Vertex> findEdges(const Vertex &source);

   // return shortest path
   list <Vertex> findPath(const Vertex &source, const Vertex &destination);
   
   // return shortest path
   list <Vertex> findPath(int iSource, int iDestination);

   // solve maze
   vector <Vertex> solveMaze();
};
#endif /* GRAPH_H */

