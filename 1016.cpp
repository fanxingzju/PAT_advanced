#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <iomanip>
using namespace std;

int rate[24];					// 一天各个时间段的费率

typedef struct node
{
	char name[25];
	char time[12];
	char line_state[10];
}node;

typedef struct timeformat
{
	int month;
	int day;
	int hour;
	int minute;
}timeformat;

// 排序的大小判断
bool nodeCompare(const node &A, const node &B)
{
	if (0 == strcmp(A.name, B.name))
	{
		if (strcmp(A.time, B.time) < 0)
		{
			return true;
		}
		else
		{
			return false;
		}
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

timeformat transform(char time[])
{
	timeformat ret;
	
	ret.month = (time[0] - '0')*10 + time[1] - '0';
	ret.day = (time[3] - '0')*10 + time[4] - '0';
	ret.hour = (time[6] - '0')*10 + time[7] - '0';
	ret.minute = (time[9] - '0')*10 + time[10] - '0';

	return ret;
}

int operator-(const timeformat &A, const timeformat &B)
{
	int ret;
	// 用来测试的数据都在同一个月份
	ret = (A.day-B.day)*24*60 + (A.hour-B.hour)*60 + (A.minute-B.minute);
	return ret;
}

// 用来分段计算费用的中间值
timeformat nextHour(const timeformat &A)
{
	timeformat ret;
	ret.month = A.month;
	if (23 == A.hour)
	{
		ret.hour = 0;
		ret.day = A.day+1;
	}
	else
	{
		ret.day = A.day;
		ret.hour = A.hour+1;
	}
	ret.minute = 0;
	return ret;
}

// 计算费用
int cost(char timeA[], char timeB[])
{
	int totalcost = 0;
	timeformat start = transform(timeA);
	timeformat end = transform(timeB);
	timeformat temp = nextHour(start);
	
	printf("%02d:%02d:%02d ", start.day, start.hour, start.minute);
	printf("%02d:%02d:%02d %d $", end.day, end.hour, end.minute, end-start);
	while (end - temp > 0)
	{
		totalcost += (temp-start)*rate[start.hour];
		start = temp;
		temp = nextHour(start);
	}
	totalcost += (end - start)*rate[start.hour];
	/* cout << fixed << setprecision(2) << totalcost*1.0/100 << endl;*/

	printf("%.2lf\n", totalcost*1.0/100);
	return totalcost;
}

// 第index条数据和它下一条数据是否匹配
bool match(node *records, int num, int index)
{
	if (index == num -1)
	{
		return false;
	}
	if (0 == strcmp(records[index].name, records[index+1].name)
		&& 0 == strcmp(records[index].line_state, "on-line")
		&& 0 == strcmp(records[index+1].line_state, "off-line"))
	{
		return true;
	}
	return false;
}


int main()
{
	int num;
	node *records = NULL;
	int tempCost = 0;
	char tempName[25];

	for (int i = 0; i != 24; ++i)
	{
		cin >> rate[i];
	}
	cin >> num;
	records = new node[num];
	for (int i = 0; i != num; ++i)
	{
		cin >> records[i].name;
		cin >> records[i].time;
		cin >> records[i].line_state;
	}
	
	memset(tempName, 0x0, 25);
	sort(records, records+num, nodeCompare);


#if 0
	cout << endl << endl;
	for (int i = 0; i != num; ++i)
	{
		cout << records[i].name << "  ";
		cout << records[i].time << "  ";
		cout << records[i].line_state << endl;
	}
	cout << endl << endl;
#endif

	for (int index = 0; index < num; ++index)
	{
		if (match(records, num, index))
		{
			if (0 != strcmp(tempName, records[index].name))
			{
				if (0 != tempCost)
				{
					/* cout << "Total amount: $" << fixed << setprecision(2) << tempCost*1.0/100 << endl;*/
					printf("Total amount: $%.2lf\n", tempCost*1.0/100);
					tempCost = 0;
				}
				memcpy(tempName, records[index].name, 25);
				printf("%s %2.2s\n", records[index].name, records[index].time);
			}
			tempCost += cost(records[index].time, records[index+1].time);
		}
	}

	if (0 != tempCost)
	{
		/* cout << "Total amount: $" << fixed << setprecision(2) << tempCost*1.0/100 << endl;*/
		printf("Total amount: $%.2lf\n", tempCost*1.0/100);
	}

	delete[] records;
	system("pause");
	return 0;
}