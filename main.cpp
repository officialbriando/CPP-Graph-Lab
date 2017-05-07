#include "AdjMatrix.h"
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
	int numNodes;
	cout << "How many nodes are in the graph?: "; cin >> numNodes;

	AdjMatrix matrix(numNodes);
	matrix.inputEdges();
	matrix.runDFS();
	matrix.runPrims();
	matrix.runDijkstras();
	
	return 0;
}