#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;

typedef struct elem
{
	char name[10];
	int height;
}elem;

vector<elem> records;
int N, K;
int outputOrder[10000];

void getOutputOrder(int len)
{
	int center = len/2;
	int count = 1;
	int offset = 1;
	memset(outputOrder, 0x0, sizeof(outputOrder));
	if (len&0x1 == 0x1)
	{
		outputOrder[center] = count++;
		while(count < len)
		{
			outputOrder[center-offset] = count++;
			outputOrder[center+offset] = count++;
			++offset;
		}
	}
	else
	{
		outputOrder[center] = count++;
		while(count < len-1)
		{
			outputOrder[center-offset] = count++;
			outputOrder[center+offset] = count++;
			++offset;
		}
		outputOrder[0] = count++;
	}
	return ;
}


bool less_than_elem(const elem &A, const elem &B)
{
	if (A.height != B.height)
	{
		return A.height > B.height;
	}
	else
	{
		if (strcmp(A.name, B.name) < 0)
		{
			return true;
		}
		return false;
	}
}


int main()
{
	elem temp;
	int lastrow = 0;
	int midrow = 0;
	int offset = 0;

	cin >> N >> K;
	for (int i = 0; i != N; ++i)
	{
		cin >> temp.name >> temp.height;
		records.push_back(temp);
	}

	sort(records.begin(), records.end(), less_than_elem);
	midrow = N/K;
	lastrow = N-midrow*(K-1);

	getOutputOrder(lastrow);
	for (int i = 0; i != lastrow; ++i)
	{
		cout << records[outputOrder[i]-1].name;
		if (i == lastrow - 1)
		{
			cout << endl;
		}
		else
		{
			cout << ' ';
		}
	}
	getOutputOrder(midrow);
	offset = lastrow;
	for (int i = 1; i != K; ++i)
	{
		for (int j = 0; j != midrow; ++j)
		{
			cout << records[outputOrder[j]+offset-1].name;
			if (j == midrow - 1)
			{
				cout << endl;
			}
			else
			{
				cout << ' ';
			}
		}
		offset += midrow;
	}


	return 0;
}