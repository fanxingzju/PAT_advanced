#include <iostream>
#include <algorithm>
#include <stdlib.h>
using namespace std;

#define SAGES 0
#define NOBLEMEN 1
#define FOOLMEN 2
#define SMALLMEN 3
#define NOTPASS 4

typedef struct node
{
	int id;
	int virtue;
	int talent;
	int total;
	int kind;
}node;

node records[100010];
bool less_than_node(const node &A, const node &B)
{
	if (A.kind != B.kind)
	{
		return A.kind < B.kind;
	}
	else
	{
		if (A.total != B.total)
		{
			return A.total > B.total;
		}
		else
		{
			if (A.virtue != B.virtue)
			{
				return A.virtue > B.virtue;
			}
			else
			{
				return A.id < B.id;
			}
		}
	}
}
int main()
{
	int N, L, H;
	int passNum = 0;
	scanf("%d %d %d", &N, &L, &H);

	for (int i = 0; i != N; ++i)
	{
		scanf("%d %d %d", &records[i].id, &records[i].virtue, &records[i].talent);
		records[i].total = records[i].virtue + records[i].talent;
		if (records[i].virtue < L || records[i].talent < L)
		{
			records[i].kind = NOTPASS;
			continue;
		}
		++passNum;
		if (records[i].virtue >= H && records[i].talent >= H)
		{
			records[i].kind = SAGES;
			continue;
		}
		
		if (records[i].virtue >= H && records[i].talent < H)
		{
			records[i].kind = NOBLEMEN;
			continue;
		}

		if (records[i].virtue >= records[i].talent)
		{
			records[i].kind = FOOLMEN;
			continue;
		}
		records[i].kind = SMALLMEN;
	}

	printf("%d\n", passNum);
	if (0 == passNum)
	{
		return 0;
	}

	sort(records, records+N, less_than_node);

	for (int i = 0; i != passNum; ++i)
	{
		printf("%08d %d %d\n", records[i].id, records[i].virtue, records[i].talent);
	}

	system("pause");
	return 0;
}
