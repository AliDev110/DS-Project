
#ifndef LINKED_LIST_CPP_
#define LINKED_LIST_CPP_

#include "LinkedList.h"
#include <iostream>
#include <string>

using namespace std;

//=====================================================================
//Constructor

LinkedList::LinkedList()
{
	head = NULL;
	tail = NULL;
	length = 0;
}

//=====================================================================
//Destructor

LinkedList::~LinkedList()
{
	ListNode* temp, * ptr;
	temp = ptr = head;

	while (ptr != NULL)
	{
		temp = ptr;
		ptr = ptr->next;

		delete temp;
	}

}

//=====================================================================
//Setter

void LinkedList::setHead(ListNode* h)
{
	head = h;
}

//-----------------------------------------------

void LinkedList::setLength(int l)
{
	length = l;
}

//-----------------------------------------------

void LinkedList::setTail(ListNode* t)
{
	tail = t;
}

//=====================================================================
//Getter

ListNode* LinkedList::getHead()
{
	return head;
}

//-----------------------------------------------

int LinkedList::getLength()
{
	return length;
}

//-----------------------------------------------

ListNode* LinkedList::getTail()
{
	return tail;
}

//=====================================================================
//Utility

void LinkedList::insert(char c)		//INSERT
{

	//Always inserts at start

	if (head == NULL) //If list is empty
	{
		head = new ListNode;
		head->binaryChar = c;
		head->next = NULL;
		tail = head;

		length++;

		return;
	}

	//else insert at end
	ListNode* temp = new ListNode;
	temp->binaryChar = c;
	temp->next = NULL;
	tail->next = temp;
	tail = temp;

	length++;
}

//-----------------------------------------------

void LinkedList::delAtEnd()
{
	if (head == NULL)
	{
		return;
	}

	if (head == tail)
	{
		delete head;
		head = tail = NULL;
		length--;
		return;
	}

	ListNode* temp = tail, *n = head;
	
	//Finding node before tail
	while (n->next != tail)
	{
		n = n->next;
	}

	//Assigning found node as tail
	tail = n;
	tail->next = NULL;

	delete temp;//delete previous tail

	length--;
}

//-----------------------------------------------

void LinkedList::display(ListNode* n)				//DISPLAY
{
	//Display

	if (n != NULL)
	{
		cout << n->binaryChar;
		display(n->next);
	}

}



#endif


