#pragma once

#include <iostream>
#include <stack>
#include <vector>
#include <queue>
using namespace std;

template<typename T>
class TreeNode
{
public:
	TreeNode<T>* left;
	TreeNode<T>* right;
	TreeNode<T>* parent;
	T val;
public:
	TreeNode(T val) :left(nullptr), right(nullptr), parent(nullptr), val(val) {};
	TreeNode(TreeNode<T>* left, TreeNode<T>* right, TreeNode<T>* parent,T val) :left(left), right(right), parent(parent), val(val) {};
	~TreeNode() {};
};

template<typename T>
class BinTree
{
private:
	TreeNode<T>* root;
public:
	BinTree() :root(nullptr) {};
	//通过层次遍历创建二叉树
	BinTree(vector<TreeNode<T>*> levelTraverse);
	~BinTree() {};
	//四种遍历：
	void PreOrderTraverse();
	void InOrderTraverse();
	void PostOrderTraverse();
	void LevelTraverse();
	//非递归先序遍历
	void NonRecurringPreOrder();
	void NonRecurringPostOrder();
};
//通过层次遍历创建二叉树
template<typename T>
inline BinTree<T>::BinTree(vector<TreeNode<T>*> levelTraverse)
{
	int num = levelTraverse.size() - 1;
	if (num == -1)
	{
		this->root = nullptr;
		return;
	}
	this->root = levelTraverse[0];
	for (int i = 0; i <= num; i++)
	{
		if (levelTraverse[i] == nullptr)
		{
			continue;
		}
		if (2 * i + 1 <= num)
		{
			levelTraverse[i]->left = levelTraverse[2 * i + 1];
		}
		else
		{
			levelTraverse[i]->left = nullptr;
		}
		if (2 * i + 2 <= num)
		{
			levelTraverse[i]->right = levelTraverse[2 * i + 2];
		}
		else
		{
			levelTraverse[i]->right = nullptr;
		}
		if ((i - 1) / 2 >= 0)
		{
			levelTraverse[i]->parent = levelTraverse[(i - 1) / 2];
		}
		else
		{
			levelTraverse[i]->parent = nullptr;
		}
	}
}
//非递归先序遍历
template<typename T>
inline void BinTree<T>::NonRecurringPreOrder()
{
	stack<TreeNode<T>*> st;
	st.push(this->root);
	while (!st.empty())
	{
		TreeNode<T>* tn = st.top();
		st.pop();
		if (tn != nullptr)
		{
			cout << tn->val << " ";
			st.push(tn->right);
			st.push(tn->left);
		}
		else
		{
			continue;
		}
	}
}

//非递归后序遍历
template<typename T>
inline void BinTree<T>::NonRecurringPostOrder()
{
	stack<TreeNode<T>*> st;
	st.push(this->root);
	vector<T> res;
	while (!st.empty())
	{
		TreeNode<T>* tn = st.top();
		st.pop();
		if (tn != nullptr)
		{
			res.push_back(tn->val);
			st.push(tn->left);
			st.push(tn->right);
		}
		else
		{
			continue;
		}
	}
	for (int i = res.size() - 1; i >= 0; i--)
	{
		cout << res[i] << " ";
	}
}

//先序遍历
template<typename T>
void preordertraverse(TreeNode<T>* tn)
{
	if (tn == nullptr)
	{
		return;
	}
	cout << tn->val << " ";
	preordertraverse(tn->left);
	preordertraverse(tn->right);
}
template<typename T>
inline void BinTree<T>::PreOrderTraverse()
{
	preordertraverse(this->root);
}
//中序遍历
template<typename T>
void inordertraverse(TreeNode<T>* tn)
{
	if (tn == nullptr)
	{
		return;
	}
	inordertraverse(tn->left);
	cout << tn->val << " ";
	inordertraverse(tn->right);
}
template<typename T>
inline void BinTree<T>::InOrderTraverse()
{
	inordertraverse(this->root);
}
//后序遍历
template<typename T>
void postordertraverse(TreeNode<T>* tn)
{
	if (tn == nullptr)
	{
		return;
	}
	postordertraverse(tn->left);
	postordertraverse(tn->right);
	cout << tn->val << " ";
}
template<typename T>
inline void BinTree<T>::PostOrderTraverse()
{
	postordertraverse(this->root);
}
//层次遍历
template<typename T>
inline void BinTree<T>::LevelTraverse()
{
	queue<TreeNode<T>*> que;
	if (this->root == nullptr)
	{
		return;
	}
	que.push(this->root);
	while (!que.empty())
	{
		TreeNode<T>* tn = que.front();
		que.pop();
		cout << tn->val << " ";
		if (tn->left != nullptr)
		{
			que.push(tn->left);
		}
		if (tn->right != nullptr)
		{
			que.push(tn->right);
		}
	}
}
