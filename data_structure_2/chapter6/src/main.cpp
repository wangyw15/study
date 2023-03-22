#include <iostream>
#include "headers/BinaryTree.hpp"

using namespace std;

int main()
{
    BinaryTree<char> tree;

    // create a binary tree
    tree.SetChild("", 'A');
    tree.AddChild("", 'l', 'B');
    tree.AddChild("l", 'l', 'D');
    tree.AddChild("l", 'r', 'E');
    tree.AddChild("lr", 'l', 'G');
    tree.AddChild("lr", 'r', 'H');
    tree.AddChild("", 'r', 'C');
    tree.AddChild("r", 'r', 'F');
    tree.AddChild("rr", 'r', 'I');

    cout << tree << endl;
    return 0;
}