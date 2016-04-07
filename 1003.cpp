#include <iostream>
using namespace std;
#define INFINITE 0x7fffffff
#define MAX_CITY 500

int main()
{
	int cities,roads,src,dst;
	int teams[MAX_CITY];
	// int pathmatrix[MAX_CITY];				// pathmatrix 用于存储最短路径下标
	int shortpathtable[MAX_CITY];			// shortpathtable用于存储到各点最短路径的权值和
	int final[MAX_CITY];					// final[i] = 1, 表示求的src到i的最短路径
	int matrix[MAX_CITY][MAX_CITY];			// 用来存储路径
	int same[MAX_CITY];						// 用来记录从src到i具有的相同最短路径个数
	int sum[MAX_CITY];						// 用来记录从src到i所能着急的最大团队个数

	int i, j, k, temp, min;
	cin >> cities >> roads >> src >> dst;

	for (i = 0; i != cities; ++i)
	{
		cin >> teams[i];
	}

	for (i = 0; i != cities; ++i)
	{
		for (j = 0; j != cities; ++j)
		{
			matrix[i][j] = INFINITE;
		}
		final [i] = 0;						// 全部顶点初始化为未知路径状态
		// pathmatrix[i] = 0;					// 初始化路径数组为0
	}

	for (k = 0; k != roads; ++k)
	{
		cin >> i >> j >> temp;
		matrix[i][j] = matrix[j][i] = temp;
	}

	for (i = 0; i != cities; ++i)
	{
		if (i == src)
		{
			continue;
		}

		shortpathtable[i] = matrix[src][i];		// 将与src点有连线的顶点加上权值

		if (INFINITE == shortpathtable[i])
		{
			same[i] = 0;
			sum[i] = teams[src];
		}
		else
		{
			same[i] = 1;
			sum[i] = teams[src]+teams[i];
		}
	}

	final[src] = 1;							// src到src不需要求路径
	shortpathtable[src] = 0;				// src到src最短路径为0
	same[src] = 1;
	sum[src] = teams[src];


	/************************************************************************/
	/* Dijstra算法                                                          */
	/************************************************************************/
	for (i =1; i != cities; ++i)
	{
		min = INFINITE;
		for (j = 0; j != cities; ++j)
		{
			if (!final[j] && shortpathtable[j] < min)		// 寻找距离src最近的点
			{
				k = j;
				min = shortpathtable[j];
			}
		}

		// 不进行不必要的计算 
		if (dst == k)
		{
			break;
		}

		final[k] = 1;						// 将目前找到的最近顶点置为1

		for (j = 0; j != cities; ++j)			// 修正当前最短路径及距离
		{
			if (!final[j] && matrix[k][j] != INFINITE)
			{
				if (min+matrix[k][j] < shortpathtable[j])
				{
					shortpathtable[j] = min + matrix[k][j];
					// pathmatrix[j] = k;
					same[j] = same[k];						// 重新计数
					sum[j] = sum[k] + teams[j];
				}
				else
				{
					if (min+matrix[k][j] == shortpathtable[j])
					{
						same[j] += same[k];	
						if (sum[k]+teams[j] > sum[j])			// 记录下团队的较大数值
						{
							sum[j] = sum[k]+teams[j];
						}
					}
				}
			}
		}

	}

	cout << same[dst] << ' ' << sum[dst] << endl;
	return 0;
}