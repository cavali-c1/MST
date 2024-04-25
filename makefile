all: main

main: main.cpp Graph.cpp Graph.h DenseGraph.h DenseGraph.cpp SparseGraph.h SparseGraph.cpp DisjointSet.h DisjointSet.cpp
	g++ -std=c++20 -o main main.cpp Graph.cpp DenseGraph.cpp SparseGraph.cpp DisjointSet.cpp 
