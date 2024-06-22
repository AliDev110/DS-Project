/*
	Ali Raza
	20I-0782
	Sec D
	Project
*/

#ifndef TREE_NODE_CPP_
#define TREE_NODE_CPP_

#include <iostream>

using namespace std;

class TreeNode
{
	char chr;
	int freq;
	TreeNode* lnode;
	TreeNode* rnode;

public: 


	//==============================================================
	//Constructor

	TreeNode()
	{
		freq = 1;
		lnode = NULL;
		rnode = NULL;
	}

	//==============================================================
	//Setters

	void setRightNode(TreeNode* r)
	{
		rnode = r;
	}

	//---------------------------------------

	void setLeftNode(TreeNode* l)
	{
		lnode = l;
	}

	//---------------------------------------

	void setChr(char k)
	{
		chr = k;
	}

	//---------------------------------------

	void setFreq(int f)
	{
		freq = f;
	}


	//==============================================================
	//Getters

	TreeNode* getRNode()
	{
		return rnode;
	}

	//---------------------------------------

	TreeNode* getLNode()
	{
		return lnode;
	}

	//---------------------------------------

	char getChr()
	{
		return chr;
	}

	//---------------------------------------

	int getFreq()
	{
		return freq;
	}



};

#endif