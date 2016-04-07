#include <stdio.h>
#include <stdlib.h>
typedef struct elem
{
	long long int interger;
	long long int numerator;
	long long int denominator;
	bool flag;					// true -> + false-> - 
}elem;

long long int gcd(long long int x, long long int y)
{
	if (x < y)
	{
		return gcd(y, x);
	}

	if (0 == y)
	{
		return x;
	}
	
	if (0 == (x&0x1))
	{
		if (0 == (y&0x1))
		{
			return (gcd(x >> 1, y >> 1) << 1);
		}
		else
		{
			return gcd(x >> 1, y);
		}
	}
	else
	{
		if (0 == (y&0x1))
		{
			return gcd(x, y >> 1);
		}
		else
		{
			return gcd(y, x-y);
		}
	}
}

elem A, B;
elem sum, difference, product, quotient;

void simple(elem &target)
{
	long long int temp;

	target.flag = true;
	if (target.denominator < 0)
	{
		target.denominator = -target.denominator;
		target.numerator = -target.numerator;
	}
	if (target.numerator < 0)
	{
		target.numerator = -target.numerator;
		target.flag = false;
	}

	if (target.numerator >= target.denominator)
	{
		target.interger = target.numerator/target.denominator;
		target.numerator -= target.interger*target.denominator;
	}

	if (0 == target.numerator)
	{
		return ;
	}

	temp = gcd(target.numerator, target.denominator);
	target.numerator /= temp;
	target.denominator /= temp;
	return ;
}

void print_elem(elem target)
{
	if (target.interger == 0 && target.numerator == 0)
	{
		printf("0");
		return ;
	}
	if (!target.flag)
	{
		printf("(-");
	}

	if (target.interger != 0)
	{
		printf("%lld", target.interger);
	}
	
	if (target.interger != 0 && target.numerator != 0)
	{
		printf(" ");
	}

	if (target.numerator != 0)
	{
		printf("%lld/%lld", target.numerator, target.denominator);
	}

	if (!target.flag)
	{
		printf(")");
	}
}

void process_sum_dif()
{
	long long int temp = gcd(A.denominator, B.denominator);

	sum.denominator = A.denominator*B.denominator/temp;
	difference.denominator = sum.denominator;

	sum.numerator = sum.denominator/A.denominator*A.numerator + sum.denominator/B.denominator*B.numerator;
	difference.numerator = sum.denominator/A.denominator*A.numerator - sum.denominator/B.denominator*B.numerator;
	return ;
}

void process_pro_quo()
{
	product.denominator = A.denominator * B.denominator;
	product.numerator = A.numerator * B.numerator;

	quotient.denominator = A.denominator * B.numerator;
	quotient.numerator = A.numerator * B.denominator;
}

int main()
{
	scanf("%lld/%lld", &A.numerator, &A.denominator);
	scanf("%lld/%lld", &B.numerator, &B.denominator);

	process_sum_dif();
	process_pro_quo();

	simple(A);
	simple(B);
	simple(sum);
	simple(difference);
	simple(product);

	print_elem(A);
	printf(" + ");
	print_elem(B);
	printf(" = ");
	print_elem(sum);
	printf("\n");

	print_elem(A);
	printf(" - ");
	print_elem(B);
	printf(" = ");
	print_elem(difference);
	printf("\n");

	print_elem(A);
	printf(" * ");
	print_elem(B);
	printf(" = ");
	print_elem(product);
	printf("\n");

	print_elem(A);
	printf(" / ");
	print_elem(B);
	printf(" = ");
	if (quotient.denominator == 0)
	{
		printf("Inf");
	}
	else
	{
		simple(quotient);
		print_elem(quotient);
	}
	printf("\n");


	system("pause");
	return 0;
}