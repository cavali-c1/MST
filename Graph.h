//===============================
// Graph.h
// Name: Tomer Osmo, Caroline Cavalier and Daniel Chu
// April 2024. 
// This file is the header file that contains the
// declaration of the virtual Graph class. 
//===============================
#include <iostream>
#include <vector>
#include <map>
#include <string>

//Dependencies
#include <stdexcept>
#include <limits>
#include <queue>
#include <utility>
#include <set>
#include <tuple>
#include "DisjointSet.h"

#ifndef GRAPH_H
#define GRAPH_H

const int DEFAULT = 10;

class Graph {
    protected:
        int vert_count;
        int edge_count;

        //Information table
        std::map<std::string, std::vector<int>> table;

        //Helper to store edges in DFS
        std::vector<std::pair<int, int>> dfs_edges;
        std::set <std::tuple<int,int,int>> edges;
    public:
        //Constructors (STL handles initialization of table and dfs_edges)
        Graph   (void) : vert_count(DEFAULT), edge_count(0) {}
        Graph   (const int V, const int E) : vert_count(V), edge_count(E) {}
        Graph   (const Graph &myGraph);

        //Destructor (No memory management needed)
        virtual ~Graph(void) {}

        //cin cout
        friend std::ostream& operator<<(std::ostream &os, const Graph &g);
        friend std::istream& operator>>(std::istream &is, Graph &g);

        //Basic funcs
        virtual bool    isEdge      (const int v1, const int v2) const = 0;
        virtual void    insertEdge  (const int v1, const int v2, int w) = 0;
        virtual int     getWeight   (const int v1, const int v2) const = 0;

        //BFS-based Algorithms
        virtual void    BFS             (int source) = 0;
        void            printBFSTable   (int source);
        void            printBFSPath    (int s, int d);
        void            printMostDistant(int s);
        bool            isConnected     (void); 

        //DFS-based Algorithms
        virtual void    DFS                     (void) = 0;
        virtual void    DFS_Visit               (int v, int &clock) = 0;
        void            printDFSTable           (void);
        void            printTopologicalSort    (void);
        void            printDFSParenthesization(void);
        void            classifyDFSEdges        (void);

        //Helper
        int size(void) const { return vert_count; }

        struct sortbythird {
            bool operator()(const std::tuple<int, int, int>& a,  const std::tuple<int, int, int>& b) const
            { 
            return (std::get<2>(a) > std::get<2>(b)); 
            }
        };

        //Project 7 algorithms:
        virtual Graph*  MST_Prim (void) = 0;
        virtual Graph*  MST_Kruskal (void) = 0;
        int mass(void);
};

#endif