// 1 2 3 5 7 2 -100 -100 8 -100 -100 9 7 -100 -100
// -100��ʾnull
// 4������

#include "headers/BinTree.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void Showtest()
{
	cout << "���˵���ʾ��" << endl;
	cout << "1.������ʾ" << endl;
	cout << "2.�ǵݹ��������" << endl;
	cout << "3.�ǵݹ�������" << endl;
	cout << "0.�˳�" << endl;
	cout << "������ѡ��";
}

int main()
{
	vector<TreeNode<int>*> LT;
	int num;
	int height;
	cout << "����������߶ȣ�";
	cin >> height;
	cout << "�����α�����(-100����nullptr)" << endl;
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
			cout << "   1.���������";
			bt.PreOrderTraverse();
			cout << endl;
			cout << "   2.���������";
			bt.InOrderTraverse();
			cout << endl;
			cout << "   3.���������";
			bt.PostOrderTraverse();
			cout << endl;
			cout << "   4.��α�����";
			bt.LevelTraverse();
			cout << endl;
			break;
		case 2:
			cout << "�ݹ鷽�������������" << endl;
			bt.PreOrderTraverse();
			cout << endl;
			cout << "�ǵݹ鷽�������������" << endl;
			bt.NonRecurringPreOrder();
			cout << endl;
			break;
		case 3:
			cout << "�ݹ鷽���ĺ��������" << endl;
			bt.PostOrderTraverse();
			cout << endl;
			cout << "�ǵݹ鷽���ĺ��������" << endl;
			bt.NonRecurringPostOrder();
			cout << endl;
			break;
		}
		cout << endl;
		Showtest();
	}
}