#include <iostream>
#include <math.h>
#include <stack>
using namespace std;

int main()
{
	int number, base;
	cin >> number >> base;
	stack<int> digits;
	int ncount = 1;
	int *narray = NULL;
	bool flag = true;

	while (number >= base)
	{
		digits.push(number%base);
		number = number/base;
		++ncount;
	}
	digits.push(number);

	narray = new int[ncount];
	for (int i = 0; i != ncount; ++i)
	{
		narray[i] = digits.top();
		digits.pop();
	}
	
	for (int i = 0; i < ncount/2; ++i)
	{
		if (narray[i] != narray[ncount-i-1])
		{
			flag = false;
			break;
		}
	}

	if (flag)
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "No" << endl;
	}

	for (int i = 0; i != ncount-1; ++i)
	{
		cout << narray[i] << ' ';
	}
	cout << narray[ncount-1] << endl;

	system("pause");
	return 0;
}