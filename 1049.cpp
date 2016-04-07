/*
================================================================================================
编号	区间		1的个数		分析
A		0~9			1
B		0~99		20			= 10 + 10*A
C		0~999		300			= 100 + 10*B
D		0~9999		4000		= 1000 + 10*C
有规律可循的
================================================================================================
*/

// 这个题目最重要的是要防止超时
#if 1
#include <iostream>
using namespace std;

// 2^30 = (2^3)^10 = 8^10 < 10^10
#define MAX_DIGIT_NUM 10

// 用作"标准"
unsigned int standard[MAX_DIGIT_NUM];

// 记录输入的每一位数字
int number[MAX_DIGIT_NUM];

void init_standard()
{
	unsigned int tmp = 1;	
	for (int i = 0; i != MAX_DIGIT_NUM; ++i)
	{
		standard[i] = (i+1)*tmp;
		tmp *= 10;
	}
}

// 返回number数组长度
int transform_to_number(unsigned int target)
{
	int length = 0;
	while (0 != target)
	{
		number[length++] = target%10;
		target /= 10;
	}
	return length;
}

unsigned int count_ones(int index)
{
	unsigned int ret = 0;
	if (0 == number[index])
	{
		ret = 0;
	}
	else
	{
		if (1 == number[index])
		{
			for (int i = index-1; i != -1; --i)
			{
				ret = ret*10 + number[i];
			}
			ret = ret + standard[index-1] + 1;
		}
		else
		{
			ret = 1;
			for (int i = 0; i != index; ++i)
			{
				ret *= 10;
			}
			ret += standard[index-1] * number[index];
		}
	}
	return ret;
}



int main()
{
	unsigned int N;
	unsigned int results = 0;
	int length = 0;						// number数组长度

	cin >> N;

	init_standard();
	length = transform_to_number(N);
	for (int i = 0; i != length; ++i)
	{
		results += count_ones(i);
	}
	
	cout << results << endl;
	system("pause");
	return 0;
}













#else

#include <iostream>
using namespace std;

unsigned int total = 0;

void count_1(int target)
{
	while (target != 0)
	{
		if (target%10 == 1)
		{
			++total;
		}
		target /= 10;
	}
}

int main()
{
	int N;
	cin >> N;

	for (int i = 0; i !=N; ++i)
	{
		count_1(i);
	}

	cout << total << endl;

	system("pause");
	return 0;
}

#endif