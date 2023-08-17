//Code taken and adapted from Data Structures and Algorithms Analysis in C++ by Clifford A. Shaffer
//Adapted by Ezra Anderson 04/17/2023
#pragma once
#include "GraphADT.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <istream> 
#include <string> 
#include <memory>
#define VISITED 1
#define UNVISITED 0
#define INFINITY 9999

// Implementation for the adjacency matrix representation
class Graphm : public Graph {
private:
	int numVertex, numEdge; // Store number of vertices, edges
	int** matrix; // Pointer to adjacency matrix
	//Smart pointers used for the mark, column, and row 
	std::unique_ptr<int[]> mark; // Pointer to mark array
	std::unique_ptr<int> column;
	std::unique_ptr<int> row;
public:
	Graphm(int numVert) // Constructor
	{
		//altered from textbook to initalize the smart pointers
		column = std::make_unique<int>(numVert);
		row = std::make_unique<int>(numVert);
		mark = std::make_unique<int[]>(numVert);
		Init(numVert);
	}
	~Graphm() { // Destructor
		//delete[] mark; // Return dynamically allocated memory
		for (int i = 0; i < numVertex; i++)
			delete[] matrix[i];
		delete[] matrix;
	}

	void Init(int n) { // Initialize the graph
		int i;
		numVertex = n;
		numEdge = 0;
		for (int i = 0; i < numVertex; i++)
			mark[i] = UNVISITED;
		matrix = (int**) new int* [numVertex]; // Make matrix
		for (i = 0; i < numVertex; i++)
			matrix[i] = new int[numVertex];
		for (i = 0; i < numVertex; i++) // Initialize to 0 weights
			for (int j = 0; j < numVertex; j++)
				matrix[i][j] = 0;
	}
	int n() { return numVertex; } // Number of vertices
	int e() { return numEdge; } // Number of edges
	// Return first neighbor of "v"
	int first(int v) {
		for (int i = 0; i < numVertex; i++)
			if (matrix[v][i] != 0) return i;
		return numVertex; // Return n if none
	}
	// Return v’s next neighbor after w
	int next(int v, int w) {
		for (int i = w + 1; i < numVertex; i++)
			if (matrix[v][i] != 0)
				return i;
		return numVertex; // Return n if none
	}
	// Set edge (v1, v2) to "wt"
	void setEdge(int v1, int v2, int wt) {
		//altered the assert statement from the textbook, checks if the weight is less than 0, and if it is not, will continue to run
		if (wt < 0)
			std::cout << "Illegal weight value" << std::endl;
		if (matrix[v1][v2] == 0) numEdge++;
		matrix[v1][v2] = wt;
	}
	void delEdge(int v1, int v2) { // Delete edge (v1, v2)
		if (matrix[v1][v2] != 0) numEdge--;
		matrix[v1][v2] = 0;
	}
	bool isEdge(int i, int j) // Is (i, j) an edge?
	{
		return matrix[i][j] != 0;
	}
	int weight(int v1, int v2) { return matrix[v1][v2]; }
	int getMark(int v) { return mark[v]; }
	void setMark(int v, int val) { mark[v] = val; }

	//Three helper functions added
	void graphIn(std::string file) //graphIn checks the file name, initalizes the adjancency matrix 
	{
		std::ifstream inFile;
		inFile.open(file);
		while (!inFile)
		{
			inFile.close();
			std::cout << "File failed to open." << std::endl << "Enter the file name again: ";
			std::string fileName;
			std::cin >> fileName;
			file = fileName;
			inFile.open(file);
		}

		//variable initialization
		int** array;
		int num;
		array = new int* [*column];

		//Nested for loop, first a row is created, and then the coloumn is looped through
		for (int i = 0; i < *row; i++)
		{
			array[i] = new int[*row];
			for (int j = 0; j < *column; j++)
			{
				//The numbers from the file are inputted into each row and column of the matric
				inFile >> num;
				array[i][j] = num;
				//Then set edge is called with the location and weight
				setEdge(i, j, num);
			}
		}	
	}

	void graphOut() //outputs graph to the terminal
	{
		std::cout << "Number of vertices: " << n() << std::endl;
		//Because the graph is undirected, divide the number of edges by 2 to display the correct number of edges
		std::cout << "Number of edges: " << e() / 2 << std::endl;
		std::cout << "Matrix is: " << std::endl;
		//same nested for loop logic from the graphIn file, 
		for (int i = 0; i < *row; i++)
		{
			//goes to each row and loops through the entire column before continuing to the next row
			for (int j = 0; j < *column; j++)
			{
				std::cout << matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}


	void graphFile(std::string file, int vert) //outputs graph to the .txt file
	{
		
		std::ofstream outFile;
		//Uses the vertex read in to create a file with the vertex searched from in the name
		std::string fileName = std::to_string(vert) + file;
		outFile.open(fileName);
		//Same function as graphOut, swapped with the ofstream outFile to output too the .txt file
		for (int i = 0; i < *row; i++)
		{
			//goes to each row and loops through the entire column before continuing to the next row
			for (int j = 0; j < *column; j++)
			{
				outFile << matrix[i][j] << " ";
			}
			outFile << std::endl;
		}
		outFile << std::endl;
	}
};

