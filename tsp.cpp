/*
 * CSC-301
 * tsp.cpp
 * Fall 2022
 *
 * Partner 1: Shuta Shibue
 * Partner 2: Gabriela Roznawska
 * Date: 2024/12/04
 */

#include "tsp.hpp"

using namespace std;

/*
 * tsp
 */
vector<int> tsp(vector<Vertex> &adjList, Vertex &start) {
    // Create the empty tour.
    vector<int> tour;
    
    // Create the vector for tracking visited during the DFS.
    int n = adjList.size();
    vector<bool> visited(n, false);


    // Create the stack for the DFS
    stack<Vertex> s;
    s.push(start);

    while (!s.empty()) {
        Vertex current = s.top();
        s.pop();
        int current_label = current.label;
        if (!visited[current_label]) {
            visited[current_label] = true;
            tour.push_back(current_label);

            // Add all the neighbors to the stack
            for (int neighbor : adjList[current_label].mstNeighbors) {
                if (!visited[neighbor]) {
                    s.push(adjList[neighbor]);
                }
            }
        }
    }

    // Add the start vertex to the tour to complete the cycle.
    tour.push_back(start.label);

    return tour;
}
