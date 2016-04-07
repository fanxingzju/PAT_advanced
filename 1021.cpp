/*
����AC��Ч�ʺܸ� 
0	����ȷ	1	256	13/13
1	����ȷ	1	296	2/2
2	����ȷ	2	304	5/5
3	����ȷ	23	1536	2/2
4	����ȷ	1	256	2/2
5	����ȷ	1	256	1/1
*/ 

#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

const int white = 0;
const int gray = 1;
const int black = 2;
typedef struct node
{
	int color;
	int height;
	vector<int> adj;
}node;
int N;
vector<node> graph;


void dfs(int index)
{
	int k;
	graph[index].color = gray;
	for (unsigned int i = 0; i < graph[index].adj.size(); ++i)
	{
		k = graph[index].adj[i];
		if (white == graph[k].color)
		{
			dfs(k);
		}
	}
	graph[index].color = black;
}

void bfs(int root, vector<int> &res)
{
	int max_height = 0;
	int index;
	int k;
	queue<int> nq;

	for (int i = 0; i != N; ++i)
	{
		graph[i].color = white;
		graph[i].height = 0;
	}

	nq.push(root);
	graph[root].color = gray;
	while (!nq.empty())
	{
		index = nq.front();
		nq.pop();
		graph[index].color = black;
		for (unsigned int i = 0; i != graph[index].adj.size(); ++i)
		{
			k = graph[index].adj[i];
			if (white == graph[k].color)
			{
				graph[k].height = graph[index].height + 1;
				graph[k].color = gray;
				nq.push(k);
				if (graph[k].height > max_height)
				{
					max_height = graph[k].height;
				}
			}
		}
	}


	for (int i = 0; i != N; ++i)
	{
		if (graph[i].height == max_height)
		{
			res.push_back(i);
		}
	}
	return ;
}

int main()
{
	int ni, nj;
	vector<int> res1, res2;
	set<int> res_all;
	int parts = 0;
	bool flag = false;

	cin >> N;
	graph.resize(N);
	for (int i = 0; i != N; ++i)
	{
		graph[i].color = white;
		graph[i].height = 0;
	}

	for (int i = 0; i != N-1; ++i)
	{
		cin >> ni >> nj;
		--ni;
		--nj;
		graph[ni].adj.push_back(nj);
		graph[nj].adj.push_back(ni);
	}
	

	for (int i = 0; i != N; ++i)
	{
		if (white == graph[i].color)
		{
			dfs(i);
			++parts;
		}
	}

	if (1 != parts)
	{
		cout << "Error: " << parts << " components" << endl;
		return 0;
	}

	bfs(0, res1);
	bfs(res1.at(0), res2);
	ni = nj = 0;
	
	for (unsigned int i = 0; i != res1.size(); ++i)
	{
		res_all.insert(res1[i]);
	}
	for (unsigned int i = 0; i != res2.size(); ++i)
	{
		res_all.insert(res2[i]);
	}
	for (set<int>::const_iterator iter = res_all.begin(); iter != res_all.end(); ++iter)
	{
		cout << (*iter)+1 << endl;
	}
	
	return 0;
}


/* ����ac
0	����ȷ	1	256	13/13
1	����ȷ	1	256	2/2
2	����ȷ	1	300	5/5
3	����ȷ	984	1212	2/2
4	����ȷ	1	256	2/2
5	����ȷ	1	316	1/1
*/
/* ϡ��ͼ���ڽӱ�Ч�ʸ���*/
#if 0
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int white = 0;
const int gray = 1;
const int black = 2;
typedef struct node
{
	int color;
	int start;
	int finish;
	int height;
	vector<int> adj;
}node;
int N;
vector<node> graph;
int ntime = 0;
int parts = 0;

void dfs(int index)
{
	int k;
	graph[index].color = gray;
	graph[index].start = ntime++;
	for (unsigned int i = 0; i < graph[index].adj.size(); ++i)
	{
		k = graph[index].adj[i];
		if (white == graph[k].color)
		{
			dfs(k);
		}
	}
	graph[index].color = black;
	graph[index].finish = ntime++;
}

