#include <iostream>
#include <stdio.h>
using namespace std;

#define MAX_LENGTH 10010
char S1[MAX_LENGTH];
char S2[MAX_LENGTH];

int flag[256];

int main()
{
	int pos = 0;
	cin.getline(S1, MAX_LENGTH);
	cin.getline(S2, MAX_LENGTH);

	while (S2[pos] != '\0')
	{
		flag[ S2[pos++] ] = 1;
	}

	pos = 0;

	while (S1[pos] != '\0')
	{
		if (0 == flag[ S1[pos] ])
		{
			printf("%c", S1[pos]);
		}
		++pos;
	}
	cout << endl;
	system("pause");
	return 0;
}