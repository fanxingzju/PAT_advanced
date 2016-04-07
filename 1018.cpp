#include <iostream>
#include <vector>
using namespace std;


#define MAX_TIME 0xffffff

vector< vector<int> > vpre;		// 记录最短路径
vector<int> bikes;
int C, N, Sp, M;
vector<int> sTime;
vector< vector<int> > records;
vector<int> visited;

vector< vector<int> > ways;
vector< pair<int, int> > results;		// first->send second->bring

/* 注意计算每种最短路径对应的send和bring bikes数量的方法！！！*/
void get_results()
{
	results.resize(ways.size());
	int index;

	// 获取每种方法的send和bring数值
	for (unsigned int i = 0; i < ways.size(); ++i)
	{
		for (int j = ways[i].size()-1; j >= 0; --j)
		{
			index = ways[i][j];
			results[i].second += bikes[index] - C/2;
#if 0
			if (bikes[index] > C/2)
			{
				results[i].second += bikes[index] - C/2;
			}

			if (bikes[index] < C/2)
			{
				results[i].second -= C/2 - bikes[index];
			}
#endif
			if (results[i].second < 0)
			{
				results[i].first -= results[i].second;
				results[i].second = 0;
			}
		}
	}

}
int best_result()
{
	int bestindex = 0;

	for (unsigned int index = 1; index < ways.size(); ++index)
	{
		if (results[bestindex].first > results[index].first)
		{
			bestindex = index;
		}
		else
		{
			if (results[bestindex].first == results[index].first)
			{
				if (results[bestindex].second > results[index].second)
				{
					bestindex = index;
				}
			}
		}
	}
	return bestindex;
}

void restore_ways(int index, vector<int> partialway)
{
	partialway.push_back(index);
	
	for (unsigned int i = 0; i < vpre[index].size(); ++i)
	{
		if (0 == vpre[index][i])
		{
			ways.push_back(partialway);
		}
		else
		{
			restore_ways(vpre[index][i], partialway);
		}
	}
}

void initialpara(unsigned int size)
{
	vpre.resize(size);
	bikes.resize(size);
	visited.resize(size);

	sTime.resize(size);
	sTime[0] = 0;
	for (int i = 1; i != size; ++i)
	{
		sTime[i] = MAX_TIME;
	}

	records.resize(size);
	for (int i = 0; i != size; ++i)
	{
		records[i].resize(size);
		for (int j = 0; j != size; ++j)
		{
			records[i][j] = MAX_TIME;
		}
	}

}



int main()
{
	int ni, nj, nt;
	int min_time = MAX_TIME;
	int min_index;
	vector<int> temp;

	cin >> C >> N >> Sp >> M;
	++N;
	initialpara(N);

	for (int i = 1; i != N; ++i)
	{
		cin >> bikes[i];
	}

	for (int i = 0; i != M; ++i)
	{
		cin >> ni >> nj >> nt;
		records[ni][nj] = records[nj][ni] = nt;
	}

	for (int i = 0; i != N; ++i)
	{
		for (int j = 0; j != N; ++j)
		{
			if (0 == visited[j] && sTime[j] < min_time)
			{
				min_time = sTime[j];
				min_index = j;
			}
		}
		visited[min_index] = 1;

		for (int k = 0; k != N; ++k)
		{
			if (sTime[k] > sTime[min_index] + records[min_index][k])
			{
				sTime[k] = sTime[min_index] + records[min_index][k];
				vpre[k].clear();
				vpre[k].push_back(min_index);
			}
			else
			{
				if (sTime[k] == sTime[min_index] + records[min_index][k])
				{
					vpre[k].push_back(min_index);
				}
			}
		}
		min_time = MAX_TIME;
	}

	
	restore_ways(Sp, temp);

	get_results();

	min_index = best_result();

	cout << results[min_index].first << ' ' << '0';
	for (int i = ways[min_index].size()-1; i >= 0; --i)
	{
		cout << "->" << ways[min_index][i];
	}
	cout << ' ' << results[min_index].second << endl;
	

	return 0;
}