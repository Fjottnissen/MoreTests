/* 
Name: Odd-Arild Kristensen
net-id: ok552888
<<<<<<< HEAD
new line 1
=======
new line 2
>>>>>>> b
*/

// Includes the standard I/O library in the programme
#include <stdio.h>
// Includes the standard library in the programme
#include <stdlib.h>
// Includes the string library in the programme
#include <string.h>
// Includes a customly made file that contains the constants used in this programme
#include "constants.h"
// Inclued a customly made file that contains the structure definitions and its alias
#include "struct_def.h"
// Inclued a customly made file that contains the externally defined global variables
#include "externs.h"
// Inclued a customly made file that contains all the prototypes used in this programme
#include "prototypes.h"

/* File that contains all the auxillery functions needed to make the programme run.
These functions do not manipulate the tree in any way, bur rather accesses it only.
*/

/*
Function that finds the height of a tree, either a complete tree, or a subtree.
It uses recursion to calculate the height of the tree.

For a certain node, the function recursively calls itself on the node's children
to get the height for its subtree's. It returns the longest path of the two children
and adds one because it would constitute another path in the tree.

@treeNode The node symbolysing the root of the tree or subtree that we want to find the height to
*/

int heightOfTree(NODE *treeNode) {
	// Declares variables to store the height of the left and right subtrees.
	int leftTreeHeight, rightTreeHight;
	// Checks if there is no node to check
	if(treeNode == NULL) {
		// Returns 0 if there is no node, there is no new edge to count.
		return 0;
	}
	// Checks if there is an actual node and if it is a leaf node. It has no children
	else if(treeNode != NULL && (treeNode->leftChild == NULL && treeNode->rightChild == NULL) ) {
		// Returns 0 if it is a leaf node, this way a tree where the root is a leaf, the tree's height is 0
		return 0;
	}
	// If treenNode exists and is not a leaf node, find find the tallest height of treeNode's subtrees
	else {
		// Recursive call to heightOfTree to find the height of treeNode's left subtree
		leftTreeHeight = heightOfTree(treeNode->leftChild);
		// Recursive call to heightOfTree to find the height of treeNode's right subtree
		rightTreeHight = heightOfTree(treeNode->rightChild);
		// Checks if the left subtree is the tallest
		if(leftTreeHeight > rightTreeHight) {
			// Returns the height of the left subtree pluss, including treeNode's height - 1
			return leftTreeHeight + 1;
		} 
		// The right subtree was the tallest
		else {
			// Returns the height of the right subtree pluss, including treeNode's height - 1
			return rightTreeHight + 1;
		}
	}
}

/*
Function that calculates the number of leaf nodes in the tree or subtree.
Uses recursion to move through the tree and check if a node is a leaf.

@treeNode Node that potentially is a leaf. Originally the root of the tree
*/

int numOfLeaves(NODE *treeNode) {
	// Checks if treeNode is NULL, if we have moved outside of the tree
	if(treeNode == NULL) {
		// Returns 0 if we have moved outside the tree, there is no leaf here
		return 0;
	}
	// Checks if treeNode have not children, i.e. it is a leaf node
	else if(treeNode->leftChild == NULL && treeNode->rightChild == NULL) {
		// Returns 1 if treeNode is a leaf
		return 1;
	}
	/* If treeNode is either an internal node or the root, find the number of leaves in
	treeNode's subtrees.
	*/
	else {
		/* Returns the sum of all the leaves in treeNode's subtrees. This is done with a 
		recursive call to numOfLeaves on treeNode's left and right children, which would
		eventually reach all the nodes, including the leaves, in the tree.
		*/
		return numOfLeaves(treeNode->leftChild) + numOfLeaves(treeNode->rightChild);
	}
}

/*
Function that finds the number of strings in a tree or subtree by using recursion.

The function assumes that the tree is filled with nodes that contain valid strings,
no node contain an empty string. As such, the function visits every node in the tree
and returns 1 for every node it visits, and thus, the number of strings.

@treeNode The node that contain the string
*/

int numOfStrings(NODE *treeNode) {
	// Checks if the current node is indeed a node
	if(treeNode == NULL) {
		// If we have moved outside the tree, return 0 - it contains no string
		return 0;
	} // We are at a node and do recursive calls to numOfStrings
	else {
		/* Makes two recursive calls to numOfStrings, one on treeNode's left and right child.
		It returns the sum of their results, and 1 for the this node's string,
		which should be the total number of strings in this particular tree/subtree.
		*/
		return ( numOfStrings(treeNode->leftChild) + numOfStrings(treeNode->rightChild) + 1);
	}
}

/*
Function that reads all the strings in a given file and inserts the read strings into a 
binary tree. 

The function uses fscanf to read strings, which are assumed to be no longer than 
15 characters, exluding the string termination character. The strings are put into the
tree by calling insert.

When done, the function returns the number of read strings, which should correspond to
all of the nodes / strings in the tree.

@inFile The input file that we are reading from
*/

int readFile(FILE *inFile) {
	// Declares a string to temporarely store the read string before inserting it to the tree
	char string[STRING_LENGTH];
	// Declares a variable to store the number of strings read
	int readStrings;
	// Initializes the number of strings read to zero
	readStrings = 0;
	// Checks if there is a a string in the file.
	if( fscanf(inFile, "%s", string) != 1) {
		// If there is no string in the file, print an error message
		fprintf(stderr, "The input file did not contain any strings to read.\n");
		// Exit the programme
		exit(1);
	}
	// If control comes here, there is at least one string in the file, and it is inserted
	insert(string, &root);
	// Increments the number of strings read
	readStrings++;
	// Loop that reads all the strings in the input file, if any
	while( fscanf(inFile, "%s", string) == 1) {
		// Inserts the last read string into the tree
		insert(string, &root);
		// Increments the number of strings read counter
		readStrings++;
	}
	// All strings have been read, and the number of strings read is returned
	return readStrings;
}
