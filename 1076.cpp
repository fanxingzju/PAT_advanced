#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct node
{
	int level;
	vector<int> kids;
}node;

vector<node> persons;
int N, L, K;
vector<bool> visited;


int levelOrderTranverse(int root)
{
	int ncount = -1;
	int ni, nj;

	queue<int> nq;
	nq.push(root);
	visited[root] = true;
	persons[root].level = 0;
	while (!nq.empty())
	{
		ni = nq.front();
		nq.pop();
		++ncount;
		if (persons[ni].level <= L-1)
		{
			for (int i = 0; i != persons[ni].kids.size(); ++i)
			{
				nj = persons[ni].kids[i];
				if (!visited[nj])
				{
					persons[nj].level = persons[ni].level+1;
					visited[nj] = true;
					nq.push(nj);
				}
			}
		}
	}
	return ncount;
}


int main()
{
	cin >> N >> L;
	int ni, nj;
	persons.resize(N);
	visited.resize(N);
	for (int i = 0; i != N; ++i)
	{
		cin >> ni;
		for (int j = 0; j != ni; ++j)
		{
			cin >> nj;
			persons[nj-1].kids.push_back(i);
		}
	}

	cin >> K;
	for (int i = 0; i != K; ++i)
	{
		cin >> ni;
		--ni;
		for (int i = 0; i != N; ++i)
		{
			visited[i] = false;
		}
		cout << levelOrderTranverse(ni) << endl;
	}
	return 0;
}
