

#ifndef TREE_CPP_
#define TREE_CPP_

#include "Tree.h"
#include "LinkedList.h"
#include <iomanip>


//==============================================================
//Constructor

Tree::Tree()
{
	root = NULL;
	noOfNodes = 0;
}


//==============================================================
//Delete Tree

void Tree::DelTree(TreeNode* n)
{
	//traverses the tree in postOrder
		//Deletes the children of each node before deleting the parent
		//Root is last node to be deleted

	if (n != NULL)
	{
		DelTree(n->getLNode());
		DelTree(n->getRNode());
		delete n;
	}

	//resetting values
	noOfNodes = 0;
	root = NULL;
}

//==============================================================
//Setters



void Tree::setRoot(TreeNode* r)
{
	root = r;
}

//--------------------------------

void Tree::setNoOfNodes(int n)
{
	noOfNodes = n;
}

//==============================================================
//Getters

TreeNode* Tree::getRoot()
{
	return root;
}

//--------------------------------

int Tree::getNoOfNodes()
{
	return noOfNodes;
}

//==============================================================
//Utility

bool Tree::find(TreeNode* n, char c)
{
	bool end = false;

	if (n != NULL)
	{
		if (n->getChr() == c)	//If char already sxists in tree
		{
			//increment frequency
			n->setFreq(n->getFreq() + 1);

			end = true;
		}
								//else
		if (!end)	//search left sub-tree
		{
			end = find(n->getLNode(), c);
		}
		if (!end)	//search right sub-tree
		{
			end = find(n->getRNode(), c);
		}
		
		

	}

	return end;
}

//----------------------------------------

void Tree::insertFromFile(char c)
{
	//This function is used to read and insert characters from the file
		//The main use here is to use a structure which can reject duplicate nodes
		//and count frequency of each char as it is inserted

	TreeNode* temp;

	if (!find(root, c))
	{

		if (root == NULL)	//If tree is empty
		{
			temp = createNode('\0', 0);
			temp->setLeftNode(createNode(c, 1));
			root = temp;
			noOfNodes++;
		}
		else if (root->getRNode() == NULL)	//if the right child of root is empty
		{
			root->setRightNode(createNode(c, 1));
			noOfNodes++;
		}
		else
		{
			//Creating new node
			temp = createNode('\0',0);

			temp->setLeftNode(root);

			//Left and right child are NULL already due to constructor
				//Frequency is set to 1 due to constructor
			
			//setting right child of new node (Leaf Node)
			temp->setRightNode(createNode(c, 1));
			noOfNodes++;

			//Setting new root
			setRoot(temp);
		
		}
	}

	
}

//----------------------------------------

TreeNode* Tree::createNode(char c, int f)
{
	//creating a new node
	TreeNode* n = new TreeNode;
	n->setChr(c);	//set char
	n->setFreq(f);	//set frequency

	//Children are NULL due to constructor

	return n;	//return new node
}

//==============================================================
//Output

void Tree::Inorder(TreeNode* n)	//Made for testing purposes
{
	if (n != NULL)
	{
		Inorder(n->getLNode());

		if (n->getChr() == ' ')
		{
			cout << "[Space] : " << "\t" << n->getFreq() << endl << endl;
		}

		else if (n->getChr() != '\0')
		{
			cout << n->getChr() << "\t: " << "\t" << n->getFreq() << endl << endl;
		}


		Inorder(n->getRNode());
	}
}

//----------------------------------------

void Tree::PrintCode(TreeNode* n, LinkedList* code, double* ABR)	//Made for testing purposes
{
	int charCol = 15;
	int freqCol = 12;
	int codeCol = 60;

	//Format for table form display
	if (n == root)
	{
		for (int i = 0; i < charCol + freqCol + codeCol + 2; i++)
		{
			cout << "-";	//printing horizontal table line
		}
		cout << endl;

		cout << left << setw(charCol) << "    Character  |" << setw(freqCol) << "  Frequency " << "| " << setw(codeCol) << "\t\t\tHuffman Code" << endl;// << endl << endl;

		for (int i = 0; i < charCol + freqCol + codeCol + 2; i++)
		{
			cout << "-";	//printing horizontal table line
		}
		cout << endl;// << endl;

	}

	if (n != NULL)
	{
		if (n->getChr() != '\0')
		{
			if (n->getChr() == ' ')	//format for white space char
			{
				cout << right << setw(charCol) << "[Space]" << "|" << right << setw(freqCol) << n->getFreq() << "|\t";
				code->display(code->getHead());
				cout << endl;
			}

			else if (n->getChr() == '\n')	//format for '\n' char
			{
				cout << right << setw(charCol) << "[new line]" << "|" << right << setw(freqCol) << n->getFreq() << "|\t";
				code->display(code->getHead());
				cout << endl;
			}

			else if (n->getChr() == '\t')	//format for '\n' char
			{
				cout << right << setw(charCol) << "[Tab]" << "|" << right << setw(freqCol) << n->getFreq() << "|\t";
				code->display(code->getHead());
				cout << endl;
			}

			else if (n->getChr() != '\0')	//general format for other characters
			{
				cout <<  right << setw(charCol) << n->getChr() << "|" << setw(freqCol) << n->getFreq() << "|\t";
				code->display(code->getHead());
				cout << endl;
			}
			

			//Calculating Average bit rate
			*ABR += n->getFreq() * code->getLength();


			//format for horizontal table lines
			for (int i = 0; i < charCol; i++)
			{
				cout << "-";
			}

			cout << "|";	//vertical table column seperator
			
			//format for horizontal table lines
			for (int i = 0; i < freqCol; i++)
			{
				cout << "-";
			}

			cout << "|"; //vertical table column seperator

			//format for horizontal table lines
			for (int i = 0; i < codeCol; i++)
			{
				cout << "-";
			}
			cout << endl;
			
		}

		code->insert('0');		//If we traverse to left child, add 0 to huffman binary code
		PrintCode(n->getLNode(), code,ABR);

		code->insert('1');		//If we traverse to right child, add 1 to huffman binary code
		PrintCode(n->getRNode(), code,ABR);

		//Function returns to previous call in stack (traverseing back up to parent so code will be smaller)
		code->delAtEnd();

	}
	else	//If node is NULL
	{
		//Function returns to previous call in stack (traverseing back up to parent so code will be smaller)
		code->delAtEnd();
	}
		

}


#endif

