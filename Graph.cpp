//================================================================
// Graph.cpp
// Tomer Osmo, Daniel Chu and Caroline Cavalier
// April 2024
// This is the Graph.cpp file that implements the virtual base Graph Class.
// This file includes the following methods : 
// default constructor, copy constructor, destructor, assignment operator,
// cin and cout operators.
//================================================================
#include "Graph.h"
#include <tuple>
#include <iomanip>
#include <algorithm>
//===========================================
// cin
// this method reads in a graph
// params: istream &is, Graph &gp
// return value: a reference to the input stream. 
//===========================================
std::istream& operator>>(std::istream &is, Graph &gp) {
    int v1, v2, weight;

    for (int i=0; i < gp.edge_count; ++i){
        if (!(is >> v1 >> v2 >> weight)) {
            if (!is.eof())
                throw std::runtime_error("operator>> - Error reading edge data");
            else  
                break;
        }
        gp.insertEdge(v1,v2, weight);       
    }
    return is;
}
//===========================================
// cout
// this method prints a graph
// params: ostream &os, const Graph &gp
// return value: a reference to the output stream. 
//===========================================
std::ostream& operator<<(std::ostream &os, const Graph &gp) {
    os << "G= (" << gp.vert_count << ", " << gp.edge_count << ") "<< std::endl;
    for (int i=0; i < gp.vert_count; ++i){
        for(int j=0; j < gp.vert_count; ++j){
            if (gp.isEdge(i, j))
            os << i << " " << j << " "<< gp.getWeight(i,j) << std::endl;
        }
    }
    return os;
}
//===========================================
// printBFSTable
// this method prints the table resulting from the BFS search algorithm
// params: source vertex
// return value: nothing.
//===========================================
void Graph::printBFSTable(int source) {
    if (table.size() != 3)
        throw std::runtime_error("printBFSTable - Invalid Table");

    for (int i=0; i < vert_count; ++i) {
        std::cout << "[" << std::setw(3) << std::setfill(' ') << i << "]: " << "dist: " 
                  << std::setw(2) << std::setfill(' ') << table["dist"][i] << "   pred: " 
                  << std::setw(2) << std::setfill(' ') << table["pred"][i] << std::endl; 
    }
}
//===========================================
// printBFSPath
// this method prints the path of vertices from the BFS path.
// params: int s and int d.
// return value: nothing.
//===========================================
void Graph::printBFSPath(int s, int d) {
    std::cout << this->size() << std::endl; 
    // account for invalid table and non-existed path
    if (table.size() != 3)  
        throw std::runtime_error("printBFSPath - Invalid Table");
    if (table["dist"][d] == std::numeric_limits<int>::infinity()) {
        std::cout << "No such path" << std::endl;
        return;
    }
    std::vector<int> path;  // create a vector for tha path
    int curr = d;           // store d in curr

    while (curr != s) {     // populate the path vector using the predecessor.
        path.insert(path.begin(), curr);
        curr = table["pred"][curr];
    }
    path.insert(path.begin(), s);

    for (const auto& vert : path)
        std::cout << "v" << vert << " ";
    std::cout << std::endl;
}
//===========================================
// printMostDistant
// this method prints the vertices/ vertex that are farthest from the input source vertex
// in the graph.
// params: int s.
// return value: nothing.
//===========================================
void Graph::printMostDistant(int s) {
    //account for invalid input source
    if (s < 0 or s > vert_count - 1)
        throw std::invalid_argument("printMostDistant - Invalid Source");
    if (table.size() != 3)
        throw std::runtime_error("printMostDistant - Invalid Table");

    int max = -1;
    std::vector<int> indices;

    // every time we find a vertex that its distance bigger than max, we clear the vector
    // and append the vertex. If it is equal to max, then we just append the vertex
    // to the vector.
    for (int i=0; i < vert_count; ++i) { 
        if (table["dist"][i] > max) {
            max = table["dist"][i];
            indices.clear(); 
            indices.emplace_back(i);
        } 
        else if (table["dist"][i] == max)
            indices.emplace_back(i);
    }
    for (int index : indices) {
        std::cout << "v" << index << " ";
    }
    std::cout << "dist=" << max - s << std::endl;
}

//===========================================
// isConnected
// this method returns a boolean value to indicate whether the input graph is connected or not.
// params: nothing.
// return value: boolean value.
//===========================================

