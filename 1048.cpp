#include <iostream>
#include <algorithm>

using namespace std;

int coins[100005];

int main()
{
	int N, M;
	int v1, v2;
	int sum;
	cin >> N >> M;
	for (int i = 0; i != N; ++i)
	{
		cin >> coins[i];
	}

	sort(coins, coins+N);

	v1 = 0;
	v2 = N-1;
	while (v1 < v2)
	{
		sum = coins[v1] + coins[v2];
		if (sum == M)
		{
			break;
		}
		else
		{
			if (sum < M)
			{
				++v1;
			}
			else
			{
				--v2;
			}
		}
	}

	if (v1 >= v2)
	{
		cout << "No Solution" << endl;
	}
	else
	{
		cout << coins[v1] << ' ' << coins[v2] << endl;
	}
	system("pause");
	return 0;
}