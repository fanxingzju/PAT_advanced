#include <iostream>
using namespace std;
#define INFINITE 0x7fffffff
#define MAX_CITY 500

int main()
{
	int cities,roads,src,dst;
	int teams[MAX_CITY];
	// int pathmatrix[MAX_CITY];				// pathmatrix ���ڴ洢���·���±�
	int shortpathtable[MAX_CITY];			// shortpathtable���ڴ洢���������·����Ȩֵ��
	int final[MAX_CITY];					// final[i] = 1, ��ʾ���src��i�����·��
	int matrix[MAX_CITY][MAX_CITY];			// �����洢·��
	int same[MAX_CITY];						// ������¼��src��i���е���ͬ���·������
	int sum[MAX_CITY];						// ������¼��src��i�����ż�������ŶӸ���

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
		final [i] = 0;						// ȫ�������ʼ��Ϊδ֪·��״̬
		// pathmatrix[i] = 0;					// ��ʼ��·������Ϊ0
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

		shortpathtable[i] = matrix[src][i];		// ����src�������ߵĶ������Ȩֵ

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

	final[src] = 1;							// src��src����Ҫ��·��
	shortpathtable[src] = 0;				// src��src���·��Ϊ0
	same[src] = 1;
	sum[src] = teams[src];


	/************************************************************************/
	/* Dijstra�㷨                                                          */
	/************************************************************************/
	for (i =1; i != cities; ++i)
	{
		min = INFINITE;
		for (j = 0; j != cities; ++j)
		{
			if (!final[j] && shortpathtable[j] < min)		// Ѱ�Ҿ���src����ĵ�
			{
				k = j;
				min = shortpathtable[j];
			}
		}

		// �����в���Ҫ�ļ��� 
		if (dst == k)
		{
			break;
		}

		final[k] = 1;						// ��Ŀǰ�ҵ������������Ϊ1

		for (j = 0; j != cities; ++j)			// ������ǰ���·��������
		{
			if (!final[j] && matrix[k][j] != INFINITE)
			{
				if (min+matrix[k][j] < shortpathtable[j])
				{
					shortpathtable[j] = min + matrix[k][j];
					// pathmatrix[j] = k;
					same[j] = same[k];						// ���¼���
					sum[j] = sum[k] + teams[j];
				}
				else
				{
					if (min+matrix[k][j] == shortpathtable[j])
					{
						same[j] += same[k];	
						if (sum[k]+teams[j] > sum[j])			// ��¼���ŶӵĽϴ���ֵ
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