#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef struct node
{
	int id;
	int level;
	vector<int> children;
}node;

node records[100];
int N, M;
int maxnum = 1, maxlevel = 1;

void set_level()
{
	queue<int> pQueue, cQueue;
	int id;

	records[1].level = 1;
	pQueue.push(1);
	while (!pQueue.empty())
	{
		while (!pQueue.empty())
		{
			cQueue.push(pQueue.front());
			pQueue.pop();
		}
		while (!cQueue.empty())
		{
			id = cQueue.front();
			cQueue.pop();
			for (int i = 0; i != records[id].children.size(); ++i)
			{
				records[records[id].children.at(i)].level = records[id].level+1;
				pQueue.push(records[id].children.at(i));
			}
		}
		if (maxnum < pQueue.size())
		{
			maxlevel = records[id].level+1;
			maxnum = pQueue.size();
		}
	}
}

int main()
{
	int parent, child, num;
	scanf("%d %d", &N, &M);
	for (int i = 0; i != N; ++i)
	{
		records[i].id = i;
	}
	for (int i = 0; i != M; ++i)
	{
		scanf("%d %d", &parent, &num);
		for (int j = 0; j != num; ++j)
		{
			scanf("%d", &child);
			records[parent].children.push_back(child);
		}
	}
	
	set_level();
	printf("%d %d\n", maxnum, maxlevel);
	system("pause");
	return 0;
}
