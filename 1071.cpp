#include <iostream>
#include <string>
#include <map>
using namespace std;

#define MAX_LENGTH 1048576+100
char buffer[MAX_LENGTH];
char input[MAX_LENGTH];
map<string, int> records;
int length = 0;

inline bool is_small_alpha(char target)
{
	return ('a' <= target && 'z' >= target);
}

inline bool is_big_alpha(char target)
{
	return ('A' <= target && 'Z' >= target);
}

inline bool is_number(char target)
{
	return ('0' <= target && '9' >= target);
}

inline bool is_alphanum(char target)
{
	return (('a'<=target && 'z'>=target) || ('A'<=target && 'Z'>=target) || ('0'<=target && '9'>=target));
}

void preocess_input()
{
	int index = 0;
	int startpos = 0;
	int endpos = 0;
	string str;
	
	while (input[endpos] != '\0')
	{
		while (input[startpos] == ' ')
		{
			++startpos;
		}
		endpos = startpos+1;
		while (input[endpos] != '\0' && input[endpos] != ' ')
		{
			++endpos;
		}
		for (index = 0; index != endpos - startpos; ++index)
		{
			buffer[index] = input[index+startpos];
		}
		buffer[index] = '\0';
		str = buffer;
		++records[str];
		startpos = endpos;
	}
}
int main()
{
	int maxnum = 0;
	map<string, int>::iterator result;
	cin.getline(input, MAX_LENGTH);
	while (input[length] != '\0')
	{
		if ('A' <= input[length] && 'Z' >= input[length])
		{
			input[length] += 'a' - 'A';
		}
		else
		{
			if (('a'<=input[length] && 'z'>=input[length]) || ('0'<=input[length] && '9'>=input[length]))
			{
				// 条件判断太不好写,故意留空
			}
			else
			{
				input[length] = ' ';
			}
		}
		++length;
	}
	preocess_input();
	for (map<string, int>::iterator iter = records.begin(); iter != records.end(); ++iter)
	{
		if (maxnum < iter->second)
		{
			result = iter;
			maxnum = iter->second;
		}
	}
	cout << result->first << ' ' << result->second << endl;

	system("pause");
	return 0;
}