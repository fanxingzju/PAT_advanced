/*
最短路径算法的应用 
*/ 
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <stdio.h>
using namespace std;

vector< set<int> > graph;				/* 用类似临接矩阵的方式记录节点间的关系*/ 
vector< vector<float> > records;
vector<float> sPath;

const float MAXLEN = 0xffffff;
const int MAXNUM = 1020;
float weight[MAXNUM][MAXNUM];
int N, M, K;
float Ds;

bool visited[1020];

typedef struct elem
{
	int index;
	float minlen;
	float maxlen;
	float total;
}elem;

vector<elem> results;

bool elem_less_than(const elem &A, const elem &B)
{
	if (A.minlen != B.minlen)
	{
		return A.minlen > B.minlen;
	}

	if (A.total != B.total)
	{
		return A.total < B.total;
	}
	return A.index < B.index;
}

int getIndex(string str)
{
	int ret = 0;
	int index = 0;
	int num = 0;

	if ('G' == str[0])
	{
		ret = N;
		index = 1;
	}
	for ( ; index < str.size(); ++index)
	{
		num = 10*num+str[index]-'0';
	}
	ret += num-1;
	return ret;
}

/* dijkstra算法*/ 
/* 类似临接矩阵的方式记录和处理数据，提高稀疏图下的计算速度*/ 
void dijkstra(int src)
{
	int minIndex;
	float mindis = 0xffffff;
	int k;

	for (int i = 0; i != N+M; ++i)
	{
		visited[i] = false;
		sPath[i] = MAXLEN;
	}
	sPath[src] = 0;
	visited[src] = true;
	for (set<int>::iterator iter = graph[src].begin(); iter != graph[src].end(); ++iter)
	{
		sPath[*iter] = weight[src][*iter];
	}

	for (int i = 0; i != N+M-1; ++i)
	{
		mindis = MAXLEN;
		for (int j = 0; j != sPath.size(); ++j)
		{
			if (!visited[j] && sPath[j] < mindis)
			{
				mindis = sPath[j];
				minIndex = j;
			}
		}
		visited[minIndex] = true;
		for (set<int>::iterator iter = graph[minIndex].begin(); iter != graph[minIndex].end(); ++iter)
		{
			 k = *iter;
			if (!visited[k] && sPath[k] > sPath[minIndex] + weight[minIndex][k])
			{
				sPath[k] = sPath[minIndex] + weight[minIndex][k];
			}
		}
	}
	
	records.push_back(sPath);

}


int main()
{
	string strA, strB;
	int ni, nj;
	float dis;
	float total = 0;
	
	cin >> N >> M >> K >> Ds;
	graph.resize(N+M);
	sPath.resize(N+M);
	for (int i = 0; i != K; ++i)
	{
		cin >> strA >> strB >> dis;
		ni = getIndex(strA);
		nj = getIndex(strB);
		weight[ni][nj] = weight[nj][ni] = dis;
		graph[ni].insert(nj);
		graph[nj].insert(ni);
	}
	
	/* 计算M个候选位置到各个点的距离*/
	for (int i = 0; i != M; ++i)
	{
		dijkstra(N+i);
	}

	/* 处理结果*/ 
	for (int i = 0; i < records.size(); ++i)
	{
		elem temp;
		temp.minlen = MAXLEN;
		temp.maxlen = 0;
		temp.total = 0;
		temp.index = i+1;
		for (int j = 0; j < N; ++j)
		{
			if (records[i][j] < temp.minlen)
			{
				temp.minlen = records[i][j];
			}
			if (records[i][j] > temp.maxlen)
			{
				temp.maxlen = records[i][j];
			}
			temp.total += records[i][j];
		}
		if (temp.maxlen <= Ds)
		{
			results.push_back(temp);
		}
	}
	if (0 != results.size())
	{
		sort(results.begin(), results.end(), elem_less_than);
		cout << 'G' << results[0].index << endl;
		printf("%0.01f %0.01f\n", results[0].minlen, results[0].total/N);
	}
	else
	{
		cout << "No Solution" << endl;
	}

	return 0;
}