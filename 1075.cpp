#include <stdio.h>
#include <algorithm>
int fullmark[5];
typedef struct node
{
	int id;
	int score[5];
	int prefectNum;
	int totalscore;
	int flag;					// flag == K 不输出
}node;

node records[10010];
int N, K, M;

bool less_than_node(const node &A, const node &B)
{
	if (A.totalscore != B.totalscore)
	{
		return A.totalscore > B.totalscore;
	}
	else
	{
		if (A.prefectNum != B.prefectNum)
		{
			return A.prefectNum > B.prefectNum;
		}
		else
		{
			// A 排在 B 后面
			if (A.flag == K && B.flag != K)
			{
				return false;
			}
			// A 排在 B 前面
			if (A.flag != K && B.flag == K)
			{
				return true;
			}
			return A.id < B.id;
		}
	}
}

int main()
{
	int user_id, problem_id, partial_score_obtained;
	int rank = 0;
	int totalnum = 0x7fffffff;
	scanf("%d %d %d", &N, &K, &M);

	for (int i = 0; i != K; ++i)
	{
		scanf("%d", fullmark+i);
	}

	for (int i = 1; i != N+1; ++i)
	{
		records[i].id = i;
		for (int j = 0; j != K; ++j)
		{
			records[i].score[j] = -2;
		}
	}

	for (int i = 0; i != M; ++i)
	{
		scanf("%d %d %d", &user_id, &problem_id, &partial_score_obtained);
		if (records[user_id].score[problem_id-1] < partial_score_obtained)
		{
			records[user_id].score[problem_id-1] = partial_score_obtained;
		}
	}

	for (int i = 1; i != N+1; ++i)
	{
		for (int j = 0; j != K; ++j)
		{
			if (records[i].score[j] < 0)
			{
				++records[i].flag;
			}
			else
			{
				if (fullmark[j] == records[i].score[j])
				{
					++records[i].prefectNum;
				}
				records[i].totalscore += records[i].score[j];
			}
		}
	}

	std::sort(records+1, records+N+1, less_than_node);

	for (int i = 1; i != N+1; ++i)
	{
		if (records[i].flag == K)
		{
			break;
		}
		if (totalnum > records[i].totalscore)
		{
			totalnum = records[i].totalscore;
			rank = i;
		}
		printf("%d %05d %d", rank, records[i].id, records[i].totalscore);
		for (int j = 0; j != K; ++j)
		{
			if (-2 == records[i].score[j])
			{
				printf(" -");
			}
			else
			{
				if (-1 == records[i].score[j])
				{
					printf(" 0");
				} 
				else
				{
					printf(" %d", records[i].score[j]);
				}
			}
		}
		printf("\n");
	}

	system("pause");
	return 0;
}
