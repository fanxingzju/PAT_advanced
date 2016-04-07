#if 1
/*
����AC�Ķ�̬�滮����
��̬�滮�����0-1��������
solution[n][m]��ʾ��ǰn��Ԫ�ؿ��Եõ��Ĳ�����m�����ֵ, ��Ȼ��
solution[n][m] = max{solution[n-1][m], solution[n-1][m-coins[n]] + coins[n]}
*/

/* ��̬�滮��ʱ�临�Ӷ�O(N*M), �����Զ�̬�Ż��Ľⷨ�������������㷨*/

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

int solution[10010][105];
int flag[10010][105];
int N, M;
int coins[10010];

int dp()
{
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= M; ++j)
		{
			if (j < coins[i] || solution[i-1][j] > solution[i-1][j-coins[i]]+coins[i])
			{
				solution[i][j] = solution[i-1][j];
			}
			else
			{
			/* ע��solution[i-1][j] == solution[i-1][j-coins[i]]+coins[i]�����, flag[i][j]Ҫ��1, �����Ż�ѡȡ"smallest sequence"*/
				solution[i][j] = solution[i-1][j-coins[i]]+coins[i];
				flag[i][j] = 1;						/* ˵������ solution[i][j] �õ��� coins[i]*/
			}
		}
	}
	return solution[N][M];
}

int main()
{
	int i, j;
	scanf("%d %d", &N, &M);
	for (i = 1; i != N+1; ++i)
	{
		scanf("%d", coins+i);
	}
	sort(coins+1, coins+N+1);
	reverse(coins+1, coins+N+1);			// �Ӵ�С����
	if (M == dp())
	{
		i = N;
		j = M;
		while (0 != j)
		{
			/*�� while (0 == flag[i][j]) �滻Ϊ while (solution[i][j] != solution[i-1][j-coins[i]]+coins[i]) Ҳ����AC,
			������Ҫflag����, �������Ż��㷨�Ŀռ临�Ӷ�*/
			while (0 == flag[i][j])
			{
				--i;
			}
			if (coins[i] != j)
			{
				printf("%d ", coins[i]);
			}
			else
			{
				printf("%d\n", coins[i]);
			}
			j -= coins[i];
			--i;
		}
	}
	else
	{
		printf("No Solution\n");
	}
	system("pause");
	return 0;
}

#else
/*
����AC�����ѷ���
���һ��caseӦ����N�ܴ�MҲ�Ƚϴ󣬽������N������С���������ֻ�к��漸������������
��ʽ�����磺N=51, M=99, 2...2(47��2), 96, 3
2�������ǽ���е�һ��
*/

/* ���ѷ�����ʱ�临�Ӷ�O(2^n), ������ʹ�� flag ֻ�ܶ��ض�����Ż� */

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
int coins[10010];
vector<int> result;

bool dfs(int money, int pos)
{
	bool flag = false;								// ȥ��flag������, ���һ��case��ʱ, 29��
	result.push_back(pos);
	money -= coins[pos++];

	if (0 == money)
	{
		return true;
	}
	if (pos >= N || coins[pos] > money)
	{
		result.pop_back();
		return false;
	}

	for (int i = pos; i < N; ++i)
	{
		if (flag && coins[i] == coins[i-1])
		{
			continue;
		}
		else
		{
			flag = false;
		}

		if (money < coins[i])
		{
			break;
		}
		else
		{
			if (dfs(money, i))
			{
				return true;
			}
			flag = true;
		}
	}
	result.pop_back();
	return false;
}

int main()
{
	scanf("%d %d", &N, &M);
	for (int i = 0; i != N; ++i)
	{
		scanf("%d", coins+i);
	}
	sort(coins, coins+N);
	for (int i = 0; i != N; ++i)
	{
		if (dfs(M, i))
		{
			break;
		}
		result.clear();
	}
	if (!result.empty())
	{
		printf("%d", coins[result[0]]);
		for (int i = 1; i != result.size(); ++i)
		{
			printf(" %d", coins[result[i]]);
		}
	}
	else
	{
		printf("No Solution");
	}
	printf("\n");

	system("pause");
	return 0;
}
#endif