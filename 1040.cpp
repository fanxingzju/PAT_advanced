#include <iostream>
using namespace std;

char buffer[1005];
int total;

// 记录对称中心位置
// int result1[1005];
// int result2[1005];

// 形式"ABCBA"
int symmetricJudge_1()
{
	int length;
	int max_length = 0;

	for (int i = 0; i != total; ++i)
	{
		length = 1;
		while (i-length >= 0 && i+length < total && buffer[i-length] == buffer[i+length])
		{
			++length;
		}
		// result1[i] = length-1;
		if (max_length < length-1)
		{
			max_length = length -1;
		}
	}
	return max_length;
}

// 形式"ABCCBA"
int symmetricJudge_2()
{
	int length;
	int max_length = 0;

	for (int i = 0; i != total; ++i)
	{
		length = 0;
		while (i-length >= 0 && i+1+length < total && buffer[i-length] == buffer[i+1+length])
		{
			++length;
		}
		// result2[i] = length;
		if (max_length < length)
		{
			max_length = length;
		}
	}
	return max_length;
}



int main()
{
	int max1, max2, max;
	cin.getline(buffer, 1005);
	while('\0' != buffer[total])
	{
		++total;
	}

	max1 = symmetricJudge_1();
	max2 = symmetricJudge_2();
	max = (2*max1+1 > 2*max2) ? (2*max1+1) : (2*max2);
	
	cout << max << endl;


	system("pause");
	return 0;
}