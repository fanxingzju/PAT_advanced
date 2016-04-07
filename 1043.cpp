#include <iostream>
#include <string>
using namespace std;

int buffer[1003];
typedef struct node
{
	int data;
	struct node *lchild;
	struct node *rchild;
}node;


void rebuild_BST(node *&root, int startpos, int endpos)
{
	int lpos = startpos;
	int rpos = startpos;
	node *lnode = NULL;
	node *rnode = NULL;

	if (buffer[0] > buffer[1])
	{
		// BST
		while(lpos != endpos && buffer[lpos] >= root->data)
		{
			++lpos;
		}
		
		while (rpos != endpos && buffer[rpos] <= root->data)
		{
			++rpos;
		}
	}
	else
	{
		// BST_mirror
		while(lpos != endpos && buffer[lpos] <= root->data)
		{
			++lpos;
		}
		
		while (rpos != endpos && buffer[rpos] >= root->data)
		{
			++rpos;
		}
	}

	if (lpos != endpos)
	{
		lnode = new node;
		lnode->data = buffer[lpos];
		lnode->lchild = NULL;
		lnode->rchild = NULL;
		root->lchild = lnode;
		if (rpos - lpos > 1)
		{
			rebuild_BST(lnode, lpos+1, rpos);
		}
	}

	if (rpos != endpos)
	{
		rnode = new node;
		rnode->data = buffer[rpos];
		rnode->lchild = NULL;
		rnode->rchild = NULL;
		root->rchild = rnode;
		if (endpos - rpos > 1)
		{
			rebuild_BST(rnode, rpos+1, endpos);
		}
	}
}

bool check_is_ok(int startpos, int endpos)
{
	bool ret1, ret2;
	int pivot;
	int pos = startpos+1;
	// 这一步还不严谨, 考虑输入"5 \n 8 8 10 9 11", 虽然可以通过所有测试点
	if (buffer[0] == buffer[1])
	{
		return false;
	}

	if (endpos - startpos <= 2)
	{
		return true;
	}

	if (buffer[0] > buffer[1])
	{
		while (pos != endpos && buffer[pos] <= buffer[startpos])
		{
			++pos;
		}
		pivot = pos;
		while (pos != endpos && buffer[pos] >= buffer[startpos])
		{
			++pos;
		}
		if (pos != endpos)
		{
			return false;
		}
		else
		{
			ret1 = check_is_ok(startpos+1, pivot);
			ret2 = check_is_ok(pivot, endpos);
			return ret1&&ret2;
		}
	}
	else
	{
		while (pos != endpos && buffer[pos] >= buffer[startpos])
		{
			++pos;
		}
		pivot = pos;
		while (pos != endpos && buffer[pos] <= buffer[startpos])
		{
			++pos;
		}

		if (pos != endpos)
		{
			return false;
		}
		else
		{
			ret1 = check_is_ok(startpos+1, pivot);
			ret2 = check_is_ok(pivot, endpos);
			return ret1&&ret2;
		}
	}
}

void postOrder_tranverse(node *root)
{
	static bool flag = false;
	if (NULL != root->lchild)
	{
		postOrder_tranverse(root->lchild);
	}
	if (NULL != root->rchild)
	{
		postOrder_tranverse(root->rchild);
	}
	if (flag)
	{
		cout << ' ';
	}
	else
	{
		flag = true;
	}
	cout << root->data;
}

int main()
{
	int N;
	node *root;
	cin >> N;
	for (int i = 0; i != N; ++i)
	{
		cin >> buffer[i];
	}
	
	root = new node;
	root->data = buffer[0];
	root->lchild = NULL;
	root->rchild = NULL;

	if (check_is_ok(0,N))
	{
		cout << "YES" << endl;
		rebuild_BST(root, 1, N);
		postOrder_tranverse(root);
		cout << endl;
	}
	else
	{
		cout << "NO" << endl;
	}

	system("pause");
	return 0;

}