/* 
1）题目中可能出现的最大数字为(36^10-1),超出int的范围(2^31-1), 但仍在long long int的范围内(2^63-1)
2）最终结果的值可能很大, 需要用long long int表示; 这也意味着不能用顺序查找的方法,只能用二分法寻找结果
3）如输入N1 N2 2 radix, 则最终结果的最小可能取值为N1中最小的一位数加一, 最大的取值可能是（N2, radix）表示的数字加一
4）在二分查找过程中,将（N, radix)转换为十进制的long long int,可能会发生溢出, 必须考虑
5）题目中已经说明输入的都是正整数,所以没有N1==N2==0的情况, 但必须考虑N1==N2, 此时如果N1==N2!=1则结果即为题目中输入的radix, 否则N1==N2==1, 则输出2
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

		/* 在二分查找中, 可能发生溢出, 必须考虑*/
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

	/* 输入的四个数字均为正数, 所以不用考虑0 0 C D的情况,只需考虑A A C D情况（A != 0）*/
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

	/* 进制的取值范围为[minradix, llB+1], 如果只取[minradix, llB]则case1不能通过*/
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