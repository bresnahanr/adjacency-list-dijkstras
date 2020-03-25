#ifndef ADJMAT_H
#define ADJMAT_H
/*
 * The adjacency matrix is stored as an array of linked lists of type
 * struct adjlistnode.  The ith entry in the array is the list of nodes (and their 
 * costs) that are adjacent to node i.
 */
typedef struct adjlistnode {
	int node;
	int cost;
	struct adjlistnode * next;
} *AdjList;

/*
 * Data structure used to calculate the shortest path between base node and
 * discovered node.
 */
typedef struct {
	int id;
	int dist;
	int prev;
} distListNode; 

typedef AdjList *AdjMatrix;

/*
 * Dynamically create an adjacency matrix using the int parameter as the
 * default size.
 */
AdjMatrix createAdjMat(int);

/* 
 * Add the edge from n1 to n2 having cost to the adjacency matrix.
 */
void addAdjMat(AdjMatrix, int n1, int n2, int cost);

/*
 * Print out the adjacency list as a series of ordered triples.
 * Each line cooresponds to one node in the graph.
 */
void printAdjMat(AdjMatrix);

/*
 * Adds source and destination nodes to the unique node set
*/
void addToSet(int node1, int node2);

/*
 * Using Dijkstra's shortest pathing algorithm calculate and display the total
 * distance each reachable node is from the base node and output the path to
 * each.
 */
void getShortestPaths(AdjMatrix mat);

/*
 * Return 1 if an element from the nodeSet is not found in the visited set,
 * return 0 if all elements are accounted for.
 */
int unvisitedExist();

/*
 * Accepts index and checks to see if flag 0 exists to indicate whether it
 * has been visited, and returns 1 if true. Confusing, yes.
 */
int notInVisited(int n);
#endif 
