#include <iostream>
#include <string>
using namespace std;

string buffer;
char integer;
string fraction;
char expsign;
unsigned int exponent;
string result;

void translate_buffer()
{
	string::const_iterator iter = buffer.begin()+3;
	string::const_iterator itmp = iter;
	integer = buffer[1];
	while (*iter != 'E')
	{
		++iter;
	}
	fraction.assign(itmp, iter);
	++iter;
	expsign = *iter;
	++iter;
	while (iter != buffer.end())
	{
		exponent = exponent*10 + *iter - '0';
		++iter;
	}
}

void clear_zeros()
{
	string::iterator iter = result.begin();
	while (*iter == '0')
	{
		++iter;
	}
	if (*iter == '.')
	{
		--iter;
	}
	result.erase(result.begin(), iter);
}

int main()
{
	cin >> buffer;
	translate_buffer();

	if ('-' == buffer[0])
	{
		cout << '-';
	}

	// 处理特殊情况
	if (0 == exponent)
	{
		result.append(1, integer);
		result.append(1, '.');
		result.append(fraction.begin(), fraction.end());
		cout << result << endl;
		return 0;
	}

	if (expsign == '+')
	{
		result.insert(result.end(), integer);

		if (fraction.size() <= exponent)
		{
			result.append(fraction.begin(), fraction.end());
			result.append(exponent-fraction.size(), '0');
		}
		else
		{
			result.append(fraction.begin(), fraction.begin()+exponent);
			result.insert(result.end(), '.');
			result.append(fraction.begin()+exponent, fraction.end());
		}
	}
	else
	{
		result.append(1, '0');
		result.append(1, '.');
		result.append(exponent-1, '0');
		result.append(1, integer);
		result.append(fraction.begin(), fraction.end());
	}
	clear_zeros();
	cout << result << endl;
	system("pause");
	return 0;
}