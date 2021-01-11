#include <iostream>
#include"BinaryTree.h"

int main() {
bst<int, int> tree;

cout<<"\nInserting nodes with 8, 6, 7, 14, 1, 10, 3, 4, and 13 "<<endl;;
tree.insertNode(8);   
tree.insertNode(6);
tree.insertNode(7);
tree.insertNode(14);
tree.insertNode(1);
tree.insertNode(10);	
tree.insertNode(3);
tree.insertNode(4);
tree.insertNode(13);


cout<<"\nThe number of nodes in the tree is now "<<tree.numNodes() <<endl;;

cout<<"\nHere are the values in the tree in-order:"<<endl;;
tree.displayInOrder();

//tree.displayPreOrder();
cout<<"\n\nNow deleting 7 from the tree...."<<endl;

//tree.deleteNode(7);
tree.remove(7);

cout<<"\nThe number of nodes in the tree is now "<<tree.numNodes()<<endl;;

cout<<"\n\nHere are the values in the tree in-order:"<<endl;;
tree.displayInOrder();

cout<<"\n\nHere are the values in the tree in post order:"<<endl;;
tree.displayPostOrder();
cout<<"\n";	
return 0;
}
