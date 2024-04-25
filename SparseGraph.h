//================================================================
// SparseGraph.h
// Tomer Osmo, Daniel Chu and Caroline Cavalier
// April 2024
// This file is the header file for the implementation of the SparseGraph
// class. Contains the declaration for the methods within the derived
// SparseGraph class. 
//================================================================

#include "Graph.h"
#include <list>

#ifndef SPARSEGRAPH_H
#define SPARSEGRAPH_H

class SparseGraph : public Graph {
   
    private:
   //adjacency list for sparse implementation.
        std::vector<std::list<std::pair<int,int>>> adj_list;
    public:
    //Constructors 
        SparseGraph(void);
        SparseGraph(const int V, const int E);
        SparseGraph(const SparseGraph &other);
    // Assignment Operators
        SparseGraph& operator=(const SparseGraph &other);
    //Basic functions
        void insertEdge(const int v1, const int v2, int w) override;
        bool isEdge(const int v1, const int v2) const override;
        int getWeight(const int v1, const int v2) const override;

        //BFS-based Algorithms
        void BFS(int source) override;

        //DFS-based Algorithms
        void DFS(void) override;
        void DFS_Visit(int v, int &clock) override;
};

#endif