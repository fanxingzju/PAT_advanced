#include <stdio.h>
#include <algorithm>
using namespace std;

typedef struct node
{
	int addr;
	int key;
	int next;
	int flag;
}node;

node records[100005];
int N;
int results[100005];


bool less_than_node(const node &A, const node &B)
{
	return A.addr < B.addr;
}

bool less_than_key(const node &A, const node &B)
{
	if (1 == A.flag && 0 == B.flag)
	{
		return true;
	}
	if (0 == A.flag && 1 == B.flag)
	{
		return false;
	}
	if (1 == A.flag && 1 == B.flag)
	{
		return A.key < B.key;
	}
	return A.addr < B.addr;
}

int binary_search_node(int target)
{
	int low = 0;
	int high = N-1;
	int mid;
	while (low <= high)
	{
		mid = (high+low)/2;
		if (records[mid].addr == target)
		{
			return mid;
		}
		if (records[mid].addr < target)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}
	return -1;
}

int main()
{
	int address;
	int length = 0;
	int index;

	scanf("%d", &N);
	scanf("%d", &address);

	for (int i = 0; i != N; ++i)
	{
		scanf("%d", &records[i].addr);
		scanf("%d", &records[i].key);
		scanf("%d", &records[i].next);
	}

	sort(records, records+N, less_than_node);

	

	while(address != -1)
	{
		index = binary_search_node(address);
		// 查找不成功
		if (index == -1)
		{
			break;
		}
		records[index].flag = 1;
		address = records[index].next;
		++length;
	}
	
	// 最后一个case
	if (0 == length)
	{
		printf("%d -1\n", length);
		return 0;
	}

	sort(records, records+N, less_than_key);

	printf("%d %05d\n", length, records[0].addr);

	for (int i = 0; i != length-1; ++i)
	{
		printf("%05d %d %05d\n", records[i].addr, records[i].key, records[i+1].addr);
	}
	printf("%05d %d -1\n", records[length-1].addr, records[length-1].key);

	system("pause");
	return 0;
}