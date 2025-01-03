/*
 * CSC-301
 * kruskal.hpp
 * Fall 2022
 *
 * Partner 1: Shuta Shibue
 * Partner 2: Gabriela Roznawska
 * Date: 2024/12/04
 */

#ifndef KRUSKAL_HPP_
#define KRUSKAL_HPP_

#include "Vertex.hpp"
#include "Edge.hpp"

/*
 * find
 */
int find(int v, std::vector<int> &pi);

/*
 * union_by_rank
 */
void union_by_rank(int u, int v, std::vector<int> &rank, std::vector<int> &pi);

/*
 * kruskal
 */
std::vector<Edge> kruskal(std::vector<Vertex> &adjList, 
                          std::vector<Edge> &edgeList);

#endif  // KRUSKAL_HPP_