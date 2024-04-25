//================================================================
// Matt Kretchmar
// April 2024
// main.cpp
// This file assumes the A-level implementation for Project 6
// and the A-level implementation for Project 7.  Comment out
// the parts that won't work with your choices.
//================================================================

#include "Graph.h"
//#include "DenseGraph.h"       // remove this for B-level
#include "SparseGraph.h"      // remove this for B-level
#include <iostream>
using namespace std;

int main ( void )
{
   Graph *gp, *mstp, *mstk;

   int nv, ne;
   cin >> nv >> ne;
   // For Project 6 A-level, test both the sparse and dense implementations
   // of MST algorithms, but leave it with the sparse implementation.
   //gp = new DenseGraph(nv,ne);
   gp = new SparseGraph(nv,ne);

   // For Project 6 B-level, test this instead
   //gp = new Graph(nv,ne);

   cin >> (*gp);
   cout << "Printing the graph that was read in:\n";
   cout << (*gp);

   // required for Project 7 A and B level
   cout << endl << endl;
   mstp = gp->MST_Prim();
   cout << "MST (Prim) is: \n";
   cout << (*mstp) << endl;
   //cout << "MST mass = " << mstp->mass() << endl;

   // for A-level on Project 7
   // comment this out if you only implement Prim
   //cout << endl << endl;
   //mstk = gp->MST_Kruskal();
   //cout << "MST (Kruskal) is: \n";
   //cout << (*mstk) << endl;
   //cout << "MST mass = " << mstk->mass() << endl;

   // remove graphs
   delete gp;
   delete mstp;
   //delete mstk;      // comment out if not used
   return 0;
}
