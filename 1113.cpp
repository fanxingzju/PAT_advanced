/* ËÍ·ÖÌâ*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N;
int n1, n2;
int S1 = 0, S2 = 0;
vector<int> ninput;
int main()
{
	cin >> N;
	ninput.resize(N);
	for (int i = 0; i != N; ++i)
	{
		cin >> ninput[i];
	}

	sort(ninput.begin(), ninput.end());

	n1 = N/2;
	n2 = N-n1;

	for (int i = 0; i != n1; ++i)
	{
		S1 += ninput[i];
	}
	for (int i = n1; i != N; ++i)
	{
		S2 += ninput[i];
	}

	cout << n2-n1 << ' ' << S2-S1 << endl;
	
	return 0;
}