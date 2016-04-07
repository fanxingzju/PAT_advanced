#include <iostream>
#include <vector>
using namespace std;

int N, M, K;
vector<int> cities;
vector< vector<int> > cur_map;
vector< vector<int> > new_map;
vector<int> visited;

void initialpara()
{
	cur_map.resize(N);
	new_map.resize(N);
	visited.resize(N);
	for (int i = 0; i != N; ++i)
	{
		cur_map[i].resize(N);
		new_map[i].resize(N);
		for (int j = 0; j != N; ++j)
		{
			cur_map[i][j] = 0;
		}
	}
	return ;
}

#if 0
void initialmap()
{
	cur_map = new int*[N];
	new_map = new int*[N];
	for (int i = 0; i != N; ++i)
	{
		cur_map[i] = new int[N];
		new_map[i] = new int[N];
		for (int j = 0; j != N; ++j)
		{
			cur_map[i][j] = 0;
		}
	}
	return ;
}

void destorymap()
{
	for (int i = 0; i != N; ++i)
	{
		delete[] cur_map[i];
		cur_map[i] = NULL;
		delete[] new_map[i];
		new_map[i] = NULL;
	}
	delete[] cur_map;
	cur_map = NULL;
	delete[] new_map;
	new_map = NULL:
}
#endif

void copymap(int index)
{
	for (int i = 0; i != N; ++i)
	{
		for (int j = 0; j != N; ++j)
		{
			if (i == index || j == index)
			{
				new_map[i][j] = 0;
			}
			else
			{
				new_map[i][j] = cur_map[i][j];
			}
		}
	}
}

void dfsmap(int target)
{
	visited[target] = 1;
	for (int i = 0; i != N; ++i)
	{
		if (0 == visited[i] && 1 == new_map[target][i])
		{
			dfsmap(i);
		}
	}
}

int partsofmap()
{
	int parts = 0;

	for (int i = 0; i != N; ++i)
	{
		visited[i] = 0;
	}
	for (int i = 0; i != N; ++i)
	{
		if (0 == visited[i])
		{
			++parts;
			dfsmap(i);
		}
	}
	return parts;
}


int main()
{
	int ni, nj, target;
	
	cin >> N >> M >> K;
	initialpara();

	for (int i = 0; i != M; ++i)
	{
		cin >> ni >> nj;
		cur_map[ni-1][nj-1] = 1;
		cur_map[nj-1][ni-1] = 1;
	}

	for (int i = 0; i != K; ++i)
	{
		cin >> target;
		copymap(target-1);
		cout << partsofmap()-2 << endl;
	}


	return 0;
}