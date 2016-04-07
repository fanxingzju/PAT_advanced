/* 各个测试点的数据量都不大*/
/* 特别注意下排序名次的确定*/
/*
注意一下输入:
5 5
310101 98 85 88
310102 70 95 88
310103 82 87 94
310104 80 80 82
310105 82 82 83
310101
310102
310103
310104
310105


正确输出是:
1 A
1 M
1 E
4 C
2 C

而不是：

1 A
1 M
1 E
3 C
2 C

课程C有2个学生的分数是82分，分数为80分的应是第4而不是第3。
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

typedef struct node
{
	int id;
	int cscore;
	int mathscore;
	int engscore;
	int totalscore;
	int crank;
	int mathrank;
	int engrank;
	int totalrank;
}node;

node records[2005];
int N, M;

bool bigger_than_totalscore(const node &A, const node &B)
{
	return A.totalscore > B.totalscore;
}

bool bigger_than_cscore(const node &A, const node &B)
{
	return A.cscore > B.cscore;
}

bool bigger_than_mathscore(const node &A, const node &B)
{
	return A.mathscore > B.mathscore;
}

bool bigger_than_engscore(const node &A, const node &B)
{
	return A.engscore > B.engscore;
}

bool less_than_id(const node &A, const node &B)
{
	return A.id < B.id;
}

int binary_search_id(int target)
{
	int low = 0;
	int high = N-1;
	int mid;
	while (low <= high)
	{
		mid = (low+high)/2;
		if (records[mid].id == target)
		{
			return mid;
		}
		else
		{
			if (records[mid].id > target)
			{
				high = mid-1;
			}
			else
			{
				low = mid+1;
			}
		}
	}
	return -1;
}

int main()
{
	int tmpscore, tmprank;
	int tmpid, index;
	int bestrank;
	char course;


	scanf("%d %d", &N, &M);
	for (int i = 0; i != N; ++i)
	{
		scanf("%d %d %d %d", &records[i].id, &records[i].cscore, &records[i].mathscore, &records[i].engscore);
		records[i].totalscore = records[i].cscore + records[i].mathscore + records[i].engscore;
	}
	
	sort(records, records+N, bigger_than_totalscore);
	tmpscore = tmprank = 0;

	for (int i = 0; i != N; ++i)
	{
		if (records[i].totalscore == tmpscore)
		{
			records[i].totalrank = tmprank;
		}
		else
		{
			tmprank = i+1;
			records[i].totalrank = tmprank;
			tmpscore = records[i].totalscore;
		}
	}

	sort(records, records+N, bigger_than_cscore);
	tmpscore = tmprank = 0;

	for (int i = 0; i != N; ++i)
	{
		if (records[i].cscore == tmpscore)
		{
			records[i].crank = tmprank;
		}
		else
		{
			tmprank = i+1;
			records[i].crank = tmprank;
			tmpscore = records[i].cscore;
		}
	}
	
	sort(records, records+N, bigger_than_mathscore);
	tmpscore = tmprank = 0;

	for (int i = 0; i != N; ++i)
	{
		if (records[i].mathscore == tmpscore)
		{
			records[i].mathrank = tmprank;
		}
		else
		{
			tmprank = i+1;
			records[i].mathrank = tmprank;
			tmpscore = records[i].mathscore;
		}
	}

	sort(records, records+N, bigger_than_engscore);
	tmpscore = tmprank = 0;

	for (int i = 0; i != N; ++i)
	{
		if (records[i].engscore == tmpscore)
		{
			records[i].engrank = tmprank;
		}
		else
		{
			tmprank = i+1;
			records[i].engrank = tmprank;
			tmpscore = records[i].engscore;
		}
	}

	sort(records, records+N, less_than_id);

	for (int i = 0; i != M; ++i)
	{
		scanf("%d", &tmpid);
		index = binary_search_id(tmpid);
		if (-1 == index)
		{
			printf("N/A\n");
			continue;
		}

		bestrank = records[index].engrank;
		course = 'E';
		if (records[index].mathrank <= bestrank)
		{
			bestrank = records[index].mathrank;
			course = 'M';
		}
		if (records[index].crank <= bestrank)
		{
			bestrank = records[index].crank;
			course = 'C';
		}
		if (records[index].totalrank <= bestrank)
		{
			bestrank = records[index].totalrank;
			course = 'A';
		}
		printf("%d %c\n", bestrank, course);
	}

	system("pause");
	return 0;
}