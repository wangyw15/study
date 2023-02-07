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

    cout << " pre order: ";
    tree.PreOrderTraverse([](char i) { cout << i << " "; }, tree.Root());
    cout << endl;

    cout << "  in order: ";
    tree.InOrderTraverse([](char i) { cout << i << " "; }, tree.Root());
    cout << endl;

    cout << "post order: ";
    tree.PostOrderTraverse([](char i) { cout << i << " "; }, tree.Root());
    cout << endl;

    cout << "leaf count: " << tree.Count() << endl;

    cout << " revoluted: ";
    tree.Revolut();
    tree.PreOrderTraverse([](char i) { cout << i << " "; }, tree.Root());
    cout << endl;

    cout << "     width: " << tree.Width() << endl;

    return 0;
}