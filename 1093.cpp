#include <iostream>
using namespace std;

#define MAX_LENGTH 100010
char buffer[MAX_LENGTH];

int pindex[MAX_LENGTH];
int aindex[MAX_LENGTH];
int tindex[MAX_LENGTH];

int plength, alength, tlength;


int main()
{
	int count = 0;
	int ppos = 0, apos = 0, tpos = 0;
	cin.getline(buffer, MAX_LENGTH);
	for (int i = 0; buffer[i] != '\0'; ++i)
	{
		switch(buffer[i])
		{
		case 'P':
			pindex[plength++] = i;
			break;
		case 'A':
			aindex[alength++] = i;
			break;
		case 'T':
			tindex[tlength++] = i;
			break;
		}
	}

	while (pindex[0] > aindex[apos])
	{
		++apos;
	}

	for ( ; apos != alength; ++apos)
	{
		while (ppos != plength && pindex[ppos] < aindex[apos])
		{
			++ppos;
		}
		--ppos;
		while (tpos != tlength && aindex[apos] > tindex[tpos])
		{
			++tpos;
		}
		if (tpos == tlength)
		{
			break;
		}
		count += (ppos+1)*(tlength-tpos);
		count %= 1000000007;
	}


	cout << count << endl;
	system("pause");
	return 0;
}