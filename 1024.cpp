#if 1
#include <iostream>
#include <vector>
#include <deque>
#include <string>
using namespace std;

deque<int> number;
deque<int> reverse;
int N, K;

void push_into_deque(long long int target)
{
	while (target != 0)
	{
		number.push_front(target%10);
		target /= 10;
	}
	return ;
}

bool isPalindromic()
{
	for (int i = 0; i != number.size()/2; ++i)
	{
		if (number[i] != number[number.size()-i-1])
		{
			return false;
		}
	}
	return true;
}

void compute_reverse()
{
	reverse.resize(number.size());
	for (int i = 0; i != number.size(); ++i)
	{
		reverse.at(i) = number.at(number.size()-1-i);
	}
	return ;
}

void compute_sum()
{
	int tempsum = 0;
	int carry = 0;
	for (int i = number.size()-1; i != -1; --i)
	{
		tempsum = number[i] + reverse[i] + carry;
		carry = tempsum/10;
		tempsum %= 10;
		number[i] = tempsum;
	}
	if (0 != carry)
	{
		number.push_front(carry);
	}
	return ;
}

void print_number()
{
	for (int i = 0; i != number.size(); ++i)
	{
		cout << number.at(i);
	}
	cout << endl;
}

int main()
{
	string str;
	cin >> str >> K;
	number.resize(str.size());
	for (int i = 0; i != number.size(); ++i)
	{
		number[i] = str[i] - '0';
	}

	/*	
	如果将上面的代码替换为如下, 则不能通过最后两个测试点, 怀疑有类似"0001 3"之类的测试数据
	cin >> N >> K;
	push_into_deque(N);
	*/

	for (int i = 0; i != K+1; ++i)
	{
		if (isPalindromic() || i == K)
		{
			print_number();
			cout << i << endl;
			break;
		}
		compute_reverse();
		compute_sum();
	}

	system("pause");
	return 0;
}




#else

/* long long int 存储结果, 输入 999999999 100,, 计算22次便会溢出, case6、8通不过, 18分*/
#include <iostream>
#include <vector>
using namespace std;

long long int N, reverse;
int K;
vector<int> nvect;

void push_into_vector(long long int target)
{
	while (target != 0)
	{
		nvect.push_back(target%10);
		target /= 10;
	}
}

bool isPalindromic()
{
	for (int i = 0; i != nvect.size()/2; ++i)
	{
		if (nvect[i] != nvect[nvect.size()-i-1])
		{
			return false;
		}
	}
	return true;
}

long long int compute_reverse()
{
	long long int ret = 0;
	for (int i = 0; i != nvect.size(); ++i)
	{
		ret = ret*10 + nvect[i];
	}
	nvect.clear();
	return ret;
}

int main()
{
	cin >> N >> K;

	for (int i = 0; i != K+1; ++i)
	{
		push_into_vector(N);
		if (isPalindromic() || i == K)
		{
			cout << N << endl;
			cout << i << endl;
			break;
		}
		reverse = compute_reverse();
		N += reverse;
	}

	system("pause");
	return 0;
}

#endif






















