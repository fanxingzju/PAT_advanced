/* 最短路径加剪枝*/
/* In case the shortest path is not unique, output the fastest one among the shortest paths, which is guaranteed to be unique. 
In case the fastest path is not unique, output the one that passes through the fewest intersections, which is guaranteed to be unique.*/
/* 有多个shortest path, 则选择其中最快的一条；
有多个fastest path, 则选择其中经过街道最少的一条！！！*/
#include <iostream>
#include <vector>
using namespace std;

const int MAXWEIGHT = 0x7fffffff;
const int MAXNODE = 505;

class node
{
public:
	node(): length(MAXWEIGHT), time(MAXWEIGHT){}
	int length;
	int time;
};
node graph[MAXNODE][MAXNODE];

int N, M;
int src, dst;

int sPathA[MAXNODE], sTimeA[MAXNODE], vPreA[MAXNODE];
int sCountB[MAXNODE], sTimeB[MAXNODE], vPreB[MAXNODE];
bool visited[MAXNODE];

bool isIdentical(int index)
{
	if (vPreA[index] == src && vPreB[index] != src)
	{
		return false;
	}
	if (vPreA[index] != src && vPreB[index] == src)
	{
		return false;
	}
	if (vPreA[index] == src && vPreB[index] == src)
	{
		return true;
	}
	if (vPreA[index] == vPreB[index])
	{
		return 	isIdentical(vPreA[index]);
	}
	else
	{
		return false;
	}
}

void dijkstraA()
{
	int minweight, ni;
	for (int i = 0; i != N; ++i)
	{
		sPathA[i] = MAXWEIGHT;
		sTimeA[i] = MAXWEIGHT;
		visited[i] = false;
	}
	sPathA[src] = 0;
	sTimeA[src] = 0;

	for (int i = 0; i != N; ++i)
	{
		minweight = MAXWEIGHT;
		for (int j = 0; j != N; ++j)
		{
			if (!visited[j] && sPathA[j] < minweight)
			{
				ni = j;
				minweight = sPathA[j];
			}
		}
		visited[ni] = true;
		/* no need to continue*/
		if (ni == dst)
		{
			break;
		}
		for (int k = 0; k != N; ++k)
		{
			if (!visited[k] && graph[ni][k].length != MAXWEIGHT)
			{
				if (sPathA[k] == sPathA[ni] + graph[ni][k].length)
				{
					if (sTimeA[k] > sTimeA[ni] + graph[ni][k].time)
					{
						vPreA[k] = ni;
						sTimeA[k] = sTimeA[ni] + graph[ni][k].time;
					}
				}

				if (sPathA[k] > sPathA[ni] + graph[ni][k].length)
				{
					sPathA[k] = sPathA[ni] + graph[ni][k].length;
					vPreA[k] = ni;
					sTimeA[k] = sTimeA[ni] + graph[ni][k].time;
				}
			}
		}
	}
	return ;
}

void dijkstraB()
{
	int minweight, ni;
	for (int i = 0; i != N; ++i)
	{
		sCountB[i] = MAXWEIGHT;
		sTimeB[i] = MAXWEIGHT;
		visited[i] = false;
	}
	sCountB[src] = 0;
	sTimeB[src] = 0;
	
	for (int i = 0; i != N; ++i)
	{
		minweight = MAXWEIGHT;
		for (int j = 0; j != N; ++j)
		{
			if (!visited[j] && sTimeB[j] < minweight)
			{
				ni = j;
				minweight = sTimeB[j];
			}
		}
		visited[ni] = true;
		/* no need to continue*/
		if (ni == dst)
		{
			break;
		}
		
		for (int k = 0; k != N; ++k)
		{
			if (!visited[k] && graph[ni][k].time != MAXWEIGHT)
			{
				if (sTimeB[k] == sTimeB[ni] + graph[ni][k].time)
				{
					if (sCountB[k] > sCountB[ni] + 1)
					{
						vPreB[k] = ni;
						sCountB[k] = sCountB[ni]+1;
					}
				}
				if (sTimeB[k] > sTimeB[ni] + graph[ni][k].time)
				{
					sTimeB[k] = sTimeB[ni] + graph[ni][k].time;
					vPreB[k] = ni;
					sCountB[k] = sCountB[ni]+1;
				}
			}
		}
	}
	return ;
}

void print_path(int vPre[], int index)
{
	if (index == src)
	{
		cout << index; 
	}
	else
	{
		print_path(vPre, vPre[index]);
		cout << " -> " << index;
	}
}

int main()
{
	int ni, nj, flag, length, time;
	cin >> N >> M;

	for (int i = 0; i != M; ++i)
	{
		cin >> ni >> nj >> flag >> length >> time;
		graph[ni][nj].time =time;
		graph[ni][nj].length = length;
		if (0 == flag)
		{
			graph[nj][ni].time = time;
			graph[nj][ni].length = length;
		}
	}
	cin >> src >> dst;

	dijkstraA();
	dijkstraB();

	if (isIdentical(dst))
	{
		cout << "Distance = " << sPathA[dst] << "; Time = " << sTimeA[dst] << ": ";
		print_path(vPreA, dst);
		cout << endl;
	}
	else
	{
		cout << "Distance = " << sPathA[dst] << ": ";
		print_path(vPreA, dst);
		cout << endl;
		cout << "Time = " << sTimeB[dst] << ": ";
		print_path(vPreB, dst);
		cout << endl;
	}

	return 0;
}