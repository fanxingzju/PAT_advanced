/* 模拟BST的建立*/
#include <iostream>
using namespace std;

class node
{
public:
	node():value(-1), lindex(-1), rindex(-1), level(0){}
	int value;
	int lindex;
	int rindex;
	int level;
};

int N;
node tree[1010];
int maxlevel = 0;

void insert_node(int root, int index)
{
	if (tree[index].value <= tree[root].value)
	{
		if (-1 == tree[root].lindex)
		{
			tree[root].lindex = index;
			tree[index].level = tree[root].level+1;
			if (tree[index].level > maxlevel)
			{
				maxlevel = tree[index].level;
			}
		}
		else
		{
			insert_node(tree[root].lindex, index);
		}
	}
	else
	{
		if (-1 == tree[root].rindex)
		{
			tree[root].rindex = index;
			tree[index].level = tree[root].level+1;
			if (tree[index].level > maxlevel)
			{
				maxlevel = tree[index].level;
			}
		}
		else
		{
			insert_node(tree[root].rindex, index);
		}
	}
}

int main()
{
	int n1 = 0, n2 = 0;
	cin >> N >> tree[0].value;
	for (int i = 1; i != N; ++i)
	{
		cin >> tree[i].value;
		insert_node(0, i);
	}

	for (int i = 0; i != N; ++i)
	{
		if (tree[i].level == maxlevel)
		{
			++n1;
		}
		else
		{
			if (tree[i].level == maxlevel-1)
			{
				++n2;
			}
		}
	}

	cout <<  n1 << " + " << n2 << " = " << n1+n2 << endl;
	return 0;
}