/* 先用dijkstra算法计算出所有最短路径，然后分析*/
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int N, K;
int src, dst;

typedef struct node
{
	int happiness;
	vector<int> adj;
}node;
vector<node> graph;

const int MAXNODE = 205;
const int MAXLEN = 0xffffff;

int weight[MAXNODE][MAXNODE];
bool visited[MAXNODE];
int sPath[MAXNODE];
vector< vector<int> > pre;
vector< vector<int> > results;

map<string,int> ston;
vector<string> ntos;
int ncount = 0;

bool mycmp(const vector<int> &A, const vector<int> &B)
{
	int ni = A.size();
	int nj = B.size();
	if (A[ni-1] != B[nj-1])
	{
		return A[ni-1] > B[nj-1];
	}
	else
	{
		return ((A[ni-1]*1.0/A[ni-2]) > (B[nj-1]*1.0/B[nj-2]));
	}
}

int getIndex(const string &str)
{
	map<string,int>::iterator iter = ston.find(str);
	if (ston.end() == iter)
	{
		ston.insert(make_pair(str, ncount++));
		ntos.push_back(str);
		return ncount-1;
	}
	else
	{
		return iter->second;
	}
}

void dijkstra(int index)
{
	int minIndex, minCost;
	int k;

	pre.resize(N);
	for (int i = 0; i != N; ++i)
	{
		visited[i] = false;
		sPath[i] = MAXLEN;
	}

	sPath[index] = 0;

	for (int i = 0; i != N; ++i)
	{
		minCost = MAXLEN;
		for (int j = 0; j != N; ++j)
		{
			if (!visited[j] && sPath[j] < minCost)
			{
				minIndex = j;
				minCost = sPath[j];
			}
		}
		visited[minIndex] = true;
		for (int i = 0; i != graph[minIndex].adj.size(); ++i)
		{
			k = graph[minIndex].adj[i];
			if (!visited[k])
			{
				if (sPath[k] > sPath[minIndex] + weight[k][minIndex])
				{
					sPath[k] = sPath[minIndex] + weight[k][minIndex];
					pre[k].clear();
					pre[k].push_back(minIndex);
				}
				else
				{
					if (sPath[k] == sPath[minIndex] + weight[k][minIndex])
					{
						pre[k].push_back(minIndex);
					}
				}
			}
		}
	}
	return ;
}

void getResults(int index, vector<int> temp)
{
	temp.push_back(index);
	for (int i = 0; i != pre[index].size(); ++i)
	{
		if (pre[index][i] == src)
		{
			results.push_back(temp);
		}
		else
		{
			getResults(pre[index][i], temp);
		}
	}
}

int main()
{
	string str, strA, strB;
	int happiness, nsize;
	int ni, nj, cost;
	vector<int> temp;

	cin >> N >> K >> str;
	src = getIndex(str);
	graph.resize(N);
	for (int i = 0; i != N-1; ++i)
	{
		cin >> str >> happiness;
		ni = getIndex(str);
		graph[ni].happiness = happiness;
	}

	for (int i = 0; i != K; ++i)
	{
		cin >> strA >> strB >> cost;
		ni = getIndex(strA);
		nj = getIndex(strB);
		weight[ni][nj] = weight[nj][ni] = cost;
		graph[ni].adj.push_back(nj);
		graph[nj].adj.push_back(ni);
	}

	dijkstra(src);
	dst = getIndex("ROM");
	getResults(dst, temp);
	for (int i = 0; i != results.size(); ++i)
	{
		nsize = results[i].size();
		happiness = 0;
		for (int j = 0; j != results[i].size(); ++j)
		{
			ni = results[i][j];
			happiness += graph[ni].happiness;
		}
		results[i].push_back(nsize);
		results[i].push_back(happiness);
	}

	sort(results.begin(), results.end(), mycmp);

	cout << results.size() << ' ';
	cout << sPath[dst] << ' ';
	nsize = results[0].size();
	cout << results[0][nsize-1] << ' ';
	cout << (results[0][nsize-1]/results[0][nsize-2]) << endl;
	cout << ntos[src];

	for (int i = nsize-3; i >= 0; --i)
	{
		cout << "->" << ntos[results[0][i]];
	}
	cout << endl;

	return 0;
}