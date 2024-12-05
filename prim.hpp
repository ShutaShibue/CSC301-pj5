/*
 * CSC-301
 * prim.hpp
 * Fall 2022
 *
 * Partner 1: Shuta Shibue
 * Partner 2: Gabriela Roznawska
 * Date: 2024/12/04
 */

#ifndef PRIM_HPP_
#define PRIM_HPP_

#include "Vertex.hpp"
#include "Edge.hpp"

/*
 * getMin
 */
int getMin(std::vector<double> &cost, std::vector<bool> &visited);

/*
 * isEmpty
 */
bool isEmpty(std::vector<bool> &visited);

/*
 * prim
 */
std::vector<Edge> prim(std::vector<Vertex> &adjList, 
                       std::vector<double> &adjMat);

#endif  // PRIM_HPP_