// �ο��������ݽṹ����AVL�Ļ�������
// ���������������˵Ĵ��룬û���ֳ��˽���AVL��֮��Ľⷨ
#include <iostream>
using namespace std;

typedef struct node
{
	int data;
	int bf;				// �ڵ�ƽ������
	struct node *lchild, *rchild;
}node;

#define LH 1
#define EH 0
#define RH -1

void R_Rotate(node *&T)
{
	node *L = T->lchild;
	T->lchild = L->rchild;
	L->rchild = T;
	T = L;
}

void L_Rotate(node *&T)
{
	node *R = T->rchild;
	T->rchild = R->lchild;
	R->lchild = T;
	T = R;
}

void LeftBalance(node *&T)
{
	node *L, *Lr;
	L = T->lchild;
	switch(L->bf)
	{
	// �½ڵ������T�����ӵ���������
	case LH:
		T->bf = L->bf = EH;
		R_Rotate(T);
		break;
	// �½ڵ������T�����ӵ���������
	case RH:
		Lr = L->rchild;
		switch(Lr->bf)
		{
		case LH:
			T->bf = RH;
			L->bf = EH;
			break;
		case EH:
			T->bf = L->bf = EH;
			break;
		case RH:
			T->bf = EH;
			L->bf = LH;
			break;
		}
		Lr->bf = EH;
		L_Rotate(T->lchild);
		R_Rotate(T);
	}
}

void RightBalance(node *&T)
{
	node *R, *Rl;
	R = T->rchild;
	switch (R->bf)
	{
	// ����T�Һ��ӵ��ҽڵ���
	case RH:
		T->bf = R->bf = EH;
		L_Rotate(T);
		break;
	//������T�Һ��ӵ���ڵ���
	case LH:
		Rl = R->lchild;
		switch (Rl->bf)
		{
		case LH:
			T->bf = EH;
			R->bf = RH;
			break;
		case EH:
			T->bf = EH;
			R->bf = EH;
			break;
		case RH:
			T->bf = LH;
			R->bf = EH;
			break;
		}
		Rl->bf = EH;
		R_Rotate(T->rchild);
		L_Rotate(T);
	}
}

bool insertAVL(node *&T, int key, bool &taller)
{
	if (NULL == T)
	{
		T = new node;
		T->lchild = T->rchild = NULL;
		T->data = key;
		T->bf = EH;
		taller = true;
	}
	else
	{
		if (key == T->data)
		{
			taller = false;
			return false;
		}
		if (key < T->data)
		{
			if (!insertAVL(T->lchild, key, taller))
			{
				return false;
			}
			if (taller)
			{
				switch(T->bf)
				{
				case LH:
					LeftBalance(T);
					taller = false;
					break;
				case EH:
					T->bf = LH;
					taller = true;
					break;
				case RH:
					T->bf = EH;
					taller = false;
					break;
				}
			}
		} 
		else
		{
			if (!insertAVL(T->rchild, key, taller))
			{
				return false;
			}
			if (taller)
			{
				switch(T->bf)
				{
				case LH:
					T->bf = EH;
					taller = false;
					break;
				case EH:
					T->bf = RH;
					taller = true;
					break;
				case RH:
					RightBalance(T);
					taller = false;
					break;
				}
			}
		}
	}
	return true;
}

void destoryAVL(node *&T)
{
	if (NULL != T->lchild)
	{
		destoryAVL(T->lchild);
	}
	if (NULL != T->rchild)
	{
		destoryAVL(T->rchild);
	}
	delete T;
}


int main()
{
	int N;
	int tmp;
	node *bitree = NULL;
	bool flag;

	scanf("%d", &N);
	for (int i = 0; i != N; ++i)
	{
		scanf("%d", &tmp);
		insertAVL(bitree, tmp, flag);
	}
	printf("%d\n", bitree->data);
	destoryAVL(bitree);
	bitree = NULL;
	system("pause");
	return 0;
}