bool Graph::isConnected(void) {
    if (table.size() != 3)  
        throw std::runtime_error("isConnected - Invalid Table");

    if (vert_count == 0)
        return false;
    
    for (int i=0; i < vert_count; ++i) {
        if (table["color"][i] == 0)     // if the color of any vertex is white it means the graph is not connected.
            return false;
    }
    return true;
} 
//===========================================
// printDFSTable
// this method print the DFS table that is created when the DFS algorithim is called on a source vertex.
// return value: nothing.
// params: none. 
//===========================================
void Graph::printDFSTable(void) {
    if (table.size() != 4)
        throw std::runtime_error("printDFSTable - Invalid Table");

    for (int i=0; i < vert_count; ++i) {
        std::cout << "[" << std::setw(3) << std::setfill(' ') << i << "]: "
                  << "dist: " << std::setw(2) << std::setfill(' ') << -1
                  << "   pred: " << std::setw(2) << std::setfill(' ') << table["pred"][i]
                  << "  (" << table["disc"][i] << "," << table["f"][i] << ")" << std::endl;
    }
}

//===========================================
// printTopologicalSort
// this method prints the vertices after they are sorted in topological order.
// return value: none.
// params: none. 
//===========================================
void Graph::printTopologicalSort(void) {
    if (table.size() != 4)
        throw std::runtime_error("printTopologicalSort - Invalid Table");

    std::vector<std::pair<int, int>> topo_sort;

    for (int i=0; i < vert_count; ++i)
        topo_sort.emplace_back(std::make_pair(table["f"][i], i)); // create vector of pairs with  the finish time and the according vertex

    std::sort(topo_sort.begin(), topo_sort.end(), std::greater<std::pair<int, int>>()); // sort the pairs from biggest to lowest 

    for (int i=0; i < topo_sort.size(); ++i) {
        std::cout << "v" << topo_sort[i].second;    // print the vector after the topological sort.

        if (i != topo_sort.size() - 1)
            std::cout << " > ";
    }
    std::cout << std::endl;
}
//===========================================
// printDFSParenthesization
// this method prints the Parenthesization structure resulting from the DFS algorihtim called on a source vertex.
// return value: nothing.
// params: none. 
//===========================================
void Graph::printDFSParenthesization(void) {
    if (table.size() != 4)
        throw std::runtime_error("printDFSParenthesization - Invalid Table");

    std::vector<std::tuple<int, int, int>> paren;

    // build vector of tuples of three elements: discovery/finish time, vertex, 0/1 indicates discovery of finish
    for (int i=0; i < vert_count; ++i) {
        paren.emplace_back(std::make_tuple(table["disc"][i], i, 0));
        paren.emplace_back(std::make_tuple(table["f"][i], i, 1));
    }
    std::sort(paren.begin(), paren.end());

    // check if discover or finish and print accordignly.
    for (const auto& x : paren) {
        if (std::get<2>(x) == 0)
            std::cout << "(v" << std::get<1>(x) << " ";
        else
            std::cout << "v" << std::get<1>(x) << ") ";
    }
    std::cout << std::endl;
}
//===========================================
// classifyDFSEdges
// this method classifes each of the given edges in a graph into four different categories including forward, backward, cross edge and 
// tree edge,
// return value: nothing.
// params: none. 
//===========================================
void Graph::classifyDFSEdges(void) {
    if (dfs_edges.size() == 0)
        throw std::runtime_error("classifyDFSEdges - No Edges");
    if (table.size() != 4)
        throw std::runtime_error("classifyDFSEdges - Invalid Table");

    for (const auto& edge : dfs_edges) {
        std::cout << "Edge (v" << edge.first << ",v" << edge.second << ") is a ";
        // if u.d < v.d < v.f < u.f then tree/forward edge
        if (table["disc"][edge.second] > table["disc"][edge.first] and table["f"][edge.second] < table["f"][edge.first])
            std::cout << "tree/forward edge" << std::endl;
        // if v.d < u.d < u.f < v.f then tree/forward edge
        if (table["disc"][edge.second] < table["disc"][edge.first] and table["f"][edge.second] > table["disc"][edge.first])
            std::cout << "back edge" << std::endl;
        // v.d < v.f < u.d < u.f .
        if (table["f"][edge.second] < table["disc"][edge.first] or table["disc"][edge.second] > table["f"][edge.first])
            std::cout << "cross edge" << std::endl;
    }
}
