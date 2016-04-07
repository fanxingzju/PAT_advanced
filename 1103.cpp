#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

vector<int> finalfactors;
int nowSum = 0;
int N, K, P;

long long int lpower(long long int n, long long int p)
{
	long long int ret  = n;
	if (n == 1)
	{
		return 1;
	}
	for (int i = 1; i != p; ++i)
	{
		ret *= n;
	}
	return ret;
}

/* 深搜剪枝, 实际上相当于是遍历查找*/
bool dfs(int N, int cur, vector<int> &factors)
{
	int low, high, sum = 0;
	long long int res = 0;
	if (cur == K)
	{
		if (0 == N)
		{
			for (int i = 0; i != factors.size(); ++i)
			{
				sum += factors[i];
			}
			if (sum >= nowSum)				/* 如果没有'=', case2通不过*/
			{
				finalfactors = factors;
				nowSum = sum;
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	low = cur > 0 ? factors[cur-1] : 1;
	high = sqrt(N*1.0) + 1;
	/* 用上面一句是363ms, 如果改成下面一句会超时, 虽然减少了循环次数, 但是pow()的耗时太长*/
	/* high = pow(N*1.0, 1.0/P)+1;*/

	for (int i = low; i < high; ++i)
	{
		res = lpower(i, P);
		if (N >= res)
		{
			factors[cur] = i;
			dfs(N-res, cur+1, factors);
		}
		else
		{
			return false;
		}
	}
	return true;
}

int main()
{
	vector<int> factors;
	cin >> N >> K >> P;
	factors.resize(K);
	
	dfs(N, 0, factors);
	reverse(finalfactors.begin(), finalfactors.end());

	if (!finalfactors.empty())
	{
		cout << N << " = ";
		cout << finalfactors[0] << "^" << P;
		for (int i = 1; i < finalfactors.size(); ++i)
		{
			cout << " + " << finalfactors[i] << "^" << P;
		}
	}
	else
	{
		cout << "Impossible";
	}
	cout << endl;

	system("pause");
	return 0;
}
