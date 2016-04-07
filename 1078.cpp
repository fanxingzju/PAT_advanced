#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#define MAX_LENGTH 10010
int occupied[MAX_LENGTH];
int position[MAX_LENGTH];
int input[MAX_LENGTH];

bool is_prime(int x)
{
	double sqrtx = sqrt(x*1.0);
	if (1 == x)
	{
		return false;
	}
	if (2 == x)
	{
		return true;
	}
	for (int i = 2; i < sqrtx+1; ++i)
	{
		if (0 == x%i)
		{
			return false;
		}
	}
	return true;
}

int main()
{
	int Msize, N;
	int pos;
	int tmp;
	scanf("%d %d", &Msize, &N);
	while (!is_prime(Msize))
	{
		++Msize;
	}
	for (int i = 0; i != N; ++i)
	{
		scanf("%d", input+i);
	}

	for (int i = 0; i != N; ++i)
	{
		pos = input[i]%Msize;
		tmp = 1;
		do 
		{
			if (0 == occupied[pos])
			{
				occupied[pos] = 1;
				position[i] = pos;
				break;
			}
			pos = (input[i]%Msize + tmp*tmp)%Msize;
			++tmp;
		} while (tmp < Msize);

		if (tmp >= Msize)
		{
			position[i] = -1;
		}

	}

	printf("%d", position[0]);
	for (int i = 1; i < N; ++i)
	{
		if (-1 == position[i])
		{
			printf(" -");
		}
		else
		{
			printf(" %d", position[i]);
		}
	}
	printf("\n");

	system("pause");
	return 0;
}