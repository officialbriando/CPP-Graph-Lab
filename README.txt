CPSC 350 Graph Lab

Notes:
- The graph will be based off the adjacency matrix class.
- Assumes that the graph is composed only of nodes which do not contain any data other then their label.
- Labels are set as ints.
- The graph is directed & unweighted.
    - Because there are no weights, Primm's and Dijkstra's algorithm will only return subtrees based on the first encountered edge.
- The adjacency matrix returned for the subtree returned from Prim's Algorithm goes across and then down (still works properly).
- Prim's Algorithm method will most likely not work for unconnected graphs at this point (since any nodes with no edges incident will never be marked visited).


References:
http://www.sanfoundry.com/cpp-program-implement-adjacency-matrix/
    - Used to research member variable of an AdjacencyMatrix class.
    

All other algorithms self-coded.
