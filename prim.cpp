/*
 * CSC-301
 * prim.cpp
 * Fall 2024
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
 * Pre-condition: The input is an initialized and true vector of costs of edges. 'Visited vector' contains booleans of whether vertex is visited or not.
 * Post-condition: The function returns the index of the vertex with the lowest cost that has not been visited.
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
 * Pre-condition: 'Visited' vector contains booleans of whether vertex is visited or not.visited vector
 * Post-condition: Returns boolean of whether function has unvisited vectors (true) or not (false)
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
 * Implements prim algorithm. Finds the MST given adjeciency matrix and list.
 * Pre-conditions: Receives adjeciency list - vector of all vertecies where each vertex represents its index. And adjeciency matix - that contains information about the costs between each vertecies in the adjeciency list.
 * Post-condition: Returns complete list of edges contained in MST and assigns proper mstNeighbors to each vertex.
 */
vector<Edge> prim(vector<Vertex> &adjList, vector<double> &adjMat) {
  vector<Edge> mst;
  int n = adjList.size();
  vector<bool> visited(n, false);
  vector<double> cost(n, numeric_limits<double>::infinity());
  vector<int> prev(n, -1);
  
  cost[0] = 0; 
  prev[0] = -1;
  
  while (!isEmpty(visited)) {
    int u = getMin(cost, visited);
    if (u == -1){
      break;
    }//if the min is not found, do not continue
    
    Vertex current = adjList[u];
    visited[u] = true;
    
    if (prev[u] != -1) {
      Edge newEdge(adjList[prev[u]], current, cost[u]);
      mst.push_back(newEdge);
      adjList[prev[u]].mstNeighbors.push_back(current.label);
      adjList[current.label].mstNeighbors.push_back(prev[u]);
    }// if the previous vertex is not the root
    
    for (int neigh : current.neighbors) {
      double edgeWeight = adjMat[u * n + neigh];
      if (!visited[neigh] && edgeWeight < cost[neigh]) {
        cost[neigh] = edgeWeight;
        prev[neigh] = u;
      }//if the neighbor is unvisited, update it
    }//for
    
  }//while
  
  return mst;
}
