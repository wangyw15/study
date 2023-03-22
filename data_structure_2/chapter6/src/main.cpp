#include <iostream>
#include "headers/BinaryTree.hpp"

using namespace std;

int main()
{
    BinaryTree<char> tree;
    
    // create a binary tree
    tree.SetChild("", 'A');
    tree.AddChild("", 'l', 'B');
    tree.AddChild("l", 'l', 'E');
    tree.AddChild("ll", 'r', 'F');
    tree.AddChild("l", 'r', 'C');
    tree.AddChild("lr", 'l', 'G');
    tree.AddChild("lr", 'r', 'D');

    cout << tree << endl;
    cout << " Tree depth: " << tree.TreeDepth() << endl;
    cout << "Tree degree: " << tree.TreeDegree() << endl;
    return 0;
}