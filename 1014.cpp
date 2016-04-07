/* 注意题目中:"Note that since the bank is closed everyday after 17:00, for those customers who cannot be served before 17:00, you must output 'Sorry' instead"*/
/* 17:00之前已经开始办理业务的, 都应该输出其结束时间*/
#include <iostream>
#include <stdio.h>
using namespace std;

#define OPENTIME 480

typedef struct node
{
	int startTime;
	int endTime;
	struct node *next;
}node;

typedef struct elem
{
	node *head;				// 该柜台每天处理的第一个顾客
	int personInQueue;
	node *first;			// 指向正在该柜台正在处理的顾客
	node *last;				// 指向该柜台正在排队的最后一名顾客
}elem;

typedef struct outcome 
{
	int startTime;
	int endTime;
}outcome;

outcome queueCase1(elem *list, int windowsNum, int transactionTime)
{
	int index = 0;
	node *temp = NULL;
	outcome ret;
	for (int i = 1; i != windowsNum; ++i)
	{
		if (list[i].personInQueue < list[0].personInQueue)
		{
			index = i;
			break;
		}
	}
	
	++list[index].personInQueue;
	temp = new node;
	if (NULL == list[index].head)
	{
		temp->startTime = OPENTIME;
		
		list[index].head = temp;
		list[index].first = temp;
		list[index].last = temp;
	}
	else
	{
		temp->startTime = list[index].last->endTime;

		list[index].last->next = temp;
		list[index].last = temp;
	}
	temp->next = NULL;
	temp->endTime = temp->startTime + transactionTime;

	ret.startTime = temp->startTime;
	ret.endTime = temp->endTime;
	return ret;
}

outcome queueCase2(elem *list, int windowsNum, int transactionTime)
{
	int index = 0;
	node *temp = NULL;
	outcome ret;
	int endtime = list[0].first->endTime;
	for (int i = 1; i != windowsNum; ++i)
	{
		if (list[i].first->endTime < endtime)
		{
			endtime = list[i].first->endTime;
			index = i;
		}
	}

	temp = new node;
	temp->startTime = list[index].last->endTime;
	temp->endTime = temp->startTime + transactionTime;
	temp->next = NULL;

	list[index].last->next = temp;
	list[index].last = list[index].last->next;
	list[index].first = list[index].first->next;
	
	ret.startTime = temp->startTime;
	ret.endTime = temp->endTime;

	return ret;
}

outcome addtolist(elem *list, int windowsNum, int maxCapcity, int transactionTime)
{
	outcome ret;
	if (maxCapcity == list[windowsNum-1].personInQueue)
	{
		ret = queueCase2(list, windowsNum, transactionTime);
	}
	else
	{
		ret = queueCase1(list, windowsNum, transactionTime);
	}
	return ret;
}


void destorylist(elem *&list, int windowsNum)
{
	node *pre = NULL;
	node *cur = NULL;
	for (int i = 0; i != windowsNum; ++i)
	{
		pre = cur = list[i].head;
		while(pre)
		{
			cur = cur->next;
			delete pre;
			pre = cur;
		}
	}
	delete[] list;
	list = NULL;
}

int main()
{

	int windowsNum;
	int maxCapcity;
	int customerNum;
	int queriesNum;
	int *transactionTime = NULL;
	outcome *result = NULL;
	elem *list = NULL;
	int *personId = NULL;
	cin >> windowsNum >> maxCapcity >> customerNum >> queriesNum;
	transactionTime = new int[customerNum];
	personId = new int[queriesNum];
	if (NULL == transactionTime)
	{
		return -1;
	}
	for (int i = 0; i != customerNum; ++i)
	{
		cin >> transactionTime[i];
	}
	for (int i = 0; i != queriesNum; ++i)
	{
		cin >> personId[i];
	}

	list = new elem[windowsNum];
	for (int i = 0; i != windowsNum; ++i)
	{
		list[i].head = NULL;
		list[i].personInQueue = 0;
		list[i].first = NULL;
		list[i].last = NULL;
	}

	result = new outcome[customerNum];

	for (int i = 0; i != customerNum; ++i)
	{
		result[i] = addtolist(list, windowsNum, maxCapcity, transactionTime[i]);
	}

	for (int i = 0; i != queriesNum; ++i)
	{
		int index = personId[i]-1;
		if (OPENTIME <= result[index].startTime && result[index].startTime < 17*60)
		{
			printf("%02d:%02d\n", result[index].endTime/60, result[index].endTime%60);
		}
		else
		{
			cout << "Sorry" << endl;
		}
	}


	destorylist(list, windowsNum);
	delete[] transactionTime;
	delete[] result;
	delete[] personId;
	system("pause");
	return 0;
}