#include <stdio.h>
#include <queue>
#include <stdlib.h>
using namespace std;

int matrix[1287][129][61];
int M, N, L, T;
int total = 0;
int dx[6] = {1, -1, 0, 0, 0, 0};
int dy[6] = {0, 0, 1, -1, 0, 0};
int dz[6] = {0, 0, 0, 0, 1, -1};

typedef struct node
{
	int xpos;
	int ypos;
	int zpos;
}node;

bool isInRange(node target)
{
	return ((target.xpos >= 0) && (target.xpos < M) && (target.ypos >= 0)
		&& (target.ypos < N) && (target.zpos >= 0) && (target.zpos < L));
}

void dfs(int xpos, int ypos, int zpos)
{
	queue<node> nQ;
	int cnt = 1;
	node cur, next;

	matrix[xpos][ypos][zpos] = 0;
	cur.xpos = xpos;
	cur.ypos = ypos;
	cur.zpos = zpos;

	nQ.push(cur);

	while (!nQ.empty())
	{
		cur = nQ.front();
		nQ.pop();

		for (int i = 0; i != 6; ++i)
		{
			next.xpos = cur.xpos + dx[i];
			next.ypos = cur.ypos + dy[i];
			next.zpos = cur.zpos + dz[i];
			if (isInRange(next) && matrix[next.xpos][next.ypos][next.zpos] == 1)
			{
				matrix[next.xpos][next.ypos][next.zpos] = 0;
				++cnt;
				nQ.push(next);
			}
		}
	}
	if (cnt >= T)
	{
		total += cnt;
	}
	
}



int main()
{
	scanf("%d %d %d %d", &M, &N, &L, &T);
	for (int k = 0; k != L; ++k)
	{
		for (int i = 0; i != M; ++i)
		{
			for (int j = 0; j != N; ++j)
			{
				scanf("%d", &matrix[i][j][k]);
			}
		}
	}

	for (int k = 0; k != L; ++k)
	{
		for (int i = 0; i != M; ++i)
		{
			for (int j = 0; j != N; ++j)
			{
				if (matrix[i][j][k] == 1)
				{
					dfs(i, j, k);
				}
			}
		}
	}

	printf("%d\n", total);
	system("pause");
	return 0;
}