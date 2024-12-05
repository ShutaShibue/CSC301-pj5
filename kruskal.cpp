/*
 * CSC-301
 * kruskal.cpp
 * Fall 2022
 *
 * Partner 1: Shuta Shibue
 * Partner 2: Gabriela Roznawska
 * Date: 2024/12/04
 */

#include "kruskal.hpp"

using namespace std;

/*
 * find
 * finds the parent of a given vertex within a set
 * Pre-conditions: v is a valid vertex within a set, and vector pi contains information about parent of each vertex
 * Post-conditons: Returns the parent of a vertex v
 */
int find(int v, vector<int> &pi) {
  if (pi[v] != v) {
    pi[v] = find(pi[v], pi);
  }//path compression
  return pi[v];
}//find


/*
 * union_by_rank
 * Unionizes two vectors according to their rank
 * Pre-condition: Input of two indexes that represent verticies within the vector. Rank contains information about ranking, and pi contains information about parents
 * Post-condition: Unionizes the two vectors (trees)
 */
void union_by_rank(int u, int v, vector<int> &rank, vector<int> &pi) {
  int root_u = find(u, pi);
  int root_v = find(v, pi);
  // if u and v are not in the same set
  if (root_u != root_v) {
    // set the parent of u to v
    if (rank[root_u] < rank[root_v]) {
      pi[root_u] = root_v;
    } else if (rank[root_u] > rank[root_v]) {
      // set the parent of v to u
      pi[root_v] = root_u;
    } else {
      // if the rank of u and v are the same then set the parent of v to u
      pi[root_v] = root_u;
      // increment the rank of u
      rank[root_u]++;
    }// else
  }// if
}// union_by_rank

/*
 * kruskal
 * Performs the krukal algorithm
 *
 * Pre-conditions:
 * adjList: adjacency list of the graph
 * edgeList: edge list of the graph, sorted by weight
 * Post-confitions: Outputs vector of edges in the MST. Assigns proper mstNeighbors to every vertex.
 */
vector<Edge> kruskal(vector<Vertex> &adjList, vector<Edge> &edgeList) {
  // Initialize the empty MST.
  vector<Edge> mst;
    
  // For each vertex, we need rank values and pi pointers (ints) for the
  // Disjoint Sets. Initialize the rank to 0 and pi to be the vertex labels.
  int n = adjList.size();
  vector<int> rank(n, 0);
  vector<int> pi(n);
  for (int i=0; i<pi.size(); i++) {
    pi[i] = i;
  }//for

  for(auto &edge : edgeList){
    int u = edge.first.label;
    int v = edge.second.label;
    
    // if u and v are not in the same set
    if(find(u, pi) != find(v, pi)){
      // add the edge to the MST
      mst.push_back(edge);
      // union the sets of u and v
      union_by_rank(u, v, rank, pi);
      // add v to u's mst neighbors
      adjList[u].mstNeighbors.push_back(v);
       // add u to v's mst neighbors
      adjList[v].mstNeighbors.push_back(u);
    }//if
  }//for

  return mst;
}//kruskal
