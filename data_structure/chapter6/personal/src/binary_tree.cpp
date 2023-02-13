#include "headers/BinaryTree.hpp"
#include <iostream>
#include <memory>

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

    std::function<void(char)> printer = [](char i) { cout << i << " "; };

    cout << "    pre order: ";
    tree.PreOrderTraverse(printer, tree.Root());
    cout << endl;

    cout << "     in order: ";
    tree.InOrderTraverse(printer, tree.Root());
    cout << endl;

    cout << "   post order: ";
    tree.PostOrderTraverse(printer, tree.Root());
    cout << endl;

    cout << "   leaf count: " << tree.LeafCount() << endl;

    cout << "    revoluted: ";
    tree.Revolut();
    tree.PreOrderTraverse(printer, tree.Root());
    cout << endl;

    cout << "        width: " << tree.Width() << endl;

    cout << "non recurring: ";
    tree.NonRecurringInOrderTraverse(printer);
    cout << endl;

    cout << "   comparison: ";
    tree.InOrderTraverse(printer, tree.Root());
    cout << endl;

    return 0;
}