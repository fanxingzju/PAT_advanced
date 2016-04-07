#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


typedef struct node
{
	int data;
	int rank;
	int index;
}node;

node records[100010];
int N;

bool less_than_data(const node &A, const node &B)
{
	return A.data < B.data;
}


int main()
{
	int maxindex = -1;
	vector<int> nvect;
	cin >> N;
	for (int i = 0; i != N; ++i)
	{
		records[i].index = i;
		cin >> records[i].data;
	}

	sort(records, records+N, less_than_data);
	for (int i = 0; i != N; ++i)
	{
		records[i].rank = i;
	}
	
	for (int i = 0; i != N; ++i)
	{
		
		if (maxindex < records[i].rank && records[i].rank == records[i].index)
		{
			nvect.push_back(records[i].data);
		}

		if (records[i].index > maxindex)
		{
			maxindex = records[i].index;
		}
	}

	cout << nvect.size() << endl;
	if (nvect.size() != 0)
	{
		for (int i = 0; i != nvect.size(); ++i)
		{
			cout << nvect[i];
			if (i != nvect.size()-1)
			{
				cout << ' ';
			}
			else
			{
				cout << endl;
			}
		}
	}
	else
	{
		/* 即使没有符合条件的pivot, 也要输出一个空行, 否则会格式错误(case2)*/
		cout << endl;
	}


	system("pause");
	return 0;
}