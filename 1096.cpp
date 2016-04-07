/* 暴力解*/
#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	int target;
	int maxcount = 0;
	int count = 0;
	int remain;
	int dividor;
	int first;

	cin >> target;
	first = target;
	for (int i = 2; i < sqrt(target*1.0)+1; ++i)
	{
		count = 0;
		remain = target;
		for (dividor = i; remain%dividor == 0; remain /= dividor, ++dividor){}
		if (dividor-i > maxcount)
		{
			maxcount = dividor-i;
			first = i;
		}
	}
	if (0 == maxcount)
	{
		/* 如果是一个质数*/
		cout << 1 << endl << target << endl;
	}
	else
	{
		cout << maxcount << endl;
		for (int i = 0; i < maxcount-1; ++i)
		{
			cout << first+i << '*';
		}
		cout << first+maxcount-1 << endl;
	}
	system("pause");
	return 0;
}