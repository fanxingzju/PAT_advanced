#include <stdio.h>
#include <algorithm>
using namespace std;

char buffer[5];
char standard[5] = "6174";
int num;
int maxnum, minnum;

void num_to_buffer()
{
	int temp = num;
	for (int i = 3; i != -1; --i)
	{
		buffer[i] = temp%10 + '0';
		temp /= 10;
	}
	buffer[4] = '\0';
}

void process()
{
	int multi = 1;
	sort(buffer, buffer+4);
	minnum = maxnum = 0;
	for (int i = 0; i != 4; ++i)
	{
		maxnum += multi * (buffer[i] - '0');
		minnum += multi * (buffer[3-i] - '0');
		multi *= 10;
	}
	num = maxnum - minnum;
}

bool is_xxxx()
{
	for(int i = 1; i != 4; ++i)
	{
		if (buffer[i] != buffer[0])
		{
			return false;
		}
	}
	return true;
}


int main()
{
	scanf("%d", &num);
	num_to_buffer();
	if (is_xxxx())
	{
		printf("%s - %s = 0000\n", buffer, buffer);
		return 0;
	}
	
	do
	{
		process();
		printf("%04d - %04d = %04d\n", maxnum, minnum, num);
		num_to_buffer();
	} while (6174 != num);

	system("pause");
	return 0;
}