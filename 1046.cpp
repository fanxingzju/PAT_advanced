#include <iostream>
#include <vector>
using namespace std;

int N;
int M;
vector<int> distances;
int sum = 0;
int limit = 0;

int compute_dis(int src, int dst)
{
	int ret = 0;
	int temp = 0;

	if (src > dst)
	{
		temp = src;
		src = dst;
		dst = temp;
	}

	ret = distances[dst] - distances[src];
	if (ret > limit)
	{
		ret = sum - ret;
	}

	return ret;
}

int main()
{
	int src, dst;
	int temp;
	cin >> N;
	distances.resize(N+1);
	distances[0] = 0;
	for (int i = 1; i != N; ++i)
	{
		cin >> temp;
		sum += temp;
		distances[i] = sum;
	}
	cin >> temp;
	sum += temp;
	distances[N] = sum;

	limit = sum/2;

	cin >> M;
	for (int i = 0; i != M; ++i)
	{
		cin >> src >> dst;
		--src;
		--dst;
		cout << compute_dis(src, dst) << endl;
	}

	return 0;
}