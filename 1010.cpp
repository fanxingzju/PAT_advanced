/* 
1����Ŀ�п��ܳ��ֵ��������Ϊ(36^10-1),����int�ķ�Χ(2^31-1), ������long long int�ķ�Χ��(2^63-1)
2�����ս����ֵ���ܴܺ�, ��Ҫ��long long int��ʾ; ��Ҳ��ζ�Ų�����˳����ҵķ���,ֻ���ö��ַ�Ѱ�ҽ��
3��������N1 N2 2 radix, �����ս������С����ȡֵΪN1����С��һλ����һ, ����ȡֵ�����ǣ�N2, radix����ʾ�����ּ�һ
4���ڶ��ֲ��ҹ�����,����N, radix)ת��Ϊʮ���Ƶ�long long int,���ܻᷢ�����, ���뿼��
5����Ŀ���Ѿ�˵������Ķ���������,����û��N1==N2==0�����, �����뿼��N1==N2, ��ʱ���N1==N2!=1������Ϊ��Ŀ�������radix, ����N1==N2==1, �����2
*/
#include <string>
#include <iostream>
using namespace std;

const int MAXLEN = 50;
const int STDRADIX = 36;
string strA, strB;
int tag;
long long radix;
long long minradix = -1;
long long llA, llB;

int c_to_n(char target)
{
	if ('0' <= target && target <= '9')
	{
		return (target-'0');
	}
	return (target-'a'+10);
}

long long str_to_ll(string str, long long radix)
{
	long long ret = 0;
	long long temp = 1;

	if (0 == radix)
	{
		return ret;
	}

	for (int i = str.size()-1; i >= 0; --i)
	{
		ret += c_to_n(str[i])*temp;
		temp *= radix;

		/* �ڶ��ֲ�����, ���ܷ������, ���뿼��*/
		if (ret < 0)
		{
			return -1;
		}
	}
	return ret;
}


long long binary_search(long long low, long long high, long long target)
{
	long long mid;
	long long value;

	while (low <= high)
	{
		mid = (low+high)/2;
		value = str_to_ll(strA, mid);

		if (value <= 0 || value > target)
		{
			high = mid - 1;
		}	
		else
		{
			if (value < target)
			{
				low = mid + 1;
			}
			else
			{
				return mid;
			}
		}
	}
	return -1;
}


int main()
{
	string temp;
	long long res;

	cin >> strA >> strB >> tag >> radix;
	if (1 == tag)
	{
		temp = strA;
		strA = strB;
		strB = temp;
	}

	llB = str_to_ll(strB, radix);

	/* ������ĸ����־�Ϊ����, ���Բ��ÿ���0 0 C D�����,ֻ�迼��A A C D�����A != 0��*/
	if (strA == strB)
	{
		if (1 == llB)
		{
			radix = 2;
		}
		cout << radix << endl;
		return 0;
	}

	for (int i = 0; i != strA.size(); ++i)
	{
		if (minradix < c_to_n(strA[i]))
		{
			minradix = c_to_n(strA[i])+1;
		}
	}

	/* ���Ƶ�ȡֵ��ΧΪ[minradix, llB+1], ���ֻȡ[minradix, llB]��case1����ͨ��*/
	res = binary_search(minradix, llB+1, llB);

	if (-1 != res)
	{
		cout << res << endl;
	}
	else
	{
		cout << "Impossible" << endl;
	}
	return 0;
}