#include <iostream>
#include <stack>
#include <string>
using namespace std;

typedef struct elem
{
	int id;
	int op;				// 1->push, 0->pop
	int key;
}elem;

elem records[35];
int N;
string operation;
int nid = 0;
stack<int> nStack;

typedef struct node
{
	int key;
	struct node *lchild;
	struct node *rchild;
}node;

// N <= 30, ¹ÊÖ±½Ó²éÕÒ
void rebuild_tree(node *&root, int id)
{
	int index = 0;
	int pushindex, popindex;
	node *lchild, *rchild;
	for (; index != 2*N; ++index)
	{
		if (records[index].id == id)
		{
			pushindex = index;
			break;
		}
	}
	for (++index; index != 2*N; ++index)
	{
		if (records[index].id == id)
		{
			popindex = index;
			break;
		}
	}
	if (pushindex+1 != popindex)
	{
		lchild = new node;
		lchild->key = records[pushindex+1].key;
		lchild->lchild = NULL;
		lchild->rchild = NULL;
		root->lchild = lchild;
		rebuild_tree(lchild, records[pushindex+1].id);
	}

	if (popindex+1 != 2*N && records[popindex+1].op == 1)
	{
		rchild = new node;
		rchild->key = records[popindex+1].key;
		rchild->lchild = NULL;
		rchild->rchild = NULL;
		root->rchild = rchild;
		rebuild_tree(rchild, records[popindex+1].id);
	}
	return ;
}


void postOrder_tranverse(node *&root)
{
	if (NULL == root)
	{
		return ;
	}
	if (NULL != root->lchild)
	{
		postOrder_tranverse(root->lchild);
	}
	if (NULL != root->rchild)
	{
		postOrder_tranverse(root->rchild);
	}
	cout << root->key << ' ';
	return ;
}

int main()
{
	node *root = NULL;
	cin >> N;
	for (int i = 0; i != 2*N; ++i)
	{
		cin >> operation;
		if ('o' == operation[1])
		{
			records[i].op = 0;
			records[i].id = nStack.top();	
			nStack.pop();
		}
		else
		{
			records[i].op = 1;
			cin >> records[i].key;
			records[i].id = ++nid;
			nStack.push(nid);
		}
	}
	root = new node;
	root->key = records[0].key;
	root->lchild = root->rchild = NULL;
	rebuild_tree(root, records[0].id);

	postOrder_tranverse(root->lchild);
	postOrder_tranverse(root->rchild);
	cout << root->key << endl;

	system("pause");
	return 0;
}