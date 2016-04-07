#include <algorithm>
#include <stdio.h>
using namespace std;

typedef struct node
{
	int number;
	int index;
}node;

bool less_than_number(const node &A, const node &B)
{
	return A.number < B.number;
}

bool less_than_index(const node &A, const node &B)
{
	return A.index < B.index;
}

bool equal_number(const node &A, const node &B)
{
	return A.number == B.number;
}

#define MAX_PEOPLE 100005
node records[MAX_PEOPLE];			// 保存所有记录
node results[MAX_PEOPLE];			// 保存所有unique记录
int totalNum, uniqueNum;

void copy_unique()
{
	node *pre, *cur, *next;
	// 先处理掉三种特殊情况
	if (0 == totalNum)
	{
		return ;
	}
	if (1 == totalNum)
	{
		results[uniqueNum++] = records[0];
		return ;
	}
	if (2 == totalNum)
	{
		if (records[0].number != records[1].number)
		{
			results[uniqueNum++] = records[0];
			results[uniqueNum++] = records[1];
		}
		return ;
	}
	// 通常情况(totalNum >= 3)
	if (records[0].number != records[1].number)
	{
		results[uniqueNum++] = records[0];
	}
	for (int i = 1; i != totalNum-1; ++i)
	{
		pre = records + i - 1;
		cur = records + i;
		next = records + i + 1;
		if (pre->number != cur->number && cur->number != next->number)
		{
			results[uniqueNum++] = *cur;
		}
	}
	if (records[totalNum-2].number != records[totalNum-1].number)
	{
		results[uniqueNum++] = records[totalNum-1];
	}
	return ;
}

int main()
{
	scanf("%d", &totalNum);
	for (int i = 0; i != totalNum; ++i)
	{
		scanf("%d", &records[i].number);
		records[i].index = i;

	}
	sort(records, records+totalNum, less_than_number);

	copy_unique();
	
	if (uniqueNum == 0)
	{
		printf("None\n");
	}
	else
	{
		sort(results, results+uniqueNum, less_than_index);
		printf("%d\n", results[0]);
	}

	system("pause");
	return 0;
}