#include <iostream>
#include <queue>
using namespace std;
typedef struct node
{
	int parent;
	int lchild;
	int rchild;
}node;

node records[12];
int N;
int root;

int cnt = 0;

void inOrder_tranverse(int index)
{
	if (records[index].lchild != -1)
	{
		inOrder_tranverse(records[index].lchild);
	}

	cout << index;
	if (cnt != N-1)
	{
		cout << ' ';
		++cnt;
	}
	else
	{
		cout << endl;
	}

	if (records[index].rchild != -1)
	{
		inOrder_tranverse(records[index].rchild);
	}
}

void levelOrder_tranverse(int root)
{
	queue<int> nQ;
	int index;
	cnt = 0;
	nQ.push(root);
	while (!nQ.empty())
	{
		index = nQ.front();
		nQ.pop();
		if (records[index].lchild != -1)
		{
			nQ.push(records[index].lchild);
		}
		if (records[index].rchild != -1)
		{
			nQ.push(records[index].rchild);
		}

		cout << index;
		if (cnt != N-1)
		{
			cout << ' ';
			++cnt;
		}
		else
		{
			cout << endl;
		}
	}
	cnt = 0;
	return ;
}

int main()
{
	char clchild, crchild;
	cin >> N;
	for (int i = 0; i != N; ++i)
	{
		records[i].parent = -1;
	}
	for (int i = 0; i != N; ++i)
	{
		cin >> crchild >> clchild;
		if ('-' == clchild)
		{
			records[i].lchild = -1;
		}
		else
		{
			records[i].lchild = clchild - '0';
			records[clchild-'0'].parent = i;
		}
		if ('-' == crchild)
		{
			records[i].rchild = -1;
		}
		else
		{
			records[i].rchild = crchild - '0';
			records[crchild-'0'].parent = i;
		}
	}
	for (int i = 0; i != N; ++i)
	{
		if (records[i].parent == -1)
		{
			root = i;
			break;
		}
	}
	levelOrder_tranverse(root);
	inOrder_tranverse(root);
	



	system("pause");
	return 0;
}