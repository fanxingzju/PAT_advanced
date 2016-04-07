#include <stdio.h>
#include <algorithm>
#include <vector>
#include <stdlib.h>
using namespace std;
typedef struct school
{
	int quota;
	vector<int> admitted;
}school;

typedef struct student
{
	int id;
	int ge;
	int gi;
	int rank;
	int prefer[5];
}student;

school *sch = NULL;
student stu[40010];

int N, M, K;

bool less_than_stu(const student &A, const student &B)
{
	if (A.ge + A.gi != B.ge + B.gi)
	{
		return (A.ge+A.gi > B.ge+B.gi);
	}
	else
	{
		return A.ge > B.ge;
	}
}

void set_rank()
{
	int prege = 0x7fffffff;
	int pregi = 0x7fffffff;
	int prerank = 0;
	for (int i = 0; i != N; ++i)
	{
		if (prege == stu[i].ge && pregi == stu[i].gi)
		{
			stu[i].rank = prerank;
		}
		else
		{
			stu[i].rank = i;
			prerank = i;
			prege = stu[i].ge;
			pregi = stu[i].gi;
		}
	}
}

bool push_in_school(int stuid, int schid)
{
	if (sch[schid].admitted.size() < sch[schid].quota
		|| stu[stuid].rank == stu[sch[schid].admitted.back()].rank)
	{
		sch[schid].admitted.push_back(stuid);
		return true;
	}
	return false;
}

int main()
{
	scanf("%d %d %d", &N, &M, &K);
	sch = new school[M];
	for (int i = 0; i != M; ++i)
	{
		scanf("%d", &sch[i].quota);
	}

	for (int i = 0; i != N; ++i)
	{
		scanf("%d %d", &stu[i].ge, &stu[i].gi);
		for (int j = 0; j != K; ++j)
		{
			scanf("%d", &stu[i].prefer[j]);
		}
		stu[i].id = i;
	}
	sort(stu, stu+N, less_than_stu);
	set_rank();
	
	for (int i = 0; i != N; ++i)
	{
		for (int j = 0; j != K; ++j)
		{
			if (push_in_school(stu[i].id, stu[i].prefer[j]))
			{
				break;
			}
		}
	}

	for (int i = 0; i != M; ++i)
	{
		if (!sch[i].admitted.empty())
		{
			sort(sch[i].admitted.begin(), sch[i].admitted.end());
			printf("%d", sch[i].admitted.at(0));
			for (vector<int>::const_iterator iter = sch[i].admitted.begin()+1;
				iter != sch[i].admitted.end(); ++iter)
			{
				printf(" %d", *iter);
			}
		}
		printf("\n");
	}
	delete[] sch;
	system("pause");
	return 0;
}