#include <stdio.h>
#include <stdlib.h>
int bits[24];

void count_bits(int target)
{
	for (int i = 0; i != 24; ++i)
	{
		if ( target >> i & 0x1 == 0x1)
		{
			++bits[i];
		}
	}
}

int main()
{
	int M, N;
	int color;
	int threshold;
	scanf("%d %d", &M, &N);
	
	for (int i = 0; i != N; ++i)
	{
		for (int j = 0; j != M; ++j)
		{
			scanf("%d", &color);
			count_bits(color);
		}
	}

	threshold = M*N/2;
	color = 0;
	for (int i = 0; i != 24; ++i)
	{
		if (bits[i] > threshold)
		{
			color |= 1 << i;
		}
	}
	printf("%d\n", color);
	system("pause");
	return 0;
}