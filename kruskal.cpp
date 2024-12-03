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
 */
int find(int v, vector<int> &pi) {
    if (pi[v] != v) {
        pi[v] = find(pi[v], pi); // path compression
    }
    return pi[v];
}

/*
 * union_by_rank
 */
void union_by_rank(int u, int v, vector<int> &rank, vector<int> &pi) {
    int root_u = find(u, pi);
    int root_v = find(v, pi);
    if (root_u != root_v) { // if u and v are not in the same set
        if (rank[root_u] < rank[root_v]) {
            pi[root_u] = root_v; // set the parent of u to v
        } else if (rank[root_u] > rank[root_v]) {
            pi[root_v] = root_u; // set the parent of v to u
        } else { // if the rank of u and v are the same
            pi[root_v] = root_u; // set the parent of v to u
            rank[root_u]++; // increment the rank of u
        }
    }
}

/*
 * kruskal
 * adjList: adjacency list of the graph
 * edgeList: edge list of the graph, sorted by weight
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
    }

    for(auto &edge : edgeList){
        int u = edge.first.label;
        int v = edge.second.label;
        if(find(u, pi) != find(v, pi)){ // if u and v are not in the same set
            mst.push_back(edge); // add the edge to the MST
            union_by_rank(u, v, rank, pi); // union the sets of u and v
            adjList[u].mstNeighbors.push_back(v); // add v to u's mst neighbors
            adjList[v].mstNeighbors.push_back(u); // add u to v's mst neighbors
        }
    }

    return mst;
}