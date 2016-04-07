// 很多时候运行超时，只需要将cin修改为scanf
#include <iostream>
#include <algorithm>
using namespace std;

long int records[2000005];
long int buffer[1000003];


int main()
{
	int lengthA, lengthB;
	int length;

	cin >> lengthA;
	for (int i = 0; i != lengthA; ++i)
	{
		scanf("%ld", records+i);
	}
	cin >> lengthB;
	for (int i = lengthA; i != lengthA+lengthB; ++i)
	{
		scanf("%ld", records+i);
	}

	sort(records, records+lengthA+lengthB);

	length = unique(records, records+lengthA+lengthB) - records;

	if (0 == length%2)
	{
		printf("%ld\n", records[length/2-1]);
	}
	else
	{
		printf("%ld\n", records[length/2]);
	}


	system("pause");
	return 0;
}

