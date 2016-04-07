#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;

typedef struct node
{
	int addr;
	int data;
	int next;
	int index;
}node;

#define MAX_NUM 100010
node input[MAX_NUM];
int flag[MAX_NUM];				// Key is an integer of which absolute value is no more than 104
node output[MAX_NUM];
node removed[MAX_NUM];
int N;
int startaddr;
int rlength;
int olength;
int length;

bool less_than_addr(const node &A, const node &B)
{
	return A.addr < B.addr;
}

bool less_than_index(const node &A, const node &B)
{
	return A.index < B.index;
}

int binary_search(int targetAddr)
{
	int low = 0;
	int high = N-1;
	int mid;
	while (low <= high)
	{
		mid = (low+high)/2;
		if (input[mid].addr == targetAddr)
		{
			return mid;
		}
		else
		{
			if (input[mid].addr > targetAddr)
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
		}
	}
	return -1;
}

int set_index()
{
	int index = 0;
	int addr = startaddr;
	int id;
	while (-1 != addr)
	{
		id = binary_search(addr);
		input[id].index = ++index;
		addr = input[id].next;
	}
	return index;
}

int main()
{
	cin >> startaddr >> N;
	int key;
	for (int i = 0; i != N; ++i)
	{
		cin >> input[i].addr >> input[i].data >> input[i].next;
		input[i].index = N+1;
	}
	sort(input, input+N, less_than_addr);
	length = set_index();						// 考虑输入有不在链表中的节点
	sort(input, input+N, less_than_index);

	for (int i = 0; i != length; ++i)
	{
		key = input[i].data;
		if (key < 0)
		{
			key = -key;
		}
		if (flag[key] == 0)
		{
			flag[key] = 1;
			output[olength++] = input[i];
		}
		else
		{
			removed[rlength++] = input[i];
		}
	}

	if (olength > 0)
	{
		for (int i = 0; i < olength-1; ++i)
		{
			output[i].next = output[i+1].addr;
		}
		output[olength-1].next = -1;

		for (int i = 0; i < olength-1; ++i)
		{
			printf("%05d %d %05d\n", output[i].addr, output[i].data, output[i].next);
		}
		printf("%05d %d -1\n", output[olength-1].addr, output[olength-1].data);
	}

	if (rlength > 0)
	{
		for (int i = 0; i < rlength-1; ++i)
		{
			removed[i].next = removed[i+1].addr;
		}
		removed[rlength-1].next = -1;

		for (int i = 0; i < rlength-1; ++i)
		{
			printf("%05d %d %05d\n", removed[i].addr, removed[i].data, removed[i].next);
		}
		printf("%05d %d -1\n", removed[rlength-1].addr, removed[rlength-1].data);
	}
	system("pause");
	return 0;
}