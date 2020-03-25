/*------------------------------------
# Ryan Bresnahan 1602641
# CMPT464 Assignment as1.c
# Instructor:  Dr. Ron Meleshko
*-----------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>
#include<string.h>
#include"adjmat.h"

// Creates adjacency matrix from user input until "0 0 0" is detected
// Prints matrix upon exiting
int main(int argc, char **argv) {
	int c;

	AdjMatrix mat = createAdjMat(50);

	// Loop for node and edge input from user
	while(1) {
		int node1, node2, cost;
		char input[16];
		scanf("%[^\n]s", input);
		sscanf(input, "%d %d %d", &node1, &node2, &cost);
		getchar();

		// Break out of while loop if 0, 0, 0 is entered
		if(node1 == 0 && node2 == 0 && cost == 0)
			break;

		addAdjMat(mat, node1, node2, cost);
		addToSet(node1, node2);

	}

	// Check for additional command line arguments
	while((c = getopt (argc, argv, "a")) != -1)
		switch(c) {
			case 'a':
				printf("Adjacency Matrix:\n\n");
				printAdjMat(mat);
				break;
			}

	printf("\nDistance\n\n");

	getShortestPaths(mat);

	return 0;
}
