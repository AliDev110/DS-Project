/*
	Ali Raza
	20I-0782
	Sec D
	Project
*/

#ifndef TREE_H_
#define TREE_H_

#include <iostream>
#include <string>
#include "TreeNode.cpp"
#include "LinkedList.h"


class Tree
{
	TreeNode* root;
	int noOfNodes;	//represents the number of leaf nodes containing characters

public:

	//Constructor
	Tree();

	//Delete Tree
	void DelTree(TreeNode*);

	//Setters
	void setRoot(TreeNode*);
	void setNoOfNodes(int);

	//Getters
	TreeNode* getRoot();
	int getNoOfNodes();

	//Utility
	TreeNode* createNode(char, int); //create new node
	bool find(TreeNode*, char);
	void insertFromFile(char);

	//Output
	void Inorder(TreeNode*);	//For testing
	void PrintCode(TreeNode*, LinkedList*, double*);

	//Testing
	

};



#endif

