/***********************************************************************
* Component:
*    Graph
* Summary:
*    This a generic class to create a graph using adjacent list.
* Author
*    Andres Rodriguez, Pedro Bastos, Fangyi Li
************************************************************************/

// helper for Visual C++
//#pragma once

// disable warning on old exception style (Visual C++ specific)
//#pragma warning( disable : 4290 )  

#include "graph.h"

/*******************************************
* GRAPH :: COPY CONSTRUCTOR
*******************************************/
Graph::Graph(const Graph & rhs) throw (const char*)
{
   grid = NULL;
   numCapacity = 0;
   vertices = NULL;
   numVertices = 0;

   *this = rhs;
}

/**********************************************
* GRAPH : NON-DEFAULT CONSTRUCTOR
* Creates a graph with a number of verticies
**********************************************/
Graph::Graph(int numVertices) throw (const char*)
{
   try
   {
      // create a set of vertex
      vertices = new set <Vertex>(numVertices);
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate memory for the graph.";
   }

   // computes number of elements in the grid
   numCapacity = numVertices * numVertices;

   // allocates grid
   grid = new bool[numCapacity];
   for (int i = 0; i < numCapacity; i++)
   {
      grid[i] = false;
   }

   // stores number of vertices
   this->numVertices = numVertices;
}

/**********************************************
* GRAPH : ASSIGNMENT
* Assignment operator
**********************************************/
Graph & Graph ::operator = (const Graph & rhs) throw (const char*)
{
   // clear past values
   clear();

   numCapacity = rhs.capacity();

   try
   {
      // create a set of vertex
      vertices = new set <Vertex>(rhs.size());
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate memory for the graph.";
   }

   set <Vertex>::iterator it;

   for (it = rhs.vertices->begin(); it != rhs.vertices->end(); ++it)
   {
      vertices->insert((*it));
   }

   // allocates grid
   grid = new bool[numCapacity];
   for (int i = 0; i < numCapacity; i++)
   {
      grid[i] = rhs.grid[i];
   }

   // stores number of vertices
   this->numVertices = rhs.numVertices;
}

/**********************************************
* GRAPH : CLEAR
* Clear the contents
**********************************************/
void Graph::clear()
{
   if (vertices != NULL)
   {
      delete vertices;
   }

   if (grid != NULL)
   {
      delete[] grid;
   }

   numCapacity = 0;
}


/**********************************************
* GRAPH : ADD
* Add an edge to graph
**********************************************/
void Graph::add(const Vertex &source, const Vertex &destination)
{
   int idxSource;
   int idxDestination;
   idxSource = source.index();

   // source vertex was not added yet
   if (findIndex(source) == NOT_FOUND )
   {
      vertices->insert(source);
   }

   idxDestination = destination.index();

   // destination vertex was not added yet
   if (findIndex(destination) == NOT_FOUND)
   {
      vertices->insert(destination);
   }


   // edge from source to destination
   grid[getGridIndex(idxSource, idxDestination)] = true;
}

/**********************************************
* GRAPH : ADD
* Add an edge to graph from a set
**********************************************/
void Graph::add(const Vertex &source, set<Vertex> &verticies)
{
   set<Vertex>::iterator it;

   for (it = verticies.begin(); it != verticies.end(); ++it)
   {
      add(source, (*it));
   }
}
/**********************************************
* GRAPH : FIND INDEX
* Find a vertex index
**********************************************/
int Graph::findIndex(const Vertex &rhs)
{
   int idx = NOT_FOUND;

   // iterator to set
   set <Vertex>::iterator it;

   // initialize all elements with NULL
   for (it = vertices->begin(); it != vertices->end(); ++it)
   {
      if ((*it).index() == rhs.index())
      {
         idx = rhs.index();
         break;
      }
   }

   // return index
   return idx;
}

/**********************************************
* GRAPH : FIND VERTEX
* Find a vertex index
**********************************************/
Vertex & Graph::findVertex(const int index)
{
   // iterator to vector
   Vertex v(index);

   // iterator to set
   set <Vertex>::iterator it = vertices->find(v);

   // return vertex
   return (*it);
}

/**********************************************
* GRAPH : FIND EDGES
* Find a vertex
**********************************************/
set <Vertex> Graph::findEdges(const Vertex &source)
{
   int destination;
   set <Vertex> edges;

   for (destination = 0; destination < size(); destination++)
   {
      if (isEdge(source.index(), destination))
      {
         edges.insert(findVertex(destination));
      }
   }

   // return set
   return edges;
}

/**********************************************
* GRAPH : FIND PATH
* Find the shortest path between two verticies
**********************************************/
list <Vertex> Graph::findPath(int iSource, int iDestination)
{
   return findPath(findVertex(iSource), findVertex(iDestination));
}

/**********************************************
* GRAPH : FIND PATH
* Find the shortest path between two verticies
**********************************************/
list <Vertex> Graph::findPath(const Vertex &source, const Vertex &destination)
{
   list<Vertex> path;
   list<Vertex> toVisit;
   set <Vertex> s;
   set <Vertex> ::iterator it;
   Vertex v;

   int distance = 0;
   int *distances = new int[size()];
   Vertex *predecessor = new Vertex[size()*size()-1];

   toVisit.push_back(source);
   for (int i = 0; i < size(); i++)
   {
      distances[i] = -1;
   }

   while (!toVisit.empty() && distances[destination.index()])
   {
      v = toVisit.front();
      toVisit.pop_front();

      if (distances[v.index()])
      {
         distance++;
      }

      s = findEdges(v);
      for (it = s.begin(); it != s.end(); ++it)
      {
         int idx = (*it).index();
         if (distances[idx] == -1)
         {
            distances[idx] = distance + 1;
            predecessor[idx] = v;
            toVisit.push_back((*it));
         }

         distance++;
      }
   }

   if (distances[destination.index()] != -1)
   {
      path.push_back(destination);

      for (int i = 1; i < distance; i++)
      {
         path.push_back(predecessor[i - 1]);
      }
   }
   return path;
}

/**********************************************
* GRAPH : SOLVE MAZE
* Solve a maze from a graph
**********************************************/
vector <Vertex> Graph::solveMaze()
{
   vector <Vertex> vPath;
   list <Vertex> lPath;
   Vertex source;
   Vertex destination;
   
   // find the first vertex in adjacent matrix
   for (int i = 0; i < numCapacity; i++)
   {
      if (grid[i])
      {
         source = findVertex(getGridRow(i));
         break;
      }
   }

   // find the last vertex in adjacent matrix
   for (int i = numCapacity-1; i >= 0 ; i--)
   {
      if (grid[i])
      {
         destination = getGridColumn(i);
         break;
      }
   }

   // get path in list<T> format
   lPath = findPath(source, destination);

   // convert list<T> to vector<T>
   list<Vertex>::iterator it;

   for (it = lPath.begin(); it != lPath.end(); ++it)
   {
      vPath.push_back((*it));
   }

   // return path in vector<T>
   return vPath;
}


