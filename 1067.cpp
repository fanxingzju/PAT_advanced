#include <stdio.h>
#include <stdlib.h>
#define MAX_NUM 100010
// ��inputOrder��¼����˳��, ����find_index��ʱ
int inputOrder[MAX_NUM];
int input[MAX_NUM];

int N;
int first_not_equal_index = 0;
int zeroIndex = 0;
int swapCount = 0;
void swap(int &zeroIndex,const int targetIndex)
{
	// ����input�е�ֵ
	int targetValue = input[targetIndex];
	input[targetIndex] = 0;
	input[zeroIndex] = targetValue;

	// ����inputOrder
	inputOrder[targetValue] = zeroIndex;
	inputOrder[0] = targetIndex;

	// ����zeroIndex
	zeroIndex = targetIndex;

	++swapCount;
}

int main()
{
	scanf("%d", &N);
	for(int i = 0; i != N; ++i)
	{
		inputOrder[i] = i;
	}
	for (int i = 0; i != N; ++i)
	{
		scanf("%d", input+i);
		inputOrder[input[i]] = i;
	}
	
	zeroIndex = inputOrder[0];

	while (N != first_not_equal_index)
	{
		while (0 != zeroIndex)
		{
			swap(zeroIndex, inputOrder[zeroIndex]);
		}
		while (N != first_not_equal_index)
		{
			if (input[first_not_equal_index] == first_not_equal_index)
			{
				++first_not_equal_index;
			}
			else
			{
				break;
			}
		}
		if (N != first_not_equal_index)
		{
			swap(zeroIndex, first_not_equal_index);
		}
	}
	printf("%d\n", swapCount);
	system("pause");
	return 0;
}



#if 0

/*
============================================================================================
���Ե�	���	��ʱ(ms)	�ڴ�(kB)	�÷�/����
0	����ȷ	1	384	15/15
1	���г�ʱ			0/3
2	���г�ʱ			0/3
3	����ȷ	1	384	2/2
4	����ȷ	1	384	1/1
5	����ȷ	1	408	1/1
============================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX_NUM 100010
int order[MAX_NUM];
int input[MAX_NUM];
int N;
int swapCount = 0;

int find_index(int value)
{
	int index = 0;
	while(index != N)
	{
		if(input[index] == value)
		{
			break;
		}
		else
		{
			++index;
		}
	}
	return index;
}

// ����input[zeroIndex] �� input[targetIndex]��ֵ, ������zeroIndex
void swap(int &zeroIndex, int &targetIndex)
{
	input[zeroIndex] = input[targetIndex];
	input[targetIndex] = 0;
	zeroIndex = targetIndex;
	++swapCount;
}

int main()
{
	int zeroIndex;
	int targetIndex;
	int firstNotEqualIndex = 0;

	scanf("%d", &N);
	for (int i = 0; i != N; ++i)
	{
		scanf("%d", input+i);
		if (input[i] == 0)
		{
			zeroIndex = i;
		}
	}

	while (N != firstNotEqualIndex)
	{
		while (0 != zeroIndex)
		{
			targetIndex = find_index(zeroIndex);
			swap(zeroIndex, targetIndex);	
		}
		while (firstNotEqualIndex != N)
		{
			if (input[firstNotEqualIndex] != firstNotEqualIndex)
			{
				break;
			}
			else
			{
				++firstNotEqualIndex;
			}
		}
		if (N != firstNotEqualIndex)
		{
			swap(zeroIndex, firstNotEqualIndex);
		}
	}
	printf("%d\n", swapCount);
	system("pause");
	return 0;

}

#endif