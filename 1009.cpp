#include <iostream>
#include <map>
#include <iomanip>
using namespace std;


int main()
{
	map<int, float> poly_fir;
	map<int, float> poly_sec;
	map<int, float> result;

	int n;
	int exp;
	float coe;
	int count = 0;

	cin >> n;
	while(n--)
	{
		cin >> exp >> coe;
		poly_fir.insert(make_pair(exp, coe));
	}
	cin >> n;
	while(n--)
	{
		cin >> exp >> coe;
		poly_sec.insert(make_pair(exp, coe));
	}

	for (map<int, float>::const_iterator it_fir = poly_fir.begin();
		it_fir != poly_fir.end(); ++it_fir)
	{
		for (map<int, float>::const_iterator it_sec = poly_sec.begin();
			it_sec != poly_sec.end(); ++it_sec)
		{
			result[it_fir->first + it_sec->first] += it_fir->second * it_sec->second;
		}
	}

	for (map<int, float>::iterator iter = result.begin(); iter != result.end(); )
	{
		if (0 == iter->second)
		{
			result.erase(iter++);
		}
		else
		{
			++iter;
			++count;
		}
	}
	cout << count;

	for (map<int, float>::reverse_iterator iter = result.rbegin(); iter != result.rend(); ++iter)
	{
		cout << ' ' << iter->first << ' ';
		cout << fixed << setprecision(1) << iter->second;
		
	}
	cout << endl;

	system("pause");
	return 0;
}