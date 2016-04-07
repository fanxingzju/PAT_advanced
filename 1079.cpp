#include <stdio.h>
#include <queue>
#include <math.h>
#include <stdlib.h>
using namespace std;
#define MAX_NUM 100010

typedef struct node
{
	int level;
	int parent;
	int amount;			// amount != 0, retails amount定义为int即可, 不需double
}node;
node records[MAX_NUM];
int N;
// P 和 r 必须定义为double, float会有case通不过
double P, r;

// O(nlgn)
void precess_level()
{
	queue<int> nQ;
	int id;
	int count = 0;
	records[0].level = 0;
	for (int i = 1; i != N; ++i)
	{
		id = i;
		count = 0;
		while (-1 == records[id].level)
		{
			nQ.push(id);
			id = records[id].parent;
			++count;
		}
		count += records[id].level;
		while (!nQ.empty())
		{
			id = nQ.front();
			nQ.pop();
			records[id].level = count--;
		}
	}
}

int main()
{
	int num, id;
	double totalsale = 0;
	scanf("%d %lf %lf", &N, &P, &r);
	// case2 1分
	if (1 == N)
	{
		scanf("%d %d", &id, &num);
		printf("%0.1lf\n", P*num);
		return 0;
	}
	for (int i = 0; i != N; ++i)
	{
		scanf("%d", &num);
		if (0 == num)
		{
			scanf("%d", &records[i].amount);
		}
		else
		{
			for (int j = 0; j != num; ++j)
			{
				scanf("%d", &id);
				records[id].parent = i;
			}
		}
		records[i].level = -1;
	}
	precess_level();
	r = 1 + r*1.0/100;
	for (int i = 1; i != N; ++i)
	{
		if (0 != records[i].amount)
		{
			totalsale += records[i].amount * pow(r, records[i].level);
		}
	}
	totalsale *= P;
	printf("%0.1lf\n", totalsale);
	system("pause");
	return 0;
}