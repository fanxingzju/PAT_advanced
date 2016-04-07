#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
using namespace std;

int N;
vector<int> ninput;
int row, col;
vector< vector<int> > matrix;
const int BORDER = 0xffffffff;
const int EMPTY = 0x7fffffff;

void initial_matrix()
{
	int xpos = 1;
	int ypos = 1;
	int steps = 0;
	int operation = 0;

	matrix.resize(row+2);
	for (int i = 0; i != row+2; ++i)
	{
		matrix[i].resize(col+2);
		for (int j = 0; j != col+2; ++j)
		{
			if (0 == i || row+1 == i)
			{
				matrix[i][j] = BORDER;
			}
			else
			{
				matrix[i][j] = EMPTY;
			}
		}
		
		matrix[i][0] = matrix[i][col+1] = BORDER;
	}

	matrix[xpos][ypos] = steps++;
	while (steps != N)
	{
		switch (operation)
		{
		case 0:
			if (EMPTY == matrix[xpos][ypos+1])
			{
				++ypos;
				matrix[xpos][ypos] = steps++;
			}
			else
			{
				++operation;
			}
			break;
		case 1:
			if (EMPTY == matrix[xpos+1][ypos])
			{
				++xpos;
				matrix[xpos][ypos] = steps++;
			}
			else
			{
				++operation;
			}
			break;
		case 2:
			if (EMPTY == matrix[xpos][ypos-1])
			{
				--ypos;
				matrix[xpos][ypos] = steps++;
			}
			else
			{
				++operation;
			}
			break;
		case 3:
			if (EMPTY == matrix[xpos-1][ypos])
			{
				--xpos;
				matrix[xpos][ypos] = steps++;
			}
			else
			{
				operation = 0;
			}
			break;
		default:
			break;
		}
	}
	return ;
}

int main()
{
	cin >> N;

	for (col = static_cast<int>(sqrt(N*1.0)); col >= 1; --col)
	{
		if (0 == N%col)
		{
			row = N/col;
			break;
		}
	}
	ninput.resize(N);
	for (int i = 0; i != N; ++i)
	{
		cin >> ninput[i];
	}
	sort(ninput.begin(), ninput.end(), greater<int>());

	initial_matrix();

	for (int i = 1; i != row+1; ++i)
	{
		for (int j = 1; j != col+1; ++j)
		{
			if (1 != j)
			{
				cout << ' ';
			}
			cout << ninput[matrix[i][j]];
		}
		cout << endl;
	}

	return 0;
}