#include <iostream>

using namespace std;

typedef struct node
{
	char buffer[25];
	bool flag;
}node;

node records[1005];

bool check_record(int index)
{
	bool ret = false;
	int pos = 0;

	while(records[index].buffer[pos] != ' ')
	{
		++pos;
	}
	while(records[index].buffer[pos] != '\0')
	{
		switch(records[index].buffer[pos])
		{
		case '1':
			records[index].buffer[pos] = '@';
			ret = true;
			break;
		case '0':
			records[index].buffer[pos] = '%';
			ret = true;
			break;
		case 'l':
			records[index].buffer[pos] = 'L';
			ret = true;
			break;
		case 'O':
			records[index].buffer[pos] = 'o';
			ret = true;
			break;
		default:
			break;
		}
		++pos;
	}
	return ret;
}

int main()
{
	int N;
	int total = 0;
	cin >> N;
	cin.get();
	for (int i = 0; i != N; ++i)
	{
		cin.getline(records[i].buffer, 25);
		records[i].flag = check_record(i);
		if (records[i].flag)
		{
			++total;
		}

	}
	if (0 == total)
	{
		if (1 == N)
		{
			cout << "There is 1 account and no account is modified" << endl;
		}
		else
		{
			cout << "There are " << N << " accounts and no account is modified"  << endl;
		}
	}
	else
	{
		cout << total << endl;
		for (int i = 0; i != N; ++i)
		{
			if (records[i].flag)
			{
				cout << records[i].buffer << endl;
			}
		}
	}
	
	system("pause");
	return 0;
}