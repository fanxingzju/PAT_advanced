#if 1
/*
可以AC的动态规划方法
动态规划经典的0-1背包问题
solution[n][m]表示用前n个元素可以得到的不超过m的最大值, 显然有
solution[n][m] = max{solution[n-1][m], solution[n-1][m-coins[n]] + coins[n]}
*/

/* 动态规划的时间复杂度O(N*M), 很明显动态优化的解法明显优于深搜算法*/

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
			/* 注意solution[i-1][j] == solution[i-1][j-coins[i]]+coins[i]的情况, flag[i][j]要置1, 这样才会选取"smallest sequence"*/
				solution[i][j] = solution[i-1][j-coins[i]]+coins[i];
				flag[i][j] = 1;						/* 说明计算 solution[i][j] 用到了 coins[i]*/
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
	reverse(coins+1, coins+N+1);			// 从大到小排序
	if (M == dp())
	{
		i = N;
		j = M;
		while (0 != j)
		{
			/*将 while (0 == flag[i][j]) 替换为 while (solution[i][j] != solution[i-1][j-coins[i]]+coins[i]) 也可以AC,
			不在需要flag数组, 还可以优化算法的空间复杂度*/
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
可以AC的深搜方法
最后一个case应该是N很大，M也比较大，将输入的N个数从小到大排序后，只有后面几个数满足条件
形式上例如：N=51, M=99, 2...2(47个2), 96, 3
2不可能是结果中的一项
*/

/* 深搜方法的时间复杂度O(2^n), 本题中使用 flag 只能对特定情况优化 */

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
	bool flag = false;								// 去掉flag相关语句, 最后一个case超时, 29分
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