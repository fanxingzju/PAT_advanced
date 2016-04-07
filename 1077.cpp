// 只需要判断输入的各个字符串结尾部分相同字符的个数即可
#include <string>
#include <iostream>
using namespace std;

string suffix;
int N;
int suffix_len = 0;
int max_len = 0;
string astr, bstr;

int main()
{
	cin >> N;
	cin.get();
	getline(cin, astr);
	max_len = astr.size();
	for (int i = 0; i != N-1; ++i)
	{
		getline(cin, bstr);
		if (max_len > bstr.size())
		{
			max_len = bstr.size();
		}
		suffix_len = 0;
		while (suffix_len < max_len && bstr[bstr.size()-1-suffix_len] == astr[astr.size()-1-suffix_len])
		{
			++suffix_len;
		}
		max_len = suffix_len;
	}

	if (0 == max_len)
	{
		cout << "nai" << endl;
	}
	else
	{
		for (int i = astr.size()-suffix_len; i != astr.size(); ++i)
		{
			cout << astr[i];
		}
		cout << endl;
	}
	system("pause");
	return 0;
}








