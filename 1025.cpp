#include <iostream>
#include <algorithm>
#include <list>
#include <stdio.h>
using namespace std;

typedef struct node
{
	unsigned long long int registration_number;
	unsigned int score;
	unsigned int final_rank;
	unsigned int location_number;
	unsigned int local_rank;
}node;

#if 0
// 每组内比较
bool local_compare(node A, node B)
{
	if (A.location_number == B.location_number)
	{
		if (A.score == B.score)
		{
			return A.registration_number < B.registration_number;
		}
		else
		{
			return A.score < B.score;
		}
	}
	else
	{
		return A.location_number < B.location_number;
	}
}
#endif

// 全部比较
bool global_compare(node &A, node &B)
{
	if (A.score == B.score)
	{
		return A.registration_number < B.registration_number;
	}
	else
	{
		return A.score > B.score;
	}	
}

int main()
{
	int n;
	int items_num; 
	int total_num = 0;
	node ntmp;
	list<node> result;
	list<node> ltmp;
	unsigned int tmpscore = 0xffffffff;
	unsigned int tmprank = 0;
	int index;

	cin >> n;

	for (int location = 1; location <= n; ++location)
	{
		cin >> items_num;
		total_num += items_num;
		while (items_num--)
		{
			cin >> ntmp.registration_number;
			cin >> ntmp.score;
			ntmp.location_number = location;
			ltmp.push_back(ntmp);
		}
		ltmp.sort(global_compare);
		index = 0;
		tmpscore = 0xffffffff;
		for (list<node>::iterator iter = ltmp.begin();
			iter != ltmp.end(); ++iter)
		{
			++index;
			if (0xffffffff == tmpscore)
			{
				iter->local_rank = index;
				tmpscore = iter->score;
				tmprank = iter->local_rank;
			}
			else
			{
				if (tmpscore == iter->score)
				{
					iter->local_rank = tmprank;
				}
				else
				{
					iter->local_rank = index;
					tmpscore = iter->score;
					tmprank = iter->local_rank;
				}
			}
		}
		result.merge(ltmp, global_compare);
		ltmp.clear();
	}
	result.sort(global_compare);
	index = 0;
	tmpscore = 0xffffffff;
	for (list<node>::iterator iter = result.begin(); iter != result.end(); ++iter)
	{
		++index;
		if (0xffffffff == tmpscore)
		{
			iter->final_rank = index;
			tmpscore = iter->score;
			tmprank = iter->final_rank;
		}
		else
		{
			if (tmpscore == iter->score)
			{
				iter->final_rank = tmprank;
			}
			else
			{
				iter->final_rank = index;
				tmpscore = iter->score;
				tmprank = iter->final_rank;
			}
		}
	}

	cout << index << endl;
	for (list<node>::iterator iter = result.begin(); iter != result.end(); ++iter)
	{
		printf("%013lld %d %d %d\n", iter->registration_number, iter->final_rank, iter->location_number, iter->local_rank);
	}

	system("pause");
	return 0;
}
