/*
	Ali Raza
	20I-0782
	Sec D
	Project
*/

#ifndef MIN_HEAP_H_
#define MIN_HEAP_H_

#include <iostream>
#include "Tree.h"
#include "TreeNode.cpp"

using namespace std;

class MinHeap
{
	TreeNode** heap;
	int ArrSize;	//Size of array where heap is created (once value is set, it is not changed)
	int heapSize;	//size of heap (changes as items get deleted or inserted)

public:

	//Constructors
	MinHeap();
	MinHeap(int);

	//Setters
	void setHeap(TreeNode*);
	void setArrSize(int);
	void setHeapSize(int);

	//Getters
	TreeNode** getHeap();
	int getArrSize();
	int getHeapSize();

	//Utility
	void insert(TreeNode*);
	void heapify(int);
	void heapSort();
	void formTree(TreeNode*);

	//Testing
	void display();


};


#endif
