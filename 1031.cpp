#include <iostream>
#include <stdio.h>
using namespace std;

char buffer[100];
unsigned int length = 0;

void draw_u_shape(int n1, int n2)
{
	for (int i = 0; i != n1 - 1; ++i)
	{
		cout << buffer[i];
		for (int j = 0; j != n2-2; ++j)
		{
			cout << ' ';
		}
		cout << buffer[length-i-1] << endl;
	}
	for (int i = n1-1; i != length-n1+1; ++i)
	{
		cout << buffer[i];
	}
	cout << endl;
}

int main()
{
	int n1, n2;

	cin.getline(buffer, 100);

	while(buffer[length] != '\0')
	{
		++length;
	}

	switch(length%3)
	{
	case 0:
		/* ±ØÐëÂú×ãn1 = n3 <= n2*/
		//n1 = length/3 + 1;
		//n2 = n1 - 1;
		n1 = length/3;
		n2 = n1+2;
		break;
	case 1:
		n1 = (length+2)/3;
		n2 = n1;
		break;
	case 2:
		n1 = (length+1)/3;
		n2 = n1 + 1;
		break;
	}
	draw_u_shape(n1, n2);
	system("pause");
	return 0;
}