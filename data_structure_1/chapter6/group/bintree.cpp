// 1 2 3 5 7 2 -100 -100 8 -100 -100 9 7 -100 -100
// -100表示null
// 4是树高

#include "headers/BinTree.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void Showtest()
{
	cout << "主菜单显示：" << endl;
	cout << "1.遍历显示" << endl;
	cout << "2.非递归先序遍历" << endl;
	cout << "3.非递归后序遍历" << endl;
	cout << "0.退出" << endl;
	cout << "请输入选择：";
}

int main()
{
	vector<TreeNode<int>*> LT;
	int num;
	int height;
	cout << "输入二叉树高度：";
	cin >> height;
	cout << "输入层次遍历：(-100视作nullptr)" << endl;
	int nd = pow(2, height) - 1;
	while (nd)
	{
		cin >> num;
		if (num == -100)
		{
			LT.push_back(nullptr);
		}
		else
		{
			TreeNode<int>* tn = new TreeNode<int>(num);
			LT.push_back(tn);
		}
		nd--;
	}
	BinTree<int> bt(LT);
	Showtest();
	int choice;
	while (cin >> choice && choice != 0)
	{
		switch (choice)
		{
		case 1:
			cout << "   1.先序遍历：";
			bt.PreOrderTraverse();
			cout << endl;
			cout << "   2.中序遍历：";
			bt.InOrderTraverse();
			cout << endl;
			cout << "   3.后序遍历：";
			bt.PostOrderTraverse();
			cout << endl;
			cout << "   4.层次遍历：";
			bt.LevelTraverse();
			cout << endl;
			break;
		case 2:
			cout << "递归方法的先序遍历：" << endl;
			bt.PreOrderTraverse();
			cout << endl;
			cout << "非递归方法的先序遍历：" << endl;
			bt.NonRecurringPreOrder();
			cout << endl;
			break;
		case 3:
			cout << "递归方法的后序遍历：" << endl;
			bt.PostOrderTraverse();
			cout << endl;
			cout << "非递归方法的后序遍历：" << endl;
			bt.NonRecurringPostOrder();
			cout << endl;
			break;
		}
		cout << endl;
		Showtest();
	}
}