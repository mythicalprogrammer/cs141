// CS-141 Lab 9 sample solution for DFS traversal - header file

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <ext/hash_map>

// hash_map is an STL extension, like map but more efficient for lookups
using __gnu_cxx::hash_map;

class Edge;
class EdgeIterator;


///////////////////////////////////////////////////////////////////////////////
// Vertex class

class Vertex
{
public:
  // Constructor takes a label and a weight for the new vertex
  Vertex(int label, double weight);

  // Mark the vertex as visited
  void markVisited();

  // Return true if the vertex has been visited, or false otherwise
  bool isVisited() const;

  // Add the edge e to the adjacency list for this vertex
  void addIncidentEdge(Edge *e);

  // Return an iterator over all edges incident upon this vertex
  EdgeIterator incidentEdges();

  double get_weight() const;
protected:
  int label;
  double weight;
  bool visited;
  std::list<Edge *> adjacentEdges;    // adjacency list

  friend std::ostream& operator<<(std::ostream& out, const Vertex& v);
};


///////////////////////////////////////////////////////////////////////////////
// Edge class

class Edge
{
public:
  // Constructor takes "from" vertex and "to" vertex for the new edge
  Edge(Vertex *from, Vertex *to);

  // Mark the edge as visited
  void markVisited();

  // Return true if the edge has been visited, or false otherwise
  bool isVisited() const;

  // Return the vertex on the other side of the edge
  Vertex *opposite(Vertex *v);

protected:
  Vertex *from, *to;
  bool visited;

  friend std::ostream& operator<<(std::ostream& out, const Edge& e);
};


///////////////////////////////////////////////////////////////////////////////
// EdgeIterator class

class EdgeIterator
{
public:
  // Constructor takes the list of edges over which to iterate
  EdgeIterator(std::list<Edge *> &edges);

  // Return true if another edge remains to be returned, or false otherwise
  bool hasNext() const;

  // Return the next edge and increment the iterator
  Edge *nextEdge();

protected:
  std::list<Edge *>::iterator i;
  std::list<Edge *>::const_iterator end;
};


///////////////////////////////////////////////////////////////////////////////
// Graph class

class Graph
{
public:
  // Destructor frees allocated memory for the graph
  ~Graph();

  // Add the vertex with the given label and weight to the graph
  void addVertex(int label, double weight = 0);

  // Add an edge from vertex with label "from" to vertex with label "to"
  void addEdge(int from, int to);

  // Run DFS traversal, starting at vertex with label s
  void dfsTraversal(int s);

protected:
  hash_map<int, Vertex *> vertices;   // vertices in graph
  std::list<Edge *> edges;            // edges in graph
  void dfsTraversal(Vertex* v);       // recursively-implemented DFS
};


#endif /* GRAPH_H */

