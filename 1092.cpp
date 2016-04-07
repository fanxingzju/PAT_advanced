#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

string shop, eva;

int shop_count[62];
int eva_count[62];
int differ = 0;

int hash_bead(char target)
{
	if (target >= '0' && target <= '9')
	{
		return target-'0';
	}
	if (target >= 'a' && target <= 'z')
	{
		return target-'a'+10;
	}
	if (target >= 'A' && target <= 'Z')
	{
		return target-'A'+36;
	}
}

void count_beads(string::const_iterator first, string::const_iterator last, int* array)
{
	for (string::const_iterator iter = first; iter != last; ++iter)
	{
		++array[hash_bead(*iter)];
	}
}

void judge()
{
	for (int i = 0; i != 62; ++i)
	{
		if (eva_count[i] > shop_count[i])
		{
			differ += eva_count[i]-shop_count[i];
		}
	}
}

int main()
{
	cin >> shop >> eva;
	count_beads(shop.begin(), shop.end(), shop_count);
	count_beads(eva.begin(), eva.end(), eva_count);
	judge();
	if (differ != 0)
	{
		cout << "No" << ' ' << differ << endl;
	}
	else
	{
		cout << "Yes" << ' ' << shop.size()-eva.size() << endl;
	}

	system("pause");
	return 0;
}