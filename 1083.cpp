#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
typedef struct node
{
	char name[12];
	char ID[12];
	int grade;
}node;

node *records = NULL;
int N;
int low, high;

bool less_than_node(const node &A, const node &B)
{
	return A.grade > B.grade;
}

int main()
{
	int count = 0;
	scanf("%d", &N);
	records = new node[N];
	for (int i = 0; i != N; ++i)
	{
		scanf("%s %s %d", records[i].name, records[i].ID, &records[i].grade);
	}
	scanf("%d %d", &low, &high);
	std::sort(records, records+N, less_than_node);

	for (int i = 0; i != N; ++i)
	{
		if (low <= records[i].grade && high >= records[i].grade)
		{
			printf("%s %s\n", records[i].name, records[i].ID);
			++count;
		}
	}
	if (0 == count)
	{
		printf("NONE\n");
	}
	delete[] records;
	system("pause");
	return 0;
}