// 4 2
// 3 4
// 10 1
// 2 2
// 8 128

#include <iostream>
#include <algorithm>
using namespace std;

struct node
{
	int left;
	int right;
	bool status;
	bool isleaf;
};
node tree[100001];
int Falling(int height, int number)
{
	for (int i = 1; i <= pow(2, height) - 1; i++)
	{
		if (i >= pow(2, height - 1))
		{
			tree[i].isleaf = 1;
		}
		else
		{
			tree[i].isleaf = 0;
			tree[i].left = i * 2;
			tree[i].right = i * 2 + 1;
		}
		tree[i].status = 0;
	}
	for (int i = 1; i <= number; i++)
	{
		int j = 1;
		while (tree[j].isleaf != 1)
		{
			if (tree[j].status == 0)
			{
				tree[j].status = 1;
				j = tree[j].left;
			}
			else
			{
				tree[j].status = 0;
				j = tree[j].right;
			}
		}
		if (i == number)
		{
			return j;
		}
	}
}

int main()
{
	int height, number;
	while (cin >> height)
	{
		cin >> number;
		cout << Falling(height, number) << endl;
	}
	return 0;
}