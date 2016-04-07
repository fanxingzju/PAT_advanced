#include <iostream>
#include <algorithm>
using namespace std;

#define FEMALE 0
#define MALE 1

typedef struct node
{
	char name[11];
	int sex;
	char ID[11];
	int grade;
}node;

void transform(char *buffer, node *target)
{
	int pos = 0;
	int index = 0;

	while(buffer[pos] != ' ')
	{
		target->name[index] = buffer[pos];
		++index;
		++pos;
	}
	target->name[index] = '\0';

	++pos;

	if (buffer[pos] == 'M')
	{
		target->sex = MALE;
	}
	else
	{
		target->sex = FEMALE;
	}
	pos += 2;
	index = 0;
	while(buffer[pos] != ' ')
	{
		target->ID[index] = buffer[pos];
		++pos;
		++index;
	}
	target->ID[index] = '\0';

	++pos;
	target->grade = 0;
	while(buffer[pos] != '\0')
	{
		target->grade = target->grade*10 + buffer[pos] - '0';
		++pos;
	}
	return;
}

bool my_less_than(node &A, node &B)
{
	if (A.sex != B.sex)
	{
		return A.sex > B.sex;
	}
	else
	{
		return A.grade < B.grade;
	}
}


int main()
{
	int N;
	char buffer[50];
	node *records;
	bool flag = true;
	
	cin >> N;
	records = new node[N];
	cin.get();
	for (int i = 0; i != N; ++i)
	{
		cin.getline(buffer, 50);
		transform(buffer, records+i);
	}
	
	sort(records, records+N, my_less_than);

	if (records[N-1].sex == FEMALE)
	{
		cout << records[N-1].name << ' ' << records[N-1].ID << endl;
	}
	else
	{
		cout << "Absent" << endl;
		flag = false;
	}

	if (records[0].sex == MALE)
	{
		cout << records[0].name << ' ' << records[0].ID << endl;
	}
	else
	{
		cout << "Absent" << endl;
		flag = false;
	}

	if (flag)
	{
		cout << records[N-1].grade - records[0].grade << endl;
	}
	else
	{
		cout <<  "NA" << endl;
	}

	free(records);

	system("pause");
	return 0;
}