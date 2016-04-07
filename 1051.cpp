// 用模拟的方法来解决, 测试case运算量都很小, 不会超时
#include <iostream>
using namespace std;

int M, N, K;

int records[1005][1005];

int stack[1005];
int length = 0;

bool push(int target)
{
	stack[length++] = target;
	if (length > M)
	{
		return false;
	}
	return true;
}

int top()
{
	return stack[length-1];
}

bool pop()
{
	--length;
	if (length < 0)
	{
		return false;
	}
	return true;
}

int size()
{
	return length;
}

void clear()
{
	length = 0;
}


bool is_ok(int index)
{
	int number = 1;
	int tmp = 0;
	clear();
	for (int i = 0; i != N; ++i)
	{
		if (tmp < records[index][i])
		{
			while (number <= records[index][i])
			{
				if (!push(number))
				{
					return false;
				}
				++number;
			}
			if (!pop())
			{
				return false;
			}
		}
		else
		{
			if (records[index][i] != top())
			{
				return false;
			}
			if (!pop())
			{
				return false;
			}
		}
		tmp = records[index][i];
	}
	return true;
}

int main()
{
	cin >> M >> N >> K;

	for (int i = 0; i != K; ++i)
	{
		for (int j = 0; j != N; ++j)
		{
			cin >> records[i][j];
		}
	}

	for (int i = 0; i != K; ++i)
	{
		if (is_ok(i))
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}

	system("pause");
	return 0;
}