#include <iostream>
#include "bst.h"
#include<chrono>
using namespace std;

int main() {
    bst<int, int> tree;
//auto start = std::chrono::high_resolution
    tree.insert(pair<int,int> (8,1));   
    tree.insert(pair<int,int> (6,2));
    tree.insert(pair<int,int> (7,3));
    tree.insert(pair<int,int> (14,4));
    tree.insert(pair<int,int> (1,5));
    tree.insert(pair<int,int> (10,6));	
    tree.insert(pair<int,int> (3,7));
    tree.insert(pair<int,int> (4,8));
    tree.insert(pair<int,int> (13,9)); 
//auto finish = std::chrono::high_resolution
    std::cout << tree << std::endl;

    tree.remove(0);
    std::cout << tree << std::endl;

    tree.remove(3);
    
    std::cout << tree << std::endl;

    tree.remove(6);

    std::cout << tree << std::endl;

    tree.balance();
    std::cout << tree << std::endl;
    tree.remove(4);
    std::cout << tree << std::endl;
    

    tree.emplace(4,1);
    tree.emplace(2,2);
    tree.emplace(1,3);
    tree.emplace(3,4);
    tree.emplace(7,5);
    tree.emplace(9,6);
    tree.emplace(8,7);

    tree.emplace(6,8);
    tree.emplace(5,9);

    std::cout << "Tree:\n" << tree << std::endl;
    
    tree.remove(4);
    std::cout << "After deleteing 4 (root is: " << tree.getRoot()->get_data().first << "):\n" << tree << std::endl;

    tree.remove(1);
    std::cout << "After deleting 1:\n" << tree << std::endl;

    tree.remove(7);
    std::cout << "After deleting 7:\n" << tree << std::endl;

    tree.emplace(7, 7);
    std::cout << "After emplacing back 7:\n" << tree << std::endl;

    tree.remove(7);
    std::cout << "After deleting 7:\n" << tree << std::endl;
    

    tree.begin();
    tree.end();
    tree.find(10);

    int a[] = {1, 3, 4};
    auto ai = std::begin(a);
    std::cout << "\nThe first element is" << std::endl;
    std::cout << *ai << '\n';
    
    
 
    bst<int,int> copy_bst{tree};
    std::cout << "The last tree is\n" << tree << std::endl; 
    std::cout << "\nCopied tree" << std::endl;
    std::cout << copy_bst << std::endl;


    bst<int,int> move_bst = std::move(tree);
    std::cout << "\nMoved tree" << std::endl;
    std::cout << move_bst << std::endl;

    tree.clear();
    std::cout << "\nAfter clear" <<  tree << std::endl;
    std::cout << tree << std::endl;
    
}
