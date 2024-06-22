/*
	Ali Raza
	20I-0782
	Sec D
	Project
*/


#include <iostream>
#include <string>
#include <fstream>
#include "Tree.h"
#include "LinkedList.h"
#include "MinHeap.h"

using namespace std;


void storeChar(Tree*, string, int*);
void readFile(Tree*, string, int*);
void heapStore(TreeNode*, MinHeap*);
void Optimal_Huffman(MinHeap*,Tree*, Tree*);
void displayTitle();
void continue0();


int main()
{
    int op = 0;
    
    double* ABR = new double; //Average bit rate
    *ABR = 0.0;
    
    string fName;
	Tree *t = new Tree;
    Tree *tOptimal = new Tree;
    LinkedList* code = new LinkedList;
	
    int *fileLength = new int;
	*fileLength = 0;

    MinHeap* heap = NULL;

    //-----------------------------------------------

    system("CLS"); //clear screen
    displayTitle(); //Title prompt

    //user inputs file name
    cout << " < Enter the file name >" << endl;
    cout << " >> ";
    cin >> fName;


    //File is opened and read
    readFile(t, fName, fileLength);

    //Used so that text on screen is not instantly cleared
    continue0();


    while (op != 3)
    {
        //reset ABR
        *ABR = 0.0;

        //Show fresh screen
        system("CLS");
        displayTitle();

        //User selects whetehr to see basic or optimal huffman code, or simply to exit the program
        cout << " [ Select from the given options: ]" << endl;
        cout << "\t1. Basic Huffman Code\n\t2. Optimal Huffman Code\n\t3. Exit" << endl << endl;
        cout << " >> ";
        cin >> op;

        //Validation check
        while (op > 3 || op < 1)
        {
            cout << endl << " *** Error: select from given options only ***" << endl;
            cout << ">> ";
            cin >> op;

        }

        //Show fresh screen
        system("CLS");
        displayTitle();


        if (op == 1)    //Display Basic Huffman Code
        {
            cout << endl << endl << "\t\t\t     [ BASIC HUFFMAN CODE ] " << endl << endl;
            t->PrintCode(t->getRoot(), code, ABR);
        }

        if (op == 2)    //Display Optimal Huffman Code
        {
            cout << endl << endl << "\t\t\t     [ OPTIMAL HUFFMAN CODE ] " << endl << endl;
            Optimal_Huffman(heap, t, tOptimal);


            tOptimal->PrintCode(tOptimal->getRoot(), code, ABR);
        }

        if (op == 3)    //Exit the program
        {
            //Deleting trees (deallocating spaces)
            t->DelTree(t->getRoot());
            tOptimal->DelTree(tOptimal->getRoot()); //tOptimal shares the same memory locations as minHeap (Shallow copy was made)
                                                    //Therefore, each node in heap does not need to be deleted (Already deleted through tOptimal)
            delete code;

            system("CLS");
            cout << " Succesfully exited..." << endl;

            return 0;
        }


        if (op != 3 && op != 4)
        {
            *ABR /= *fileLength;    //Final step for ABR calculation 

            //Display file and compression data
            cout << endl << endl << " [ ABR ] = " << *ABR << endl;
            cout << endl << " [ COMPRESSION RATIO ] = " << 8 / *ABR << endl;
            cout << endl << " [ Original File Length ] = " << *fileLength << " Bytes" << endl << endl;

            //Used so that text on screen is not instantly cleared
            continue0();
        }


    }


   

}



//========================================================================================
//DISPLAY MESSAGES

void displayTitle()
{
    //Display program title
    cout << "\t\t\t\t  ===========================================" << endl;
    cout << "\t\t\t\t /                                           \\" << endl;
    cout << "\t\t\t\t|              TEXT FILE COMPRESSOR           |" << endl;
    cout << "\t\t\t\t \\                                           /" << endl;
    cout << "\t\t\t\t  ===========================================" << endl << endl;
}



void continue0()
{
    char c = '\0';

    cout << endl << " (Enter 'c' to continue)" << endl;

    while (c != 'C' && c != 'c')    //Validation check
    {
        cin >> c;
    }
}



