#if 1
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef struct node
{
	char name[10];
	int age;
	int netWorth;
}node;

typedef struct elem
{
	int max_num;
	int Amin;
	int Amax;
}elem;

node records[100005];
elem queries[100005];

int N, M;

bool less_than_node(const node &A, const node &B)
{
	if (A.netWorth != B.netWorth)
	{
		return A.netWorth > B.netWorth;
	}
	else
	{
		if (A.age != B.age)
		{
			return A.age < B.age;
		}
		else
		{
			return strcmp(A.name, B.name) < 0;
		}
	}
}


void process_query(int index)
{
	int count = 0;
	for (int i = 0; i != N; ++i)
	{
		if (count >= queries[index].max_num)
		{
			return ;
		}

		if (records[i].age >= queries[index].Amin && records[i].age <= queries[index].Amax)
		{
			++count;
			printf("%s %d %d\n", records[i].name, records[i].age, records[i].netWorth);
		}
	}
	if (0 == count)
	{
		printf("None\n");
	}
	return ;
}


int main()
{
	scanf("%d %d", &N, &M);
	for (int i = 0; i != N; ++i)
	{
		scanf("%s %d %d", records[i].name, &records[i].age, &records[i].netWorth);
	}

	sort(records, records+N, less_than_node);

	for (int i = 0; i != M; ++i)
	{
		scanf("%d %d %d", &queries[i].max_num, &queries[i].Amin, &queries[i].Amax);
	}

	for (int i = 0; i != M; ++i)
	{
		printf("Case #%d:\n", i+1);
		process_query(i);
	}

	system("pause");
	return 0;
}








#else
// case 2³¬Ê±, Ë¼¿¼¸´ÔÓÁË
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef struct node
{
	char name[10];
	int age;
	int netWorth;
}node;

typedef struct elem
{
	int max_num;
	int Amin;
	int Amax;
}elem;

node records[100005];
node results[100005];
elem queries[100005];
int N, M;

bool less_than_age(const node &A, const node &B)
{
	return A.age < B.age;
}

bool less_than_netWorth(const node &A, const node &B)
{
	if (A.netWorth != B.netWorth)
	{
		return A.netWorth > B.netWorth;
	}
	else
	{
		if (A.age != B.age)
		{
			return A.age < B.age;
		}
		else
		{
			if (strcmp(A.name, B.name) < 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

int find_first_not_less(int targetAge)
{
	int index = 0;
	while (index != N && records[index].age < targetAge)
	{
		++index;
	}
	return index;
}

int find_last_not_bigger(int targetAge)
{
	int index = N-1;
	while (index != -1 && records[index].age > targetAge)
	{
		--index;
	}
	return index;
}

void process_query(int index)
{
	int startpos = find_first_not_less(queries[index].Amin);
	int endpos = find_last_not_bigger(queries[index].Amax);
	int num = endpos-startpos+1;
	if (startpos == N || endpos == -1 || num <= 0)
	{
		printf("None\n");
		return ;
	}

	memcpy(results, records+startpos, num*sizeof(node));

	sort(results, results+num, less_than_netWorth);
	
	for (int i = 0; i != queries[index].max_num && i != num; ++i)
	{
		printf("%s %d %d\n", results[i].name, results[i].age, results[i].netWorth);
	}

}


int main()
{
	scanf("%d %d", &N, &M);
	for (int i = 0; i != N; ++i)
	{
		scanf("%s %d %d", records[i].name, &records[i].age, &records[i].netWorth);
	}

	sort(records, records+N, less_than_age);


	for (int i = 0; i != M; ++i)
	{
		scanf("%d %d %d", &queries[i].max_num, &queries[i].Amin, &queries[i].Amax);
	}

	for (int i = 0; i != M; ++i)
	{
		printf("Case #%d:\n", i+1);
		process_query(i);
	}

	system("pause");
	return 0;
}

#endif