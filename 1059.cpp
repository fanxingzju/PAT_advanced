#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	unsigned long int prime;
	unsigned long int count;
}node;


// ÊÔÖµ
#define MAX_PRIME_FACTORS_NUM 100000
node results[MAX_PRIME_FACTORS_NUM];

int main()
{
	unsigned long int target;
	unsigned long int prime = 2;
	unsigned long int pre_prime = 0;
	unsigned long int length = 0;

	scanf("%ld", &target);

	printf("%ld=", target);
	if (1 == target)
	{
		printf("1\n");
		return 0;
	}

	while (1 != target)
	{
		if (0 == target%prime)
		{
			target /= prime;
			if (prime == pre_prime)
			{
				++results[length-1].count;
			}
			else
			{
				pre_prime = prime;
				results[length].prime = prime;
				results[length++].count = 1;
			}
		}
		else
		{
			while (0 != target%prime)
			{
				++prime;
			}
		}
	}

	if (1 == results[0].count)
	{
		printf("%ld", results[0].prime);
	}
	else
	{
		printf("%ld^%ld", results[0].prime, results[0].count);
	}
	
	for (unsigned long int i = 1; i < length; ++i)
	{
		printf("*");
		if (1 == results[i].count)
		{
			printf("%ld", results[i].prime);
		}
		else
		{
			printf("%ld^%ld", results[i].prime, results[i].count);
		}
	}
	printf("\n");

	system("pause");
	return 0;
}