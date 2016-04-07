#include <iostream>
#include <string.h>
using namespace std;

typedef struct record  
{
	char ID_number[16];
	char Sign_in_time[9];
	char Sign_out_time[9];
}record;

void cin_record(record &temp)
{
	char buf[40];
	int length = 1;

	cin.getline(buf, 40);
	while(' ' != buf[length])
	{
		++length;
	}
	memcpy(temp.ID_number, buf, length);
	temp.ID_number[length] = '\0';
	memcpy(temp.Sign_in_time, buf+length+1, 8);
	temp.Sign_in_time[8] =  '\0';
	memcpy(temp.Sign_out_time, buf+length+10, 8);
	temp.Sign_out_time[8] = '\0';
}

int main()
{
	record temp;
	record first_in;
	record last_out;
	int M;

	cin >> M;
	cin.get();							// 读入紧接M后的回车
	cin_record(temp);
	first_in = temp;
	last_out = temp;
	--M;
	while (M--)
	{
		cin_record(temp);
		if (strcmp(temp.Sign_in_time, first_in.Sign_in_time) < 0)
		{
			first_in = temp;
		}
		if (strcmp(temp.Sign_out_time, last_out.Sign_out_time) > 0)
		{
			last_out = temp;
		}
	}

	cout << first_in.ID_number << ' ' << last_out.ID_number << endl;

	// system("pause");
	return 0;
}