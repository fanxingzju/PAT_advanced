#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 120
char A[MAX_LENGTH];
char B[MAX_LENGTH];
char stdA[MAX_LENGTH];
char stdB[MAX_LENGTH];
int N;

bool is_equal()
{
	// 不用担心越界问题
	int i;
	for (i = 0; stdA[i] != '\0' && stdB[i] != '\0'; ++i)
	{
		if (stdA[i] != stdB[i])
		{
			return false;
		}
	}
	if (stdA[i] != stdB[i])
	{
		return false;
	}
	return true;
}

void transform_std(const char *target, char *stdtar)
{
	int first_nz_pos = -1;
	int dot_pos = -1;
	int i, j;
	int length;
	int k;
	bool flag = false;

	// 对全部输出相同的部分
	stdtar[0] = '0';
	stdtar[1] = '.';

	// 找寻第一个非零的位置和小数点位置
	for (length = 0; target[length] != '\0'; ++length)
	{
		if (-1 == first_nz_pos && '0' != target[length] && '.' != target[length])
		{
			first_nz_pos = length;
		}
		if (-1 == dot_pos && '.' == target[length])
		{
			dot_pos = length;
		}
	}
	// 设定特殊情况下小数点位置
	if (-1 == dot_pos)
	{
		dot_pos = length;
	}
	// 输入为0
	if (-1 == first_nz_pos)
	{
		for (i = 2; i != 2+N; ++i)
		{
			stdtar[i] = '0';
		}
		stdtar[i++] = '*';
		stdtar[i++] = '1';
		stdtar[i++] = '0';
		stdtar[i++] = '^';
		stdtar[i++] = '0';
		return ;
	}

	i = 2;
	for (j = 0; j != N; ++j)
	{
		if (first_nz_pos+j == dot_pos)
		{
			flag = true;
		}
		if (!flag)
		{
			if (first_nz_pos+j < length)
			{
				stdtar[i++] = target[first_nz_pos+j];
			}
			else
			{
				stdtar[i++] = '0';
			}
		}
		else
		{
			if (first_nz_pos+j+1 < length)
			{
				stdtar[i++] = target[first_nz_pos+j+1];
			}
			else
			{
				stdtar[i++] = '0';
			}
		}
	}

	stdtar[i++] = '*';
	stdtar[i++] = '1';
	stdtar[i++] = '0';
	stdtar[i++] = '^';

	// 确定指数k
	if (dot_pos > first_nz_pos)
	{
		k = dot_pos - first_nz_pos;
	}
	else
	{
		k = dot_pos - first_nz_pos + 1;
	}
	
	if (k < 0)
	{
		stdtar[i++] = '-';
		k = -k;
	}

	// k <= 100
	flag = false;
	if (0 != k/100)
	{
		stdtar[i++] = k/100 + '0';
		k = k%100;
		flag = true;
	}

	if (0 != k/10 || flag)
	{
		stdtar[i++] = k/10 + '0';
		k = k%10;
		flag = true;
	}
	stdtar[i++] = k + '0';
	stdtar[i++] = '\0';
	return ;
}


int main()
{
	scanf("%d", &N);
	scanf("%s", A);
	scanf("%s", B);
	transform_std(A, stdA);
	transform_std(B, stdB);
	if (is_equal())
	{
		printf("YES ");
		printf("%s\n", stdA);
	}
	else
	{
		printf("NO ");
		printf("%s %s\n", stdA, stdB);
	}


	system("pause");
	return 0;
}