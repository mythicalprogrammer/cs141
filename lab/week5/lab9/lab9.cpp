// CS-141 Lab 9 sample solution for DFS traversal - main

#include <iostream>
#include <sstream>

#include "graph.h"

using namespace std;

int main()
{
  // Read in number of vertices and edges
  int numVertices, numEdges;
  char comma;
  cin >> numVertices >> comma >> numEdges;

  // Throw away end-of-line whitespace
  string line;
  getline(cin, line);

  // Declare a graph
  Graph g;

  // Read vertices and add to graph
  for (int i = 0; i < numVertices; ++i)
  {
    getline(cin, line);
    istringstream iss(line);
    int label;
    char semicolon;
    double weight = 0;    // use 0 if no weight present
    iss >> label >> semicolon >> weight;
    g.addVertex(label, weight);
  }

  // Read edges and add to graph
  for (int i = 0; i < numEdges; ++i)
  {
    int v1, v2;
    cin >> v1 >> comma >> v2;
    g.addEdge(v1, v2);
  }

  // Output dot prologue
  cout << "digraph G {\n";

  // Perform DFS, starting at vertex 0
  g.dfsTraversal(0);

  // Output dot epilogue
  cout << "}\n";

  // All done
  return 0;
}

