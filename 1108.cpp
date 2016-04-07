/*
case3是只有一个合法输入的情况，printf("The average of %d number is %0.02f\n"
case4中可能有类似"123."的输入
*/

#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
using namespace std;


vector<float> records;

bool checkstr(string str)
{
	bool ispositive = true;
	int dotnum = 0;
	int dotpos = -1;
	float number;

	if (str[0] == '-')
	{
		ispositive = false;
		str = str.substr(1, str.size()-1);
	}

	for (int i = 0; i != str.size(); ++i)
	{
		if ('0' <= str[i] && '9' >= str[i])
		{
		}
		else
		{
			if ('.' == str[i])
			{
				++dotnum;
				dotpos = i;
			}
			else
			{
				return false;
			}
		}
	}

	if (dotnum > 1)
	{
		return false;
	}

	/* (dotpos != str.size()-2 && dotpos != str.size()-3)*/
	if (1 == dotnum && dotpos < static_cast<int>(str.size())-3)
	{
		return false;
	}
	number = atof(&str[0]);
	if (number > 1000)
	{
		return false;
	}
	if (!ispositive)
	{
		number = -number;
	}

	records.push_back(number);
	return true;
}

int main()
{
	int N;
	string str;
	float total = 0;

	cin >> N;
	for (int i = 0; i != N; ++i)
	{
		cin >> str;
		if (!checkstr(str))
		{
			cout << "ERROR: " << str << " is not a legal number" << endl;
		}
	}

	if (records.size() == 0)
	{
		cout << "The average of 0 numbers is Undefined" << endl;
	}
	else
	{
		if (records.size() == 1)
		{
			printf("The average of %d number is %0.02f\n", records.size(), records[0]);
		}
		else
		{
			for (int i = 0; i != records.size(); ++i)
			{
				total += records[i];
			}
			printf("The average of %d numbers is %0.02f\n", records.size(), total/records.size());
		}
	}


	return 0;
}