#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
using namespace std;


typedef struct node
{
	string	plate;
	int		time;
	string	statue;
}node;

typedef struct elem
{
	string	plate;
	int		intime;
	int		outtime;
}elem;

node inputs[10010];
elem records[5005];
map<string, int> mCar;
int N, K;
bool less_than_node(const node &A, const node &B)
{
	if (A.plate != B.plate)
	{
		return A.plate < B.plate;
	} 
	else
	{
		return A.time < B.time;
	}
}

bool less_than_elem(const elem &A, const elem &B)
{
	return A.outtime < B.outtime;
}

int main()
{
	int hh, mm, ss;
	int query;
	int num = 0;
	int index = 0;
	int count = 0;
	int max_time = -1;
	vector<string> results;

	cin >> N >> K;
	for (int i = 0; i != N; ++i)
	{
		cin >> inputs[i].plate;
		scanf("%d:%d:%d", &hh, &mm, &ss);
		inputs[i].time = hh*3600+mm*60+ss;
		cin >> inputs[i].statue;
	}
	
	sort(inputs, inputs+N, less_than_node);

	for (int i = 0; i < N-1; )
	{
		if ((inputs[i].plate == inputs[i+1].plate) && (inputs[i].statue[0] == 'i') && (inputs[i+1].statue[0] == 'o'))
		{
			records[num].plate = inputs[i].plate;
			records[num].intime = inputs[i].time;
			records[num].outtime = inputs[i+1].time;
			mCar[records[num].plate] += records[num].outtime - records[num].intime;
			++num;
			i += 2;
		}
		else
		{
			++i;
		}
	}
	
	sort(records, records+num, less_than_elem);

	for (int i = 0; i != K; ++i)
	{
		scanf("%d:%d:%d", &hh, &mm, &ss);
		query = hh*3600+mm*60+ss;
		count = 0;
		while (index < num && records[index].outtime <= query)
		{
			++index;
		}
		for (int j = index; j < num; ++j)
		{
			if (records[j].intime <= query)
			{
				++count;
			}
		}
		printf("%d\n", count);
	}

	for (map<string, int>::iterator iter = mCar.begin(); iter != mCar.end(); ++iter)
	{
		if (iter->second > max_time)
		{
			max_time = iter->second;
		}
	}

	for (map<string, int>::iterator iter = mCar.begin(); iter != mCar.end(); ++iter)
	{
		if (iter->second == max_time)
		{
			results.push_back(iter->first);
		}
	}

	sort(results.begin(), results.end());
	for (vector<string>::iterator iter = results.begin(); iter != results.end(); ++iter)
	{
		cout << *iter << " ";
	}
	hh = max_time/3600;
	mm = (max_time-hh*3600)/60;
	ss = max_time%60;
	printf("%02d:%02d:%02d\n", hh, mm, ss);

	system("pause");
	return 0;
}

