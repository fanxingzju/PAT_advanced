#include <iostream>
#include <string>
using namespace std;

string slow_std[13] = {"", "jan", "feb", "mar", "apr", "may", "jun", "jly", "aug", "sep", "oct", "nov", "dec"};
string shigh_std[13] = {"", "tam", "hel", "maa", "huh", "tou", "kes", "hei", "elo", "syy", "lok", "mer", "jou"};
int N;
string buffer;
string szero = "tret";

void mars_process()
{
	string slow, shigh;
	string::iterator iter = buffer.begin()+3;
	int number = 0;
	if (buffer == szero)
	{
		cout << '0' << endl;
		return ;
	}
	if (3 == buffer.size())
	{
		for (int i = 1; i != 13; ++i)
		{
			if (buffer == slow_std[i])
			{
				cout << i << endl;
				return ;
			}
			if (buffer == shigh_std[i])
			{
				cout << i*13 << endl;
				return ;
			}
		}
	}
	shigh.assign(buffer.begin(), iter);
	++iter;
	slow.assign(iter, buffer.end());
	for (int i = 1; i != 13; ++i)
	{
		if (slow == slow_std[i])
		{
			number += i;
		}
		if (shigh == shigh_std[i])
		{
			number += 13*i;
		}
	}
	cout << number << endl;
	return ;
}

void earth_process()
{
	int nlow, nhigh;
	int number = 0;
	for (int i = 0; i != buffer.size(); ++i)
	{
		number = number*10 + buffer[i] - '0';
	}
	if (0 == number)
	{
		cout << szero << endl;
		return ;
	}
	nlow = number%13;
	nhigh = number/13;
	if (0 != nhigh)
	{
		cout << shigh_std[nhigh];
	}
	if (0 != nhigh && 0 != nlow)
	{
		cout << ' ';
	}
	if (0 != nlow)
	{
		cout << slow_std[nlow];
	}
	cout << endl;
}

int main()
{
	cin >> N;
	cin.get();
	for (int i = 0; i != N; ++i)
	{
		getline(cin, buffer);
		if (buffer[0] >= '0' && buffer[0] <= '9')
		{
			earth_process();
		}
		else
		{
			mars_process();
		}
	}


	system("pause");
	return 0;
}