

#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <string>
#include "TreeNode.cpp"

using namespace std;

class ListNode
{
public:

	char binaryChar;
	ListNode* next;

	//Constructor
	ListNode()
	{
		next = NULL;
	}
};

#endif

