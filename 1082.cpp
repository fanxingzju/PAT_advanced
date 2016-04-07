#include <iostream>
#include <string>
using namespace std;

string pronounce[10] = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
string scale[3] = {"Shi","Bai", "Qian"};

string sinput;
int ninput;
bool flag = true;

void print_space()
{
	if (flag)
	{
		flag = false;
	}
	else
	{
		cout << ' ';
	}
}

void transform_str_to_n()
{
	for (string::const_iterator iter= sinput.begin(); iter != sinput.end(); ++iter)
	{
		ninput = ninput*10 + *iter - '0';
	}
}


bool process_4_digits(int spos, int epos)
{
	int length = epos - spos;
	bool ret = false;					// true有输出, false没有输出
	
	for (int i = spos; i <= epos; ++i)
	{
		--length;
		if (sinput[i] != '0')
		{
			if (i > 2)
			{
				if (sinput[i-1] == '0')
				{
					print_space();
					cout << "ling";
				}
			}

			print_space();
			cout << pronounce[sinput[i]-'0'];
			if (length >= 0)
			{
				print_space();
				cout << scale[length];
			}
			ret = true;
		}
	}
	return ret;
}



int main()
{
	int spos;
	cin >> sinput;

	if ('-' == sinput.at(0))
	{
		print_space();
		cout << "Fu";
		sinput.erase(sinput.begin());
	}

	transform_str_to_n();

	if (0 == ninput)
	{
		cout << pronounce[0] << endl;
		return 0;
	}

	if (9 == sinput.size())
	{
		print_space();
		cout << pronounce[sinput[0]-'0'];
		print_space();
		cout << "Yi";
	}
	ninput %= 100000000;
	if (0 == ninput)
	{
		cout << endl;
		return 0;
	}
	ninput %= 10000;
	if (sinput.size() > 4)
	{
		spos = sinput.size() > 8 ? (sinput.size()-8) : 0;
		if (process_4_digits(spos, sinput.size()-5))
		{
			print_space();
			cout << "Wan";
		}
	}
	if (0 == ninput)
	{
		return 0;
	}
	
	spos = sinput.size() > 4 ? (sinput.size()-4) : 0;
	process_4_digits(spos, sinput.size()-1);

	cout << endl;
	system("pause");
	return 0;
}