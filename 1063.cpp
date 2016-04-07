/*
==========================================================
测试点	结果	用时(ms)	内存(kB)	得分/满分
0	答案正确	1	412	12/12
1	答案正确	1	424	3/3
2	答案正确	1	384	3/3
3	答案正确	6	768	3/3
4	答案正确	31	768	4/4
==========================================================
*/
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
using namespace std;
int records[50][10005];
int N, M, K;


int main()
{
	int id1, id2;
	int index1, index2;
	int nc, nt;
	scanf("%d", &N);
	for (int i = 0; i != N; ++i)
	{
		scanf("%d", &M);
		records[i][0] = M;
		for (int j = 1; j != M+1; ++j)
		{
			scanf("%d", &records[i][j]);
		}
		sort(records[i]+1, records[i]+M+1);
		M = unique(records[i]+1, records[i]+M+1) - (records[i]+1);
		records[i][0] = M;
	}

	scanf("%d", &K);
	for (int i = 0; i != K; ++i)
	{
		scanf("%d %d", &id1, &id2);
		--id1;
		--id2;
		index1 = index2 = 1;
		nc = nt = 0;
		while(index1 != records[id1][0]+1 && index2 != records[id2][0]+1)
		{
			if (records[id1][index1] == records[id2][index2])
			{
				++nc;
				++index1;
				++index2;
			}
			else
			{
				if (records[id1][index1] < records[id2][index2])
				{
					++index1;
				}
				else
				{
					++index2;
				}
			}
		}
		nt = records[id1][0] + records[id2][0] - nc;
		printf("%0.1f%%\n", nc*1.0/nt*100);
	}


	system("pause");
	return 0;
}






#if 0
// 利用set去重,可以通过
/*
==========================================================
测试点	结果	用时(ms)	内存(kB)	得分/满分
0	答案正确	1	384	12/12
1	答案正确	1	432	3/3
2	答案正确	1	384	3/3
3	答案正确	6	384	3/3
4	答案正确	91	2816	4/4
==========================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <algorithm>			// set_intersection(...)
#include <iterator>				// inserter(...)
using namespace std;
int N, M, K;
set<int> nSet[50];
int main()
{
	int tmp;
	set<int> result;
	int index1, index2;
	int nc, nt;
	scanf("%d", &N);
	for (int i = 0; i != N; ++i)
	{
		scanf("%d", &M);
		for (int j = 0; j != M; ++j)
		{
			scanf("%d", &tmp);
			nSet[i].insert(tmp);
		}
	}
	scanf("%d", &K);
	for (int i = 0; i != K; ++i)
	{
		scanf("%d %d", &index1, &index2);
		--index1;
		--index2;
		set_intersection(nSet[index1].begin(), nSet[index1].end(), 
			nSet[index2].begin(), nSet[index2].end(), inserter(result, result.end()));
		nc = result.size();
		nt = nSet[index1].size() + nSet[index2].size() - nc;
		result.clear();
		printf("%0.1f%%\n", nc*1.0/nt*100);
	}
	system("pause");
	return 0;
}
#endif

#if 0
// 用records数组来记录某个数是否在全部N组输入中是否出现, 反而增加了计算量
// 最后一个case超时
#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
	int data;
	int index[50];
	struct node *next;
}node;
int queries[4010];
node *nlist = NULL;
int N, M, K;

void insert(int key, int index)
{
	node *pre = NULL;
	node *cur = nlist;
	node *ntmp;

	while (cur != NULL && cur->data < key)
	{
		pre = cur;
		cur = cur->next;
	}

	if (NULL != cur && cur->data == key)
	{
		cur->index[index] = 1;
		return ;
	}

	// 插在链表头
	if (NULL == pre)
	{
		ntmp = new node;
		ntmp->data = key;
		ntmp->index[index] = 1;
		ntmp->next = nlist;
		nlist = ntmp;
		return ;
	}

	ntmp = new node;
	ntmp->data = key;
	ntmp->index[index] = 1;
	ntmp->next = pre->next;
	pre->next = ntmp;
	return ;
}

void freelist()
{
	node *ntmp = nlist;
	while (NULL != nlist)
	{
		ntmp = nlist;
		nlist = nlist->next;
		free(ntmp);
	}
}

void process_query(int index1, int index2)
{
	int nc = 0, nt = 0;
	node *ntmp = nlist;
	while (NULL != ntmp)
	{
		if (ntmp->index[index1] == 1 && ntmp->index[index2] == 1)
		{
			++nc;
		}
		if (ntmp->index[index1] == 1 || ntmp->index[index2] == 1)
		{
			++nt;
		}
		ntmp = ntmp->next;
	}
	if (0 == nt)
	{
		printf("0.0\n");
	}
	else
	{
		printf("%0.1f%%\n", nc*1.0/nt*100);
	}
}

void nlistShow()
{
	node *tmp = nlist;
	while (NULL != tmp)
	{
		printf("%d ", tmp->data);
		for (int i = 0; i != 50; ++i)
		{
			if (1 == tmp->index[i])
			{
				printf("%d ", i);
			}
		}
		tmp = tmp->next;
		printf("\n");
	}
}

int main()
{
	int tmp;
	scanf("%d", &N);
	for (int i = 0; i != N; ++i)
	{
		scanf("%d", &M);
		for (int j = 0; j != M; ++j)
		{
			scanf("%d", &tmp);
			insert(tmp, i);
		}
	}
	// nlistShow();
	scanf("%d", &K);
	for (int i = 0; i != K; ++i)
	{
		scanf("%d %d", queries+2*i, queries+2*i+1);
	}
	for (int i = 0; i != K; ++i)
	{
		process_query(queries[i*2]-1, queries[i*2+1]-1);
	}
	system("pause");
	return 0;
}
#endif