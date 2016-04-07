/* 10^5(decimal) = 11000011010100000(binary)(共17位)*/
#include <iostream>
#include <math.h>
#include <stack>
using namespace std;

bool isPrime(int target)
{
	double temp = sqrt(target*1.0);
	if (0 == target || 1 == target)
	{
		return false;
	}
	for (int i = 2; i <= temp; ++i)
	{
		if (0 == target%i)
		{
			return false;
		}
	}
	return true;
}

typedef struct node
{
	int flag;							/* 0表示是reversible primes*/
	struct node *next;
}node;

int main()
{
	int integer;
	int radix;
	stack<int> digit;
	int value;
	int temp;
	node *list = new node;
	node *pre = list;
	node *cur;
	
	cin >> integer;
	while (integer >= 0)
	{
		cur = new node;
		cur->next = NULL;
		pre->next = cur;
		pre = cur;
		cin >> radix;
		if (!isPrime(integer))
		{
			cur->flag = -1;
			cin >> integer;
			continue;
		}

		while (radix <= integer)
		{
			digit.push(integer%radix);
			integer /= radix;
		}
		digit.push(integer);

		value = 0;
		temp = 1;
		while (!digit.empty())
		{
			value += digit.top()*temp;
			temp *= radix;
			digit.pop();
		}
		
		if (!isPrime(value))
		{
			cur->flag = -1;
		}
		else
		{
			cur->flag = 0;
		}

		cin >> integer;
	}

	cur = list->next;
	while (NULL != cur)
	{
		if (0 == cur->flag)
		{
			cout << "Yes" << endl;
		}
		else
		{
			cout << "No" << endl;
		}
		pre = cur;
		cur = cur->next;
		delete pre;
	}
	delete list;

	system("pause");
	return 0;
}