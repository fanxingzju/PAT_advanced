#include <iostream>
#include <queue>
using namespace std;

typedef struct myElement 
{
	int			ID;
	int			level;				// ��������һ��
	int			flag;				// û�к�����Ϊ0, �к���Ϊ1
	int			firstchild;			// ָ���һ������ ���û�к���flag��Ϊ0
	int			next;				// ָ����һ���Լ�����ͬ˫�׵��ֵ�, ���Ϊ0���ʾ��Ϊ�Լ�˫�׵����һ������
}Element;

Element tree[101];					// �����洢���� ( ��ʹ��tree[0] )
									// ��Աȫ����ʼ��Ϊ0


int locateID(const int &ID)
{	
	int index;
	for (index = 1; 0 != tree[index].ID; ++index)
	{
		if (ID == tree[index].ID)
		{
			return index;
		}
	}
	return -1;
}

int main()
{
	int M, N, K, ID;
	int freepos = 1;					// ָ���һ�������ڴ洢���ݵ�λ��
	int parentpos;						// ���ڵ�λ��
	int curpos;							// ��ǰԪ�ص�λ��
	int prepos;							// ǰһ��Ԫ�ص�λ��
	int rootpos;						// ����λ��
	queue<int> tque;					// ���ڲ������

	int level = 1;
	int cnt = 0;

	// ������Ϣ��������
	cin >> N >> M;
	while(M--)
	{
		cin >> ID >> K;
		parentpos = locateID(ID);
		if (-1 == parentpos)
		{
			parentpos = freepos++;
		}
		// ���ڵ�
		tree[parentpos].ID = ID;		// ���֮ǰ���ڸ�ID�ڵ�, �൱����������һ��
		tree[parentpos].flag = 1;

		// �����M��Ϊ����Ҷ�ӡ��ڵ㣬����������һ������
		--K;
		cin >> ID;
		curpos = locateID(ID);
		if (-1 == curpos)
		{
			curpos = freepos++;
		}
		tree[parentpos].firstchild = curpos;			// �������ø��ڵ�ĵ�һ������

		// ���õ�һ�����ӽڵ�
		// ���ӽڵ�flag����Ҫ�Ķ��� �����û�к��ӣ� ����0����
		// ���ӽڵ�nextλ���ö��� ���ֳ�ʼ״̬��0����
		tree[curpos].ID = ID;			// ��֮ǰ���ڴ�ID, �������ò����������

		prepos = curpos;
		while (K--)
		{
			cin >> ID;
			curpos = locateID(ID);
			if (-1 == curpos)
			{
				curpos = freepos++;
			}
			tree[prepos].next = curpos;		// ��������ǰһ�����ӽڵ����Ϣ
			// ���õ�ǰ���ӽڵ�
			tree[curpos].ID = ID;			// ���֮ǰ���ڸ�ID, �ظ����ò����������
			prepos = curpos;
		}
	}

	rootpos = locateID(1);
	tree[rootpos].level = 1;
	tque.push(rootpos);

	// �������, ȷ��ÿ���ڵ�����һ��
	while (!tque.empty())
	{
		parentpos = tque.front();
		tque.pop();

		if (level != tree[parentpos].level)
		{
			++level;							// �µ�һ��, ���¿�ʼ����
			cout << cnt << ' ';
			cnt = 0;
		}

		if (0 == tree[parentpos].firstchild)
		{
			++cnt;
		}



		curpos = tree[parentpos].firstchild;
		while (0 != curpos)
		{
			tree[curpos].level = tree[parentpos].level+1;
			tque.push(curpos);
			curpos = tree[curpos].next;						// ������һ���ڵ�
		}
	}

	cout << cnt << endl;

	// system("pause");
	return 0;
}







