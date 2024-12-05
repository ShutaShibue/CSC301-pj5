/*
 * CSC-301
 * prim.cpp
 * Fall 2022
 *
 * Partner 1: Shuta Shibue
 * Partner 2: Gabriela Roznawska
 * Date: 2024/12/04
 */

#include "prim.hpp"
#include <limits>
using namespace std;

/*
 * getMin
 * Loops over vectors in "cost" array. Returns the index of the vertex with the smallest cost that has not yet been visited.
 */
int getMin(vector<double> &cost, vector<bool> &visited) {
  int min = -1;
  double minCost = numeric_limits<double>::infinity();
  for (int i=0; i<cost.size(); i++){
      if (!visited[i] && (cost[i] < minCost)){
      min = i;
      minCost = cost[i];
    }//if
  }//for
  return min;
}//getMin

/*
 * isEmpty
 * Checks if all verticies were visited. If so, returns "true" - the queue is empty and there is no more verticies to visit. If any vertex has not been visited, it returns "false".
 *
 */
bool isEmpty(vector<bool> &visited) {
  for(int i=0; i<visited.size(); i++){
    if(!visited[i]){
      return false;
    }//if
  }//for
  return true;
}

/*
 * prim
 */
vector<Edge> prim(vector<Vertex> &adjList, vector<double> &adjMat) {
  // Initialize the empty MST.
  vector<Edge> mst;
  
  int n = adjList.size();
  vector<bool> visited(n, false);
  vector<double> cost(n, numeric_limits<double>::infinity());
  vector<int> prev(n, -1);
  
  cost[0] = 0; 
  prev[0] = -1;
  
  while (!isEmpty(visited)) {
    int u = getMin(cost, visited);
    if (u == -1) break; // if
    Vertex current = adjList[u];
    visited[u] = true;
    
    if (prev[u] != -1) { // if the previous vertex is not the root
      Edge newEdge(adjList[prev[u]], current, cost[u]);
      mst.push_back(newEdge);
      newEdge.printEdge();
    }//if
    
    for (int neigh : current.neighbors) {
      double edgeWeight = adjMat[u * n + neigh];
      if (!visited[neigh] && edgeWeight < cost[neigh]) {
        cost[neigh] = edgeWeight;
        prev[neigh] = u;
      }//if
    }//for
  }//while
  
  return mst;
}
