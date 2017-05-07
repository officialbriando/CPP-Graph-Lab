#include "AdjMatrix.h"
#include "GenStack.h"
#include <iostream>

using namespace std;

AdjMatrix::AdjMatrix(int n)			//Constructor for the matrix class.
{
	numNodes = n;
	wasVisited = new bool[numNodes];		//Initialized visited array with number of nodes.
	for(int i = 0; i < numNodes; ++i)
	{
		wasVisited[i] = false;			//Defaults every node to unvisited.
	}

	matrix = new int*[numNodes];			//Initialized a new array of arrays to set up matrix.
	for(int i = 0; i < numNodes; ++i)
	{
		matrix[i] = new int[numNodes];
		for(int j = 0; j < numNodes; ++j)
		{
			matrix[i][j] = 0;			// Defaults every edge in the matrix to 0.
		}
	}

	primsMatrix = new int*[numNodes];			
	for(int i = 0; i < numNodes; ++i)
	{
		primsMatrix[i] = new int[numNodes];
		for(int j = 0; j < numNodes; ++j)
		{
			primsMatrix[i][j] = 0;			
		}
	}
}

AdjMatrix::~AdjMatrix() {}

void AdjMatrix::setEdge(int source, int dest)				//Setting unweighted edges.
{
	if(source > numNodes || source < 1 || dest > numNodes || dest < 1)	//Error checking to prevent ArrayIndexOutOfBounds.
	{
		cout << "This is not a valid edge." << endl;
	}
	else
	{
		matrix[source - 1][dest - 1] = 1;					//Sets the corresponding slot in the matrix to 1.
	}
}

void AdjMatrix::inputEdges()
{
	cout << "Enter edges (source index followed by destination index). Enter -1 for both to stop." << endl;

	bool done = false;
	while(!done)		//Keeps prompting for edges while done is false.
	{
		int source; int dest;

		cout << "Enter edge: ";
		cin >> source >> dest;

		if(source == -1 && dest == -1)		//Exit condition.
		{
			done = true;
			continue;
		}

		setEdge(source, dest);				//Calls setEdge() from above.
	}
}

void AdjMatrix::runDFS()
{
	int startNode;
	cout << "Choose a node (#) to start a depth first-search of your graph: ";
	cin >> startNode;

	GenStack<int> nodeStack(numNodes);		//Initializes a stack used for DFS algorithm.

	int discovered[numNodes];				//Keeps track of nodes in order of discovery.
	for(int i = 0; i < numNodes; ++i)
	{
		discovered[i] = 0;
	}

	int order = 0;							//Index for discovered nodes array.

	int current = startNode;

	bool done = false;
	while(!done)
	{
		if(wasVisited[current - 1] == false)
		{
			discovered[order] = current;
			order++;
		}

		wasVisited[current - 1] = true;		//Marks the current node as visited (will only change unvisited nodes).

		bool nextNode = false;
		for(int i = 0; i < numNodes; ++i)
		{
			if(matrix[current - 1][i] != 0)
			{
				if(wasVisited[i] == false)
				{
					nodeStack.push(current);		//Pushes the current node onto a stack.
					
					current = ++i;			//If there is an unvisited adjacent node, sets that to current
					nextNode = true;		//and indicates that the search has progressed.

					break;					
				}							
			}
		}

		if(!nextNode)						//If there are no unvisited edges, pops a node off the stack and
		{									//sets current node to it.
			if(nodeStack.isEmpty())	//Stops the search once there is nothing left in the stack.
			{
				done = true;
			}
			else
			{
				current = nodeStack.pop();
			}
		}
	}

	cout << "The order of discovered nodes using Depth First-Search is: " << endl;
	for(int i = 0; i <= order; ++i)
	{
		if(discovered[i] > 0 && discovered[i] <= numNodes)
		{
			cout << discovered[i] << " -> ";	//Prints out the order of discovered nodes.			
		}
	}
	cout << endl;
}

