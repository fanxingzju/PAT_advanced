#include <iostream>
using namespace std;

const int maxmax = 0xffffff;
const int maxnode = 505;

int N, M, S, D;
int vpre[maxnode];
int Distance[maxnode][maxnode];
int Cost[maxnode][maxnode];
bool visited[maxnode];
int sDis[maxnode];
int sCost[maxnode];

void print_path(int index)
{
	if (index != S)
	{
		print_path(vpre[index]);
	}
	cout << index << ' ';
}

int main()
{
	int ni, nj, nd, nc;
	int min_index, min_dis;
	cin >> N >> M >> S >> D;

	for (int i = 0; i != N; ++i)
	{
		for (int j = 0; j != N; ++j)
		{
			if (i == j)
			{
				Distance[i][j] = 0;
				Cost[i][j] = 0;
			} 
			else
			{
				Distance[i][j] = maxmax;
				Cost[i][j] = maxmax;
			}
		}
		visited[i] = false;
		sDis[i] = maxmax;
		sCost[i] = maxmax;
	}

	for(int i = 0; i != M; ++i)
	{
		cin >> ni >> nj >> nd >> nc;
		if ((nd < Distance[ni][nj]) || (nd == Distance[ni][nj] && nc < Cost[ni][nj]))
		{
			Distance[ni][nj] = Distance[nj][ni] = nd;
			Cost[ni][nj] = Cost[nj][ni] = nc;
		}
	}

	sDis[S] = 0;
	sCost[S] = 0;
	for (int i = 0; i != N; ++i)
	{
		min_dis = maxmax;
		for (int j = 0; j != N; ++j)
		{
			if (!visited[j] && sDis[j] < min_dis)
			{
				min_dis = sDis[j];
				min_index = j;
			}
		}
		visited[min_index] = true;

		if (min_index == D)
		{
			break;
		}

		for (int k = 0; k != N; ++k)
		{
			if (!visited[k])
			{
				if (sDis[k] > sDis[min_index] + Distance[min_index][k])
				{
					sDis[k] = sDis[min_index] + Distance[min_index][k];
					sCost[k] = sCost[min_index] + Cost[min_index][k];
					vpre[k] = min_index;
				}
				else
				{
					if (sDis[k] == sDis[min_index] + Distance[min_index][k])
					{
						if (sCost[vpre[k]] + Cost[vpre[k]][k] > sCost[min_index] + Cost[min_index][k])
						{
							sCost[k] = sCost[min_index] + Cost[min_index][k];
							vpre[k] = min_index;
						}
					}
				}
			}
		}
	}
	print_path(D);
	cout << sDis[D] << ' ' << sCost[D] << endl;
	return 0;		
}