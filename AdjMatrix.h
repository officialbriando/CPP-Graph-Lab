using namespace std;

class AdjMatrix
{
	private:
		int numNodes;	//Used to initialize the matrix and other collections.

	  //char* nodeLabels;	  Array used to keep track of node labels, should you want one.
		bool* wasVisited;	//Array used to mark visited nodes.

		int** matrix; 		//2D int array used as the matrix; ints will be 0/1 for unweighted edges.
		int** primsMatrix;
	public:
		AdjMatrix(int n);
		~AdjMatrix();

		void setEdge(int source, int dest);
		void inputEdges();
		void runDFS();
		void runPrims();
		void runDijkstras();

		void resetVisited();
};
