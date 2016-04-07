#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;


bool str_less_than(const string &A, const string &B)
{
	if (A.size() < B.size() && A == B.substr(0, A.size()))
	{
		return A+B < B+A;
	}
	if (A.size() > B.size() && B == A.substr(0, B.size()))
	{
		return A+B < B+A;
	}
	return A < B;
}

vector<string> records;
int main()
{
	int N;
	string res = "";

	cin >> N;
	records.resize(N);
	for (int i = 0; i != N; ++i)
	{
		cin >> records[i];
	}
	sort(records.begin(), records.end(), str_less_than);

	for (int i = 0; i != records.size(); ++i)
	{
		res += records[i];
	}

	/* res = "" 时, 调用res.at(0)会异常退出*/
	while (0 != res.size() && res.at(0) == '0')
	{
		res.erase(0,1);
	}

	if (res == "")
	{
		cout << 0 << endl;
	}
	else
	{
		cout << res << endl;
	}

	return 0;
}