void AdjMatrix::runPrims()
{
	resetVisited();
	int discovered[numNodes];
	for(int i = 0; i < numNodes; ++i)
	{
		discovered[i] = 0;
	}
	int order = 0;
	
	int startNode;
	cout << "Choose a node (#) to start a Prim's Algorithm analysis: ";
	cin >> startNode;

	bool done = false;
	int sourceNode;

	wasVisited[startNode - 1] = true;
	discovered[order] = startNode;
	order++;

	while(!done)
	{
		int cheapestNode = numNodes + 1;			//Initializes the cheapest Node to an unexisting node (guarantees all existing nodes will be lower index).
		int cheapestNodeWeight = 1000;				//Initializes the cheapest NodeWeight to 1000 (assuming all edges in the graph are <1000).

		for(int i = 0; i < numNodes; ++i)		//Searches through all discovered nodes for the cheapest adjacent node.
		{
			if(discovered[i] != 0)							
			{
				for(int j = 0; j < numNodes; ++j)
				{
					if((matrix[discovered[i]-1][j] != 0) && (wasVisited[j] != true))		
					{
						if(matrix[discovered[i]-1][j] < cheapestNodeWeight)
						{
							sourceNode = discovered[i] - 1;
							cheapestNodeWeight = matrix[discovered[i]-1][j];
							cheapestNode = j;
						}
					}
				}
			}
		}
		discovered[order] = cheapestNode + 1; order++;
		primsMatrix[sourceNode][cheapestNode] = cheapestNodeWeight;
		wasVisited[cheapestNode] = true;
		done = true;
		for(int i = 0; i < numNodes; ++i)
		{
			if(wasVisited[i] == false)
			{
				done = false;
				break;
			}
		}
	}

	cout << "The order of discovered nodes using Prim's Algorithm is: " << endl;
	for(int i = 0; i < numNodes; ++i)
	{
		if(discovered[i] != 0)
		{
			cout << discovered[i] << " -> ";
		}
	}
	cout << endl;

	cout << "The adjacency matrix for Prim's Algorithm subtree is: " << endl;
	for(int i = 0; i < numNodes; ++i)
	{
		for(int j = 0; j < numNodes; ++j)
		{
			cout << primsMatrix[i][j] << "   ";
		}
		cout << endl << endl;
	}
}

void AdjMatrix::runDijkstras()
{
	resetVisited();
	int discovered[numNodes];
	for(int i = 0; i < numNodes; ++i)
	{
		discovered[i] = 0;
	}
	int order = 0;

	int startNode;
	cout << "Choose a node (#) to start a Dijkstra's Algorithm analysis: ";
	cin >> startNode;

	int prevNode = startNode;
	int current = startNode;

	int distance = 0;

	bool done = false;

	while(!done)
	{
		if(wasVisited[current - 1] != true)
		{
			wasVisited[current - 1] = true;
			discovered[order] = current;
			order++;
		}

		bool adjacentNodes = false;					//Checks if there are any existing adjacent nodes.
		for(int i = 0; i < numNodes; ++i)
		{
			if(matrix[current - 1][i] != 0)
			{
				adjacentNodes = true;
				break;
			}
		}
		if(!adjacentNodes)
		{
			if(current = startNode)
			{
				done = true;
			}
			else
			{
				current = prevNode;
			}
			continue;
		}


		bool allNodesVisited = true;
		for(int i = 0; i < numNodes; ++i)
		{
			if(matrix[current - 1][i] != 0)
			{
				if(wasVisited[i] == false)
				{
					allNodesVisited = false;
				}
			}
		}	
		if(allNodesVisited)
		{
			done = true;
			continue;
		}


		int cheapestNode = numNodes + 1;
		int cheapestNodeWeight = 1000;

		for(int i = 0; i < numNodes; ++i)
		{
			if((matrix[current - 1][i] != 0) && (wasVisited[i] == false) && (matrix[current - 1][i] < cheapestNodeWeight))
			{
				cheapestNode = i;
				cheapestNodeWeight = matrix[current - 1][i];
			}
		}

		prevNode = current;
		current = cheapestNode + 1;
		distance += cheapestNodeWeight;
	}

	cout << "The order of discovered nodes using Dijkstra's algorithm is: " << endl;
	for(int i = 0; i < numNodes; ++i)
	{
		if(discovered[i] != 0)
		{
			cout << discovered[i] << " -> ";
		}
	}
	cout << endl;
	cout << "The distance is: " << distance << endl;
}

void AdjMatrix::resetVisited()
{
	for(int i = 0; i < numNodes; ++i)
	{
		wasVisited[i] = false;			//Defaults every node to unvisited.
	}
}
