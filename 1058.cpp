#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct currency
{
	unsigned int G;
	unsigned int S;
	unsigned int K;
}currency;

currency sum_currency(const currency &A, const currency &B)
{
	currency ret;
	int carry = 0;
	memset(&ret, 0, sizeof(currency));
	ret.K = (A.K + B.K) % 29;
	carry = (A.K + B.K) / 29;
	ret.S = (A.S + B.S + carry) % 17;
	carry = (A.S + B.S + carry) / 17;
	ret.G = (A.G + B.G + carry);
	return ret;
}

int main()
{
	currency A, B, C;
	
	scanf("%d.%d.%d", &A.G, &A.S, &A.K);
	scanf("%d.%d.%d", &B.G, &B.S, &B.K);

	C = sum_currency(A, B);
	printf("%d.%d.%d\n", C.G, C.S, C.K);
	system("pause");
	return 0;
}