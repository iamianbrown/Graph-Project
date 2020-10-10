# Graph-Project
In this project I implemented a matrix representation of a graph, Dijkstra's algorithm (using a heap data structure), Kruskal's algorithm, and Prim's algorithm

Graph.h
This is the file where I define my Graph class, which includes the connectivity matrix, random graph generation capability, plus all of my algorithm methods.

Tree.h
This is where I define my Tree class, the return type of both Kruskal and Prim's algorithms. Note that the algorithms themselves are defined in the Graph class, 
since they are methods which act on Graph.

Utils.h
This is where I define my global functions that are not related to the Graph or Tree data types.
