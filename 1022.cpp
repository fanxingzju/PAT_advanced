#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

int temp[10005];

typedef struct records
{
	unsigned int ID;
	char title[85];
	char author[85];
	int keyWordNum;
	char keyWords[5][11];
	char publisher[85];
	char publishYear[6];
}records;

// 格式转换
int printBufferToKeyword(char *buffer, records *lib)
{
	int keyWordNum = 0;
	int startpos = 0;
	int endpos = -1;
	int index = 0;
	int i;

	do
	{
		++endpos;
		if (' ' == buffer[endpos] || '\0' == buffer[endpos])
		{
			for (i = 0; i != endpos-startpos; ++i)
			{
				lib->keyWords[index][i] = buffer[startpos+i];
			}
			lib->keyWords[index][i] = '\0';
			startpos = endpos+1;
			++index;
			++keyWordNum;
		}	
	}while ('\0' != buffer[endpos]);

	return keyWordNum;
}

// 返回匹配成功的个数
int titleMatch(records *lib, int num, char *title)
{
	int index = 0;
	for (int i = 0; i != num; ++i)
	{
		if (0 == strcmp(title, lib[i].title))
		{
			temp[index++] = lib[i].ID;
		}
	}
	sort(temp, temp+index);
	return index;
}
// 返回匹配成功的个数
int authorMatch(records *lib, int num, char *author)
{
	int index = 0;
	for (int i = 0; i != num; ++i)
	{
		if (0 == strcmp(author, lib[i].author))
		{
			temp[index++] = lib[i].ID;
		}
	}
	sort(temp, temp+index);
	return index;
}
// 返回匹配成功的个数
int keyWordMatch(records *lib, int num, char *keyWord)
{
	int index = 0;
	for (int i = 0; i != num; ++i)
	{
		for (int j = 0; j != lib[i].keyWordNum; ++j)
		{
			if (0 == strcmp(keyWord, lib[i].keyWords[j]))
			{
				temp[index++] = lib[i].ID;
				break;
			}
		}
	}
	sort(temp, temp+index);
	return index;
}
// 返回匹配成功的个数
int publisherMatch(records *lib, int num, char *publisher)
{
	int index = 0;
	for (int i = 0; i != num; ++i)
	{
		if (0 == strcmp(publisher, lib[i].publisher))
		{
			temp[index++] = lib[i].ID;
		}
	}
	sort(temp, temp+index);
	return index;
}
// 返回匹配成功的个数
int publishYearMatch(records *lib, int num, char *publishYear)
{
	int index = 0;
	for (int i = 0; i != num; ++i)
	{
		if (0 == strcmp(publishYear, lib[i].publishYear))
		{
			temp[index++] = lib[i].ID;
		}
	}
	sort(temp, temp+index);
	return index;
}

int main()
{
	unsigned int num, queryNum;
	records *lib;
	int **result;							// 记录每次询问的结果	result[i][0]用来记录第i次询问的答案个数
	char **querys;							// 记录每次询问的问题
	int count;
	char buffer[120];

	cin >> num;
	lib = new records[num];
	for (int i = 0; i != num; ++i)
	{
		cin >> lib[i].ID;
		cin.get();
		cin.getline(lib[i].title, 85);
		cin.getline(lib[i].author, 85);
		cin.getline(buffer, 120);
		lib[i].keyWordNum = printBufferToKeyword(buffer, &lib[i]);
		cin.getline(lib[i].publisher, 85);
		cin.getline(lib[i].publishYear, 6);
	}
	cin >> queryNum;
	result = new int*[queryNum];
	querys = new char*[queryNum];
	cin.get();
	for (int i = 0; i != queryNum; ++i)
	{
		querys[i] = new char[80];
		cin.getline(querys[i], 120);
		switch(querys[i][0])
		{
		case '1':
			count = titleMatch(lib, num, querys[i]+3);
			result[i] = new int[count+1];
			result[i][0] = count;
			memcpy(result[i]+1, temp, count*sizeof(int));
			break;
		case '2':
			count = authorMatch(lib, num, querys[i]+3);
			result[i] = new int[count+1];
			result[i][0] = count;
			memcpy(result[i]+1, temp, count*sizeof(int));
			break;
		case '3':
			count = keyWordMatch(lib, num, querys[i]+3);
			result[i] = new int[count+1];
			result[i][0] = count;
			memcpy(result[i]+1, temp, count*sizeof(int));
			break;
		case '4':
			count = publisherMatch(lib, num, querys[i]+3);
			result[i] = new int[count+1];
			result[i][0] = count;
			memcpy(result[i]+1, temp, count*sizeof(int));
			break;
		case '5':
			count = publishYearMatch(lib, num, querys[i]+3);
			result[i] = new int[count+1];
			result[i][0] = count;
			memcpy(result[i]+1, temp, count*sizeof(int));
			break;
		}
	}
	
	for (int i = 0; i != queryNum; ++i)
	{
		cout << querys[i] << endl;
		if (0 == result[i][0])
		{
			cout << "Not Found" << endl;
		}
		else
		{
			for (int j = 1; j <= result[i][0]; ++j)
			{
				printf("%07d\n", result[i][j]);
			}
		}
	}





	delete[] lib;
	for (int i = 0; i != queryNum; ++i)
	{
		delete[] result[i];
		delete[] querys[i];
	}
	delete[] result;
	delete[] querys;
	system("pause");
	return 0;
}