#include <iostream>
#include <algorithm>
using namespace std;

unsigned int records[100010];
int N, p;
int maxlen = 0;
int main()
{
	cin >> N >> p;
	for (int i = 0; i != N; ++i)
	{
		cin >> records[i];
	}
	sort(records, records+N);

	for (int i = 0; i < N-maxlen-1; ++i)
	{
		if (records[i]*p < records[i+maxlen])
		{
			continue;
		}
		else
		{
			while (i+maxlen < N && records[i]*p >= records[i+maxlen])
			{
				++maxlen;
			}
			--maxlen;
		}
	}
	++maxlen;
	cout << maxlen << endl;
	system("pause");
	return 0;
}