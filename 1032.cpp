// 注意最后输出结果的格式
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

typedef struct node
{
	int addr;
	char data;
	int next;
	int head;					/* 表头节点的地址， 用以区分节点属于哪个链表*/
}node;

node records[100005];
int num;

bool compare_less_than(node &A, node &B)
{
	return A.addr < B.addr;
}

int binary_search(int target)
{
	int low = 0, high = num - 1;
	int mid;
	
	if (-1 == target)
	{
		return -1;
	}
	while (low <= high)
	{
		mid = (low+high)/2;
		if (target < records[mid].addr)
		{
			high = mid-1;
		}
		else
		{
			if (target > records[mid].addr)
			{
				low = mid+1;
			} 
			else
			{
				return mid;
			}
		}
	}

	return -1;
}


int main()
{
	int listA, listB;
	int indexA, indexB;
	cin >> listA >> listB >> num;

	for (int i = 0; i != num; ++i)
	{
		cin >> records[i].addr;
		cin >> records[i].data;
		cin >> records[i].next;
		records[i].head = -1;
	}

	// 为了速度，先排序，然后二分查找
	sort(records, records+num, compare_less_than);

	indexA = binary_search(listA);
	indexB = binary_search(listB);

	if (-1 == indexA || -1 == indexB)
	{
		cout << "-1" << endl;
		return 0;
	}

	while (-1 != indexA && -1 != indexB)
	{
		if (records[indexA].head == listB)
		{
			cout << setfill('0') << setw(5) << records[indexA].addr << endl;
			system("pause");
			return 0;
		}
		else
		{
			records[indexA].head = listA;
			indexA = binary_search(records[indexA].next);
		}
		if (records[indexB].head == listA)
		{
			cout << setfill('0') << setw(5) << records[indexB].addr << endl;
			system("pause");
			return 0;
		} 
		else
		{
			records[indexB].head = listB;
			indexB = binary_search(records[indexB].next);
		}
	}

	if (-1 == indexA)
	{
		while (-1 != indexB)
		{
			if (records[indexB].head == listA)
			{
				cout << setfill('0') << setw(5) << records[indexB].addr << endl;
				system("pause");
				return 0;
			} 
			else
			{
				records[indexB].head = listB;
				indexB = binary_search(records[indexB].next);
			}
		}
	}
	else
	{
		while (-1 != indexA)
		{
			if (records[indexA].head == listB)
			{
				cout << setfill('0') << setw(5) << records[indexA].addr << endl;
				system("pause");
				return 0;
			}
			else
			{
				records[indexA].head = listA;
				indexA = binary_search(records[indexA].next);
			}
		}
	}

	cout << "-1" << endl;


	system("pause");
	return 0;
}
