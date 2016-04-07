#include <stdio.h>
#include <algorithm>
using namespace std;

typedef struct node
{
	int addr;
	int data;
	int next;
}node;

int N, K;
int length = 0;

node input[100010];
node result[100010];
bool less_than_node(const node &A, const node &B)
{
	return A.addr < B.addr;
}

int binary_search_node(int target)
{
	int low = 0;
	int high = N-1;
	int mid;
	while (low <= high)
	{
		mid = (low+high)/2;
		if (input[mid].addr == target)
		{
			return mid;
		}
		else
		{
			if (input[mid].addr > target)
			{
				high = mid-1;
			}
			else
			{
				low = mid+1;
			}
		}
	}
	return -1;
}

void reverse_fixup()
{
	int parts = length/K;
	node temp;
	for (int i = 0; i != parts; ++i)
	{
		for (int j = 0; j != K/2; ++j)
		{
			temp = result[i*K+j];
			result[i*K+j] = result[i*K+K-j-1];
			result[i*K+K-j-1] = temp;
		}
	}
	for (int i = 0; i != length-1; ++i)
	{
		result[i].next = result[i+1].addr;
	}
	result[length-1].next = -1;
}

int main()
{
	int startaddr, index, parts;
	scanf("%d %d %d", &startaddr, &N, &K);
	for (int i = 0; i != N; ++i)
	{
		scanf("%d %d %d", &input[i].addr, &input[i].data, &input[i].next);
	}

	sort(input, input+N, less_than_node);

	for (int i = 0; i != N; ++i)
	{
		index = binary_search_node(startaddr);
		result[i] = input[index];
		startaddr = input[index].next;
		++length;
		if (-1 == startaddr)
		{
			break;
		}
	}
	
	reverse_fixup();

	for(int i = 0; i != length-1; ++i)
	{
		printf("%05d %d %05d\n", result[i].addr, result[i].data, result[i].next);
	}
	printf("%05d %d -1\n", result[length-1].addr, result[length-1].data);

	system("pause");
	return 0;
}