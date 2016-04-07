#include <algorithm>
#include <vector>
#include <stdio.h>
#include <string>
using namespace std;


vector<int> courses[2505];
// 建立student name和int一一对应关系
// each contains a student's name (3 capital English letters plus a one-digit number)
int hashName(const char *name)
{
	return (name[0]-'A')*26*26*10 + (name[1]-'A')*26*10 + (name[2]-'A')*10 + (name[3]-'0');
}

void rhashName_print(int id)
{
	char name[5];
	name[4] = '\0';
	name[3] = id%10 + '0';
	id /= 10;
	name[2] = id%26 + 'A';
	id /= 26;
	name[1] = id%26 + 'A';
	id /= 26;
	name[0] = id%26 + 'A';
	printf("%s\n", name);
}

int main()
{
	int N, K;
	int hname, index, num;
	char name[5];
	scanf("%d %d", &N, &K);



	for (int i = 0; i != N; ++i)
	{
		scanf("%s", name);
		scanf("%d", &num);
		hname = hashName(name);
		for (int j = 0; j != num; ++j)
		{
			scanf("%d", &index);
			courses[index].push_back(hname);
		}
	}

	for (int i = 1; i <= K; ++i)
	{
		printf("%d %d\n", i, courses[i].size());
		sort(courses[i].begin(), courses[i].end());
		for (int j = 0; j != courses[i].size(); ++j)
		{
			rhashName_print(courses[i][j]);
		}
	}

	system("pause");
	return 0;
}