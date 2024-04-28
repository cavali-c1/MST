//================================================================
// DenseGraph.cpp
// Tomer Osmo, Daniel Chu and Caroline Cavalier
// April 2024
// This is the DenseGraph.cpp file contains the derived DenseGraph class. 
// The implementation utilizes a matrix structure.
// The DenseGraph.cpp file includes the following methods : 
// copy constructor, default constructor, destructor, assignment operator,
//  isEdge, getWeight and insertEdge.
// Important to note that differences in output within file may occur
// if the input graph is directed or undirected, depending on the 
// input of the user. 
//================================================================

#include "DenseGraph.h"

//===========================================
// Default constructor
// this method creates and initialize a denseGraph object
// params: none
// return value: none
//===========================================
DenseGraph::DenseGraph(void) : \
    Graph(DEFAULT, 0), matrix(DEFAULT, std::vector<int>(DEFAULT, -1)) {}

//===========================================
// Default constructor
// this method creates and initialize a denseGraph object
// params: vertices, edges
// return value: none
//===========================================
DenseGraph::DenseGraph(const int V, const int E) : \
    Graph(V, E), matrix(V, std::vector<int>(V, -1)) {}

//===========================================
// copy constructor
// this method creates and initialize a denseGraph object
// params: const Graph &gp
// return value: none
//===========================================

DenseGraph::DenseGraph(const DenseGraph &other) : \
    Graph(other.vert_count, other.edge_count), matrix(other.matrix) {}

//===========================================
// assignment operator
// this method creates a new denseGraph with same vertices 
// and edges and returns the new object.
// params: const denseGraph &gp
// return value: denseGraph object. 
//===========================================
DenseGraph& DenseGraph::operator=(const DenseGraph &other) {
    if (this != &other) {
        vert_count = other.vert_count;
        edge_count = other.edge_count;
        matrix = other.matrix;
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
bool DenseGraph::isEdge(const int v1, const int v2) const {
    if (v1 >= vert_count or v2 >= vert_count or v1 < 0 or v2 < 0)
        throw std::invalid_argument("isEdge - Invalid Vertices");

    return matrix[v1][v2] >= 0;
}
//===========================================
// getWeight
// this method returns the weight fro the edge from v1 to v2. 
// The method will throw an exception if there is no edge or if the vertices
// are invalid. 
// params: two vertices - v1, v2. 
// return value: the weight for the edge from v
int DenseGraph::getWeight(const int v1, const int v2) const {
    if (v1 >= vert_count or v2 >= vert_count or v1 < 0 or v2 < 0)
        throw std::invalid_argument("getWeight - Invalid Vertices");
    if (!isEdge(v1,v2)) return -1;

    return matrix[v1][v2];
}
 //===========================================
// insertEdge
// this method inserts a new edge into the graph
// throws an exception if the two vertices or the weight are invalid.
// params: two vertices - v1, v2 and the weight value. 
// return value: none.
//===========================================

void DenseGraph::insertEdge(const int v1, const int v2, int w) {
    if (v1 >= vert_count or v2 >= vert_count or v1 < 0 or v2 < 0)
        throw std::invalid_argument("insertEdge - Invalid Vertices");
    if (w < 0) 
        throw std::invalid_argument("insertEdge - Invalid Weight");

    if (matrix[v1][v2] == -1) {
        matrix[v1][v2] = w;

        #ifndef DIRECTED_GRAPH
        matrix[v2][v1] = w;
        #endif
    }
}

 //===========================================
// BFS
// implementation of a breadth first search algorithim
// params: source vertex
// return value: none.
//===========================================

void DenseGraph::BFS(int source) {
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

        for (int i=0; i < vert_count; ++i) {
            if (table["color"][i] == 0 and isEdge(u, i)) {
                table["color"][i] = 1;
                table["dist"][i] = table["dist"][u] + 1;
                table["pred"][i] = u;
                Q.push(i);
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

void DenseGraph::DFS(void) {
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
void DenseGraph::DFS_Visit(int v, int &clock) {
    clock++;

    table["disc"][v] = clock;
    table["color"][v] = 1;
    
    for (int i=0; i < vert_count; ++i) {
        if (isEdge(v, i)) {
            dfs_edges.emplace_back(std::make_pair(v, i));

            if (table["color"][i] == 0) {
                table["pred"][i] = v;
                DFS_Visit(i, clock);
            }
        }
    }
    clock++;
    table["f"][v] = clock;
    table["color"][v] = 2;
}

DenseGraph* DenseGraph::MST_Prim(){

    DenseGraph* mst_graph = new DenseGraph(vert_count, edge_count);
    std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, sortbythird> pq;

    std::set<int> inset;
    std::set<int> outset;

    inset.insert(0);
    for (int i = 1; i < vert_count; ++i)
        outset.insert(i);

    for (int i = 1; i < vert_count; ++i) {
        if (matrix[0][i] >= 0) 
            pq.push(std::make_tuple(0, i, matrix[0][i]));
    }

    while (!outset.empty() && !pq.empty()) {
        auto uvw = pq.top();
        pq.pop();

        int u = std::get<int>(uvw);
        int v = std::get<int>(uvw);
        int w = std::get<int>(uvw);

        if ((inset.count(u) && outset.count(v)) || (inset.count(v) && outset.count(u))) {
            mst_graph->insertEdge(u, v, w);
            mst_graph->insertEdge(v, u, w); 

           
            int new_vertex = outset.count(v) ? v : u;   
            inset.insert(new_vertex);
            outset.erase(new_vertex);
            
            for (int i = 0; i < vert_count; ++i) {
                if (outset.count(i) && matrix[new_vertex][i] >= 0)
                    pq.push(std::make_tuple(new_vertex, i, matrix[new_vertex][i]));
            }
        }
    }

    return mst_graph;
}