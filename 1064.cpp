#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <queue>
using namespace std;

int records[1005];
int num = 0;
int standard[12] = {0, 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047};


int rootIndex(int startpos, int endpos)
{
	int length = endpos - startpos;
	int height = 1;
	int rootpos;
	while (standard[height] < length)
	{
		++height;
	}
	if (standard[height] == length)
	{
		rootpos = startpos + standard[height]/2;
	}
	else
	{
		if ( (length - standard[height-1]) <= (standard[height] - standard[height-1])/2)
		{
			rootpos = length - standard[height-2] - 1 + startpos;
		}
		else
		{
			rootpos = standard[height-1] + startpos;
		}
	}
	return rootpos;
}

void levelOrderTranverse()
{
	queue<int> nQ;
	int count = 0;
	int startpos, endpos, rootpos;
	nQ.push(0);
	nQ.push(num);
	while (!nQ.empty())
	{
		startpos = nQ.front();
		nQ.pop();
		endpos = nQ.front();
		nQ.pop();
		rootpos = rootIndex(startpos, endpos);
		if (++count != num)
		{
			printf("%d ", records[rootpos]);
		} 
		else
		{
			printf("%d\n", records[rootpos]);
		}
		if (rootpos > startpos)
		{
			nQ.push(startpos);
			nQ.push(rootpos);
		}
		if (rootpos+1 < endpos)
		{
			nQ.push(rootpos+1);
			nQ.push(endpos);
		}
	}
}

#if 0
void levelOrderTranverse(int startpos, int endpos)
{
	int length = endpos - startpos;
	int height = 1;
	int rootpos;
	while (standard[height] < length)
	{
		++height;
	}
	if (standard[height] == length)
	{
		rootpos = startpos + standard[height]/2;
	}
	else
	{
		rootpos = length - standard[height-2] - 1 + startpos;
	}
	
	if (++ncount != num)
	{
		printf("%d ", records[rootpos]);
	}
	else
	{
		printf("%d", records[rootpos]);
	}

	if (startpos < rootpos)
	{
		levelOrderTranverse(startpos, rootpos);
	}
	if (endpos > rootpos+1)
	{
		levelOrderTranverse(rootpos+1, endpos);
	}
}
#endif


int main()
{
	scanf("%d", &num);
	for (int i = 0; i != num; ++i)
	{
		scanf("%d", records+i);
	}
	sort(records, records+num);
	
	levelOrderTranverse();
	system("pause");
	return 0;
}