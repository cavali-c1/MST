//================================================================
// DenseGraph.h
// Tomer Osmo, Daniel Chu and Caroline Cavalier
// April 2024
// This file is the header file for the implementation of the DenseGraph
// class. Contains the declaration for the methods within the 
// DenseGraph class in the .cpp file. 
//================================================================

#include "Graph.h"
#include<tuple>
#include <set>

#ifndef DENSEGRAPH_H
#define DENSEGRAPH_H

class DenseGraph : public Graph {
    private:
        std::vector<std::vector<int>> matrix;
    public:
        DenseGraph(void); // default constructor
        DenseGraph(const int V, const int E); //constructor with vertices and edges.
        DenseGraph(const DenseGraph &other); //copy constructor

        DenseGraph& operator=(const DenseGraph &other); //asignment operator

        void insertEdge(const int v1, const int v2, int w) override; //insertEdge
        bool isEdge(const int v1, const int v2) const override; // isEdge
        int getWeight(const int v1, const int v2) const override; //getWeight

        //BFS-based Algorithms
        void BFS(int source) override; // breadth first search

        //DFS-based Algorithms
        void DFS(void) override; // depth first search
        void DFS_Visit(int v, int &clock) override; // depth first search visi (helper function for DFS)
        
       // project 7 algorithms 
        DenseGraph*     MST_Prim (void) override;
};

#endif