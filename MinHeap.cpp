
#ifndef MIN_HEAP_CPP_
#define MIN_HEAP_CPP_

#include "MinHeap.h"

//===================================================
//Constructors

MinHeap::MinHeap()
{
	ArrSize = 0;
	heapSize = 0;
	heap = NULL;
}

//-------------------------

MinHeap::MinHeap(int s)
{
	ArrSize = s;
	heapSize = 0;
	heap = new TreeNode*[s];
}

//===================================================
//Setters

void MinHeap::setHeap(TreeNode* h)
{
	*heap = h;
}

//-------------------------

void MinHeap::setArrSize(int s)
{
	ArrSize = s;
}

//-------------------------

void MinHeap::setHeapSize(int s)
{
	heapSize = s;
}

//===================================================
//Getters

TreeNode** MinHeap::getHeap()
{
	return heap;
}

//-------------------------

int MinHeap::getArrSize()
{
	return ArrSize;
}

//-------------------------

int MinHeap::getHeapSize()
{
	return heapSize;
}

//===================================================
//Utility

void MinHeap::heapSort()
{
	TreeNode* temp;


	while (heapSize > 0)	//until the array is fully sorted (all elements are removed)
	{
		//Step 1: swap root with end leaf
		temp = heap[0];
		heap[0] = heap[heapSize-1];
		heap[heapSize-1] = temp;

		//adjust size of heap
		heapSize--;

		//Calling to swap nodes until heap order is maintained
		heapify(0);
	}

	
	
}

//-------------------------

void MinHeap::formTree(TreeNode* n)
{

	if (heapSize <= ArrSize)
	{
		//inserts in sequence in order to maintain almost complete binary tree property
		heap[heapSize-1] = n;
		
	}
}

//-------------------------

void MinHeap::insert(TreeNode* n)
{
	TreeNode* temp;
	int i;

	if (n->getFreq() != 0 && heapSize < ArrSize)
	{
		//inserts in sequence in order to maintain almost complete binary tree property
		//Deep copy
		heap[heapSize] = new TreeNode;
		heap[heapSize]->setChr(n->getChr());
		heap[heapSize]->setFreq(n->getFreq());

		// [ NOTE: Original Tree gets deleted after transfering nodes to heap ]

		heapSize++;	//size of heap is incremented

		i = heapSize-1;	//index of node recently inserted

		//Swapping to maintain heap order
		while (i > 0 && heap[i]->getFreq() <= heap[(i - 1) / 2]->getFreq())
		{
			//Comparing child with parent
			temp = heap[i];
			heap[i] = heap[(i - 1) / 2];
			heap[(i - 1) / 2] = temp;

			i = (i - 1) / 2;
		}
	}
	
}

//-------------------------

void MinHeap::heapify(int n)
{	//index of root is passed (n)

	TreeNode* temp;
	int smallest, left, right;
	
	smallest = n;			//parent
	left = (n * 2) + 1;		//left child
	right = (n * 2) + 2;	//right child


	if (left < heapSize && heap[smallest]->getFreq() > heap[left]->getFreq())
	{
		//if parent > left child
		smallest = left;
	}
	if (right < heapSize && heap[smallest]->getFreq() > heap[right]->getFreq())
	{
		//if right cjild is smaller than left child and parent
		smallest = right;
	}

	if (smallest != n)
	{
		//Swapping
		temp = heap[smallest];
		heap[smallest] = heap[n];
		heap[n] = temp;

		//Recursive call
		heapify(smallest);
	}




}

//===================================================
//Utility
//FOR TESTING
void MinHeap::display()
{
	for (int i = 0; i < ArrSize; i++)
	{


		if (heap[i]->getChr() == ' ')
		{
			cout << "[Space]: " << heap[i]->getFreq() << endl;
		}

		else if (heap[i]->getChr() == '\n')
		{
			cout << "[New Line]: " << heap[i]->getFreq() << endl;
		}

		else if (heap[i]->getChr() == '\0')
		{
			cout << "[INTERNAL]: " << heap[i]->getFreq() << endl;
		}

		else
		{
			cout << heap[i]->getChr() << ": " << heap[i]->getFreq() << endl;
		}
	
	}

	cout << endl;
}





#endif