#include <stdio.h>
#include <vector>
using namespace std;

// 不能用int作为返回值, 可能溢出
// 题目中说sequence长度不大于10^5,此处的返回值最大可能为10^5, 正好溢出
double multiNum(int index, int total)
{
	int pre_num = index;
	int beh_num = total - 1 - index;
	return (pre_num+1)*1.0*(beh_num+1);
}


int main()
{
	vector<double>	records;
	double sum = 0;
	double temp;
	int N;

	scanf("%d", &N);
	for (int i = 0; i != N; ++i)
	{
		scanf("%lf", &temp);
		records.push_back(temp);
	}

	for (int i = 0; i != N; ++i)
	{
		sum += records[i]*multiNum(i, N);
	}
	
	printf("%0.02lf\n", sum);

	return 0;
}




#if 0
// 后两个case超时, 必须注意分析问题
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

float records[100010];
int N;
float result = 0;
int main()
{
	float sum = 0;
	float tmpsum = 0;
	cin >> N;
	for (int i = 0; i != N; ++i)
	{
		scanf("%f", records+i);
	}
	for (int i = 0; i != N; ++i)
	{
		sum = 0;
		tmpsum = 0;
		for (int j = i; j != N; ++j)
		{
			tmpsum += records[j];
			sum += tmpsum;
		}
		result += sum;
	}
	printf("%0.02f\n", result);
	system("pause");
	return 0;
}
#endif