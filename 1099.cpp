#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

typedef struct node
{
	int parent;
	int data;
	int lindex;
	int rindex;
}node;

node records[105];
node tree[105];
int N;
int root = 0;
vector<int> nums;
vector<int> leaves;
int cnt = 0;

void levelOrder_tranverse()
{
	queue<int> nQ;
	int index;
	nQ.push(0);
	while (!nQ.empty())
	{
		index = nQ.front();
		nQ.pop();
		if (tree[index].lindex != -1)
		{
			nQ.push(tree[index].lindex);
		}
		if (tree[index].rindex != -1)
		{
			nQ.push(tree[index].rindex);
		}
		cout << tree[index].data;
		if (N != ++cnt)
		{
			cout << ' ';
		}
	}
	return ;
}


void process_leaves()
{
	int lchild;
	while (-1 != root)
	{
		lchild = root;

		while (records[lchild].lindex != -1)
		{
			lchild = records[lchild].lindex;
		}
		leaves.push_back(lchild);

		if (lchild == root)
		{
			root = records[root].rindex;
		}
		else
		{
			records[records[lchild].parent].lindex = records[lchild].rindex;
			if (records[lchild].rindex != -1)
			{
				records[records[lchild].rindex].parent = records[lchild].parent;
			}
		}
	}
	return ;
}


int main()
{
	int temp;
	cin >> N;
	for (int i = 0; i != N; ++i)
	{
		cin >> records[i].lindex >> records[i].rindex;
		if (records[i].lindex != -1)
		{
			records[records[i].lindex].parent = i;
		}
		if (records[i].rindex != -1)
		{
			records[records[i].rindex].parent = i;
		}
	}
	records[0].parent = -1;
	memcpy(tree, records, N*sizeof(node));
	process_leaves();

	for (int i = 0; i != N; ++i)
	{
		cin >> temp;
		nums.push_back(temp);
	}
	sort(nums.begin(), nums.end());

	for (int i = 0; i != N; ++i)
	{
		tree[leaves[i]].data = nums[i];
	}
	
	levelOrder_tranverse();
	cout << endl;

	system("pause");
	return 0;
}