#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>

using namespace std;

typedef struct node
{
	unsigned int ID;
	char name[9];
	unsigned int grade;
}node;

node records[100005];

bool compare_column1(node &A, node &B)
{
	return A.ID < B.ID;
}

bool compare_column2(node &A, node &B)
{
	int ret = strcmp(A.name, B.name);
	if (0 == ret)
	{
		return compare_column1(A, B);
	}
	else
	{
		if (ret < 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}


bool compare_column3(node &A, node &B)
{
	if (A.grade == B.grade)
	{
		return compare_column1(A, B);
	}
	return A.grade < B.grade;
}


int main()
{
	int num;
	int column;
	cin >> num >> column;

	for (int i = 0; i != num; ++i)
	{
		cin >> records[i].ID;
		cin >> records[i].name;
		cin >> records[i].grade;
	}

	switch (column)
	{
	case 1:
		sort(records, records+num, compare_column1);
		break;
	case 2:
		sort(records, records+num, compare_column2);
		break;
	case 3:
		sort(records, records+num, compare_column3);
		break;
	}

	for (int i = 0; i != num; ++i)
	{
		printf("%06d ", records[i].ID);
		printf("%s ", records[i].name);
		printf("%d\n", records[i].grade);
	}

	system("pause");
	return 0;
}