int bfs(int root)
{
	int ret = 0;
	int index;
	int k;
	queue<int> nq;

	for (int i = 0; i != N; ++i)
	{
		graph[i].color = white;
		graph[i].height = 0;
	}
	
	nq.push(root);
	graph[root].color = gray;
	while (!nq.empty())
	{
		index = nq.front();
		nq.pop();
		graph[index].color = black;
		for (unsigned int i = 0; i != graph[index].adj.size(); ++i)
		{
			k = graph[index].adj[i];
			if (white == graph[k].color)
			{
				graph[k].height = graph[index].height + 1;
				graph[k].color = gray;
				nq.push(k);
				if (graph[k].height > ret)
				{
					ret = graph[k].height;
				}
			}
		}
	}
	return ret;
}

int main()
{
	int ni, nj, nh;
	int max_height = 0;
	vector<int> results;

	cin >> N;
	graph.resize(N);
	for (int i = 0; i != N; ++i)
	{
		graph[i].color = white;
		graph[i].height = 0;
	}
	for (int i = 0; i != N-1; ++i)
	{
		cin >> ni >> nj;
		--ni;
		--nj;
		graph[ni].adj.push_back(nj);
		graph[nj].adj.push_back(ni);
	}

	for (int i = 0; i != N; ++i)
	{
		if (white == graph[i].color)
		{
			dfs(i);
			++parts;
		}
	}

	
	if (1 != parts)
	{
		cout << "Error: " << parts << " components" << endl;
	}
	else
	{
		for (int i = 0; i != N; ++i)
		{
/************************************************************************/
/* ע�͵������if ������ac											*/
/* ��������:2 1 2														*/
/************************************************************************/
			/* if (graph[i].start + 1 == graph[i].finish) */
			{
				nh = bfs(i);
				if (nh > max_height)
				{
					max_height = nh;
					results.clear();
					results.push_back(i);
				}
				else
				{
					if (nh == max_height)
					{
						results.push_back(i);
					}
				}
			}
		}

		for (unsigned int i = 0; i != results.size(); ++i)
		{
			cout << results[i]+1 << endl;
		}
	}
	
	return 0;
}

#endif


#if 0
// ��ʱ
#include <iostream>
#include <queue>
using namespace std;

int graph[10002][10002];				/* 1��ʾ����·��*/
int visited[10002];						/* 1Ϊ�Ѿ�����*/
int result[10002];

void DFS(int root, int num)
{
	visited[root] = true;
	for (int i = 1; i <= num; ++i)
	{
		if (1 == graph[root][i] && 0 == visited[i])
		{
			DFS(i, num);
		}
	}
}

// ������ֵ��ʾ��rootΪ��������������
// ���ظ�ֵ��ʾͼ�ж��ٸ�����ͨ�Ĳ���
int levelCount(int root, int num)
{
	int level;						// ��¼��rootΪ��������������
	int part;						// ��¼ͼ�ж��ٸ��໥����ͨ������(���"Error: K components") 
	bool flag = true;				// �������ͨͼ, ��Ϊtrue; ��֮Ϊfalse
	int count, temp;
	queue<int> Q;
	for (int i = 1; i <= num; ++i)
	{
		visited[i] = 0;
	}

	Q.push(root);
	count = 1;
	level = 0;
	visited[root] = 1;
	part = 1;

	while(!Q.empty())
	{
		while(count--)
		{
			temp = Q.front();
			Q.pop();
			for (int i = 1; i <= num; ++i)
			{
				if (1 == graph[temp][i] && 0 == visited[i])
				{
					visited[i] = 1;
					Q.push(i);
				}
			}
		}
		count = Q.size();
		++level;
	}
	for (int i = 1; i <= num; ++i)
	{
		// ����δ�����ʵĵ�
		if (0 == visited[i])
		{
			flag = false;
			DFS(i, num);
			++part;
		}
	}
	if (flag)
	{
		return level;
	}
	else
	{
		return -part;
	}
}

int main()
{
	int num;
	int row, col;
	int maxlevel = 0;
	cin >> num;
	for (int i = 1; i != num; ++i)
	{
		cin >> row >> col;
		graph[row][col] = graph[col][row] = 1;
	}
	for (int i = 1; i <= num; ++i)
	{
		result[i] = levelCount(i, num);
		if (result[i] < 0)
		{
			cout << "Error: " << -result[i] <<  " components" << endl;
			system("pause");
			return 0;
		}
		if (result[i] > maxlevel)
		{
			maxlevel = result[i];
		}
	}

	for (int i = 1; i <= num; ++i)
	{
		if (result[i] == maxlevel)
		{
			cout << i << endl;
		}
	}
	
	system("pause");
	return 0;
}

#endif