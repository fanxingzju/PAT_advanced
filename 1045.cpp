#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> stripeA, stripeB;

int lcs_length[205][10005];

int LCS()
{
	int maxlen = 0;
	for (int i = 0; i != stripeA.size(); ++i)
	{
		lcs_length[i][0] = 0;
	}
	for (int i = 0; i != stripeB.size(); ++i)
	{
		lcs_length[0][i] = 0;
	}

	for (int i = 1; i < stripeA.size(); ++i)
	{
		for (int j = 1; j < stripeB.size(); ++j)
		{
			maxlen = lcs_length[i-1][j] > lcs_length[i][j-1] ? lcs_length[i-1][j] : lcs_length[i][j-1];
			//maxlen = maxlen > lcs_length[i-1][j-1] ? maxlen : lcs_length[i-1][j-1];
			if (stripeA[i] == stripeB[j])
			{
				++maxlen;
			}
			lcs_length[i][j] = maxlen;
		}
	}
	return maxlen;
}

int main()
{
	int length;
	cin >> N;
	cin >> length;
	stripeA.resize(length+1);
	for (int i = 1; i != length+1; ++i)
	{
		cin >> stripeA[i];
	}
	cin >> length;
	stripeB.resize(length+1);
	for (int i = 1; i != length+1; ++i)
	{
		cin >> stripeB[i];
	}

	cout << LCS() << endl;

	return 0;
}