// 所有case通过
#include <stdio.h>
#include <algorithm>
using namespace std;

typedef struct node
{
	int startpos;
	int endpos;
	int sum;
}node;

node results[100005];
int diamonds[100005];

bool node_less_than(const node &A, const node &B)
{
	if (A.sum == B.sum)
	{
		return A.startpos < B.startpos;
	}
	else
	{
		return A.sum < B.sum;
	}
}

int main()
{
	int N, M;
	int sum = 0;
	int i, j;
	scanf("%d %d", &N, &M);
	for (i = 1; i != N+1; ++i)
	{
		scanf("%d", diamonds+i);
	}

	// 改进循环部分
	// j只增不减
	j = 1;
	for (i = 1; i != N+1; ++i)
	{
		// dimonds[0] = 0; 所以不会引起错误
		sum = sum - diamonds[i-1];
		for ( ; j != N+1 && sum < M; ++j)
		{
			sum += diamonds[j];
		}
		results[i].startpos = i;
		results[i].endpos = j-1;
		results[i].sum = sum;
	}

	sort(results+1, results+1+N, node_less_than);

	i = 1;

	while (results[i].sum < M)
	{
		++i;
	}

	sum = results[i].sum;

	while (sum == results[i].sum)
	{
		printf("%d-%d\n", results[i].startpos, results[i].endpos);
		++i;
	}
	system("pause");
	return 0;
}






#if 0
// case 2, 5 超时
#include <stdio.h>
#include <algorithm>
using namespace std;

typedef struct node
{
	int startpos;
	int endpos;
	int sum;
}node;

node results[100005];
int diamonds[100005];

bool node_less_than(const node &A, const node &B)
{
	if (A.sum == B.sum)
	{
		return A.startpos < B.startpos;
	}
	else
	{
		return A.sum < B.sum;
	}
}

int main()
{
	int N, M;
	int sum;
	int i, j;
	scanf("%d %d", &N, &M);
	for (i = 1; i != N+1; ++i)
	{
		scanf("%d", diamonds+i);
	}

	for (i = 1; i != N+1; ++i)
	{
		sum = 0;
		for (j = i; j != N+1 && sum < M; ++j)
		{
			sum += diamonds[j];
		}
		results[i].startpos = i;
		results[i].endpos = --j;
		results[i].sum = sum;
	}

	sort(results+1, results+1+N, node_less_than);

	i = 1;

	while (results[i].sum < M)
	{
		++i;
	}

	sum = results[i].sum;

	while (sum == results[i].sum)
	{
		printf("%d-%d\n", results[i].startpos, results[i].endpos);
		++i;
	}
	system("pause");
	return 0;
}
#endif