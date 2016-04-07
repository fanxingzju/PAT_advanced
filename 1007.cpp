/* 简单的动态规划, 注意Case:3 -1 0 -2 正确的输出应该为:0 0 0 */
#include <iostream>
using namespace std;

int nums[10010];
int main()
{
	int K;
	int maxsum = -1;
	int first, last = 0, sum = 0;

	cin >> K;
	first = K;

	for (int i = 0; i != K; ++i)
	{
		cin >> nums[i];
	}

	for (int i = 0; i != K; ++i)
	{
		for (int j = i; j < K; ++j)
		{
			if (j == i)
			{
				sum = nums[i];
			}
			else
			{
				sum += nums[j];
			}
			if ((sum > maxsum) || (sum == maxsum && i < first && j < last))
			{
				maxsum = sum;
				first = i;
				last = j;
			}
		}
	}
	if (-1 == maxsum)
	{
		cout << "0 " << nums[0] << ' ' << nums[K-1] << endl;
	}
	else
	{
		cout << maxsum << ' ' << nums[first] << ' ' << nums[last] << endl;
	}

	system("pause");
	return 0;
}

