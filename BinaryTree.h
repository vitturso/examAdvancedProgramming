#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>
#include <utility>

using namespace std;

template <class T, class U>
class bst
{
public:
struct TreeNode
{
TreeNode *left = NULL;
TreeNode *right= NULL;
TreeNode *head= NULL;
std::pair<T, U> value;
};
TreeNode *root;


void insert(TreeNode *&, TreeNode *&);
void destroySubTree(TreeNode *);
void deleteNode(T, TreeNode *&);
void makeDeletion(TreeNode *&);
void displayInOrder(TreeNode *);
void displayPreOrder(TreeNode *);
void displayPostOrder(TreeNode *);
int countNodes(TreeNode *&);
public:
bst() // Constructor
{ root = NULL; }
~bst() // Destructor
{ destroySubTree(root); }
void insertNode(T);
bool searchNode(T);
void remove(T);
void displayInOrder()
{ displayInOrder(root); }
void displayPreOrder()
{ displayPreOrder(root); }
void displayPostOrder()
{ displayPostOrder(root); }
int numNodes();
};

//*************************************************************
template <class T, class U>
void bst<T, U>::insert(TreeNode *&nodePtr, TreeNode *&newNode)
{
if (nodePtr == NULL)
{
// Insert the node.
nodePtr = newNode;
}
else if (newNode->value.first < nodePtr->value.first)
{
// Search the left branch
insert(nodePtr->left, newNode);
}
else
{
// Search the right branch
insert(nodePtr->right, newNode);
}
}

//**********************************************************
template <class T, class U>
	void bst<T, U>::insertNode(T num)
	{
	TreeNode *newNode = NULL; // Pointer to a new node.
	// Create a new node and store num in it.
	newNode = new TreeNode;
	newNode->value.first = num;
	newNode->left = newNode->right = NULL;
	// Insert the node.
	insert(root, newNode);
	}

//***************************************************
template <class T, class U>
void bst<T, U>::destroySubTree(TreeNode *nodePtr)
{
if (nodePtr->left)
{
destroySubTree(nodePtr->left);
}
if (nodePtr->right)
{
destroySubTree(nodePtr->right);
}
delete nodePtr;
}

//***************************************************
template <class T, class U>
bool bst<T, U>::searchNode(T num)
{
bool status = false;
TreeNode *nodePtr = root;
while (nodePtr)
{
if (nodePtr->value.first == num)
{
status = true;
}
else if (num < nodePtr->value.first)
{
nodePtr = nodePtr->left;
}
else
{
nodePtr = nodePtr->right;

}
}
return status;
}

//**********************************************
template <class T, class U>
void bst<T, U>::remove(T num)
{
deleteNode(num, root);
}

//********************************************
template <class T, class U>
void bst<T, U>::deleteNode(T num, TreeNode *&nodePtr)
{
//cout<<"la valore del nodeptr"<<nodePtr->value.first<<endl;
if (num < nodePtr->value.first)
{
deleteNode(num, nodePtr->left);
}
else if (num > nodePtr->value.first)
{
deleteNode(num, nodePtr->right);
}
else
{
makeDeletion(nodePtr);
}
}

//***********************************************************
template <class T, class U>
void bst<T, U>::makeDeletion(TreeNode *&nodePtr)
{


// Temporary pointer, used in reattaching the left subtree.
TreeNode *tempNodePtr = NULL;
if (nodePtr == NULL)
{
cout << "Cannot delete empty node.\n";
}
else if (nodePtr->right == NULL)
{
//cout<<"ptr right null"<<endl;
tempNodePtr = nodePtr;
nodePtr = nodePtr->left; // Reattach the left child
delete tempNodePtr;
}
else if (nodePtr->left == NULL)
{
//cout<<"ptr left null"<<endl;
tempNodePtr = nodePtr;
nodePtr = nodePtr->right; // Reattach the right child
delete tempNodePtr;
}
// If the node has two children.
else
{
//cout<<"ptr no null"<<endl;
// Move one node the right.
tempNodePtr = nodePtr->right;
// Go to the end left node.
while (tempNodePtr->left)
{
tempNodePtr = tempNodePtr->left;
}
// Reattach the left subtree.
tempNodePtr->left = nodePtr->left;
tempNodePtr = nodePtr;
// Reattach the right subtree.
nodePtr = nodePtr->right;
delete tempNodePtr;
}

//cout<<"\n\nNow deleting "<<nodePtr->value.first<<" from the tree...."<<endl;
}

//****************************************************************
template <class T, class U>
void bst<T, U>::displayInOrder(TreeNode *nodePtr)
{
if (nodePtr)
{
displayInOrder(nodePtr->left);
cout << nodePtr->value.first <<" ";
displayInOrder(nodePtr->right);
}
}

//****************************************************************
template <class T, class U>
void bst<T, U>::displayPreOrder(TreeNode *nodePtr)
{
if (nodePtr)
{
cout << nodePtr->value.first <<" ";
displayPreOrder(nodePtr->left);
displayPreOrder(nodePtr->right);
}
}

//****************************************************************
template <class T, class U>
void bst<T, U>::displayPostOrder(TreeNode *nodePtr)
{
if (nodePtr)
{
displayPostOrder(nodePtr->left);
displayPostOrder(nodePtr->right);
cout <<nodePtr->value.first<<" ";
}

}

//****************************************************************
template <class T, class U>
int bst<T, U>::numNodes()
{
return countNodes(root);
}

//****************************************************************
template <class T, class U>
int bst<T, U>::countNodes(TreeNode *&nodePtr)
{
int count;
if (nodePtr == NULL)
{
count = 0;
}
else
{
count = 1 + countNodes(nodePtr->left) + countNodes(nodePtr->right);
}
return count;
}
#endif
