#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAXKEYS = 37;
const int UNKNOW = -1;
const int COMMON = 0;
const int STUCK = 1;
string instr;
int k;
int status[MAXKEYS];		/*-1 -> 没有出现, 0 -> 普通键位, 1 -> 损坏键位*/
bool visited[MAXKEYS];

vector<char> stuck_keys;
vector<char> original;


bool isequal(char A, char B)
{
	if (A >= 'A' && A <= 'Z')
	{
		A = A - 'A' + 'a';
	}
	if (B >= 'A' && B <= 'Z')
	{
		B = B - 'A' + 'a';
	}
	return A==B;
}

int getIndex(char A)
{
	if (A >= 'A' && A <= 'Z')
	{
		A = A - 'A' + 'a';
	}
	if ('0' <= A && A <= '9')
	{
		return (A-'0');
	}
	if ('a' <= A && A <= 'z')
	{
		return (A-'a'+10);
	}
	return 36;
}

void print_vect(const vector<char> &cvec)
{
	for (int i = 0; i != cvec.size(); ++i)
	{
		cout << cvec[i];
	}
	cout << endl;
}

int main()
{
	int index;
	int ncount;
	cin >> k;
	cin >> instr;
	for (int i = 0; i != MAXKEYS; ++i)
	{
		status[i] = UNKNOW;
		visited[i] = false;
	}

	for (int pos = 0; pos < instr.size(); )
	{
		index = getIndex(instr[pos]);
		ncount = 0;
		if (UNKNOW == status[index] || STUCK == status[index])
		{
			if (pos + 1 < instr.size())
			{
				if (instr[pos] != instr[pos+1])
				{
					status[index] = COMMON;
					++pos;
				}
				else
				{
					ncount = 2;
					while (ncount < k && pos+ncount < instr.size())
					{
						if (instr[pos] != instr[pos+ncount])
						{
							break;
						}
						++ncount;
					}
					if (ncount == k)
					{
						status[index] = STUCK;
					}
					else
					{
						status[index] = COMMON;
					}
					pos += ncount;
				}
			}
			else
			{
				status[index] = COMMON;
				++pos;
			}
		}
		else
		{
			++pos;
		}
	}

	for (int i = 0; i < instr.size(); )
	{
		index = getIndex(instr[i]);
		original.push_back(instr[i]);
		if (status[index] == COMMON)
		{
			++i;
		}
		else
		{
			if (!visited[index])
			{
				stuck_keys.push_back(instr[i]);
				visited[index] = true;
			}
			i += k;
		}
	}

	print_vect(stuck_keys);
	print_vect(original);

	return 0;
}