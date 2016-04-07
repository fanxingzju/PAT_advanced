// A student name consists of 3 capital English letters plus a one-digit number. 
// ����ʹ�ù�ϣ��
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> students[26*26*26*10+5];

int hashName(const char *name)
{
	return (name[0]-'A')*26*26*10 + (name[1]-'A')*26*10 + (name[2]-'A')*10 + (name[3]-'0');
}

int main()
{
	int N, K;
	int index, N_i;
	char name[5];
	int hname;

	scanf("%d %d", &N, &K);
	for (int i = 0; i != K; ++i)
	{
		scanf("%d %d", &index, &N_i);
		for (int j = 0; j != N_i; ++j)
		{
			scanf("%s", name);
			hname = hashName(name);
			students[hname].push_back(index);
		}
	}
	
	for (int i = 0; i != N; ++i)
	{
		scanf("%s", name);
		hname = hashName(name);
		printf("%s", name);
		printf(" %d", students[hname].size());
		sort(students[hname].begin(), students[hname].end());
		
		for (int j = 0; j != students[hname].size(); ++j)
		{
			printf(" %d", students[hname][j]);
		}
		printf("\n");
	}
	system("pause");
	return 0;
}









// �Ľ�����㷨
// case5 ��ʱ
#if 0
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// ѧ�������Ϳγ���
int N, K;
// K <= 2500, N sub i <= 200
// records[i][j] ��ʾ ѡ��i���γ̵ĵ�j��ͬѧ
// records[0][..]����
string records[2503][203];

// courses[i]ѡ��i���γ̵�����
int courses[2503];

// �洢��i��query��ѧ������
string students[40005];

// results[i][0] ��¼��i��ѧ��ѡ������
// results[i][1..results[i][0]] �ֱ��¼��i��ѧ��ѡ�Ŀγ����
int results[40005][2505];


typedef struct node
{
	string name;
	int index;
}node;
// �洢������queryѧ��
node students_tmp[40005];

int find_index(string target)
{
	int low, high, mid;
	low = 0;
	high = N-1;
	while (low <= high)
	{
		mid = (low+high)/2;
		if (target < students_tmp[mid].name)
		{
			high = mid-1;
		}
		else
		{
			if (target > students_tmp[mid].name)
			{
				low = mid+1;
			}
			else
			{
				return students_tmp[mid].index;
			}
		}
	}
	return -1;
}

bool my_less_than(const node &A, const node &B)
{
	return A.name < B.name;
}

int main()
{
	int index, N_i;


	cin >> N >> K;

	for (int i = 0; i != K; ++i)
	{
		cin >> index >> N_i;
		courses[index] = N_i;
		for (int j = 0; j != N_i; ++j)
		{
			cin >> records[index][j];
		}
	}

	for (int i = 0; i != N; ++i)
	{
		cin >> students[i];
		students_tmp[i].name = students[i];
		students_tmp[i].index = i;
	}

	// ������,�����,���ٲ��Ҵ���
	sort(students_tmp, students_tmp+N, my_less_than);

	for (int i = 1; i <= K; ++i)
	{
		for (int j = 0; j != courses[i]; ++j)
		{
			int temp = find_index(records[i][j]);
			++results[temp][0];
			results[temp][results[temp][0]] = i;
		}
	}

	for (int i = 0; i != N; ++i)
	{
		cout << students[i] << ' ' << results[i][0];
		for (int j = 1; j <= results[i][0]; ++j)
		{
			cout << ' ' << results[i][j];
		}
		cout << endl;
	}

	
	system("pause");
	return 0;
}
#endif




// case5 ��ʱ
#if 0
#include <iostream>
#include <string>
using namespace std;

// ѧ�������Ϳγ���
int N, K;
// K <= 2500, N sub i <= 200
// records[i][j] ��ʾ ѡ��i���γ̵ĵ�j��ͬѧ
// records[0][..]����
string records[2503][203];

// courses[i]ѡ��i+1���γ̵�����
int courses[2503];

// �洢��i��query��ѧ������
string students[40005];

// results[i][0] ��¼��i��ѧ��ѡ������
// results[i][1..results[i][0]] �ֱ��¼��i��ѧ��ѡ�Ŀγ����
int results[40005][2505];

int find_index(string target)
{
	for (int i = 0; i != N; ++i)
	{
		if (0 == target.compare(students[i]))
		{
			return i;
		}
	}
	return -1;
}

int main()
{
	int index, N_i;


	cin >> N >> K;

	for (int i = 0; i != K; ++i)
	{
		cin >> index >> N_i;
		courses[index] = N_i;
		for (int j = 0; j != N_i; ++j)
		{
			cin >> records[index][j];
		}
	}

	for (int i = 0; i != N; ++i)
	{
		cin >> students[i];
	}

	for (int i = 1; i <= K; ++i)
	{
		for (int j = 0; j != courses[i]; ++j)
		{
			int temp = find_index(records[i][j]);
			++results[temp][0];
			results[temp][results[temp][0]] = i;
		}
	}

	for (int i = 0; i != N; ++i)
	{
		cout << students[i] << ' ' << results[i][0];
		for (int j = 1; j <= results[i][0]; ++j)
		{
			cout << ' ' << results[i][j];
		}
		cout << endl;
	}

	
	system("pause");
	return 0;
}
#endif