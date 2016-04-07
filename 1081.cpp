#include <stdio.h>
#include <stdlib.h>
typedef struct elem
{
	long long int num;
	long long int den;
}elem;
elem records[100];
int N;
elem result;
// 最重要的是需要一个高效的求两个数最大公约数的方法
long long int gcd(long long int A, long long int B)
{
	if (A < B)
	{
		return gcd(B, A);
	}
	if (0 == B)
	{
		return A;
	}
	else
	{
		if (0 == A&0x1)
		{
			if (0 == B&0x1)
			{
				return (gcd(A >> 1, B >> 1) << 1);
			}
			else
			{
				return gcd(A >> 1, B);
			}
		}
		else
		{
			if (0 == B&0x1)
			{
				return gcd(A, B >> 1);
			}
			else
			{
				return gcd(B, A-B);
			}
		}
	}
}

int main()
{
	long long int A, B, temp;
	bool flag = false;
	scanf("%d", &N);
	for (int i = 0; i != N; ++i)
	{
		scanf("%lld/%lld", &A, &B);
		if (B < 0)
		{
			B = -B;
			A = -A;
		}
		records[i].num = A;
		records[i].den = B;
	}
	result.den = records[0].den;
	for (int i = 1; i != N; ++i)
	{
		temp = gcd(result.den, records[i].den);
		result.den = result.den*records[i].den/temp;
	}
	result.num = 0;
	
	for (int i = 0; i != N; ++i)
	{
		result.num += (result.den/records[i].den)*records[i].num;
	}
	if (result.num == 0)
	{
		printf("0\n");
		return 0;
	}
	if (result.num < 0)
	{
		printf("-");
		result.num = -result.num;
	}
	temp = gcd(result.num, result.den);
	result.num /= temp;
	result.den /= temp;
	temp = result.num/result.den;
	if (temp >= 1)
	{
		result.num -= temp*result.den;
		printf("%lld", temp);
		flag = true;
	}

	if (result.num != 0)
	{
		if (flag)
		{
			printf(" ");
		}
		printf("%lld/%lld", result.num, result.den);
	}
	printf("\n");
	system("pause");
	return 0;
}