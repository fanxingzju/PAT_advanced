#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string.h>
using namespace std;

int hobbies[1005][1005];
int people[1005][1005];
vector<int> result;
int cluster[1005];

int N;

int cluster_size()
{
	int ret = 0;
	for (int i = 1; i != 1005; ++i)
	{
		if (1 == cluster[i])
		{
			++ret;
		}
	}
	return ret;
}

bool is_hobby_empty(int index)
{
	for (int i = 0; i != 1005; ++i)
	{
		if (hobbies[index][i] != 0)
		{
			return false;
		}
	}
	return true;
}

void dfs(int index)
{
	vector<int> people_vec;
	for (int i = 0; i != 1005; ++i)
	{
		if (1 == hobbies[index][i] && 0 == cluster[i])
		{
			cluster[i] = 1;
			people_vec.push_back(i);
			people[i][index] = 0;
		}
		hobbies[index][i] = 0;
	}
	
	for (int i = 0; i != people_vec.size(); ++i)
	{
		for (int j = 1; j != 1005; ++j)
		{
			if (people[people_vec[i]][j] == 1)
			{
				people[people_vec[i]][j] = 0;
				dfs(j);
			}
		}
	}
}

int main()
{
	int tmpnum, hobby;
	scanf("%d", &N);
	for (int i = 1; i != N+1; ++i)
	{
		scanf("%d:", &tmpnum);
		for (int j = 0; j != tmpnum; ++j)
		{
			scanf("%d", &hobby);
			people[i][hobby] = 1;
			hobbies[hobby][i] = 1;
		}
	}

	for (int i = 1; i != 1001; ++i)
	{
		if (!is_hobby_empty(i))
		{
			memset(cluster, 0x0, 1005*sizeof(int));
			dfs(i);
			tmpnum = cluster_size();
			result.push_back(tmpnum);
		}	
	}
	
	cout << result.size() << endl;
	sort(result.begin(), result.end());
	cout << result[result.size()-1];
	for (int i = result.size()-2; i > -1; --i)
	{
		cout << ' ' << result[i];
	}
	cout << endl;
	system("pause");
	return 0;
}