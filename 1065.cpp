// 两种方法均可以通过所有case
#if 1

#include <iostream>
using namespace std;
long long int A[11];
long long int B[11];
long long int C[11];
long long int sum = 0;
int N;
int main()
{
	cin >> N;
	for (int i = 0; i != N; ++i)
	{
		cin >> A[i] >> B[i] >> C[i];
	}
	for (int i = 0; i != N; ++i)
	{

		cout << "Case #" << i+1 << ": ";
		sum = A[i] + B[i];
		if (A[i] > 0 && B[i] > 0 && sum <= 0)
		{
			cout << "true" << endl;
			continue;
		}
		if (A[i] < 0 && B[i] < 0 && sum >= 0)
		{
			cout << "false" << endl;
			continue;
		}
		if (sum > C[i])
		{
			cout << "true" << endl;
		}
		else
		{
			cout << "false" << endl;
		}
	}
	system("pause");
	return 0;
}



#else
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
using namespace std;

string records[35];
int totalNum;
bool results[11];


string sum_AB(const string &A, const string &B)
{
	string ret;
	char sum[30];
	int lengA = A.size();
	int lengB = B.size();
	int i, j;
	int carry = 0;
	int temp = 0;
	int sum_pos = 30;
	memset(sum, 0, 30*sizeof(char));

	for (i = lengA-1, j = lengB-1; i != -1 && j != -1; --i, --j)
	{
		temp = A[i] + B[j] - 2*'0' + carry;
		sum[--sum_pos] = temp%10 + '0';
		carry = temp/10;
	}

	if (-1 == i && -1 == j && 0 != carry)
	{
		sum[--sum_pos] = carry + '0';
	}

	while (j != -1)
	{
		temp = B[j--] - '0' + carry;
		sum[--sum_pos] = temp%10 + '0';
		carry = temp/10;
	}

	while (i != -1)
	{
		temp = A[i--] - '0' + carry;
		sum[--sum_pos] = temp%10 + '0';
		carry = temp/10;
	}
	ret.assign(sum+sum_pos, sum+30);

	return ret;
}

bool A_bigger_than_B(const string &A, const string &B)
{
	if (A.size() != B.size())
	{
		return A.size() > B.size();
	}
	else
	{
		return A > B;
	}
}

/*
============================================================================
A B C	flag	A+B>C(等价于)	
+ + +	000		A+B>C
+ + -	001		true
+ - +	010		A>(-B)+C
+ - -	011		A+(-C)>(-B)
- + +	100		B>(-A)+C
- + -	101		B+(-C)>_A
- - +	110		false
- - -	111		(-C)>(-A)+(-B)
============================================================================
*/

void process_ABC(int index)
{
	unsigned int flag = 0;
	string sum;
	if (records[3*index][0] == '-')
	{
		flag |= 0x00000004;
		records[3*index].erase(0,1);
	}
	if (records[3*index+1][0] == '-')
	{
		flag |= 0x00000002;
		records[3*index+1].erase(0,1);
	}
	if (records[3*index+2][0] == '-')
	{
		flag |= 0x00000001;
		records[3*index+2].erase(0,1);
	}
	switch(flag)
	{
	case 0:
		sum = sum_AB(records[3*index], records[3*index+1]);
		results[index] = A_bigger_than_B(sum, records[3*index+2]);
		break;
	case 1:
		results[index] = true;
		break;
	case 2:
		sum = sum_AB(records[3*index+1], records[3*index+2]);
		results[index] = A_bigger_than_B(records[3*index], sum);
		break;
	case 3:
		sum = sum_AB(records[3*index], records[3*index+2]);
		results[index] = A_bigger_than_B(sum, records[3*index+1]);
		break;
	case 4:
		sum = sum_AB(records[3*index], records[3*index+2]);
		results[index] = A_bigger_than_B(records[3*index+1], sum);
		break;
	case 5:
		sum = sum_AB(records[3*index+1], records[3*index+2]);
		results[index] = A_bigger_than_B(sum, records[3*index]);
		break;
	case 6:
		results[index] = false;
		break;
	case 7:
		sum = sum_AB(records[3*index], records[3*index+1]);
		results[index] = A_bigger_than_B(records[3*index+2], sum);
		break;
	default:
		break;
	}
}


int main()
{
	cin >> totalNum;
	for (int i = 0; i != totalNum; ++i)
	{
		cin >> records[3*i];
		cin >> records[3*i+1];
		cin >> records[3*i+2];
		process_ABC(i);
	}
	for (int i = 0; i != totalNum; ++i)
	{
		cout << "Case #" << i+1 << ": ";
		if (results[i])
		{
			cout << "true" << endl;
		}
		else
		{
			cout << "false" << endl;
		}
	}

	system("pause");
	return 0;
}

#endif
