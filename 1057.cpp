/* ���������ϵĴ𰸣���ȡ����״����+���ֲ��ҡ��ķ���*/
/* 1057. Stack (30)���ֽⷨ�ܽᣨ���ӻ⣩ http://blog.csdn.net/sinat_29278271/article/details/47291659 */

#include <cstdio>
#include <stack>
using namespace std;
const int MAXNUM = 100005;

stack<int> nStack;
int ninput[MAXNUM] = {0};

int lowbit(int key)
{
	return key&(-key);
}

/*	opt = 1,	��key��������
	opt = -1,	��key�Ƴ�����*/
void update(int *narray, int key, int opt)
{
	while (key < MAXNUM)
	{
		narray[key] += opt;
		key += lowbit(key);
	}
}

int getSum(int *narray, int key)
{
	int sum = 0;
	while (key > 0)
	{
		sum += narray[key];
		key -= lowbit(key);
	}
	return sum;
}

int findMid(int *narray, int value)
{
	int low = 0;
	int high = MAXNUM;
	int mid, temp;
	/* �˳�ѭ����Ψһ������low > high (����˵��ʱlow == high+1)*/
	while (low <= high)
	{
		mid = (low+high)/2;
		temp = getSum(narray, mid);
		if (temp >= value)
		{
			high = mid-1;
		} 
		else
		{
			low = mid+1;
		}
	}
	return low;
}

int main()
{
	char buffer[20];
	
	int N, temp;
	scanf("%d", &N);
	for (int i = 0; i != N; ++i)
	{
		scanf("%s", buffer);
		switch (buffer[1])
		{
		case 'u':
			scanf("%d", &temp);
			nStack.push(temp);
			update(ninput, temp, 1);
			break;
		case 'o':
			if (nStack.empty())
			{
				printf("Invalid\n");
			}
			else
			{
				temp = nStack.top();
				printf("%d\n", temp);
				update(ninput, temp, -1);
				nStack.pop();
			}
			break;
		case 'e':
			if (nStack.empty())
			{
				printf("Invalid\n");
			}
			else
			{
				temp = findMid(ninput, (nStack.size()+1)/2);
				printf("%d\n", temp);
			}
			break;
		}
	}
	return 0;
}