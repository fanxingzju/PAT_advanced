#include <stdio.h>
#include <stdlib.h>
#include <deque>

using namespace std;
int main()
{
	int a,b,result = 0;
	scanf("%d%d",&a,&b);
	result = a + b;
	if (result < 0)
	{
		printf("-");
		result = -result;
	}
	if (result == 0)
	{
		printf("0");
	}

	deque<char> output;
	int count = 0;

	while(result != 0)
	{
		if ((count%3 == 0)&&(count != 0))
		{
			output.push_front(',');
		}
		int temp = result % 10;
		result = (result - temp)/10;
		output.push_front(temp+'0');
		++count;
	}
	for (deque<char>::iterator iter = output.begin(); iter != output.end(); ++iter)
	{
		printf("%c",*iter);
	}
	printf("\n");
	system("pause");
	return 0;
}