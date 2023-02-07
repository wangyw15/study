#include "headers/BinaryTree.hpp"
#include <iostream>
#include <memory>

using namespace std;

int main()
{
    BinaryTree<char> tree;

    // create a binary tree
    tree.Root()->Data = 'A';
    tree.Root()->LeftChild = shared_ptr<Node<char>>(new Node<char>);
    tree.Root()->LeftChild->Data = 'B';
    tree.Root()->LeftChild->LeftChild = shared_ptr<Node<char>>(new Node<char>);
    tree.Root()->LeftChild->LeftChild->Data = 'D';
    tree.Root()->LeftChild->RightChild = shared_ptr<Node<char>>(new Node<char>);
    tree.Root()->LeftChild->RightChild->Data = 'E';
    tree.Root()->LeftChild->RightChild->LeftChild =
        shared_ptr<Node<char>>(new Node<char>);
    tree.Root()->LeftChild->RightChild->LeftChild->Data = 'G';
    tree.Root()->LeftChild->RightChild->RightChild =
        shared_ptr<Node<char>>(new Node<char>);
    tree.Root()->LeftChild->RightChild->RightChild->Data = 'H';
    tree.Root()->RightChild = shared_ptr<Node<char>>(new Node<char>);
    tree.Root()->RightChild->Data = 'C';
    tree.Root()->RightChild->RightChild =
        shared_ptr<Node<char>>(new Node<char>);
    tree.Root()->RightChild->RightChild->Data = 'F';
    tree.Root()->RightChild->RightChild->RightChild =
        shared_ptr<Node<char>>(new Node<char>);
    tree.Root()->RightChild->RightChild->RightChild->Data = 'I';

    // display the binary tree
    cout << tree << endl;

    // traverse
    cout << " pre order: ";
    tree.PreOrderTraverse([](char i) { cout << i << " "; }, tree.Root());
    cout << endl;

    cout << "  in order: ";
    tree.InOrderTraverse([](char i) { cout << i << " "; }, tree.Root());
    cout << endl;

    cout << "post order: ";
    tree.PostOrderTraverse([](char i) { cout << i << " "; }, tree.Root());
    cout << endl;

    return 0;
}