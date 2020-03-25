/*------------------------------------
# Ryan Bresnahan 1602641
# CMPT464 Assignment as1.c
# Instructor:  Dr. Ron Meleshko
*-----------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"adjmat.h"

#define MAXNODES 100
int nodeSet[MAXNODES] = {'\0'};
int visited[MAXNODES] = {0};

// Allocate space for an adjacency list
AdjMatrix createAdjMat(int size) {
	AdjMatrix mat = calloc(size, sizeof(struct adjlistnode*));
	return mat;
}

// Assume routes are non directed and require two entries for in the
// adjacency list
void addAdjMat(AdjMatrix adjMat, int n1, int n2, int cost) {

	// Add route of initial order
	struct adjlistnode *newNode1 = calloc(1, sizeof(struct adjlistnode));
	newNode1->node = n2;
	newNode1->cost = cost;
	newNode1->next = adjMat[n1];
	adjMat[n1] = newNode1;

	// Add route of reverse order
	struct adjlistnode *newNode2 = calloc(1, sizeof(struct adjlistnode));
	newNode2->node = n1;
	newNode2->cost = cost;
	newNode2->next = adjMat[n2];
	adjMat[n2] = newNode2;
}

// Adds source and destination nodes to the unique node set
void addToSet(int node1, int node2) {
	nodeSet[node1] = node1;
	nodeSet[node2] = node2;
}

// Iterate the adjacency list and output current entries by starting node
void printAdjMat(AdjMatrix mat) {
	for(int i = 0; i < MAXNODES; i++) {
		struct adjlistnode *p = mat[i];
		while(p != NULL) {
			printf("(%d %d %d)", i, p->node, p->cost);
			p = p->next;
			if(p == NULL) printf("\n");
		}
	}
}

// Using Dijkstra's shortest pathing algorithm calculate and display the total
// distance each reachable node is from the base node and output the path to
// each.
void getShortestPaths(AdjMatrix mat) {

	//Create distance table with default distances at infinity aside from start
	distListNode* distTable = malloc(MAXNODES * sizeof(distListNode*));

	for(int i = 0; i < MAXNODES; i++) {
		if(mat[i] != NULL) {
			distTable[i].id = i;
			distTable[i].prev = -1;
		}
		else 
			distTable[i].id = -1;
		distTable[i].dist = INFINITY;
	}
	distTable[0].dist = 0;

	// While nodes have been unvisited find lowest unvisited distance and
	// update distance of neighbouring nodes
	while(unvisitedExist()) {

		int current;
		float smallest = INFINITY;

		for(int i = 0; i < MAXNODES; i++) {
			if((distTable[i].dist < smallest) && (notInVisited(i))) {
				current = i;
				smallest = distTable[i].dist;
			}
		}

		// Update distances of neighbours
		struct adjlistnode *p = mat[current];
		while(p != NULL) {
			int newDist = distTable[current].dist + p->cost;
			if(newDist < distTable[p->node].dist) {
				distTable[p->node].dist = newDist;
				distTable[p->node].prev = current;
			}
			p = p->next;
		}

		// Mark current node as visited
		visited[current] = 1;
		free(p);
	}

	// Print the distances to each node
	for(int i = 0; i < MAXNODES; i++) {
		if(distTable[i].id >= 0)
			printf("source to %d is %d\n", i, distTable[i].dist);
	}

	printf("\nPaths\n\n");

	//Print the paths to each node by adding the route to a stack array
	for(int i = 1; i < MAXNODES; i++) {
		if(distTable[i].id >= 0) {
			int stack[MAXNODES], elem = 0;
			int p = distTable[i].id;
			while(p != -1) {
				stack[elem] = p;
				elem++;
				p = distTable[p].prev;
			}
			while(--elem >= 0)
				printf("%d ", stack[elem]);
			printf("\n");
		}
	}
	printf("\n");
}

// Return 1 if an element from the nodeSet is not found in the visited set,
// return 0 if all elements are accounted for.
int unvisitedExist() {
	for(int i = 0; i < MAXNODES; i++) {
		if((nodeSet[i] != '\0') && (visited[i] == 0))
			return 1;
	}
	return 0;
}

// Accepts index and checks to see if flag 0 exists to indicate whether it
// has been visited, and returns 1 if true. Confusing, yes.
int notInVisited(int n) {
	if(visited[n] == 0)
		return 1;
	else
		return 0;
}