//========================================================================================
//OPTIMAL HUFFMAN

void Optimal_Huffman(MinHeap* minHeap, Tree *t, Tree* tOptimal)
{
    int i = 0, j = 0;
    TreeNode* left, * right, *parent = NULL, *temp;

    //A new heap is created of size = no. of nodes in the tree
    minHeap = new MinHeap(t->getNoOfNodes());

    //The nodes from the tree are inserted into the heap (deep copies are made so that original tree is unchanged)
    heapStore(t->getRoot(), minHeap);

    //t->DelTree(t->getRoot());

    //Sorting heap into descending order
    minHeap->heapSort();




    //****[ The following code generates the whole Optimal Huffman tree ]****

    //resetting the heap size after the heapSort() function mad it 0
    minHeap->setHeapSize(minHeap->getArrSize());

    //setting starting index values
    i = minHeap->getHeapSize() - 1;
    
    //Loop starts from end of heap (smallest values are at the end of the array)
    while (minHeap->getHeapSize() > 1)
    {
        left = minHeap->getHeap()[i];       //left child
        right = minHeap->getHeap()[i - 1];  //right child

        minHeap->setHeapSize(minHeap->getHeapSize() - 1);   //decement heap size by 1  
                                                           //(not 2 since we need to store the parent node in th heap as well)
        
        //updating value of indexes
        i = minHeap->getHeapSize()-1;

        //creating parent node (frequency = sum of the frequency of its children)
        parent = t->createNode('\0', left->getFreq() + right->getFreq());
        parent->setLeftNode(left);      //setting left child   
        parent->setRightNode(right);    //setting right child

        //inserting parent into heap (shallow copy)
        minHeap->formTree(parent);

        //index variable for inner loop is set
        j = i;

        //This loop reorders the heap array into descending order
        while (j > 0 && minHeap->getHeap()[j]->getFreq() > minHeap->getHeap()[j - 1]->getFreq())
        {
            //swapping
            temp = minHeap->getHeap()[j];
            minHeap->getHeap()[j] = minHeap->getHeap()[j - 1];
            minHeap->getHeap()[j - 1] = temp;

            j--;
        }

       
    }    
    

    //Setting Optimal Tree
    tOptimal->setRoot(minHeap->getHeap()[0]);
    tOptimal->setNoOfNodes(minHeap->getArrSize());

}





//========================================================================================
//HEAP

void heapStore(TreeNode* n, MinHeap* heap)
{
    //This function inserts every element of the tree into a min heap
        //a preorder recursive pattern is followed

    if (n != NULL)
    {
        //inserting node into the min heap
        heap->insert(n);

        heapStore(n->getLNode(), heap);
        heapStore(n->getRNode(), heap);
    }

}




//========================================================================================
//FILING


//The following function extracts characters from a full string and inserts them 
void storeChar(Tree* t, string s, int* fileLength)
{
    int i = 0;


    while (s[i] != '\0')
    {
        t->insertFromFile(s[i]); //Insert char into Tree

        i++;
    }

    *fileLength += i;

}

//------------------------------------------------------------

void readFile(Tree* t, string fName, int* fileLength)
{
    ifstream file(fName);
    string line;

    //If file name is incorrect, ask user to enter correct file name
    while (!file)
    {
        cout << endl << "  ---------------------------------------------------" << endl;
        cout << " !*** Failed to open file OR file does not exists ***!" << endl;
        cout << "  ---------------------------------------------------" << endl << endl;
        cout << " < Enter file name aagin > " << endl;
        cout << ">> ";
        cin >> fName;

        file.open(fName);
    }

    //File has been opened
    if (file)
    {
        cout << endl << "  --------------------------------" << endl;
        cout << " | *** File read successfully *** |" << endl;
        cout << "  --------------------------------" << endl << endl;
    }

    while (!file.eof())
    {
        getline(file, line);    //Extracting line 

        if (!file.eof())
        {
            t->insertFromFile('\n'); //Insert end of line character (moving to next line)
        }

        storeChar(t, line, fileLength);
    }


    file.close();


}

