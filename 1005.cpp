#include <iostream>
using namespace std;

// N < 10^100, sum < 10*100 = 1000, sum最大为三位数
void spell(const int &num)
{
	switch(num)
	{
	case 0:
		cout << "zero";
		break;
	case 1:
		cout << "one";
		break;
	case 2:
		cout << "two";
		break;
	case 3:
		cout << "three";
		break;
	case 4:
		cout << "four";
		break;
	case 5:
		cout << "five";
		break;
	case 6:
		cout << "six";
		break;
	case 7:
		cout << "seven";
		break;
	case 8:
		cout << "eight";
		break;
	case 9:
		cout << "nine";
		break;
	default:
		cout << "error";
		break;
	}
}



int main()
{
	char ctemp;
	int ntemp = 0;
	int sum = 0;
	int flag = 0;					// 用于控制输出格式
	ctemp = cin.get();
	while (ctemp != '\n')
	{
		sum += ctemp - '0';
		ctemp = cin.get();
	}
	ntemp = sum/100;
	if (0 != ntemp)
	{
		spell(ntemp);
		cout << ' ';
		flag = 1;
	}
	sum = sum - ntemp*100;
	ntemp = sum/10;

	if (1 == flag || 0 != ntemp)
	{
		spell(ntemp);
		cout << ' ';
		flag = 1;
	}

	ntemp = sum - ntemp*10;
	spell(ntemp);

	// system("pause");
	return 0;
}