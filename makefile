all: main

main: main.cpp Graph.cpp Graph.h SparseGraph.h SparseGraph.cpp # DenseGraph.h DenseGraph.cpp DisjointSet.h DisjointSet.cpp
	g++ -std=c++17 -o main main.cpp Graph.cpp SparseGraph.cpp # DenseGraph.cpp DisjointSet.cpp 
