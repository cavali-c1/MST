//================================================================
// SparseGraph.cpp
// Tomer Osmo, Daniel Chu and Caroline Cavalier
// April 2024
// This is the SparseGraph.cpp file contains the derived SparseGraph class. 
// The implementation utilizes an array of linked lists via the stl.
// The SparseGraph.cpp file includes the following methods : 
// copy constructor, default constructor, destructor, assignment operator,
// isEdge, getWeight and insertEdge.
// Important to note that differences in output within file may occur
// if the input graph is directed or undirected, depending on the 
// input of the user. 
//================================================================

#include "SparseGraph.h"
#include <stdexcept>
#include <limits>
#include <queue>
//===========================================
// Default constructor
// this method creates and initialize a SparseGraph object with default parameters. 
// params: none
// return value: none
//===========================================
SparseGraph::SparseGraph(void) : \
    Graph(DEFAULT, 0), adj_list(DEFAULT) {}
//===========================================
// Default constructor
// this method creates and initialize a SparseGraph object with vertices and edges.
// params: vertices, edges
// return value: none
//===========================================
SparseGraph::SparseGraph(const int V, const int E) : \
    Graph(V, E), adj_list(V) {}
//===========================================
// copy constructor
// this method creates a copy of the SparseGraph object. 
// params: const Graph &gp
// return value: none
//===========================================
SparseGraph::SparseGraph(const SparseGraph &other) : \
    Graph(other.vert_count, other.edge_count), adj_list(other.adj_list) {}
//===========================================
// assignment operator
// this method creates a new SparseGraph object with same vertices 
// and edges.
// params: const sparseGraph &gp
// return value: SparseGraph object. 
//===========================================
SparseGraph& SparseGraph::operator=(const SparseGraph &other) {
    if (this != &other) {
        vert_count = other.vert_count;
        edge_count = other.edge_count;
        adj_list = other.adj_list;
    }
    return *this;
}
//===========================================
// isEdge
// this method is a boolean function which returns true if there is an edge from 
// v1 to v2. Will throw exception if input vertices are invalid. 
// params: two vertices - v1, v2. 
// return value: boolean value
//===========================================
bool SparseGraph::isEdge(const int v1, const int v2) const {
    if (v1 >= vert_count or v2 >= vert_count or v1 < 0 or v2 < 0)
        throw std::invalid_argument("isEdge - Invalid Vertices");

    for (const auto& edge : adj_list[v1]) {
        if (edge.first == v2)
            return true;
    }
    return false;
}
//===========================================
// getWeight
// this method returns the weight from the edge from v1 to v2. 
// The method will throw an exception if there is no edge or if the vertices
// are invalid. 
// params: two vertices - v1, v2. 
// return value: the weight for the edge from v1 to v2. 
//===========================================
int SparseGraph::getWeight(const int v1, const int v2) const {
    if (v1 >= vert_count or v2 >= vert_count or v1 < 0 or v2 < 0)
        throw std::invalid_argument("getWeight - Invalid Vertices");
    if (!isEdge(v1,v2)) return -1;

    int w = -1;
    for (const auto& edge : adj_list[v1]) {
        if (edge.first == v2) {
            w = edge.second;
            break;
        }
    }
    return w;
}
//===========================================
// insertEdge
// this method inserts a new edge into the graph
// throws an exception if the two vertices or the weight are invalid.
// params: two vertices - v1, v2 and the weight value. 
// return value: none.
//===========================================
void SparseGraph::insertEdge(const int v1, const int v2, int w) {
    if (v1 >= vert_count or v2 >= vert_count or v1 < 0 or v2 < 0)
        throw std::invalid_argument("insertEdge - Invalid Vertices");
    if (w < 0) 
        throw std::invalid_argument("insertEdge - Invalid Weight");

    adj_list[v1].emplace_back(v2, w);

    #ifndef DIRECTED_GRAPH
    adj_list[v2].emplace_back(v1, w);
    #endif
}
//===========================================
// BFS
// implementation of a breadth first search algorithim
// params: source vertex
// return value: none.
//===========================================
void SparseGraph::BFS(int source) {
    if (source < 0 or source > vert_count - 1)
        throw std::invalid_argument("BFS - source out of range");

    table["color"].assign(vert_count, 0); //0: W, 1: G, 2: B
    table["dist"].assign(vert_count, std::numeric_limits<int>::infinity());
    table["pred"].assign(vert_count, -1); //-1: NIL

    table["color"][source] = 1;
    table["dist"][source] = 0;
    table["pred"][source] = -1;

    std::queue<int> Q;
    Q.push(source);

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        for (const auto& edge : adj_list[u]) {
            if (table["color"][edge.first] == 0) {
                table["color"][edge.first] = 1;
                table["dist"][edge.first] = table["dist"][u] + 1;
                table["pred"][edge.first] = u;
                Q.push(edge.first);
            }
        }
        table["color"][u] = 2;
    }
}
//===========================================
// DFS
// implementation of the depth first search algorithm
// params: none.
// return value: none.
//===========================================
void SparseGraph::DFS(void) {
    dfs_edges.clear();

    table["color"].assign(vert_count, 0); //0: W, 1: G, 2: B
    table["pred"].assign(vert_count, -1); //-1: NIL
    table["disc"].assign(vert_count, -1);
    table["f"].assign(vert_count, -1);

    int time = 0;
    for (size_t i=0; i < vert_count; ++i) {
        if (table["color"][i] == 0)
            DFS_Visit(i, time);
    }
}
 //===========================================
// DFS_Visit
// implementation of the depth first search visit algorithm. 
// used as helper function to be used in the above DFS algorithm, searches through all adjacent vertices. 
// params: int v and clock time.
// return value: none.
//===========================================
void SparseGraph::DFS_Visit(int v, int &clock) {
    clock++;

    table["disc"][v] = clock;
    table["color"][v] = 1;

    for (const auto& edge : adj_list[v]) {
        dfs_edges.emplace_back(std::make_pair(v, edge.first));

        if (table["color"][edge.first] == 0) {
            table["pred"][edge.first] = v;
            DFS_Visit(edge.first, clock);
        }
    }
    clock++;
    table["f"][v] = clock;
    table["color"][v] = 2;
}