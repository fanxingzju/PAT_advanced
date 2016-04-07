#include <iostream>

using namespace std;

char radix[13] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C'};

int main()
{
	int red, green, blue;
	char result[8];

	cin >> red >> green >> blue;

	result[0] = '#';
	result[1] = radix[red/13];
	result[2] = radix[red%13];

	result[3] = radix[green/13];
	result[4] = radix[green%13];

	result[5] = radix[blue/13];
	result[6] = radix[blue%13];
 
	result[7] = '\0';

	cout << result << endl;
	system("pause");
	return 0;
}