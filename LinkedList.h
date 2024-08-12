

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <iostream>
#include <string>
#include "TreeNode.cpp"
#include "ListNode.h"

using namespace std;


class LinkedList		//Used to store char array of huffman code
{
	ListNode* head;
	ListNode* tail;
	int length;

	public:

		//Constructor
		LinkedList();

		//Destructor
		~LinkedList();

		//Setter
		void setHead(ListNode*);
		void setTail(ListNode*);
		void setLength(int);

		//Getter
		ListNode* getHead();
		ListNode* getTail();
		int getLength();

		//Utility
		void insert(char);
		void delAtEnd();
		void display(ListNode*);

};



#endif

