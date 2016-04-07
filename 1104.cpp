#include <stdio.h>
#include <vector>
using namespace std;

// ������int��Ϊ����ֵ, �������
// ��Ŀ��˵sequence���Ȳ�����10^5,�˴��ķ���ֵ������Ϊ10^5, �������
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
// ������case��ʱ, ����ע���������
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