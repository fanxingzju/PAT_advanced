#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int N, K;
int totalnodes = 0;
map<string,int> records;
const int maxnum = 2005;
int gangtag = 0;

typedef struct node
{
	string name;
	int weight;
	int tag;
	set<int> neighbour;
}node;

vector<node> graph;
int weight[maxnum][maxnum];
bool isvisited[maxnum];

map<string, int> results;

inline int getIndex(const string str)
{
	map<string,int>::iterator iter = records.find(str);
	node temp;
	if (records.end() == iter)
	{
		records.insert(make_pair(str, totalnodes++));
		temp.name = str;
		temp.weight = 0;
		graph.push_back(temp);
		return totalnodes-1;
	}
	else
	{
		return iter->second;
	}
}

void bfs(int root)
{
	int index;
	int members = 0;						/* 记录该Gang中的人数*/
	int gangweight = 0;						/* 记录该Gang总权重*/
	int headweight = 0;
	int headindex;

	queue<int> nq;
	nq.push(root);
	isvisited[root] = true;
	while (!nq.empty())
	{
		index = nq.front();
		graph[index].tag = gangtag;
		nq.pop();
		++members;

		for (set<int>::iterator iter = graph[index].neighbour.begin(); iter != graph[index].neighbour.end(); ++iter)
		{
			if (!isvisited[*iter])
			{
				nq.push(*iter);
				isvisited[*iter] = true;
			}
			graph[index].weight += weight[index][*iter];
		}
		if (graph[index].weight > headweight)
		{
			headweight = graph[index].weight;
			headindex = index;
		}
		gangweight += graph[index].weight;
	}
	++gangtag;

	if (members > 2 && gangweight > 2*K)
	{
		results.insert(make_pair(graph[headindex].name, members));
	}
}

int main()
{
	string strA, strB;
	int ntime;
	int ni, nj;

	cin >> N >> K;
	for (int i = 0; i != N; ++i)
	{
		cin >> strA >> strB >> ntime;
		ni = getIndex(strA);
		nj = getIndex(strB);
		weight[ni][nj] += ntime;
		weight[nj][ni] = weight[ni][nj];
		graph[ni].neighbour.insert(nj);
		graph[nj].neighbour.insert(ni);
	}

	for (int i = 0; i != maxnum; ++i)
	{
		isvisited[i] = false;
	}

	for (int i = 0; i != totalnodes; ++i)
	{
		if (!isvisited[i])
		{
			bfs(i);
		}
	}
	cout << results.size() << endl;
	for (map<string,int>::iterator iter = results.begin(); iter != results.end(); ++iter)
	{
		cout << iter->first << ' ' << iter->second << endl;
	}

	return 0;
}