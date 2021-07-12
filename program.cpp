/**
 * depth-first search
 * Jon Beck
 */
#include <iostream>
#include <list>
#include <vector>
#include "graph.h"
using namespace std;

/**
 * the routine to start at node u and go as far as possible without cycling
 * @param g the adjacency lists graph
 * @param start_vertex the starting vertex
 * @param visited the global list of already-visited vertices
 */
void explore(const Graph& g, size_t start_vertex, vector<bool>& visited);

/**
 * the dfs algorithm proper
 * @param g the graph to run dfs on
 */
void dfs(const Graph& g);

/**
 * previsit: for now, just report
 * @param vertex the vertex we are previsiting
 */
void previsit(size_t vertex);

/**
 * postvisit: for now, just report
 * @param vertex the vertex we are postvisiting
 */
void postvisit(size_t vertex);

/**
 * utility function to provide a "global" counter, incremented
 * each time the function is called
 * @return the next counter value
 */
size_t get_clock();

int main()
{
  // declare a graph and read it in from standard input
  Graph g;
  g.read_graph();

  g.dump(); // just so we can see the contents of the graph

  dfs(g);
  return 0;
}

void explore(const Graph& g, size_t start_vertex, vector<bool>& visited)
{
  // set this vertex as visited, and get its adjacency list
  visited.at(start_vertex) = true;
  previsit(start_vertex);

  list<size_t> list_of_adjacent_vertices {g.get_list(start_vertex)};

  // go through start_vertex's adjacency list, exploring each unvisited
  // vertex one by one
  for (auto vertex : list_of_adjacent_vertices)
  {
    if (!visited.at(vertex))
    {
      explore(g, vertex, visited);
    }
  }
  postvisit(start_vertex);
}

void dfs(const Graph& g)
{
  cout << "starting dfs";
  vector<bool> visited(g.size(), false);

  size_t connected_component_counter {0};

  for (size_t vertex {0}; vertex < g.size(); vertex++)
  {
    if (!visited.at(vertex))
    {
      cout << endl << "Connected component: " <<
        connected_component_counter << endl;
      connected_component_counter++;
      explore(g, vertex, visited);
    }
  }
  cout << endl << "finished dfs" << endl;
}

void previsit(size_t vertex)
{
  cout << '+'<< vertex << ' ' << to_string(get_clock()) << ' ';
}

void postvisit(size_t vertex)
{
  cout << '-'<< vertex << ' ' << to_string(get_clock()) << ' ';
}

size_t get_clock()
{
  static size_t clock {0};
  return ++clock;
}
