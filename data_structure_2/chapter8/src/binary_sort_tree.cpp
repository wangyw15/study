#include <iostream>
#include <string>
#include "headers/BinarySortTree.hpp"

using namespace std;

int main()
{
    BinarySortTree<int> tree;
    tree.SetChild("", 39);
    tree.AddChild("", 'l', 100);
    tree.AddChild("", 'r', 68);
    tree.AddChild("l", 'l', 8);
    tree.AddChild("l", 'r', 23);
    tree.AddChild("r", 'l', 46);
    tree.AddChild("r", 'r', 75);
    tree.AddChild("lr", 'r', 34);
    tree.AddChild("rr", 'l', 71);
    tree.AddChild("rr", 'r', 86);

    cout << (tree.IsBST() ? "true" : "false") << endl;
    tree.InsertAsBST(17);
    cout << tree << endl;
    tree.DeleteAsBST(68);
    cout << tree << endl;
    return 0;
}
