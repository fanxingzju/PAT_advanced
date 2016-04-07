#include <iostream>
#include <queue>
using namespace std;

typedef struct myElement 
{
	int			ID;
	int			level;				// 在树的哪一层
	int			flag;				// 没有孩子则为0, 有孩子为1
	int			firstchild;			// 指向第一个孩子 如果没有孩子flag设为0
	int			next;				// 指向下一个自己的相同双亲的兄弟, 如果为0则表示它为自己双亲的最后一个孩子
}Element;

Element tree[101];					// 用来存储数据 ( 不使用tree[0] )
									// 成员全部初始化为0


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
	int freepos = 1;					// 指向第一个可用于存储数据的位置
	int parentpos;						// 父节点位置
	int curpos;							// 当前元素的位置
	int prepos;							// 前一个元素的位置
	int rootpos;						// 根的位置
	queue<int> tque;					// 用于层序遍历

	int level = 1;
	int cnt = 0;

	// 读入信息，建立树
	cin >> N >> M;
	while(M--)
	{
		cin >> ID >> K;
		parentpos = locateID(ID);
		if (-1 == parentpos)
		{
			parentpos = freepos++;
		}
		// 父节点
		tree[parentpos].ID = ID;		// 如果之前存在该ID节点, 相当于重新设置一遍
		tree[parentpos].flag = 1;

		// 输入的M行为“非叶子”节点，即它至少有一个孩子
		--K;
		cin >> ID;
		curpos = locateID(ID);
		if (-1 == curpos)
		{
			curpos = freepos++;
		}
		tree[parentpos].firstchild = curpos;			// 补充设置父节点的第一个孩子

		// 设置第一个孩子节点
		// 孩子节点flag不需要改动， 如果它没有孩子， 保持0即可
		// 孩子节点next位不用动， 保持初始状态的0即可
		tree[curpos].ID = ID;			// 如之前存在此ID, 重新设置不会引起错误

		prepos = curpos;
		while (K--)
		{
			cin >> ID;
			curpos = locateID(ID);
			if (-1 == curpos)
			{
				curpos = freepos++;
			}
			tree[prepos].next = curpos;		// 补充设置前一个孩子节点的信息
			// 设置当前孩子节点
			tree[curpos].ID = ID;			// 如果之前存在该ID, 重复设置不会引起错误
			prepos = curpos;
		}
	}

	rootpos = locateID(1);
	tree[rootpos].level = 1;
	tque.push(rootpos);

	// 层序遍历, 确定每个节点在哪一层
	while (!tque.empty())
	{
		parentpos = tque.front();
		tque.pop();

		if (level != tree[parentpos].level)
		{
			++level;							// 新的一层, 重新开始计数
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
			curpos = tree[curpos].next;						// 处理下一个节点
		}
	}

	cout << cnt << endl;

	// system("pause");
	return 0;
}







