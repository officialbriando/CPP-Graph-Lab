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
			matrix[i][j] = 0;			// Defaults every weight in the matrix to 0.
		}
	}
}

AdjMatrix::~AdjMatrix() {}

void AdjMatrix::setEdge(int source, int dest)				//Setting unweighted edges.
{
	if(source > numNodes || source < 0 || dest > numNodes || dest < 9)	//Error checking to prevent ArrayIndexOutOfBounds.
	{
		cout << "This is not a valid edge." << endl;
	}
	else
	{
		matrix[source -1][dest - 1] = 1;					//Sets the corresponding slot in the matrix to one.
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

	int order = 0;							//Index for discovered array.

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
			if(matrix[current - 1][i] == 1)
			{
				if(wasVisited[i] == false)
				{
					current = ++i;			//If there is an unvisited adjacent node, sets that to current
					nextNode = true;		//and indicates that the search has progressed.

					nodeStack.push(current);		//Pushes the current node onto a stack.
					break;					
				}							
			}
		}

		if(!nextNode)						//If there are no unvisited edges, pops a node off the stack and
		{									//sets current node to the top of the stack.
			nodeStack.pop();
			if(nodeStack.isEmpty() == 1)	//Stops the search once there is nothing left in the stack.
			{
				done = true;
			}
			else
			{
				current = nodeStack.peek();
			}
		}
	}

	cout << "The order of discovered nodes using Depth First-Search is: " << endl;
	for(int i = 0; i <= order; ++i)
	{
		cout << discovered[i] << " -> ";
	}
}