#include <iostream>
#include <string>
using namespace std;
string original, typedout, womoutkey;

void recordx(char x)
{
	for (string::const_iterator iter = womoutkey.begin(); iter != womoutkey.end(); ++iter)
	{
		if (*iter == x)
		{
			return ;
		}
	}
	womoutkey.append(1, x);
	return ;
}

void transform_to_capital(string::iterator first, string::iterator last)
{
	string::iterator iter = first;
	while (iter != last)
	{
		if (*iter >= 'a' && *iter <= 'z')
		{
			*iter += 'A'-'a';
		}
		++iter;
	}
}

int main()
{
	string::iterator oiter, titer;
	cin >> original >> typedout;
	transform_to_capital(original.begin(), original.end());
	transform_to_capital(typedout.begin(), typedout.end());
	oiter = original.begin();
	titer = typedout.begin();
	
	while(titer != typedout.end())
	{
		if (*oiter == *titer)
		{
			++oiter;
			++titer;
		}
		else
		{
			recordx(*oiter);
			++oiter;
		}
	}
	for ( ; oiter != original.end(); ++oiter)
	{
		recordx(*oiter);
	}
	cout << womoutkey << endl;
	system("pause");
	return 0;
}