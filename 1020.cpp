#include <iostream>
#include <queue>
using namespace std;

typedef struct node
{
	int data;
	struct node *lchild;
	struct node *rchild;
}node;

#define MAXLENGTH 32

#if 0
void preOrderTraverse(node *root)
{
	if (root)
	{
		cout << root->data << ' ';
		preOrderTraverse(root->lchild);
		preOrderTraverse(root->lchild);
	}
}

void inOrderTraverse(node *root)
{
	if (root)
	{
		inOrderTraverse(root->lchild);
		cout << root->data << ' ';
		inOrderTraverse(root->rchild);
	}
}

void postOrderTraverse(node *root)
{
	if (root)
	{
		postOrderTraverse(root->lchild);
		postOrderTraverse(root->rchild);
		cout << root->data << ' ';
	}
}
#endif 
void levelOrderTraverse(node *root)
{
	queue<node *> Q;
	node *temp;
	bool flag = false;
	if (root)
	{
		Q.push(root);
		while (!Q.empty())
		{
			temp = Q.front();
			Q.pop();
			if (flag)
			{
				cout << ' ';
			}
			else
			{
				flag = true;
			}
			cout << temp->data;
			if (temp->lchild)
			{
				Q.push(temp->lchild);
			}
			if (temp->rchild)
			{
				Q.push(temp->rchild);
			}
		}
	}
}

bool inPostOrderRestore(int *postOrder, int *inOrder, int num, node *root)
{
	int index = 0;
	root->data = postOrder[num-1];
	while (index != num)
	{
		if (inOrder[index] == postOrder[num-1])
		{
			break;
		}
		++index;
	}
	// 未找到相同项，输入数据有问题
	if (num == index)
	{
		return false;
	}
	// 左子树不为空
	if (0 != index)
	{
		root->lchild = new node;
		root->lchild->lchild = NULL;
		root->lchild->rchild = NULL;
		inPostOrderRestore(postOrder, inOrder, index, root->lchild);
	}

	// 右子树不为空
	if (index != num-1)
	{
		root->rchild = new node;
		root->rchild->lchild = NULL;
		root->rchild->rchild = NULL;
		// 调整位置
		for (int i = index; i != num-1; ++i)
		{
			inOrder[i] = inOrder[i+1];
		}
		inPostOrderRestore(postOrder+index, inOrder+index, num-index-1, root->rchild);
	}
	return true;
}


int main()
{

	int num;
	node *root;
	int postOrder[MAXLENGTH];
	int inOrder[MAXLENGTH];

	cin >> num;
	root = new node;

	root->lchild = NULL;
	root->rchild = NULL;

	for (int i = 0; i != num; ++i)
	{
		cin >> postOrder[i];
	}
	for (int i = 0; i != num; ++i)
	{
		cin >> inOrder[i];
	}
	inPostOrderRestore(postOrder, inOrder, num, root);
	levelOrderTraverse(root);
	cout << endl;

	system("pause");
	return 0;

}




