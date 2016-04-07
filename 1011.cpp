#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	double game[3][3];
	int choice[3];
	double result = 1;
	int temp = 0;

	for (int i = 0; i != 3; ++i)
	{
		int index = 0;
		for (int j = 0; j != 3; ++j)
		{
			cin >> game[i][j];
			if (game[i][j] > game[i][index])
			{
				index = j;
			}
		}
		choice[i] = index;
	}
	for (int i = 0; i != 3; ++i)
	{
		result *= game[i][choice[i]];
		switch(choice[i])
		{
		case 0:
			cout << "W ";
			break;
		case 1:
			cout << "T ";
			break;
		case 2:
			cout << "L ";
			break;
		default:
			system("pause");
			return -1;
		}
	}
	result = (result*0.65-1)*2;

	temp = int(result*100);

	/* 处理精度损失的问题, 并进行四舍五入*/
	if(result-temp*0.01 >= 0.004999999)
	{
		result += 0.005000001;
	}

	cout << fixed << setprecision(2) << result << endl;
	system("pause");
	return 0;
}
