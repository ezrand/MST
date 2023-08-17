#include "Graphm.h"
#include <iostream> 
#include <fstream>

using namespace std;

const int vertices = 6;

//Function declarations 
void mst(Graphm* graph, int num, int vert);
int minVertex(Graphm* G, int* D);
void Prim(Graphm* G, int* D, int s);

int main()
{
	//create the graph, read in the graph from the file, display it, and then search it with the mst function starting at the specified vertex
	Graphm * mstGraph = new Graphm(vertices);
	mstGraph->graphIn("input.txt");
	mstGraph->graphOut();
	mst(mstGraph, 1, 0);

	//create the graph, read in the graph from the file, display it, and then search it with the mst function starting at the specified vertex
	Graphm* mstGraph1 = new Graphm(vertices);
	mstGraph1->graphIn("input.txt");
	mstGraph1->graphOut();
	mst(mstGraph1, 2, 4);

	//create the graph, read in the graph from the file, display it, and then search it with the mst function starting at the specified vertex
	Graphm* mstGraph2 = new Graphm(vertices);
	mstGraph2->graphIn("input.txt");
	mstGraph2->graphOut();
	mst(mstGraph2, 3, 2);
	
	system("pause");
	return 0;
}

void mst(Graphm * graph, int num, int vert) //Helper function to consolodate graph initialization 
{
	cout << "Begin MST " << num << " starting at Vertex " << vert << endl; 
	//new array of ints, with a for loop to intialize it
	int* D = new int[vertices];
	for (int i = 0; i < vertices; i++)
	{
		D[i] = INFINITY;
	}
	//Vertex searching from is set to 0 as it costs nothing to reach
	D[vert] = 0;
	//Graph, ints, and vertex read in to Prim algorithm
	Prim(graph, D, vert);
	cout << "End of MST " << num << endl << endl;
}

//Code taken and adapted from Data Structures and Algorithms Analysis in C++ by Clifford A. Shaffer
//Adapted by Ezra Anderson 04/17/2023
int minVertex(Graphm* G, int* D) { // Find min cost vertex
	int i, v = -1;
	// Initialize v to some unvisited vertex
	for (i = 0; i < G->n(); i++)
		if (G->getMark(i) == UNVISITED) { v = i; break; }
	for (i++; i < G->n(); i++) // Now find smallest D value
		if ((G->getMark(i) == UNVISITED) && (D[i] < D[v]))
			v = i;
	return v;
}

void Prim(Graphm* G, int* D, int s) { // Prim’s MST algorithm
	//newGraph and V added and altered from textbook so it could be outputted to the file
	Graphm * newGraph = new Graphm(vertices);
	int* V = new int [vertices];
	int i, w;
	for (int i = 0; i < G->n(); i++) // Initialize
		D[i] = INFINITY;
	D[s] = 0;
	for (i = 0; i < G->n(); i++) { // Process the vertices
		int v = minVertex(G, D);
		G->setMark(v, VISITED);
		if (v != s)
		{
			cout << "Adding edge " << V[v] << " to " << v << endl; 
			//adding the edge twice so it is undirected
			newGraph->setEdge(v, V[v], D[v]); // Add edge to MST
			newGraph->setEdge(V[v], v, D[v]); //Add edge to MST
		}
		if (D[v] == INFINITY) return; // Unreachable vertices
		for (w = G->first(v); w < G->n(); w = G->next(v, w))
			if (D[w] > G->weight(v, w)) {
				D[w] = G->weight(v, w); // Update distance
				V[w] = v; // Where it came from
			}
	}
	newGraph->graphFile("vertex.txt", s);
	newGraph->graphOut();
}