#include <iostream>
#include <algorithm>
#include <string.h>
#include <iomanip>
using namespace std;

#define OPENTIME 8*3600
#define CLOSETIME 17*3600

typedef struct node
{
	int startTime;
	int endTime;
	struct node *next;
}node;

typedef struct elem
{
	int arriveTime;
	int processTime;
}elem;

typedef struct list
{
	node *first;
	node *processing;
}list;

int transform(char time[])
{
	int ret = 0;

	ret = ((time[0] - '0')*10 + (time[1] - '0')) * 3600
		+ ((time[3] - '0')*10 + (time[4] - '0')) * 60
		+ ((time[6] - '0')*10 + (time[7] - '0'));
	return ret;
}

bool elemCompare(const elem &A, const elem &B)
{
	return A.arriveTime < B.arriveTime;
}

int main()
{
	int N, K;
	elem *customers;					// ����Ĺ˿�����
	char time[10];
	int *waitTime;						// ÿ���˵ĵȴ�ʱ��
	list *windows;						// ÿ�����ڵĶ���
	int validCount = 0;					// ��Ч�������(��17��00��00ǰ�ִ�bank)
	node *temp = NULL;

	int result = 0;


	cin >> N >> K;
	customers = new elem[N];
	waitTime = new int[N];
	windows = new list[K];
	// waiTime ȫ����ʼ��Ϊ0
	memset(waitTime, 0, sizeof(int)*N);
	// ��ʼ����������
	memset(windows, 0, sizeof(list)*K);

	for (int i = 0; i != N; ++i)
	{
		cin >> time >> customers[i].processTime;
		customers[i].arriveTime = transform(time);
		customers[i].processTime *= 60;					// ����ת��Ϊ��
		if (customers[i].arriveTime <= CLOSETIME)
		{
			++validCount;
		}
	}

	sort(customers, customers+N, elemCompare);

#if 0
	cout << endl << endl;

	for (int i = 0; i != N; ++i)
	{
		cout << customers[i].arriveTime << ' ' << customers[i].processTime << endl;
	}

	cout << endl << endl;

#endif

	for (int i = 0; i != K && i != validCount; ++i)
	{
		temp = new node;
		if(customers[i].arriveTime <= OPENTIME)
		{
			temp->startTime = OPENTIME;
			waitTime[i] = OPENTIME - customers[i].arriveTime;
		}
		else
		{
			temp->startTime = customers[i].arriveTime;
		}
		temp->endTime = temp->startTime + customers[i].processTime;
		temp->next = NULL;
		windows[i].first = temp;
		windows[i].processing = temp;
	}

	for (int i = K; i < validCount; ++i)
	{
		temp = new node;
		int index = 0;										// �����˽����Ķ���
		int endTime = windows[0].processing->endTime;

		for (int j = 1; j != K; ++j)
		{
			if (endTime > windows[j].processing->endTime)
			{
				endTime = windows[j].processing->endTime;
				index = j;
			}
		}

		if (customers[i].arriveTime < endTime)
		{
			temp->startTime = windows[index].processing->endTime;
			waitTime[i] = temp->startTime - customers[i].arriveTime;
		}
		else
		{
			temp->startTime = customers[i].arriveTime;
		}

		temp->endTime = temp->startTime + customers[i].processTime;
		temp->next = NULL;
		windows[index].processing->next = temp;
		windows[index].processing = temp;		
	}

	for (int i = 0; i != validCount; ++i)
	{
		/* cout << waitTime[i] << endl;*/
		result += waitTime[i];
	}
	cout << fixed << setprecision(1) << result*1.0/60/validCount << endl;

	system("pause");
}