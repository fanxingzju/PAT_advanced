#include <stdio.h>
#include <stack>
#include <stdlib.h>
#include <math.h>
using namespace std;

typedef struct node
{
	int parent;
	int height;
}node;


node records[100010];
int N;
double P, r;

int maxheight = -1;
int count = 0;

void set_height(int id)
{
	stack<int> nStack;
	int nparent;
	while (records[id].height == -1)
	{
		nStack.push(id);
		id = records[id].parent;
	}

	nparent = id;

	while (!nStack.empty())
	{
		id = nStack.top();
		nStack.pop();
		records[id].height = records[nparent].height+1;
		nparent = id;
	}
}


int main()
{
	int rootindex = 0;
	scanf("%d %lf %lf", &N, &P, &r);
	for (int i = 0; i != N; ++i)
	{
		records[i].height = -1;
		scanf("%d", &records[i].parent);
		if (records[i].parent == -1)
		{
			records[i].height = 0;
		}
	}
	
	for (int i = 0; i != N; ++i)
	{
		set_height(i);
	}

	for (int i = 0; i != N; ++i)
	{
		if (maxheight == records[i].height)
		{
			++count;
		}
		else
		{
			if (maxheight < records[i].height)
			{
				maxheight = records[i].height;
				count = 1;
			}
		}
	}
	r = 1 + r/100;
	printf("%0.2lf %d\n", P*pow(r, maxheight), count);
	system("pause");
	return 0;
}